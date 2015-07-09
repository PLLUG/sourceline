#include "texteditforrenameitems.h"
#include <QKeyEvent>

TextEditForRenameItems::TextEditForRenameItems()
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

TextEditForRenameItems::TextEditForRenameItems(QWidget *parent)
{

}

void TextEditForRenameItems::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        this->setText(this->toPlainText());
    }
    else
    {
        QTextEdit::keyPressEvent(event);
    }
}

