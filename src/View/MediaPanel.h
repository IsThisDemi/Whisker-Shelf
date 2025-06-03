#ifndef VIEW_MEDIAPANEL_H
#define VIEW_MEDIAPANEL_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QScrollArea>
#include <QLabel>
#include <algorithm>
#include <QMultiMap>

#include "../Media/Article.h"
#include "../Media/Audio.h"
#include "../Media/Book.h"
#include "../Media/Film.h"
#include "AddMediaDialogueWindow.h"
#include "MediaWidget.h"

namespace View
{

    class MediaPanel : public QWidget
    {
        Q_OBJECT

    private:
        QVBoxLayout *mainLayout;

        QHBoxLayout *searchLayout;
        QLineEdit *searchBar;
        QPushButton *returnBackButton;

        QGridLayout *mediaLayout;
        QScrollArea *scrollArea;
        std::vector<MediaWidget *> mediaWidgets;
        QWidget *mediaWidgetContainer;

        QPushButton *addMediaButton;

        AddMediaDialogueWindow *addWindow;

        MediaWidget *mediaWidget; // Temporary pointer, creates objects to be inserted into the mediaWidgets vector, and then it automatically disassociates the memory on the Heap from it via shallow copy,
                                    // So that memory on the Heap is cleaned up at the time of cleanup of the vector itself.
    protected:
        void mousePressEvent(QMouseEvent *event) override;

    signals:
        void areThereAnyMedias();
        void searchSignal();
        void oneCharacterSearch();
        void searchResults(const std::vector<MediaWidget *> &mediaWidgets);
        void returnBackSignal();
        void mediaSelected(const unsigned int &id);
        void createAndAddMediaSignal();
        void finallyYouCanCreateAndAddMedia(const std::vector<Media::AbstractMedia *> &medias);
        void mediaAdded(Media::AbstractMedia *media);

    public slots:
        void afterTextChangedSlot();
        void search();
        void returnBackFromSearch();
        void addMediaSlot();
        void createAndAddMediaSlot();
        void youCanCheckIfNameAndIDAreUnique(const std::vector<Media::AbstractMedia *> &medias);
        void handleMediaWidgetSelected(MediaWidget *sender);
        void handleMediaAdded(Media::AbstractMedia *media);

    public:
        explicit MediaPanel(const std::vector<Media::AbstractMedia *> &medias, QWidget *parent);
        void createPanel(const std::vector<Media::AbstractMedia *> &medias);
        void updateSearchResults(const std::vector<Media::AbstractMedia *> &medias);
        int findLengthOfLongestCommonSubstring(const QString &str1, const QString &str2);
        std::vector<Media::AbstractMedia *> getMediasForKey(const QMultiMap<int, Media::AbstractMedia *> &mediaMap, int key);

        void setIconOfMediaWidget(const QIcon &icon);

        void afterTextChanged(const bool &thereAreMedias);
        void modifyOneName(const std::string &previousName, const std::string &newName);
        void setColors(Media::AbstractMedia *previousCurrentMedia, Media::AbstractMedia *newCurrentMedia);

        ~MediaPanel();
    };

}

#endif
