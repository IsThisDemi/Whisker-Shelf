#ifndef ABOVE_IMAGE_WIDGET_H
#define ABOVE_IMAGE_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QDialog>

#include "../Media/AbstractMedia.h"
#include "ModifyMediaDialogueWindow.h"

namespace View
{
    class AboveImageWidget : public QWidget
    {
        Q_OBJECT

    private:
        QFrame *greyPanel;
        QGridLayout *layout;

        // Common labels
        QLabel *mediaTitleLabel;
        QLabel *mediaIDLabel;
        QLabel *mediaDescriptionLabel;
        QLabel *mediaAuthorLabel;

        // Label for specific media values
        QLabel *mediaValue1Label;
        QLabel *mediaValue2Label;
        QLabel *mediaValue3Label;
        QLabel *mediaValue4Label;

        QPushButton *modifyButton;
        QPushButton *deleteButton;

        ModifyMediaDialogueWindow *modifyWindow;

    signals:
        void setIsSaved(const bool &value);
        void modifySignal();
        void applyChangesSignal();
        void finallyYouCanApplyChanges(const std::vector<Media::AbstractMedia *> &medias);
        void saveModifySignal(const std::string &name, const std::string &description, const std::string &brand, const double &value1, const double &value2, const std::string &value3, const double &value4);
        void nameHasBeenModified(const std::string &previousName, const std::string &newName);
        void mediaDeleted();

    public slots:
        void modifySlot();
        void applyChangesSlot();
        void youCanCheckIfNameIsUnique(const std::vector<Media::AbstractMedia *> &medias);
        void saveModifySlot(const std::string &name, const std::string &description, const std::string &brand, const double &value1, const double &value2, const std::string &value3, const double &value4);
        void nameModifiedSlot(const std::string &previousName, const std::string &newName);
        void deleteSlot();

    public:
        AboveImageWidget(QWidget *parent = nullptr);
        void createGreyPanel();
        void createAboveImageForMedia(Media::AbstractMedia *media);

        void createTheRestOfLabelsArticle(const std::string &journalName, const std::string &volumeNumber, const unsigned int &pageCount, const std::string &doi);
        void createTheRestOfLabelsAudio(const std::string &format, const std::string &artist, const std::string &album, const double &duration);
        void createTheRestOfLabelsBook(const std::string &publisher, const std::string &genre, const std::string &isbn, const double &pageCount);
        void createTheRestOfLabelsFilm(const std::string &director, const std::string &genre, const double &duration, const double &budget);

        unsigned int getId() const;
        void modify(Media::AbstractMedia *media);
        void saveModify(Media::AbstractMedia *media, const std::string &name, const std::string &description, const std::string &brand, const double &value1, const double &value2, const std::string &value3, const double &value4);

        void setMediaTitleLabel(const std::string &title);
        void setDescriptionLabel(const std::string &description);
        void setMediaAuthorLabel(const std::string &author);
        void setMediaValue1Label(const std::string &type, const double &value);
        void setMediaValue2Label(const std::string &type, const double &value);
        void setMediaValue3Label(const std::string &type, const std::string &value);
        void setMediaValue4Label(const std::string &type, const double &value);

        ~AboveImageWidget();
    };
}

#endif
