#include "texteditforrename.h"

/*!
 * \brief constructor with paramenters
 * \param widget which is parent for text edit
 */
TextEditForRename::TextEditForRename(QWidget *parent) : QTextEdit(parent)
{
    connect(this->document(), SIGNAL(contentsChanged()), this, SLOT(slotUpdateHeight()));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->installEventFilter(parent);
}

/*!
 * \brief catch event click Key_Return for finish editing TextEdit
 * \param action after event
 */
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

/*!
 * \brief catch events Resize and PolishRequest
 * \param object
 * \param event
 * \return actions after events Resize and PolishRequest
 */
bool TextEditForRename::eventFilter(QObject *object, QEvent *event)
{
    Q_UNUSED(object)
    if (event->type() == QEvent::Resize)
    {
        slotUpdateHeight();
    }
    if (event->type() == QEvent::PolishRequest)
    {
        slotUpdateHeight();
        QTextCursor cursor = this->textCursor();
        cursor.setPosition(0);
        cursor.setPosition(this->toPlainText().length(), QTextCursor::KeepAnchor);
        this->setTextCursor(cursor);
        this->setAlignment(Qt::AlignCenter);
    }
    return false;
}

/*!
 * \brief update height
 */
void TextEditForRename::slotUpdateHeight()
{
    //hight+5 for native look in editor
    this->setFixedHeight(this->document()->size().height()+5);
}


