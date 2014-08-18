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

#include "testplugin.h"
#include "gitfakecomponent.h"
#include "pluginsettings.h"
#include "customsettingpage.h"
#include "fakecommand.h"

TestPlugin::TestPlugin(QObject *pParent) :
    Plugin(pParent)
{
    GitFakeComponent *gitFakeComponent = new GitFakeComponent(this);
    this->addComponent(gitFakeComponent);

    PluginSettings *lPSettings = new PluginSettings(this);
    CustomSettingPage *lSettingPage = new CustomSettingPage(lPSettings);
    this->addComponent(lSettingPage);

    FakeCommand *lFakeCommand = new FakeCommand(this);
    this->addComponent(lFakeCommand);
}
