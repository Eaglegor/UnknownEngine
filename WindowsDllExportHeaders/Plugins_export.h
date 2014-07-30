
#ifndef PLUGINS_EXPORT_H
#define PLUGINS_EXPORT_H

#ifdef PLUGINS_STATIC_DEFINE
#  define PLUGINS_EXPORT
#  define PLUGINS_NO_EXPORT
#else
#  ifndef PLUGINS_EXPORT
#    ifdef Plugins_EXPORTS
        /* We are building this library */
#      define PLUGINS_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define PLUGINS_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef PLUGINS_NO_EXPORT
#    define PLUGINS_NO_EXPORT 
#  endif
#endif

#ifndef PLUGINS_DEPRECATED
#  define PLUGINS_DEPRECATED __declspec(deprecated)
#endif

#ifndef PLUGINS_DEPRECATED_EXPORT
#  define PLUGINS_DEPRECATED_EXPORT PLUGINS_EXPORT PLUGINS_DEPRECATED
#endif

#ifndef PLUGINS_DEPRECATED_NO_EXPORT
#  define PLUGINS_DEPRECATED_NO_EXPORT PLUGINS_NO_EXPORT PLUGINS_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define PLUGINS_NO_DEPRECATED
#endif

#endif
