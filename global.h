#ifndef GLOABAL_H
#define GLOABAL_H

#include <QtCore/qglobal.h>

#if not defined(LIBQXMLEDIT_LIBRARY_STATIC)

#if defined(LIBQXMLEDIT_LIBRARY)
#  define LIBQXMLEDITSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBQXMLEDITSHARED_EXPORT Q_DECL_IMPORT
#endif

#else
#  define LIBQXMLEDITSHARED_EXPORT
#endif

#endif // GLOABAL_H
