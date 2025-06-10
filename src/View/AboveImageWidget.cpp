#include "AboveImageWidget.h"
#include "AboveImageLabelsCreatorVisitor.h"

namespace View
{
    AboveImageWidget::AboveImageWidget(QWidget *parent) : QWidget(parent),
                                                         greyPanel(nullptr),
                                                         layout(nullptr),
                                                         mediaTitleLabel(nullptr),
                                                         mediaIDLabel(nullptr),
                                                         mediaDescriptionLabel(nullptr),
                                                         mediaAuthorLabel(nullptr),
                                                         mediaValue1Label(nullptr),
                                                         mediaValue2Label(nullptr),
                                                         mediaValue3Label(nullptr),
                                                         mediaValue4Label(nullptr),
                                                         modifyButton(nullptr),
                                                         deleteButton(nullptr),
                                                         modifyWindow(nullptr)
    {
        createGreyPanel();
    }

    void AboveImageWidget::createTheRestOfLabelsArticle(const std::string &journalName, const std::string &volumeNumber, const unsigned int &pageCount, const std::string &doi)
    {
        // Esempio di implementazione: aggiorna le label specifiche per Article
        if (!mediaValue1Label) mediaValue1Label = new QLabel(this);
        if (!mediaValue2Label) mediaValue2Label = new QLabel(this);
        if (!mediaValue3Label) mediaValue3Label = new QLabel(this);
        if (!mediaValue4Label) mediaValue4Label = new QLabel(this);
        
        // Set object names and styles
        mediaValue1Label->setObjectName("aboveValue1");
        mediaValue2Label->setObjectName("aboveValue2");
        mediaValue3Label->setObjectName("aboveValue3");
        mediaValue4Label->setObjectName("aboveValue4");
        
        mediaValue1Label->setStyleSheet("QLabel#aboveValue1 { color: #2D3748; }");  // Dark gray
        mediaValue2Label->setStyleSheet("QLabel#aboveValue2 { color: #2D3748; }");
        mediaValue3Label->setStyleSheet("QLabel#aboveValue3 { color: #2D3748; }");
        mediaValue4Label->setStyleSheet("QLabel#aboveValue4 { color: #2D3748; }");
        
        mediaValue1Label->setText("Journal: " + QString::fromStdString(journalName));
        mediaValue2Label->setText("Volume: " + QString::fromStdString(volumeNumber));
        mediaValue3Label->setText("Pages: " + QString::number(pageCount));
        mediaValue4Label->setText("DOI: " + QString::fromStdString(doi));
    }

    void AboveImageWidget::createTheRestOfLabelsAudio(const std::string &format, const std::string &album, const double &duration)
    {
        if (!mediaValue1Label) mediaValue1Label = new QLabel(this);
        if (!mediaValue2Label) mediaValue2Label = new QLabel(this);
        if (!mediaValue3Label) mediaValue3Label = new QLabel(this);
        mediaValue1Label->setText("Format: " + QString::fromStdString(format));
        mediaValue2Label->setText("Album: " + QString::fromStdString(album));
        mediaValue3Label->setText("Duration: " + QString::number(duration) + " min");
    }

    void AboveImageWidget::createTheRestOfLabelsBook(const std::string &publisher, const std::string &genre, const std::string &isbn, const double &pageCount)
    {
        if (!mediaValue1Label) mediaValue1Label = new QLabel(this);
        if (!mediaValue2Label) mediaValue2Label = new QLabel(this);
        if (!mediaValue3Label) mediaValue3Label = new QLabel(this);
        if (!mediaValue4Label) mediaValue4Label = new QLabel(this);
        mediaValue1Label->setText("Publisher: " + QString::fromStdString(publisher));
        mediaValue2Label->setText("Genre: " + QString::fromStdString(genre));
        mediaValue3Label->setText("ISBN: " + QString::fromStdString(isbn));
        mediaValue4Label->setText("Pages: " + QString::number(pageCount));
    }

    void AboveImageWidget::createTheRestOfLabelsFilm(const std::string &productionCompany, const std::string &genre, const double &duration, const double &budget)
    {
        if (!mediaValue1Label) mediaValue1Label = new QLabel(this);
        if (!mediaValue2Label) mediaValue2Label = new QLabel(this);
        if (!mediaValue3Label) mediaValue3Label = new QLabel(this);
        if (!mediaValue4Label) mediaValue4Label = new QLabel(this);
        mediaValue1Label->setText("Production Company: " + QString::fromStdString(productionCompany));
        mediaValue2Label->setText("Genre: " + QString::fromStdString(genre));
        mediaValue3Label->setText("Duration: " + QString::number(duration) + " min");
        mediaValue4Label->setText("Budget: $" + QString::number(budget));
    }

    void AboveImageWidget::createGreyPanel()
    {
        // Remove all dynamically allocated objects from before.
        delete greyPanel;
        delete mediaTitleLabel;
        delete mediaIDLabel;
        delete mediaDescriptionLabel;
        delete mediaAuthorLabel;
        delete mediaValue1Label;
        delete mediaValue2Label;
        delete mediaValue3Label;
        delete mediaValue4Label;
        delete modifyButton;
        delete deleteButton;
        delete modifyWindow;
        delete layout;

        // Set all pointers to nullptr.
        greyPanel = nullptr;
        mediaTitleLabel = nullptr;
        mediaIDLabel = nullptr;
        mediaDescriptionLabel = nullptr;
        mediaAuthorLabel = nullptr;
        mediaValue1Label = nullptr;
        mediaValue2Label = nullptr;
        mediaValue3Label = nullptr;
        mediaValue4Label = nullptr;
        modifyButton = nullptr;
        deleteButton = nullptr;
        modifyWindow = nullptr;
        layout = nullptr;

        // Create the grey panel.
        greyPanel = new QFrame(this);
        greyPanel->setObjectName("emptyPanel");
        greyPanel->setGeometry(0, 0, 714, 85);
        greyPanel->show();
    }

    void AboveImageWidget::createAboveImageForMedia(Media::AbstractMedia *media)
    {
        // Remove dynamically allocated objects from before.
        delete greyPanel;
        delete mediaTitleLabel;
        delete mediaIDLabel;
        delete mediaDescriptionLabel;
        delete mediaAuthorLabel;
        delete mediaValue1Label;
        delete mediaValue2Label;
        delete mediaValue3Label;
        delete mediaValue4Label;
        delete modifyButton;
        delete deleteButton;
        delete modifyWindow;
        delete layout;

        // Set pointers to nullptr.
        greyPanel = nullptr;
        mediaTitleLabel = nullptr;
        mediaIDLabel = nullptr;
        mediaDescriptionLabel = nullptr;
        mediaAuthorLabel = nullptr;
        mediaValue1Label = nullptr;
        mediaValue2Label = nullptr;
        mediaValue3Label = nullptr;
        mediaValue4Label = nullptr;
        modifyButton = nullptr;
        deleteButton = nullptr;
        modifyWindow = nullptr;
        layout = nullptr;

        // Save the current media ID
        id = media->getId();

        // Create visual buttons.
        modifyButton = new QPushButton(QIcon(":/Assets/Icons/edit.png"), tr("Edit"), this);
        deleteButton = new QPushButton(QIcon(":/Assets/Icons/delete.png"), tr("Delete"), this);

        // Assign shortcuts to QPushButtons.
        modifyButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_E));
        deleteButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_D));

        // Create labels for media data.
        mediaTitleLabel = new QLabel(QString::fromStdString(media->getTitle()), this);
        QFont fontLabel = QFont();
        fontLabel.setPointSize(20);

        // Set font, objectName and color for all labels
        mediaTitleLabel->setFont(fontLabel);
        mediaTitleLabel->setObjectName("mediaTitleLabel");
        mediaTitleLabel->setStyleSheet("QLabel { color: #1A365D; }");

        mediaIDLabel = new QLabel(QString("ID: %1").arg(media->getId()), this);
        mediaIDLabel->setFont(fontLabel);
        mediaIDLabel->setObjectName("mediaIDLabel");
        mediaIDLabel->setStyleSheet("QLabel { color: #2D3748; }");

        mediaDescriptionLabel = new QLabel(QString("Description: %1").arg(QString::fromStdString(media->getDescription())), this);
        mediaDescriptionLabel->setFont(fontLabel);
        mediaDescriptionLabel->setObjectName("mediaDescriptionLabel");
        mediaDescriptionLabel->setStyleSheet("QLabel { color: #2D3748; }");
        mediaDescriptionLabel->setWordWrap(true);

        mediaAuthorLabel = new QLabel(QString("Author: %1").arg(QString::fromStdString(media->getAuthor())), this);
        mediaAuthorLabel->setFont(fontLabel);
        mediaAuthorLabel->setObjectName("mediaAuthorLabel");
        mediaAuthorLabel->setStyleSheet("QLabel { color: #2D3748; }");
        mediaDescriptionLabel->setWordWrap(true);

        // Usa il nuovo visitor dedicato per AboveImageWidget
        AboveImageLabelsCreatorVisitor aboveImageLabelsCreatorVisitor(this);
        media->accept(aboveImageLabelsCreatorVisitor);

        // Set styles and font for title label
        QFont fontTitle = mediaTitleLabel->font();
        fontTitle.setPointSize(36);
        mediaTitleLabel->setFont(fontTitle);
        mediaTitleLabel->setObjectName("mediaTitleLabel");
        mediaTitleLabel->setStyleSheet("QLabel#mediaTitleLabel { color: #1A365D; }");

        // Apply styles to value labels
        if (mediaValue1Label) {
            mediaValue1Label->setStyleSheet("QLabel { color: #2D3748; }");
            mediaValue1Label->setFont(fontLabel);
        }
        if (mediaValue2Label) {
            mediaValue2Label->setStyleSheet("QLabel { color: #2D3748; }");
            mediaValue2Label->setFont(fontLabel);
        }
        if (mediaValue3Label) {
            mediaValue3Label->setStyleSheet("QLabel { color: #2D3748; }");
            mediaValue3Label->setFont(fontLabel);
        }
        if (mediaValue4Label) {
            mediaValue4Label->setStyleSheet("QLabel { color: #2D3748; }");
            mediaValue4Label->setFont(fontLabel);
        }

        // Create layouts to organize widgets.
        layout = new QGridLayout(this);

        // Add widgets to the data layout.
        layout->addWidget(mediaTitleLabel, 0, 0);
        layout->addWidget(modifyButton, 0, 1);
        layout->addWidget(deleteButton, 0, 2);
        layout->addWidget(mediaIDLabel, 1, 0);
        layout->addWidget(mediaAuthorLabel, 1, 1);
        layout->addWidget(mediaDescriptionLabel, 1, 2, 3, 2, Qt::AlignTop);
        layout->addWidget(mediaValue1Label, 2, 0);
        layout->addWidget(mediaValue2Label, 3, 0);
        layout->addWidget(mediaValue3Label, 2, 1);
        layout->addWidget(mediaValue4Label, 3, 1);

        // Set the main layout for the widget.
        setLayout(layout);

        // Connect button signals to slots.
        connect(modifyButton, &QPushButton::clicked, this, &AboveImageWidget::modifySlot);
        connect(deleteButton, &QPushButton::clicked, this, &AboveImageWidget::deleteSlot);
    }

    unsigned int AboveImageWidget::getId() const
    {
        return id;
    }

    void AboveImageWidget::modifySlot()
    {
        emit modifySignal();
    }

    void AboveImageWidget::modify(Media::AbstractMedia *media)
    {
        if (dynamic_cast<Media::Article *>(media))
        {
            Media::Article *article = static_cast<Media::Article *>(media);

            std::map<std::string, std::variant<std::string, unsigned int, double>> mediaFields;
            mediaFields["journalName"] = article->getJournalName();
            mediaFields["volumeNumber"] = article->getVolumeNumber();
            mediaFields["pageCount"] = article->getPageCount();
            mediaFields["doi"] = article->getDoi();

            modifyWindow = new ModifyMediaDialogueWindow(article->getId(), "Article", article->getTitle(), 
                                                       article->getDescription(), article->getAuthor(),
                                                       mediaFields, article->getCoverImage());

            connect(modifyWindow, &ModifyMediaDialogueWindow::saveModify, this, 
                   [this, article](const std::string &name, const std::string &description, const std::string &author,
                         const std::map<std::string, std::variant<std::string, unsigned int, double>> &fields,
                         const std::string &coverImage) {
                       // Update media object
                       article->setTitle(name);
                       article->setDescription(description);
                       article->setAuthor(author);
                       article->setPageCount(std::get<unsigned int>(fields.at("pageCount")));
                       article->setJournalName(std::get<std::string>(fields.at("journalName")));
                       article->setVolumeNumber(std::get<std::string>(fields.at("volumeNumber")));
                       article->setDoi(std::get<std::string>(fields.at("doi")));
                       if (!coverImage.empty()) {
                           article->setCoverImage(coverImage);
                       }

                       // Update UI
                       createAboveImageForMedia(article);
                       
                       // Notify of changes
                       emit setIsSaved(false);
                       emit mediaModified(article->getId());
                   });

            modifyWindow->exec();
        }
        else if (dynamic_cast<Media::Audio *>(media))
        {
            Media::Audio *audio = static_cast<Media::Audio *>(media);

            std::map<std::string, std::variant<std::string, unsigned int, double>> mediaFields;
            mediaFields["duration"] = audio->getDuration();
            mediaFields["format"] = audio->getFormat();
            mediaFields["album"] = audio->getAlbum();

            modifyWindow = new ModifyMediaDialogueWindow(audio->getId(), "Audio", audio->getTitle(), 
                                                       audio->getDescription(), audio->getAuthor(),
                                                       mediaFields, audio->getCoverImage());

            connect(modifyWindow, &ModifyMediaDialogueWindow::saveModify, this,
                   [this, audio](const std::string &name, const std::string &description, const std::string &author,
                         const std::map<std::string, std::variant<std::string, unsigned int, double>> &fields,
                         const std::string &coverImage) {
                       // Update media object
                       audio->setTitle(name);
                       audio->setDescription(description);
                       audio->setAuthor(author);
                       audio->setDuration(std::get<unsigned int>(fields.at("duration")));
                       audio->setFormat(std::get<std::string>(fields.at("format")));
                       audio->setAlbum(std::get<std::string>(fields.at("album")));
                       if (!coverImage.empty()) {
                           audio->setCoverImage(coverImage);
                       }

                       // Update UI
                       createAboveImageForMedia(audio);

                       // Notify of changes
                       emit setIsSaved(false);
                       emit mediaModified(audio->getId());
                   });

            modifyWindow->exec();
        }
        else if (dynamic_cast<Media::Book *>(media))
        {
            Media::Book *book = static_cast<Media::Book *>(media);

            std::map<std::string, std::variant<std::string, unsigned int, double>> mediaFields;
            mediaFields["isbn"] = book->getIsbn();
            mediaFields["pageCount"] = book->getPageCount();
            mediaFields["publisher"] = book->getPublisher();
            mediaFields["genre"] = book->getGenre();

            modifyWindow = new ModifyMediaDialogueWindow(book->getId(), "Book", book->getTitle(), 
                                                       book->getDescription(), book->getAuthor(),
                                                       mediaFields, book->getCoverImage());

            connect(modifyWindow, &ModifyMediaDialogueWindow::saveModify, this,
                   [this, book](const std::string &name, const std::string &description, const std::string &author,
                         const std::map<std::string, std::variant<std::string, unsigned int, double>> &fields,
                         const std::string &coverImage) {
                       // Update media object
                       book->setTitle(name);
                       book->setDescription(description);
                       book->setAuthor(author);
                       book->setPageCount(std::get<unsigned int>(fields.at("pageCount")));
                       book->setPublisher(std::get<std::string>(fields.at("publisher")));
                       book->setGenre(std::get<std::string>(fields.at("genre")));
                       book->setIsbn(std::get<std::string>(fields.at("isbn")));
                       if (!coverImage.empty()) {
                           book->setCoverImage(coverImage);
                       }

                       // Update UI
                       createAboveImageForMedia(book);

                       // Notify of changes
                       emit setIsSaved(false);
                       emit mediaModified(book->getId());
                   });

            modifyWindow->exec();
        }
        else if (dynamic_cast<Media::Film *>(media))
        {
            Media::Film *film = static_cast<Media::Film *>(media);

            std::map<std::string, std::variant<std::string, unsigned int, double>> mediaFields;
            mediaFields["duration"] = film->getDuration();
            mediaFields["budget"] = film->getBudget();
            mediaFields["genre"] = film->getGenre();
            mediaFields["productionCompany"] = film->getProductionCompany();

            modifyWindow = new ModifyMediaDialogueWindow(film->getId(), "Film", film->getTitle(), 
                                                       film->getDescription(), film->getAuthor(),
                                                       mediaFields, film->getCoverImage());

            connect(modifyWindow, &ModifyMediaDialogueWindow::saveModify, this,
                   [this, film](const std::string &name, const std::string &description, const std::string &author,
                         const std::map<std::string, std::variant<std::string, unsigned int, double>> &fields,
                         const std::string &coverImage) {
                       // Update media object
                       film->setTitle(name);
                       film->setDescription(description);
                       film->setAuthor(author);
                       film->setDuration(std::get<unsigned int>(fields.at("duration")));
                       film->setBudget(std::get<double>(fields.at("budget")));
                       film->setGenre(std::get<std::string>(fields.at("genre")));
                       film->setProductionCompany(std::get<std::string>(fields.at("productionCompany")));
                       if (!coverImage.empty()) {
                           film->setCoverImage(coverImage);
                       }

                       // Update UI
                       createAboveImageForMedia(film);

                       // Notify of changes
                       emit setIsSaved(false);
                       emit mediaModified(film->getId());
                   });

            modifyWindow->exec();
        }
    }

    // No implementations needed for removed slots and methods

    void AboveImageWidget::nameModifiedSlot(const std::string &previousName, const std::string &newName)
    {
        emit nameHasBeenModified(previousName, newName);
    }

    void AboveImageWidget::deleteSlot()
    {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Delete media", "Are you sure you want to delete this media?",
            QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            emit mediaDeleted();
        }
    }

    void AboveImageWidget::setMediaTitleLabel(const std::string &title)
    {
        mediaTitleLabel->setText(QString::fromStdString(title));
    }

    void AboveImageWidget::setDescriptionLabel(const std::string &description)
    {
        mediaDescriptionLabel->setText("Description: " + QString::fromStdString(description));
    }

    void AboveImageWidget::setMediaAuthorLabel(const std::string &author)
    {
        mediaAuthorLabel->setText("Author: " + QString::fromStdString(author));
    }

    void AboveImageWidget::setMediaValue1Label(const std::string &type, const double &value)
    {
        if (type == "Article" || type == "Book")
            mediaValue1Label->setText("Pages: " + QString::number(value));
        if (type == "Audio" || type == "Film")
            mediaValue1Label->setText("Duration: " + QString::number(value) + " min");
    }

    void AboveImageWidget::setMediaValue2Label(const std::string &type, const double &value)
    {
        if (type == "Film")
            mediaValue2Label->setText("Budget: $" + QString::number(value));
    }

    void AboveImageWidget::setMediaValue3Label(const std::string &type, const std::string &value)
    {
        if (type == "Audio")
            mediaValue3Label->setText("Format: " + QString::fromStdString(value));
        if (type == "Film")
            mediaValue3Label->setText("Genre: " + QString::fromStdString(value));
    }

    void AboveImageWidget::setMediaValue4Label([[maybe_unused]] const std::string &type, [[maybe_unused]] const double &value)
    {
        // Currently not used for any media type
    }

    AboveImageWidget::~AboveImageWidget()
    {
        delete greyPanel;

        delete mediaTitleLabel;
        delete mediaIDLabel;
        delete mediaDescriptionLabel;
        delete mediaAuthorLabel;
        delete mediaValue1Label;
        delete mediaValue2Label;
        delete mediaValue3Label;
        delete mediaValue4Label;

        delete modifyButton;
        delete deleteButton;

        delete modifyWindow;

        delete layout;
    }
}
