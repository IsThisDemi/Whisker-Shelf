#ifndef VIEW_ABSTRACT_DIALOGUE_WINDOW_H
#define VIEW_ABSTRACT_DIALOGUE_WINDOW_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <regex>

#include "../Media/Article.h"
#include "../Media/Audio.h"
#include "../Media/Book.h"
#include "../Media/Film.h"
namespace View
{
    class AbstractDialogueWindow : public QDialog
    {
        Q_OBJECT
    public:
        AbstractDialogueWindow(QDialog *parent = nullptr);
        virtual ~AbstractDialogueWindow();
    };
}
#endif