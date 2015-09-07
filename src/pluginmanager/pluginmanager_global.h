#ifndef PLUGINMANAGER_GLOBAL_H
#define PLUGINMANAGER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PLUGINMANAGER_LIBRARY)
#  define PLUGINMANAGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PLUGINMANAGERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PLUGINMANAGER_GLOBAL_H
