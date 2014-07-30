
#ifndef RESOURCEMANAGER_EXPORT_H
#define RESOURCEMANAGER_EXPORT_H

#ifdef RESOURCEMANAGER_STATIC_DEFINE
#  define RESOURCEMANAGER_EXPORT
#  define RESOURCEMANAGER_NO_EXPORT
#else
#  ifndef RESOURCEMANAGER_EXPORT
#    ifdef ResourceManager_EXPORTS
        /* We are building this library */
#      define RESOURCEMANAGER_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define RESOURCEMANAGER_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef RESOURCEMANAGER_NO_EXPORT
#    define RESOURCEMANAGER_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef RESOURCEMANAGER_DEPRECATED
#  define RESOURCEMANAGER_DEPRECATED __attribute__ ((__deprecated__))
#  define RESOURCEMANAGER_DEPRECATED_EXPORT RESOURCEMANAGER_EXPORT __attribute__ ((__deprecated__))
#  define RESOURCEMANAGER_DEPRECATED_NO_EXPORT RESOURCEMANAGER_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define RESOURCEMANAGER_NO_DEPRECATED
#endif

#endif
