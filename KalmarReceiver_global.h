#ifndef KALMARLIB_GLOBAL_H
#define KALMARLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KALMARRECEIVER_LIBRARY)
#  define KALMARRECEIVER_EXPORT Q_DECL_EXPORT
#else
#  define KALMARRECEIVER_EXPORT Q_DECL_IMPORT
#endif

#endif // KALMARLIB_GLOBAL_H