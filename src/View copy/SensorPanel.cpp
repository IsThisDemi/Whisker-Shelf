#include "SensorPanel.h"
#include "SetTypeAndIconOfSensorWidgetVisitor.h"
#include <stdexcept>

namespace View
{

    SensorPanel::SensorPanel(const std::vector<Sensor::AbstractSensor *> &sensors, QWidget *parent)
        : QWidget(parent), mainLayout(nullptr), searchLayout(nullptr), searchBar(nullptr),
          returnBackButton(nullptr), sensorLayout(nullptr), scrollArea(nullptr), sensorWidgetContainer(nullptr),
          addSensorButton(nullptr), addWindow(nullptr), sensorWidget(nullptr)
    {
        createPanel(sensors);
    }

    void SensorPanel::createPanel(const std::vector<Sensor::AbstractSensor *> &sensors)
    {
        // Remove all dynamically allocated objects from before
        delete searchBar;
        delete returnBackButton;
        for (SensorWidget *widget : sensorWidgets)
        {
            delete widget;
        }
        sensorWidgets.clear();
        delete addSensorButton;
        delete addWindow;
        delete sensorLayout;
        delete sensorWidgetContainer;
        delete scrollArea;
        delete searchLayout;
        delete mainLayout;

        // Set pointers a nullptr
        searchBar = nullptr;
        returnBackButton = nullptr; 
        addSensorButton = nullptr;
        addWindow = nullptr;
        sensorLayout = nullptr;
        sensorWidgetContainer = nullptr;
        scrollArea = nullptr;
        searchLayout = nullptr;
        mainLayout = nullptr;

        // Search bar

        searchBar = new QLineEdit(this);
        searchBar->setEnabled(false);
        searchBar->setPlaceholderText("Search");
        searchBar->setFixedHeight(43);

        returnBackButton = new QPushButton(QIcon(":/Assets/Icons/back.png"), "", this);
        returnBackButton->setShortcut(Qt::Key_Escape);
        returnBackButton->setObjectName("backButton");

        returnBackButton->setEnabled(false);

        searchLayout = new QHBoxLayout();
        searchLayout->addWidget(searchBar);
        searchLayout->addWidget(returnBackButton);

        // Il vero e proprio pannello dei sensori

        scrollArea = new QScrollArea(this);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        if (!sensors.empty())
        {
            sensorLayout = new QGridLayout();
            sensorLayout->setSpacing(30);

            int row = 0;
            int column = 0;
            const int maxColumns = 3; // Maximum number of columns before wrapping to the next row

            for (Sensor::AbstractSensor *sensor : sensors)
            {
                sensorWidget = new SensorWidget(this);
                sensorWidget->setName(QString::fromStdString(sensor->getName()));
                sensorWidget->setId(sensor->getId());
                if (typeid(*sensor) == typeid(Sensor::Humidity))
                {
                    sensorWidget->setData(static_cast<Sensor::Humidity *>(sensor)->getHumidity(), " %");
                }
                else if (typeid(*sensor) == typeid(Sensor::Temperature))
                {
                    sensorWidget->setData(static_cast<Sensor::Temperature *>(sensor)->getTemperature(), " °");
                }
                else if (typeid(*sensor) == typeid(Sensor::Light))
                {
                    sensorWidget->setData(static_cast<Sensor::Light *>(sensor)->getIntensity(), " %");
                }
                else if (typeid(*sensor) == typeid(Sensor::Wind))
                {
                    sensorWidget->setData(static_cast<Sensor::Wind *>(sensor)->getDirection(), " °");
                }

                SetTypeAndIconOfSensorWidgetVisitor setTypeAndIconOfSensorWidgetVisitor(this);
                sensor->accept(setTypeAndIconOfSensorWidgetVisitor);

                sensorLayout->addWidget(sensorWidget, row, column); // Add widget to grid layout
                sensorWidgets.push_back(sensorWidget);              // Add widget to list

                // Update row and column
                column++;
                if (column >= maxColumns)
                {
                    column = 0;
                    row++;
                }

                sensorWidget = nullptr;
            }

            sensorWidgetContainer = new QWidget();
            sensorWidgetContainer->setObjectName("sensorWidgetContainer");
            sensorWidgetContainer->setLayout(sensorLayout);
            scrollArea->setWidget(sensorWidgetContainer);
        }

        // Add button

        addSensorButton = new QPushButton(QIcon(":/Assets/Icons/add.png"), "", this);
        addSensorButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_A));

        mainLayout = new QVBoxLayout(this);

        mainLayout->addLayout(searchLayout);
        mainLayout->addWidget(scrollArea);
        mainLayout->addWidget(addSensorButton);

        connect(returnBackButton, &QPushButton::clicked, this, &SensorPanel::returnBackFromSearch);
        connect(addSensorButton, &QPushButton::clicked, this, &SensorPanel::addSensorSlot);

        connect(searchBar, &QLineEdit::textChanged, this, &SensorPanel::afterTextChangedSlot);

        for (SensorWidget *sensorWidget : sensorWidgets)
        {
            connect(sensorWidget, &SensorWidget::selected, this, &SensorPanel::handleSensorWidgetSelected);
        }
    }

    // Update the search results
    void SensorPanel::updateSearchResults(const std::vector<Sensor::AbstractSensor *> &sensors)
    {
        // Clear previous widgets and layout
        for (SensorWidget *widget : sensorWidgets)
        {
            delete widget;
        }
        sensorWidgets.clear();

        delete sensorLayout;
        delete sensorWidgetContainer;
        sensorLayout = nullptr;
        sensorWidgetContainer = nullptr;

        QString searchString = searchBar->text();

        // Map to associate each sensor with the length of the longest common substring
        QMultiMap<int, Sensor::AbstractSensor *> sensorMatchLengthMap;

        // Calculate the length of the longest common substring for each sensor
        for (auto it = sensors.rbegin(); it != sensors.rend(); ++it)
        {
            Sensor::AbstractSensor *sensor = *it;
            int maxLength = 0;
            QString sensorName = QString::fromStdString(sensor->getName());
            QString sensorId = QString::number(sensor->getId());
            QString sensorType;
            if (dynamic_cast<Sensor::Humidity *>(sensor))
                sensorType = "Humidity";
            else if (dynamic_cast<Sensor::Light *>(sensor))
                sensorType = "Light";
            else if (dynamic_cast<Sensor::Temperature *>(sensor))
                sensorType = "Temperature";
            else
                sensorType = "Wind";

            // Calculate the length of the longest common substring between the name, ID, and type of the sensor
            int nameMatchLength = findLengthOfLongestCommonSubstring(searchString, sensorName);
            int idMatchLength = findLengthOfLongestCommonSubstring(searchString, sensorId);
            int typeMatchLength = findLengthOfLongestCommonSubstring(searchString, sensorType);

            int matchLength = qMax(nameMatchLength, qMax(idMatchLength, typeMatchLength));

            if (searchString.length() == 1)
            {
                if (matchLength > maxLength)
                    maxLength = matchLength;
                if (maxLength != 0)
                    sensorMatchLengthMap.insert(maxLength, sensor);
            }
            else
            {
                if (matchLength >= (searchString.length() / 2) && matchLength > maxLength)
                    maxLength = matchLength;
                if (maxLength >= (searchString.length() / 2))
                    sensorMatchLengthMap.insert(maxLength, sensor);
            }
        }

        // Get the keys of the map multiplier
        QList<int> sortedKeys = sensorMatchLengthMap.keys();

        // Remove duplicates from the list
        sortedKeys.erase(std::unique(sortedKeys.begin(), sortedKeys.end()), sortedKeys.end());

        // Sort the keys of the map multiplier in ascending order based on the length of the longest common substring
        std::sort(sortedKeys.begin(), sortedKeys.end());

        sensorLayout = new QGridLayout(); // Use QGridLayout instead of QFlowLayout

        int row = 0;
        int column = 0;
        const int maxColumns = 3; // Maximum number of columns before wrapping to the next row

        // Add sensors to the scroll area layout based on the ordering
        for (int i = sortedKeys.size() - 1; i >= 0; --i)
        {
            // Get the sensors corresponding to the key, which may be more than one because I'm using a QMultiMap
            std::vector<Sensor::AbstractSensor *> sensorsForKey = getSensorsForKey(sensorMatchLengthMap, sortedKeys[i]);

            for (Sensor::AbstractSensor *sensor : sensorsForKey)
            {
                // Create a widget to display the sensor
                sensorWidget = new SensorWidget(this);

                sensorWidget->setName(QString::fromStdString(sensor->getName()));
                sensorWidget->setId(sensor->getId());
                if (typeid(*sensor) == typeid(Sensor::Humidity))
                {
                    sensorWidget->setData(static_cast<Sensor::Humidity *>(sensor)->getHumidity(), " %");
                }
                else if (typeid(*sensor) == typeid(Sensor::Temperature))
                {
                    sensorWidget->setData(static_cast<Sensor::Temperature *>(sensor)->getTemperature(), " °");
                }
                else if (typeid(*sensor) == typeid(Sensor::Light))
                {
                    sensorWidget->setData(static_cast<Sensor::Light *>(sensor)->getIntensity(), " %");
                }
                else if (typeid(*sensor) == typeid(Sensor::Wind))
                {
                    sensorWidget->setData(static_cast<Sensor::Wind *>(sensor)->getDirection(), " °");
                }

                SetTypeAndIconOfSensorWidgetVisitor setTypeAndIconOfSensorWidgetVisitor(this);
                sensor->accept(setTypeAndIconOfSensorWidgetVisitor);

                sensorLayout->addWidget(sensorWidget, row, column); // Add widget to grid layout
                sensorWidgets.push_back(sensorWidget);              // Add to SensorWidgets vector

                // Update row and column
                column++;
                if (column >= maxColumns)
                {
                    column = 0;
                    row++;
                }

                // Now that it made a shallow copy, sensorWidget can "cut its string"
                sensorWidget = nullptr;
            }
        }

        sensorWidgetContainer = new QWidget();
        sensorWidgetContainer->setObjectName("sensorWidgetContainer");
        sensorWidgetContainer->setLayout(sensorLayout);
        scrollArea->setWidget(sensorWidgetContainer);

        // Connect signals and slots for the newly added sensorWidgets
        for (SensorWidget *sensorWidget : sensorWidgets)
        {
            connect(sensorWidget, &SensorWidget::selected, this, &SensorPanel::handleSensorWidgetSelected);
        }

        emit searchResults(sensorWidgets);
    }

    // Finds the length of the longest common substring between two given strings
    // Time complexity: O(m*n)
    // Space complexity: O(m*n)
    int SensorPanel::findLengthOfLongestCommonSubstring(const QString &str1, const QString &str2)
    {
        // Initialize variables
        int m = str1.length();
        int n = str2.length();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        int maxLength = 0;

        // Calculate lengths of longest common substrings
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (str1[i - 1] == str2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    maxLength = std::max(maxLength, dp[i][j]);
                }
            }
        }

        return maxLength;
    }

    // Extract all sensors associated with a specific key from the multi-map
    std::vector<Sensor::AbstractSensor *> SensorPanel::getSensorsForKey(const QMultiMap<int, Sensor::AbstractSensor *> &sensorMap, int key)
    {
        std::vector<Sensor::AbstractSensor *> result;

        // Get an interval of iterators that covers all values associated with the specified key
        auto range = sensorMap.equal_range(key);

        // Iterate through the elements in the interval
        for (auto it = range.first; it != range.second; ++it)
        {
            result.push_back(it.value()); // Add the sensor to the vector
        }

        return result;
    }

    // Set the icon of the sensor widget
    void SensorPanel::setIconOfSensorWidget(const QIcon &icon)
    {
        sensorWidget->setIcon(icon);
    }

    // Handle mouse press event
    void SensorPanel::mousePressEvent(QMouseEvent *event)
    {
        // Enable the search bar if the mouse click is within it
        if (searchBar->rect().contains(event->pos()))
        {
            searchBar->setEnabled(true);
        }
        else
        {
            // Propagate the event to the parent widget
            QWidget::mousePressEvent(event);
        }
    }

    // Slot for afterTextChanged signal
    void SensorPanel::afterTextChangedSlot()
    {
        emit areThereAnySensors();
    }

    // Handle afterTextChanged signal
    void SensorPanel::afterTextChanged(const bool &thereAreSensors)
    {
        QString text = searchBar->text();

        if (thereAreSensors)
        {
            search();
        }
    }

    // Handle the 'Search' button click or Enter key press
    void SensorPanel::search()
    {
        returnBackButton->setEnabled(true);

        QString searchString = searchBar->text();

        emit searchSignal();
    }

    // Handle the 'Return Back' button click
    void SensorPanel::returnBackFromSearch()
    {
        searchBar->clear();
        returnBackButton->setEnabled(false);

        emit returnBackSignal();
    }

    // Handle the selection of a SensorWidget
    void SensorPanel::handleSensorWidgetSelected(SensorWidget *sender)
    {
        if (!sender)
        {
            qWarning() << "SensorWidget pointer is null!";
            return;
        }

        try
        {
            emit sensorSelected(sender->getId());
        }
        catch (const std::exception &e)
        {
            return;
        }
    }

    // Slot for handling the 'Add Sensor' button click
    void SensorPanel::addSensorSlot()
    {
        // Create a new add sensor dialog window
        addWindow = new AddSensorDialogueWindow();

        // Connect signals and slots
        connect(addWindow, &AddSensorDialogueWindow::createAndAddSignal, this, &SensorPanel::createAndAddSensorSlot);
        connect(this, &SensorPanel::finallyYouCanCreateAndAddSensor, addWindow, &AddSensorDialogueWindow::createAndAddSensor);
        connect(addWindow, &AddSensorDialogueWindow::sensorAdded, this, &SensorPanel::handleSensorAdded);

        // Show the dialog
        addWindow->exec();
    }

    // Slot for handling the create and add sensor signal
    void SensorPanel::createAndAddSensorSlot()
    {
        emit createAndAddSensorSignal();
    }

    // Slot for handling the name and ID uniqueness check signal
    void SensorPanel::youCanCheckIfNameAndIDAreUnique(const std::vector<Sensor::AbstractSensor *> &sensors)
    {
        emit finallyYouCanCreateAndAddSensor(sensors);
    }

    // Slot for handling the sensor added signal
    void SensorPanel::handleSensorAdded(Sensor::AbstractSensor *sensor)
    {
        // Refresh the sensor panel to show the new sensor
        emit sensorAdded(sensor);
    }

    // Update the name of a sensor widget
    void SensorPanel::modifyOneName(const std::string &previousName, const std::string &newName)
    {
        // Iterate through all sensor widgets
        for (SensorWidget *sensorWidget : sensorWidgets)
        {
            // If the current sensor widget name matches the previous name, update it with the new name
            if (sensorWidget->getName() == previousName)
            {
                sensorWidget->setName(QString::fromStdString(newName));
                return;
            }
        }
    }

    // Set the colors of the sensor widgets
    void SensorPanel::setColors(Sensor::AbstractSensor *previousSensor, Sensor::AbstractSensor *newSensor)
    {
        try
        {
            if (previousSensor != nullptr)
            { // If this is the first sensor created, no predecessor is selected
                // Search for the previousSensor in the sensorWidgets
                for (SensorWidget *widget : sensorWidgets)
                {
                    if (widget->getId() == previousSensor->getId())
                    {
                        widget->setBackGroundColor(QColor("#FFFFFF")); // Set the widget border color to white
                        break;
                    }
                }
            }

            // Search for the newSensor in the sensorWidgets
            for (SensorWidget *widget : sensorWidgets)
            {
                if (widget->getId() == newSensor->getId())
                {
                    widget->setBackGroundColor(QColor("#3E0040")); // Set the backgroundWidget border color to dark purple
                    break;
                }
            }
        }
        catch (const std::exception &e)
        { // If the ID can't be read, no color is changed
            return;
        }
    }

    // Destructor that deletes all dynamically allocated objects
    SensorPanel::~SensorPanel()
    {
        delete searchBar;
        // delete goButton;
        delete returnBackButton;

        for (SensorWidget *widget : sensorWidgets)
        {
            delete widget;
        }
        sensorWidgets.clear();

        delete addSensorButton;

        delete addWindow;

        delete sensorLayout;
        delete sensorWidgetContainer;
        delete scrollArea;
        delete searchLayout;
        delete mainLayout;
    }

}
