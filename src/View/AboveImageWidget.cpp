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
        mediaValue1Label->setText("Journal: " + QString::fromStdString(journalName));
        mediaValue2Label->setText("Volume: " + QString::fromStdString(volumeNumber));
        mediaValue3Label->setText("Pages: " + QString::number(pageCount));
        mediaValue4Label->setText("DOI: " + QString::fromStdString(doi));
    }

    void AboveImageWidget::createTheRestOfLabelsAudio(const std::string &format, const std::string &artist, const std::string &album, const double &duration)
    {
        if (!mediaValue1Label) mediaValue1Label = new QLabel(this);
        if (!mediaValue2Label) mediaValue2Label = new QLabel(this);
        if (!mediaValue3Label) mediaValue3Label = new QLabel(this);
        if (!mediaValue4Label) mediaValue4Label = new QLabel(this);
        mediaValue1Label->setText("Format: " + QString::fromStdString(format));
        mediaValue2Label->setText("Artist: " + QString::fromStdString(artist));
        mediaValue3Label->setText("Album: " + QString::fromStdString(album));
        mediaValue4Label->setText("Duration: " + QString::number(duration) + " min");
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

    void AboveImageWidget::createTheRestOfLabelsFilm(const std::string &director, const std::string &genre, const double &duration, const double &budget)
    {
        if (!mediaValue1Label) mediaValue1Label = new QLabel(this);
        if (!mediaValue2Label) mediaValue2Label = new QLabel(this);
        if (!mediaValue3Label) mediaValue3Label = new QLabel(this);
        if (!mediaValue4Label) mediaValue4Label = new QLabel(this);
        mediaValue1Label->setText("Director: " + QString::fromStdString(director));
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

        mediaIDLabel = new QLabel(QString("ID: %1").arg(media->getId()), this);
        mediaIDLabel->setFont(fontLabel);

        mediaDescriptionLabel = new QLabel(QString("Description: %1").arg(QString::fromStdString(media->getDescription())), this);
        mediaDescriptionLabel->setFont(fontLabel);
        mediaDescriptionLabel->setWordWrap(true);

        mediaAuthorLabel = new QLabel(QString("Author: %1").arg(QString::fromStdString(media->getAuthor())), this);
        mediaAuthorLabel->setFont(fontLabel);
        mediaDescriptionLabel->setWordWrap(true);

        // Usa il nuovo visitor dedicato per AboveImageWidget
        AboveImageLabelsCreatorVisitor aboveImageLabelsCreatorVisitor(this);
        media->accept(aboveImageLabelsCreatorVisitor);

        // Set font size for media title label.
        QFont fontTitle = mediaTitleLabel->font();
        fontTitle.setPointSize(36);
        mediaTitleLabel->setFont(fontTitle);
        mediaTitleLabel->setObjectName("mediaTitleLabel");

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
        if (mediaIDLabel != nullptr)
        {
            bool ok = true;
            QString idText = mediaIDLabel->text();
            QString idSubstring = idText.mid(4);
            unsigned int id = idSubstring.toUInt(&ok);
            if (ok)
            {
                return id;
            }
            else
            {
                qWarning() << "Invalid media ID!";
                throw std::exception();
            }
        }
        else
        {
            qWarning() << "No media selected in AboveImageWidget!";
            throw std::exception();
        }
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

            modifyWindow = new ModifyMediaDialogueWindow(article->getId(), "Article", article->getTitle(), article->getDescription(), article->getAuthor(),
                                                       article->getPageCount(), 0, "", 0);

            connect(modifyWindow, &ModifyMediaDialogueWindow::applySignal, this, &AboveImageWidget::applyChangesSlot);
            connect(this, &AboveImageWidget::finallyYouCanApplyChanges, modifyWindow, &ModifyMediaDialogueWindow::applyChanges);
            connect(modifyWindow, &ModifyMediaDialogueWindow::mediaModified, this, &AboveImageWidget::saveModifySlot);
            connect(modifyWindow, &ModifyMediaDialogueWindow::mediaNameModified, this, &AboveImageWidget::nameModifiedSlot);

            modifyWindow->exec();
        }
        else if (dynamic_cast<Media::Audio *>(media))
        {
            Media::Audio *audio = static_cast<Media::Audio *>(media);

            modifyWindow = new ModifyMediaDialogueWindow(audio->getId(), "Audio", audio->getTitle(), audio->getDescription(), audio->getAuthor(),
                                                       audio->getDuration(), 0, audio->getFormat(), 0);

            connect(modifyWindow, &ModifyMediaDialogueWindow::applySignal, this, &AboveImageWidget::applyChangesSlot);
            connect(this, &AboveImageWidget::finallyYouCanApplyChanges, modifyWindow, &ModifyMediaDialogueWindow::applyChanges);
            connect(modifyWindow, &ModifyMediaDialogueWindow::mediaModified, this, &AboveImageWidget::saveModifySlot);
            connect(modifyWindow, &ModifyMediaDialogueWindow::mediaNameModified, this, &AboveImageWidget::nameModifiedSlot);

            modifyWindow->exec();
        }
        else if (dynamic_cast<Media::Book *>(media))
        {
            Media::Book *book = static_cast<Media::Book *>(media);

            modifyWindow = new ModifyMediaDialogueWindow(book->getId(), "Book", book->getTitle(), book->getDescription(), book->getAuthor(),
                                                       book->getPageCount(), 0, "", 0);

            connect(modifyWindow, &ModifyMediaDialogueWindow::applySignal, this, &AboveImageWidget::applyChangesSlot);
            connect(this, &AboveImageWidget::finallyYouCanApplyChanges, modifyWindow, &ModifyMediaDialogueWindow::applyChanges);
            connect(modifyWindow, &ModifyMediaDialogueWindow::mediaModified, this, &AboveImageWidget::saveModifySlot);
            connect(modifyWindow, &ModifyMediaDialogueWindow::mediaNameModified, this, &AboveImageWidget::nameModifiedSlot);

            modifyWindow->exec();
        }
        else if (dynamic_cast<Media::Film *>(media))
        {
            Media::Film *film = static_cast<Media::Film *>(media);

            modifyWindow = new ModifyMediaDialogueWindow(film->getId(), "Film", film->getTitle(), film->getDescription(), film->getAuthor(),
                                                       film->getDuration(), 0, film->getGenre(), 0);

            connect(modifyWindow, &ModifyMediaDialogueWindow::applySignal, this, &AboveImageWidget::applyChangesSlot);
            connect(this, &AboveImageWidget::finallyYouCanApplyChanges, modifyWindow, &ModifyMediaDialogueWindow::applyChanges);
            connect(modifyWindow, &ModifyMediaDialogueWindow::mediaModified, this, &AboveImageWidget::saveModifySlot);
            connect(modifyWindow, &ModifyMediaDialogueWindow::mediaNameModified, this, &AboveImageWidget::nameModifiedSlot);

            modifyWindow->exec();
        }
    }

    void AboveImageWidget::applyChangesSlot()
    {
        emit applyChangesSignal();
    }

    void AboveImageWidget::youCanCheckIfNameIsUnique(const std::vector<Media::AbstractMedia *> &medias)
    {
        emit finallyYouCanApplyChanges(medias);
    }

    void AboveImageWidget::saveModifySlot(const std::string &name, const std::string &description, const std::string &brand, const double &value1, const double &value2, const std::string &value3, const double &value4)
    {
        emit saveModifySignal(name, description, brand, value1, value2, value3, value4);
    }

    void AboveImageWidget::saveModify(Media::AbstractMedia *media, const std::string &name, const std::string &description, const std::string &brand, const double &value1, const double &value2, const std::string &value3, [[maybe_unused]] const double &value4)
    {
        if (dynamic_cast<Media::Article *>(media))
        {
            Media::Article *article = static_cast<Media::Article *>(media);

            article->setTitle(name);
            article->setDescription(description);
            article->setAuthor(brand);
            article->setPageCount(value1);
        }
        else if (dynamic_cast<Media::Audio *>(media))
        {
            Media::Audio *audio = static_cast<Media::Audio *>(media);

            audio->setTitle(name);
            audio->setDescription(description);
            audio->setAuthor(brand);
            audio->setDuration(value1);
            audio->setFormat(value3);
        }
        else if (dynamic_cast<Media::Book *>(media))
        {
            Media::Book *book = static_cast<Media::Book *>(media);

            book->setTitle(name);
            book->setDescription(description);
            book->setAuthor(brand);
            book->setPageCount(value1);
        }
        else if (dynamic_cast<Media::Film *>(media))
        {
            Media::Film *film = static_cast<Media::Film *>(media);

            film->setTitle(name);
            film->setDescription(description);
            film->setAuthor(brand);
            film->setDuration(value1);
            film->setGenre(value3);
        }

        // Update widget
        setMediaTitleLabel(name);
        setDescriptionLabel(description);
        setMediaAuthorLabel(brand);
        if (dynamic_cast<Media::Article *>(media))
        {
            setMediaValue1Label("Article", value1);
        }
        if (dynamic_cast<Media::Audio *>(media))
        {
            setMediaValue1Label("Audio", value1);
            setMediaValue3Label("Audio", value3);
        }
        if (dynamic_cast<Media::Book *>(media))
        {
            setMediaValue1Label("Book", value1);
        }
        if (dynamic_cast<Media::Film *>(media))
        {
            setMediaValue1Label("Film", value1);
            setMediaValue3Label("Film", value3);
        }

        // Notify main window of changes
        emit setIsSaved(false);
    }

    void AboveImageWidget::nameModifiedSlot(const std::string &previousName, const std::string &newName)
    {
        emit nameHasBeenModified(previousName, newName);
    }

    void AboveImageWidget::deleteSlot()
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Media", "Are you sure you want to delete this media permanently?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
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
            mediaValue2Label->setText("Rating: " + QString::number(value) + "/10");
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
