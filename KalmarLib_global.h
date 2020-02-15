#ifndef KALMARLIB_GLOBAL_H
#define KALMARLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KALMARLIB_LIBRARY)
#  define KALMARLIB_EXPORT Q_DECL_EXPORT
#else
#  define KALMARLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // KALMARLIB_GLOBAL_H
