#include "AbstractDialogueWindow.h"

namespace View
{
    AbstractDialogueWindow::AbstractDialogueWindow(QDialog *parent) : QDialog(parent) {}

    AbstractDialogueWindow::~AbstractDialogueWindow() = default;
}