#ifndef TEXTEDITFORRENAME_H
#define TEXTEDITFORRENAME_H

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>
#include <QEvent>
#include <QObject>


class TextEditForRename : public QTextEdit
{
    Q_OBJECT
public:

    explicit TextEditForRename(QWidget *parent = 0);

    void keyPressEvent(QKeyEvent *event);

    bool eventFilter(QObject *object, QEvent *event);

signals:

public slots:

    void slotUpdateHeight();
};

#endif // TEXTEDITFORRENAME_H
