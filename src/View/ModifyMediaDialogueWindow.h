#ifndef MODIFYMEDIADIALOGUEWINDOW_H
#define MODIFYMEDIADIALOGUEWINDOW_H

#include "AbstractDialogueWindow.h"
#include <map>
#include <variant>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

namespace View
{

    class ModifyMediaDialogueWindow : public AbstractDialogueWindow
    {
        Q_OBJECT

    private:
        unsigned int id;
        std::string type;
        std::string originalMediaName;
        std::string originalMediaDescription;
        std::string originalMediaBrand;
        
        // Common fields across all media types
        std::string originalCoverImage;

        // Article specific fields
        std::string originalJournalName;
        std::string originalVolume;
        unsigned int originalPageCount;
        std::string originalDoi;

        // Audio specific fields 
        unsigned int originalDuration;
        std::string originalFormat;
        std::string originalArtist;
        std::string originalAlbum;

        // Book specific fields
        std::string originalIsbn;
        unsigned int originalBookPageCount;
        std::string originalPublisher;
        std::string originalBookGenre;

        // Film specific fields
        std::string originalDirector;
        unsigned int originalFilmDuration;
        std::string originalFilmGenre;
        double originalBudget;
        double originalRating;

        // UI Labels
        QLabel *nameLabel;
        QLabel *descriptionLabel;
        QLabel *brandLabel;
        QLabel *coverImageLabel;
        QLabel *coverImagePreview;
        
        // Media type specific labels
        QLabel *field1Label;
        QLabel *field2Label;
        QLabel *field3Label;
        QLabel *field4Label;

        // Common input fields
        QLineEdit *nameLineEdit;
        QLineEdit *descriptionLineEdit;
        QLineEdit *brandLineEdit;

        // Media type specific input fields  
        QLineEdit *field1Edit;
        QLineEdit *field2Edit;
        QLineEdit *field3Edit;
        QLineEdit *field4Edit;

        QPushButton *discardButton;
        QPushButton *applyButton;
        QPushButton *selectCoverButton;

        QVBoxLayout *mainLayout;
        QHBoxLayout *nameLayout;
        QHBoxLayout *descriptionLayout;
        QHBoxLayout *brandLayout;
        QHBoxLayout *coverImageLayout;
        QHBoxLayout *value1Layout;
        QHBoxLayout *value2Layout;
        QHBoxLayout *value3Layout;
        QHBoxLayout *value4Layout;

        QString selectedCoverPath;

        void setupUI();
        void setupCommonFields();
        void setupMediaTypeSpecificFields();
        void setupArticleFields();
        void setupAudioFields();
        void setupBookFields();
        void setupFilmFields();
        void setupCoverImageSection();
        void setupButtons();
        void connectSignals();
        bool validateMediaTypeSpecificFields();
        bool differentFromOriginal();

    signals:
        void applySignal();
        void saveModify(const std::string &name, const std::string &description, const std::string &brand,
                       const std::map<std::string, std::variant<std::string, unsigned int, double>> &mediaFields,
                       const std::string &coverImage);

    public slots:
        void afterTextChanged();
        void discardChanges();
        void applySlot();
        void selectCoverImage();

    public:
        explicit ModifyMediaDialogueWindow(const unsigned int &Id, const std::string &Type, 
                                       const std::string &MediaName,
                                       const std::string &MediaDescription, 
                                       const std::string &MediaBrand,
                                       const std::map<std::string, std::variant<std::string, unsigned int, double>> &MediaFields,
                                       const std::string &CoverImage, 
                                       AbstractDialogueWindow *parent = nullptr);

        void applyChanges(const std::vector<Media::AbstractMedia *> medias);
        ~ModifyMediaDialogueWindow();
    };

}

#endif
