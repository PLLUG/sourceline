#ifndef SLAPI_GLOBAL_H
#define SLAPI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SLAPI_LIBRARY)
#  define SLAPISHARED_EXPORT Q_DECL_EXPORT
#else
#  define SLAPISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SLAPI_GLOBAL_H

