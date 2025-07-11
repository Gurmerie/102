#ifndef EXPORTLIB_GLOBAL_H
#define EXPORTLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EXPORTLIB_LIBRARY)
#define EXPORTLIB_EXPORT Q_DECL_EXPORT
#else
#define EXPORTLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // EXPORTLIB_GLOBAL_H
