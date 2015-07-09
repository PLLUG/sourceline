#ifndef TEXTEDITFORRENAME_H
#define TEXTEDITFORRENAME_H

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>

class TextEditForRename : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEditForRename(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);

signals:

public slots:
};

#endif // TEXTEDITFORRENAME_H
