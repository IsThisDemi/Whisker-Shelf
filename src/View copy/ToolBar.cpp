#include "ToolBar.h"

namespace View {
    // Constructor
    // Initializes toolbar with actions and connections
    ToolBar::ToolBar(QToolBar *parent) : QToolBar(parent)
    {
        // Define toolbar actions
        openAction = new QAction(
            QIcon(QPixmap((":/Assets/Icons/open.png"))),
            tr("Open"), this);

        saveAction = new QAction(
            QIcon(QPixmap((":/Assets/Icons/save.png"))),
            tr("Save"), this);

        saveAsAction = new QAction(
            QIcon(QPixmap((":/Assets/Icons/save-as.png"))),
            tr("Save as"), this);

        // Add actions to toolbar
        addAction(openAction);
        addAction(saveAction);
        addAction(saveAsAction);

        // Connect actions to shortcuts
        openAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
        saveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
        saveAsAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));

        // Default state, save/save as actions disabled
        saveAction->setEnabled(false);
        saveAsAction->setEnabled(false);

        // Connect actions to slots
        connect(openAction, &QAction::triggered, this, &ToolBar::openSlot);
        connect(saveAction, &QAction::triggered, this, &ToolBar::saveSlot);
        connect(saveAsAction, &QAction::triggered, this, &ToolBar::saveAsSlot);
    }

    // Slot for open action
    void ToolBar::openSlot() {
        emit openSignal();
    }

    // Slot for save action
    void ToolBar::saveSlot() {
        emit saveSignal();
    }

    // Slot for save as action
    void ToolBar::saveAsSlot() {
        emit saveAsSignal();
    }

    // Enable save action
    void ToolBar::enableSaveAction() {
        saveAction->setEnabled(true);
    }

    // Disable save action
    void ToolBar::disableSaveAction() {
        saveAction->setEnabled(false);
    }

    // Enable save as action
    void ToolBar::enableSaveAsAction() {
        saveAsAction->setEnabled(true);
    }

    // Disable save as action
    void ToolBar::disableSaveAsAction() {
        saveAsAction->setEnabled(false);
    }

    // Opens a JSON file and loads it into a repository.
    // If the file is empty, nothing happens.
    void ToolBar::openJsonFile(Utility::Repository::JsonRepository*& repository)
    {
        QString defaultFolder = QDir::currentPath();
        QFileDialog dialog(this);
        dialog.setDirectory(defaultFolder);
        QString fileName = dialog.getOpenFileName(this, "Open JSON file", defaultFolder, "JSON Files (*.json)");
        
        if (!fileName.isEmpty())
        {
            delete repository;
            repository = new Utility::Repository::JsonRepository(Utility::Repository::JsonRepository::fromPath(fileName.toStdString()));
            repository->load();
            emit fileOpenedSignal();
        }
    }

    // Saves medias to a JSON file. If the repository is null, it prompts the user
    // to choose a file. Otherwise, it overwrites the existing repository.
    void ToolBar::saveJsonFile(const std::vector<Media::AbstractMedia*>& medias, Utility::Repository::JsonRepository*& repo)
    {
        if (repo == nullptr)
        {
            saveAsJsonFile(medias, repo);
        }
        else
        {
            repo->overwrite(medias);
            repo->store();
            emit setIsSavedSignal(true);
        }
    }


     // Saves medias to a JSON file. If the repository is null, it prompts the user
     // to choose a file. Otherwise, it overwrites the existing repository.
    void ToolBar::saveAsJsonFile(const std::vector<Media::AbstractMedia*>& medias, Utility::Repository::JsonRepository*& repo) {
        QString folder = QDir::currentPath();
        QFileDialog dialog(this);
        dialog.setDirectory(folder);

        QString filename = dialog.getSaveFileName(this, "Save JSON file", folder, "JSON Files (*.json)");

        // If a file was selected
        if (!filename.isEmpty()) {
            // Ensure the file has a .json extension
            if (!filename.endsWith(".json", Qt::CaseSensitive)) {
                filename += ".json";
            }

            // If the repository is null, create a new one, otherwise update the path
            if (repo == nullptr) {
                repo = new Utility::Repository::JsonRepository(Utility::Repository::JsonRepository::fromPath(filename.toStdString()));
            } else {
                repo->setPath(filename.toStdString());
            }

            // Overwrite and store the medias
            repo->overwrite(medias);
            repo->store();

            // Update UI
            emit setIsSavedSignal(true);
        }
    }

    // Clean up memory
    ToolBar::~ToolBar() {
        delete openAction;
        delete saveAction;
        delete saveAsAction;
    }
}