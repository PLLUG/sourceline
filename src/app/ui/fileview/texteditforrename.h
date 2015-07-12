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
     * \brief constructor
     * \param parent
     */
    explicit TextEditForRename(QWidget *parent = 0);

    /*!
     * \brief keyPressEvent
     * \param event
     */
    void keyPressEvent(QKeyEvent *event);

    /*!
     * \brief eventFilter
     * \param object
     * \param event
     * \return always false
     */
    bool eventFilter(QObject *object, QEvent *event);

signals:

public slots:
    /*!
     * \brief slotUpdateHeight
     */
    void slotUpdateHeight();
};

#endif // TEXTEDITFORRENAME_H
