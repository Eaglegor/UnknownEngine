
#ifndef OGRERENDERSYSTEM_EXPORT_H
#define OGRERENDERSYSTEM_EXPORT_H

#ifdef OGRERENDERSYSTEM_STATIC_DEFINE
#  define OGRERENDERSYSTEM_EXPORT
#  define OGRERENDERSYSTEM_NO_EXPORT
#else
#  ifndef OGRERENDERSYSTEM_EXPORT
#    ifdef OgreRenderSystem_EXPORTS
        /* We are building this library */
#      define OGRERENDERSYSTEM_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define OGRERENDERSYSTEM_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef OGRERENDERSYSTEM_NO_EXPORT
#    define OGRERENDERSYSTEM_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef OGRERENDERSYSTEM_DEPRECATED
#  define OGRERENDERSYSTEM_DEPRECATED __attribute__ ((__deprecated__))
#  define OGRERENDERSYSTEM_DEPRECATED_EXPORT OGRERENDERSYSTEM_EXPORT __attribute__ ((__deprecated__))
#  define OGRERENDERSYSTEM_DEPRECATED_NO_EXPORT OGRERENDERSYSTEM_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define OGRERENDERSYSTEM_NO_DEPRECATED
#endif

#endif
