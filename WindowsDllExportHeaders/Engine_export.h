
#ifndef ENGINE_EXPORT_H
#define ENGINE_EXPORT_H

#ifdef ENGINE_STATIC_DEFINE
#  define ENGINE_EXPORT
#  define ENGINE_NO_EXPORT
#else
#  ifndef ENGINE_EXPORT
#    ifdef Engine_EXPORTS
        /* We are building this library */
#      define ENGINE_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define ENGINE_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef ENGINE_NO_EXPORT
#    define ENGINE_NO_EXPORT 
#  endif
#endif

#ifndef ENGINE_DEPRECATED
#  define ENGINE_DEPRECATED __declspec(deprecated)
#endif

#ifndef ENGINE_DEPRECATED_EXPORT
#  define ENGINE_DEPRECATED_EXPORT ENGINE_EXPORT ENGINE_DEPRECATED
#endif

#ifndef ENGINE_DEPRECATED_NO_EXPORT
#  define ENGINE_DEPRECATED_NO_EXPORT ENGINE_NO_EXPORT ENGINE_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define ENGINE_NO_DEPRECATED
#endif

#endif
