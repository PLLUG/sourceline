#ifndef GUIDEFS_H
#define GUIDEFS_H

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
    EditMenuGroup,
    HelpMenuGroup,
    MENU_GROUP_COUNT
};

#endif // GUIDEFS_H
