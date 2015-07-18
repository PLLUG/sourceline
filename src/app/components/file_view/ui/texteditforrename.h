#ifndef TEXTEDITFORRENAME_H
#define TEXTEDITFORRENAME_H

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>
#include <QEvent>
#include <QObject>

/*!
 * \brief text edit for rename objects (folder and files)
 */
class TextEditForRename : public QTextEdit
{
    Q_OBJECT
public:
    /*!
     * \brief constructor with paramenters
     * \param widget which is parent for text edit
     */
    explicit TextEditForRename(QWidget *parent = 0);

    /*!
     * \brief catch event click Key_Return for finish editing TextEdit
     * \param action after event
     */
    void keyPressEvent(QKeyEvent *event);

    /*!
     * \brief catch events Resize and PolishRequest
     * \param object
     * \param event
     * \return actions after events Resize and PolishRequest
     */
    bool eventFilter(QObject *object, QEvent *event);

signals:

public slots:

    /*!
     * \brief update height
     */
    void slotUpdateHeight();
};

#endif // TEXTEDITFORRENAME_H
