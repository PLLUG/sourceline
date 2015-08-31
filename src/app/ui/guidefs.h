#ifndef GUIDEFS_H
#define GUIDEFS_H
#include <QObject>
#include <QString>
#include <array>

/*!
 * \file guidefs.h
 */

enum  class DockType : char {
    UknownType = 0,
    FileView,
    RevisionTable,
    HistoryTree,
    Console,
    EditorView
};

enum MenuGroup {
    UknownMenuGroup = 0,
    FileMenuGroup,
    ViewMenuGroup,
    EditMenuGroup,
    HelpMenuGroup,
    MENU_GROUP_COUNT
};

static const QString gMenuGroups[] = {QObject::tr("&Unknown"), QObject::tr("&File"), QObject::tr("&View"), QObject::tr("&Edit"), QObject::tr("&Help")};

#endif // GUIDEFS_H
