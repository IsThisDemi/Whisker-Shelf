#ifndef VIEW_MAINWINDOW_H
#define VIEW_MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <vector>

#include "Utility/Repository/JsonRepository.h"
#include "AboveImageWidget.h"
#include "ImageCoverWidget.h"
#include "MediaPanel.h"
#include "StatusBar.h"
#include "ToolBar.h"
namespace View
{

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    private:
        std::vector<Media::AbstractMedia *> medias;
        Utility::Repository::JsonRepository *repository;

        bool isSaved;

        QWidget *centralWidget;
        QVBoxLayout *mainLayout;
        QHBoxLayout *centralLayout;
        QHBoxLayout *toolbarLayout;
        QVBoxLayout *rightPanelLayout;

        StatusBar *statusBar;
        MediaPanel *mediaPanel;
        AboveImageWidget *aboveImageWidget;
        ImageCoverWidget *imageCoverWidget;
        ToolBar *toolBar;

    signals:
        void youCanCheckIfNameAndIDAreUnique(const std::vector<Media::AbstractMedia *> &medias);
        void youCanCheckIfNameIsUnique(const std::vector<Media::AbstractMedia *> &medias);

    public slots:
        void closeEvent(QCloseEvent *event);
        void openHandler();
        void saveHandler();
        void saveAsHandler();
        void fileOpenedHandler();
        void setIsSaved(const bool &value);
        void checkIfAreThereAnyMedias();
        void searchHandler();
        void searchResultsHandler(const std::vector<MediaWidget *> &mediaWidgets);
        void returnBackHandler();
        void mediaSelectedHandler(const unsigned int &id);
        void mediaAddedHandler(Media::AbstractMedia *media);
        void createAndAddMediaHandler();
        void modifyHandler();
        void nameModifiedHandler(const std::string &previousName, const std::string &newName);
        void mediaDeletedHandler();
        void mediaModifiedHandler(unsigned int id);

    public:
        MainWindow(QWidget *parent = nullptr);

        bool maybeSave();
        Media::AbstractMedia *getCurrentlySelectedMedia();
        void setMedias();

        ~MainWindow();
    };
}
#endif // MAINWINDOW_H
