/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Yura Olenych (yura.olenych@users.sourceforge.net)             ***
***                                                                          ***
***    This file is part of SourceLine Project.                              ***
***                                                                          ***
***    SourceLine is free software: you can redistribute it and/or modify    ***
***    it under the terms of the GNU General Public License as published by  ***
***    the Free Software Foundation, either version 3 of the License, or     ***
***    (at your option) any later version.                                   ***
***                                                                          ***
***    SourceLine is distributed in the hope that it will be useful,         ***
***    but WITHOUT ANY WARRANTY; without even the implied warranty of        ***
***    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         ***
***    GNU General Public License for more details.                          ***
***                                                                          ***
***    You should have received a copy of the GNU General Public License     ***
***    along with this program.  If not, see <http://www.gnu.org/licenses/>. ***
***                                                                          ***
*******************************************************************************/

#ifndef ICONIZEDLINEEDIT_H
#define ICONIZEDLINEEDIT_H

#include <QLineEdit>

class QPushButton;

class IconizedLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit IconizedLineEdit(QWidget *parent = 0);

    enum IconVisibilityMode {
           IconAlwaysVisible =0,
           IconVisibleOnHover,
           IconVisibleOnTextPresence,
           IconVisibleOnEmptyText,
           IconAlwaysHidden
    };
    void setIconVisibility(IconVisibilityMode pIconVisibilityMode);

    bool isIconVisible() const;
    void setIconPixmap(const QPixmap &pPixmap);
    void setIconTooltip(const QString &pToolTip);
    void updateIconPositionAndSize();

signals:
    void signalIconClicked();

public slots:

private:
     QPushButton *mIconLabel;
     IconVisibilityMode mIconVisibilityMode;

private:
    void setIconVisible(bool pIsVisible);

private slots:
    void slotIconClicked();
    void slotTextChanged(const QString &pText);

};

#endif // ICONIZEDLINEEDIT_H
