
#ifndef XMLSCENELOADER_EXPORT_H
#define XMLSCENELOADER_EXPORT_H

#ifdef XMLSCENELOADER_STATIC_DEFINE
#  define XMLSCENELOADER_EXPORT
#  define XMLSCENELOADER_NO_EXPORT
#else
#  ifndef XMLSCENELOADER_EXPORT
#    ifdef XmlSceneLoader_EXPORTS
        /* We are building this library */
#      define XMLSCENELOADER_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define XMLSCENELOADER_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef XMLSCENELOADER_NO_EXPORT
#    define XMLSCENELOADER_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef XMLSCENELOADER_DEPRECATED
#  define XMLSCENELOADER_DEPRECATED __attribute__ ((__deprecated__))
#  define XMLSCENELOADER_DEPRECATED_EXPORT XMLSCENELOADER_EXPORT __attribute__ ((__deprecated__))
#  define XMLSCENELOADER_DEPRECATED_NO_EXPORT XMLSCENELOADER_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define XMLSCENELOADER_NO_DEPRECATED
#endif

#endif
