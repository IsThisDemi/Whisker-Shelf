#include "MainWindow.h"

#include <stdexcept>
#include <QFile>

namespace View
{

    // Constructor for MainWindow
    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), repository(nullptr), isSaved(true), centralWidget(nullptr), mainLayout(nullptr), centralLayout(nullptr), toolbarLayout(nullptr),
          rightPanelLayout(nullptr), statusBar(nullptr), mediaPanel(nullptr), aboveImageWidget(nullptr), imageCoverWidget(nullptr), toolBar(nullptr)
    {
        setWindowTitle("WhiskerShelf");

        // Create layouts
        mainLayout = new QVBoxLayout;
        centralLayout = new QHBoxLayout;
        rightPanelLayout = new QVBoxLayout;
        toolbarLayout = new QHBoxLayout;

        // Create widgets
        mediaPanel = new MediaPanel(medias, this);
        mediaPanel->setFixedWidth(500);

        aboveImageWidget = new AboveImageWidget(this);
        aboveImageWidget->setMinimumWidth(714);
        aboveImageWidget->setMinimumHeight(85);
        aboveImageWidget->setObjectName("AboveImageWidget");

        imageCoverWidget = new ImageCoverWidget(this);
        imageCoverWidget->setMinimumWidth(714);
        imageCoverWidget->setMinimumHeight(300);
        imageCoverWidget->setObjectName("ImageCoverWidget");





        toolBar = new ToolBar();
        toolBar->setObjectName("Toolbar");

        // Add toolbar to toolbar layout
        toolbarLayout->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
        toolbarLayout->addWidget(toolBar);

        statusBar = new StatusBar();
        statusBar->setFixedHeight(20);

        // Add widgets to layouts


        // Add widgets to layouts
        rightPanelLayout->addWidget(aboveImageWidget);
        rightPanelLayout->addWidget(imageCoverWidget);
        rightPanelLayout->setAlignment(Qt::AlignTop);

        centralLayout->addWidget(mediaPanel);
        centralLayout->addLayout(rightPanelLayout);

        mainLayout->addLayout(centralLayout);
        mainLayout->addLayout(toolbarLayout);
        mainLayout->addWidget(statusBar);

        // Set main panel
        centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        centralWidget->setLayout(mainLayout);
        this->setMinimumSize(1200, 800);

        // Connect signals
        connect(toolBar, &ToolBar::openSignal, this, &MainWindow::openHandler);
        connect(toolBar, &ToolBar::saveSignal, this, &MainWindow::saveHandler);
        connect(toolBar, &ToolBar::saveAsSignal, this, &MainWindow::saveAsHandler);
        connect(toolBar, &ToolBar::fileOpenedSignal, this, &MainWindow::fileOpenedHandler);
        connect(toolBar, &ToolBar::setIsSavedSignal, this, &MainWindow::setIsSaved);

        connect(mediaPanel, &MediaPanel::areThereAnyMedias, this, &MainWindow::checkIfAreThereAnyMedias);
        connect(mediaPanel, &MediaPanel::searchSignal, this, &MainWindow::searchHandler);
        connect(mediaPanel, &MediaPanel::searchResults, this, &MainWindow::searchResultsHandler);
        connect(mediaPanel, &MediaPanel::returnBackSignal, this, &MainWindow::returnBackHandler);
        connect(mediaPanel, &MediaPanel::mediaSelected, this, &MainWindow::mediaSelectedHandler);
        connect(mediaPanel, &MediaPanel::mediaAdded, this, &MainWindow::mediaAddedHandler);
        connect(mediaPanel, &MediaPanel::createAndAddMediaSignal, this, &MainWindow::createAndAddMediaHandler);
        connect(this, &MainWindow::youCanCheckIfNameAndIDAreUnique, mediaPanel, &MediaPanel::youCanCheckIfNameAndIDAreUnique);

        connect(aboveImageWidget, &AboveImageWidget::setIsSaved, this, &MainWindow::setIsSaved);
        connect(aboveImageWidget, &AboveImageWidget::nameHasBeenModified, this, &MainWindow::nameModifiedHandler);
        connect(aboveImageWidget, &AboveImageWidget::mediaDeleted, this, &MainWindow::mediaDeletedHandler);
        connect(aboveImageWidget, &AboveImageWidget::modifySignal, this, &MainWindow::modifyHandler);
        connect(aboveImageWidget, &AboveImageWidget::mediaModified, this, &MainWindow::mediaModifiedHandler);
        connect(aboveImageWidget, &AboveImageWidget::mediaModified, mediaPanel, &MediaPanel::mediaModifiedHandler);
    }

    // Check if there are any unsaved changes and ask the user if they want to save them
    bool MainWindow::maybeSave()
    {
        // If no medias and no repository, it doesn't make sense to ask to save
        if (medias.empty() && repository == nullptr)
            return true;

        // If there are unsaved changes
        if (!isSaved)
        {
            QMessageBox messageBox(QMessageBox::Warning, "Application", "Save unsaved changes?", 
                                 QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, this);
            
            // Customize buttons style
            QPushButton *saveButton = qobject_cast<QPushButton*>(messageBox.button(QMessageBox::Save));
            QPushButton *discardButton = qobject_cast<QPushButton*>(messageBox.button(QMessageBox::Discard));
            QPushButton *cancelButton = qobject_cast<QPushButton*>(messageBox.button(QMessageBox::Cancel));

            // Set minimum width for buttons and adjust other properties
            if (saveButton) saveButton->setMinimumWidth(100);
            if (discardButton) discardButton->setMinimumWidth(100);
            if (cancelButton) cancelButton->setMinimumWidth(100);
            
            // Set the text for buttons (optional, if you want different text)
            if (saveButton) saveButton->setText("Save");
            if (discardButton) discardButton->setText("Don't Save");
            if (cancelButton) cancelButton->setText("Cancel");

            QMessageBox::StandardButton ret = static_cast<QMessageBox::StandardButton>(messageBox.exec());

            // If the user cancels, return false
            if (ret == QMessageBox::Cancel)
                return false;

            // If the user decides to save
            if (ret == QMessageBox::Save)
                toolBar->saveJsonFile(medias, repository);

            // Clear medias and repository
            medias.clear();
            delete repository;
            repository = nullptr;

            // Recreate the interface
            mediaPanel->createPanel(medias);
            aboveImageWidget->createGreyPanel();
            imageCoverWidget->setImage("");

            // Mark as saved and disable save as action
            setIsSaved(true);
            toolBar->disableSaveAsAction();
        }

        return true;
    }

    // Get the currently selected media
    Media::AbstractMedia *MainWindow::getCurrentlySelectedMedia()
    {
        try
        {
            unsigned int id = aboveImageWidget->getId();

            for (Media::AbstractMedia *media : medias)
            {
                if (media->getId() == id)
                    return media;
            }

            return nullptr;
        }
        catch (const std::exception &e)
        {
            return nullptr;
        }
    }

    // This function is called to replace the medias in the MainWindow with those read from the repository.
    // If there are already medias, they are deleted before adding the new ones.
    // This allows the medias to be updated when a new file is opened.
    void MainWindow::setMedias()
    {
        if (!medias.empty())
        {
            // Delete all medias and clear the vector
            for (Media::AbstractMedia *media : medias)
            {
                delete media;
            }
            medias.clear();
        }

        // Read the medias from the repository and add them to the vector
        std::vector<Media::AbstractMedia *> new_medias(repository->readAll());
        for (Media::AbstractMedia *media : new_medias)
        {
            medias.push_back(media->clone());
        }
    }

    // This function is called when the user attempts to close the window.
    // If there are unsaved changes, the user is asked if they want to save them.
    // If the user cancels the save operation, the window is not closed.
    void MainWindow::closeEvent(QCloseEvent *event)
    {
        // Maybe save the changes and then accept the event to close the window.
        if (maybeSave())
        {
            event->accept();
        }
        else
        {
            // If the user has clicked on "Cancel", do not close the window.
            event->ignore();
        }
    }

    // This function is called when the user attempts to open a new file.
    // If there are unsaved changes, the user is asked if they want to save them.
    // If the user cancels the save operation, the file is not opened.
    void MainWindow::openHandler()
    {
        // Maybe save the changes and then attempt to open the new file.
        if (maybeSave())
        {
            toolBar->openJsonFile(repository);
        }
    }

    // This function is called when the user attempts to save the current file.
    // The medias are saved to the repository and the status bar is updated.
    void MainWindow::saveHandler()
    {
        toolBar->saveJsonFile(medias, repository);
    }

    // This function is called when the user attempts to save the current file with a new name.
    // The medias are saved to a new file and the status bar is updated.
    void MainWindow::saveAsHandler()
    {
        toolBar->saveAsJsonFile(medias, repository);
    }

    // Update medias
    // Create (or recreate) the MediaPanel
    // Select the first media
    // Update the StatusBar
    // Activate "Save with name" button
    void MainWindow::fileOpenedHandler()
    {
        setMedias();
        mediaPanel->createPanel(medias);
        mediaSelectedHandler(medias[0]->getId());
        statusBar->updateBecauseMediaPanelIsNotEmpty();
        toolBar->enableSaveAsAction();
    }

    // Update the "Save" button state
    void MainWindow::setIsSaved(const bool &value)
    {
        isSaved = value;
        if (isSaved)
            toolBar->disableSaveAction();
        else
            toolBar->enableSaveAction();
    }

    // Check if there are any medias
    void MainWindow::checkIfAreThereAnyMedias()
    {
        mediaPanel->afterTextChanged(!medias.empty());
    }

    // Update the search results
    void MainWindow::searchHandler()
    {
        mediaPanel->updateSearchResults(medias);
    }

    // Update the UI after a search
    void MainWindow::searchResultsHandler(const std::vector<MediaWidget *> &mediaWidgets)
    {
        if (mediaWidgets.empty())
        {
            aboveImageWidget->createGreyPanel();
            imageCoverWidget->setImage("");
            statusBar->updateAfterResearch(0);
        }
        else
        {
            mediaPanel->handleMediaWidgetSelected(mediaWidgets[0]);
            statusBar->updateAfterResearch(mediaWidgets.size());
        }
    }

    // Return back to the main UI
    void MainWindow::returnBackHandler()
    {
        mediaPanel->createPanel(medias);
        if (!medias.empty())
            mediaSelectedHandler(medias[0]->getId());
    }

    // If no media is selected, show the selected one
    // If a different media is selected, change the right panels
    // If the same media is selected, only update the color
    void MainWindow::mediaSelectedHandler(const unsigned int &id) 
    {
        Media::AbstractMedia *currentMedia = getCurrentlySelectedMedia();

        for (Media::AbstractMedia *media : medias)
        {
            if (media->getId() == id)
            {
                // Aggiorna i colori
                mediaPanel->setColors(currentMedia, media);
                
                // Aggiorna AboveImageWidget
                aboveImageWidget->createAboveImageForMedia(media);
                
                // Aggiorna ImageCoverWidget
                QString coverImage = QString::fromStdString(media->getCoverImage());
                if (!coverImage.isEmpty()) {
                    imageCoverWidget->setImage(coverImage);
                } else {
                    // Se non c'è un'immagine di copertina, usa l'icona predefinita
                    QString imagePath;
                    if (dynamic_cast<Media::Article *>(media))
                        imagePath = ":/Assets/Icons/Medias/article.png";
                    else if (dynamic_cast<Media::Audio *>(media))
                        imagePath = ":/Assets/Icons/Medias/audio.png";
                    else if (dynamic_cast<Media::Book *>(media))
                        imagePath = ":/Assets/Icons/Medias/book.png";
                    else if (dynamic_cast<Media::Film *>(media))
                        imagePath = ":/Assets/Icons/Medias/movie.png";
                    imageCoverWidget->setImage(imagePath);
                }
                
                // Aggiorna la barra di stato
                statusBar->updateAfterMediaSelected();
                return;
            }
        }
    }

    // Add the new media to the medias queue
    // Refresh the MediaPanel. If it was showing search results, they disappear and it switches back to the panel that shows all medias
    // Select the newly created media
    // Activate the "Save" button
    // If this is the first media added, activate the "Save as" button
    void MainWindow::mediaAddedHandler(Media::AbstractMedia *media)
    {
        medias.push_back(media);
        mediaPanel->createPanel(medias);
        mediaSelectedHandler(media->getId());
        setIsSaved(false);
        if (medias.size() == 1)
            toolBar->enableSaveAsAction();
    }

    // Emits a signal to check if the name and ID are unique
    void MainWindow::createAndAddMediaHandler()
    {
        emit youCanCheckIfNameAndIDAreUnique(medias);
    }

    // Activates the "Modify" button
    void MainWindow::modifyHandler()
    {
        aboveImageWidget->modify(getCurrentlySelectedMedia());
    }

    // Modifies the name of the currently selected media in the MediaPanel
    void MainWindow::nameModifiedHandler(const std::string &previousName, const std::string &newName)
    {
        mediaPanel->modifyOneName(previousName, newName);
    }

    // Handle the deletion of the currently selected media
    void MainWindow::mediaDeletedHandler()
    {
        // Delete the currently selected media
        Media::AbstractMedia *media = getCurrentlySelectedMedia();
        auto it = medias.begin();
        for (; it != medias.end(); ++it)
        {
            if (media->getId() == (*it)->getId())
            {
                delete *it;
                it = medias.erase(it);
                break;
            }
        }

        // Refresh the MediaPanel
        mediaPanel->createPanel(medias); // The check if "medias" is empty is already executed inside the "createPanel" function

        if (!medias.empty())
        {
            // If the deleted media was not the last one, select the next one, otherwise select the previous one
            if (it != medias.end())
                mediaSelectedHandler((*it)->getId());
            else
            {
                it--;
                mediaSelectedHandler((*it)->getId());
            }
        }
        else
        { // If "medias" is empty, recreate the initial screen
            aboveImageWidget->createGreyPanel();
            imageCoverWidget->setImage("");
            statusBar->updateBecauseMediaPanelIsEmpty();

            // Since the user has deleted all the medias, the "Save with name" button is disabled

            // If no repository has been created, the "Save" button is also disabled
            if (repository == nullptr)
            {
                toolBar->disableSaveAction();
                return; // Finish here, otherwise the last line of this method would undo the previous disactivation
            }
        }

        // Enable the "Save" button
        setIsSaved(false);
    }

    // Update the cover image after media modification
    void MainWindow::mediaModifiedHandler(unsigned int id) 
    {
        // Safety check for widget
        if (!imageCoverWidget) return;

        // Find the media safely
        Media::AbstractMedia* targetMedia = nullptr;
        for (Media::AbstractMedia *media : medias) {
            if (media && media->getId() == id) {
                targetMedia = media;
                break;
            }
        }

        if (!targetMedia) return;

        QString coverImage;
        try {
            coverImage = QString::fromStdString(targetMedia->getCoverImage());
        } catch (...) {
            coverImage = "";
        }
        qDebug() << "[mediaModifiedHandler] coverImage path =" << coverImage;

        if (!coverImage.isEmpty()) {
            imageCoverWidget->setImage(coverImage);
        } else {
            // Use default icon based on media type
            QString imagePath = ":/Assets/Icons/media.png";
            if (dynamic_cast<Media::Article *>(targetMedia))
                imagePath = ":/Assets/Icons/Medias/article.png";
            else if (dynamic_cast<Media::Audio *>(targetMedia))
                imagePath = ":/Assets/Icons/Medias/audio.png";
            else if (dynamic_cast<Media::Book *>(targetMedia))
                imagePath = ":/Assets/Icons/Medias/book.png";
            else if (dynamic_cast<Media::Film *>(targetMedia))
                imagePath = ":/Assets/Icons/Medias/movie.png";
            imageCoverWidget->setImage(imagePath);
        }
    }

    // Destructor that cleans up dynamically allocated objects
    MainWindow::~MainWindow()
    {
        // Delete each media object and clear the vector
        for (Media::AbstractMedia *media : medias)
        {
            delete media;
        }
        medias.clear();

        // Delete the widgets and layouts
        delete toolBar;
        delete mediaPanel;
        delete aboveImageWidget;
        delete imageCoverWidget;
        delete statusBar;

        delete centralLayout;
        delete mainLayout;
        delete centralWidget;
    }

}