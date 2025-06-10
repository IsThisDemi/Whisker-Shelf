#ifndef VIEW_ADD_MEDIA_DIALOGUE_WIDGET_H
#define VIEW_ADD_MEDIA_DIALOGUE_WIDGET_H

#include "AbstractDialogueWindow.h"

namespace View
{

    class AddMediaDialogueWindow : public AbstractDialogueWindow
    {
        Q_OBJECT

    private:
        QLabel *typeLabel;
        QLabel *nameLabel;
        QLabel *descriptionLabel;
        QLabel *authorLabel;
        QLabel *productionCompanyLabel;
        QLabel *coverImageLabel;
        QLabel *coverImagePreview;
        QLabel *pagesLabel;
        QLabel *durationLabel;
        QLabel *genreLabel;
        QLabel *formatLabel;
        QLabel *journalLabel;
        QLabel *volumeLabel;
        QLabel *doiLabel;
        QLabel *albumLabel;
        QLabel *isbnLabel;
        QLabel *publisherLabel;
        QLabel *budgetLabel;

        QComboBox *typeComboBox;
        QLineEdit *nameLineEdit;
        QLineEdit *descriptionLineEdit;
        QLineEdit *authorLineEdit;
        QLineEdit *productionCompanyLineEdit;
        QLineEdit *pagesLineEdit;
        QLineEdit *durationLineEdit;
        QLineEdit *genreLineEdit;
        QLineEdit *formatLineEdit;
        QLineEdit *journalLineEdit;
        QLineEdit *volumeLineEdit;
        QLineEdit *doiLineEdit;
        QLineEdit *albumLineEdit;
        QLineEdit *isbnLineEdit;
        QLineEdit *publisherLineEdit;
        QLineEdit *budgetLineEdit;

        QPushButton *discardButton;
        QPushButton *createButton;

        QVBoxLayout *mainLayout;
        QHBoxLayout *typeLayout;
        QHBoxLayout *nameLayout;
        QHBoxLayout *descriptionLayout;
        QHBoxLayout *authorLayout;
        QHBoxLayout *productionCompanyLayout;
        QHBoxLayout *pagesLayout;
        QHBoxLayout *durationLayout;
        QHBoxLayout *genreLayout;
        QHBoxLayout *formatLayout;
        QHBoxLayout *journalLayout;
        QHBoxLayout *volumeLayout;
        QHBoxLayout *doiLayout;
        QHBoxLayout *albumLayout;
        QHBoxLayout *isbnLayout;
        QHBoxLayout *publisherLayout;
        QHBoxLayout *budgetLayout;
        QHBoxLayout *coverImageLayout;
        QHBoxLayout *buttonsLayout;
        
        QPushButton *selectCoverButton;
        QString selectedCoverPath;

    signals:
        void createAndAddSignal();
        void mediaAdded(Media::AbstractMedia *media);

    public slots:
        void createAndAddSlot();
        void discardChanges();
        void onTypeChanged(int index);
        void selectCoverImage();

    public:
        explicit AddMediaDialogueWindow(AbstractDialogueWindow *parent = nullptr);

        bool differentFromOriginal();
        void createAndAddMedia(const std::vector<Media::AbstractMedia *> &medias);

        ~AddMediaDialogueWindow();
    };

}

#endif
