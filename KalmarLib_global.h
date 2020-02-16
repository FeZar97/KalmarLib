#ifndef KALMARLIB_GLOBAL_H
#define KALMARLIB_GLOBAL_H

#include <QtCore/qglobal.h>

typedef void	(__stdcall *LptSendCodeFct)(unsigned short, unsigned char);

#if defined(KALMARLIB_LIBRARY)
#  define KALMARLIB_EXPORT Q_DECL_EXPORT
#else
#  define KALMARLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // KALMARLIB_GLOBAL_H
