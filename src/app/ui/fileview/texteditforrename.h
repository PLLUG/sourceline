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
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *object, QEvent *event);

signals:

public slots:
    void slotUpdateHeight();
};

#endif // TEXTEDITFORRENAME_H
