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

#include "iconizedlineedit.h"

#include <QPushButton>
#include <QStyle>
#include <QSize>

#include <QDebug>

IconizedLineEdit::IconizedLineEdit(QWidget *parent) :
    QLineEdit(parent),
    mIconVisibilityMode(IconAlwaysVisible)
{
     mIconLabel = new QPushButton(this);

     connect(this, SIGNAL(textChanged(QString)),
             this, SLOT(slotTextChanged(QString)), Qt::UniqueConnection);
     connect(mIconLabel, SIGNAL(clicked()), SLOT(slotIconClicked()));
}

void IconizedLineEdit::setIconVisibility(IconizedLineEdit::IconVisibilityMode pIconVisibilityMode)
{
    mIconVisibilityMode = pIconVisibilityMode;
    switch (pIconVisibilityMode)
    {
    case IconAlwaysVisible:
        setIconVisible(true);
        break;
    case IconVisibleOnEmptyText:
    case IconVisibleOnTextPresence:
        slotTextChanged(text());
        break;
    default:
        setIconVisible(false);
        break;
    }
}

bool IconizedLineEdit::isIconVisible() const
{
    return mIconLabel->isVisible();
}

void IconizedLineEdit::setIconPixmap(const QPixmap &pPixmap)
{
    mIconLabel->setIcon(QIcon(pPixmap));
    updateIconPositionAndSize();
}

void IconizedLineEdit::setIconTooltip(const QString &pToolTip)
{
    mIconLabel->setToolTip(pToolTip);
}

void IconizedLineEdit::updateIconPositionAndSize()
{
    mIconLabel->setFixedSize(QSize(this->height()-2, this->height()-2));
    mIconLabel->setIconSize(mIconLabel->size());
    mIconLabel->move(this->width() - mIconLabel->width() - 1, 1);
}

void IconizedLineEdit::setIconVisible(bool pIsVisible)
{
    mIconLabel->setVisible(pIsVisible);
    if (pIsVisible)
    {
        QMargins lMargins = textMargins();
        lMargins.setRight(mIconLabel->size().width() + 1);
        setTextMargins(lMargins);
    }
    else
    {
        setTextMargins(QMargins(0,0,0,0));
    }
}

void IconizedLineEdit::slotIconClicked()
{
    emit signalIconClicked();
}

void IconizedLineEdit::slotTextChanged(const QString &pText)
{
    if (IconVisibleOnEmptyText == mIconVisibilityMode)
    {
        setIconVisible(pText.isEmpty());
    }
    else if (IconVisibleOnTextPresence == mIconVisibilityMode)
    {
        setIconVisible(!pText.isEmpty());
    }
}
