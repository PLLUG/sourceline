/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Volodymyr Kochyn  (vovakochyn@gmail.com)                      ***
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

#include "graphfield.h"
#include "node.h"

GraphField::GraphField() :
    mWidth(0),
    mHeight(0)
{
}

int GraphField::width() const
{
    return mWidth;
}

int GraphField::height() const
{
    return mHeight;
}

void GraphField::addCommit(Node *pNode, Node *pParent)
{
    pNode->setCoorginate(pParent ? pParent->x() : mWidth, mHeight);
    ++mHeight;
}

void GraphField::addBranch(Node *pNode)
{
    pNode->setCoorginate(mWidth, mHeight);
    ++mWidth;
    ++mHeight;
}
