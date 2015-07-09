#include "texteditforrename.h"

TextEditForRename::TextEditForRename(QWidget *parent) : QTextEdit(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    connect(this->document(), SIGNAL(contentsChanged()), this, SLOT(slotpdateHeight()));
    slotpdateHeight();
    this->installEventFilter(this);
}

void TextEditForRename::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        this->setEnabled(false);
    }
    else
    {
        QTextEdit::keyPressEvent(event);
    }
}

bool TextEditForRename::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::Resize) {
      slotpdateHeight();
    }
    return false;
}

void TextEditForRename::slotpdateHeight()
{
    this->setFixedHeight(this->document()->size().height() + 5);
}


