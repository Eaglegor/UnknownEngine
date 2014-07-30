
#ifndef PLUGINS_EXPORT_H
#define PLUGINS_EXPORT_H

#ifdef PLUGINS_STATIC_DEFINE
#  define PLUGINS_EXPORT
#  define PLUGINS_NO_EXPORT
#else
#  ifndef PLUGINS_EXPORT
#    ifdef Plugins_EXPORTS
        /* We are building this library */
#      define PLUGINS_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define PLUGINS_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef PLUGINS_NO_EXPORT
#    define PLUGINS_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef PLUGINS_DEPRECATED
#  define PLUGINS_DEPRECATED __attribute__ ((__deprecated__))
#  define PLUGINS_DEPRECATED_EXPORT PLUGINS_EXPORT __attribute__ ((__deprecated__))
#  define PLUGINS_DEPRECATED_NO_EXPORT PLUGINS_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define PLUGINS_NO_DEPRECATED
#endif

#endif
