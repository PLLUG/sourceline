#ifndef GUIDEFS_H
#define GUIDEFS_H
#include <QObject>
#include <QString>

/*!
 * \file guidefs.h
 */

namespace DockTypes
{
    enum DockType {
        UknownType = 0,
        FileView,
        RevisionTable,
        HistoryTree,
        Console,
        EditorView,
        DOCK_TYPE_COUNT
    };
}

enum MenuGroups {
    UknownMenuGroup = 0,
    FileMenuGroup,
    ViewMenuGroup,
    EditMenuGroup,
    HelpMenuGroup,
    MENU_GROUP_COUNT
};

static const QString gMenuGroups[] = {QObject::tr("&Unknown"), QObject::tr("&File"), QObject::tr("&View"), QObject::tr("&Edit"), QObject::tr("&Help")};

#endif // GUIDEFS_H
