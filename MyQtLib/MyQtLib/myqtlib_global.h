#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MYQTLIB_LIB)
#  define MYQTLIB_EXPORT Q_DECL_EXPORT
# else
#  define MYQTLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define MYQTLIB_EXPORT
#endif
