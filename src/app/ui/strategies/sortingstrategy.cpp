/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Priyma Yuriy (priymayuriy@gmail.com)                          ***
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
#include "sortingstrategy.h"

QList<UserAction *> MenuCreationStrategy::getAllByKind(int pCommandKind, const QList<UserAction *> &pListUserActions)
{
    QList<UserAction *> rResult;

    foreach (UserAction *lUserAction, pListUserActions)
    {
        if (lUserAction->commandKind() == pCommandKind)
        {
            rResult.append(lUserAction);
        }
    }
    return std::move(rResult);
}

// Exmaple: QList<int> lOrderedKinds;
//          lOrderedKinds << ChekoutCommand << UpdateCommand << ExportCommand << ImportCommand;
//          QList<UserAction *> lRepositoryMenuActions = getAllOrderedByKinds(lOrderedKinds, pListUserActions);
QList<UserAction *> MenuCreationStrategy::getAllOrderedByKinds(QList<int> pListKinds, const QList<UserAction *> &pListUserActions)
{
    QList<UserAction *> rResult;

    foreach (int lKind, pListKinds)
    {
        foreach (UserAction *lUserAction, getAllByKind(lKind, pListUserActions))
        {
            rResult.append(lUserAction);
        }
    }
    return std::move(rResult);
}
