
#ifndef COMPONENTSYSTEM_EXPORT_H
#define COMPONENTSYSTEM_EXPORT_H

#ifdef COMPONENTSYSTEM_STATIC_DEFINE
#  define COMPONENTSYSTEM_EXPORT
#  define COMPONENTSYSTEM_NO_EXPORT
#else
#  ifndef COMPONENTSYSTEM_EXPORT
#    ifdef ComponentSystem_EXPORTS
        /* We are building this library */
#      define COMPONENTSYSTEM_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define COMPONENTSYSTEM_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef COMPONENTSYSTEM_NO_EXPORT
#    define COMPONENTSYSTEM_NO_EXPORT 
#  endif
#endif

#ifndef COMPONENTSYSTEM_DEPRECATED
#  define COMPONENTSYSTEM_DEPRECATED __declspec(deprecated)
#endif

#ifndef COMPONENTSYSTEM_DEPRECATED_EXPORT
#  define COMPONENTSYSTEM_DEPRECATED_EXPORT COMPONENTSYSTEM_EXPORT COMPONENTSYSTEM_DEPRECATED
#endif

#ifndef COMPONENTSYSTEM_DEPRECATED_NO_EXPORT
#  define COMPONENTSYSTEM_DEPRECATED_NO_EXPORT COMPONENTSYSTEM_NO_EXPORT COMPONENTSYSTEM_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define COMPONENTSYSTEM_NO_DEPRECATED
#endif

#endif
