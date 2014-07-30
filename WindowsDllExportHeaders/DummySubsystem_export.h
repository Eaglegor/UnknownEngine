
#ifndef DUMMYSUBSYSTEM_EXPORT_H
#define DUMMYSUBSYSTEM_EXPORT_H

#ifdef DUMMYSUBSYSTEM_STATIC_DEFINE
#  define DUMMYSUBSYSTEM_EXPORT
#  define DUMMYSUBSYSTEM_NO_EXPORT
#else
#  ifndef DUMMYSUBSYSTEM_EXPORT
#    ifdef DummySubsystem_EXPORTS
        /* We are building this library */
#      define DUMMYSUBSYSTEM_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define DUMMYSUBSYSTEM_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef DUMMYSUBSYSTEM_NO_EXPORT
#    define DUMMYSUBSYSTEM_NO_EXPORT 
#  endif
#endif

#ifndef DUMMYSUBSYSTEM_DEPRECATED
#  define DUMMYSUBSYSTEM_DEPRECATED __declspec(deprecated)
#endif

#ifndef DUMMYSUBSYSTEM_DEPRECATED_EXPORT
#  define DUMMYSUBSYSTEM_DEPRECATED_EXPORT DUMMYSUBSYSTEM_EXPORT DUMMYSUBSYSTEM_DEPRECATED
#endif

#ifndef DUMMYSUBSYSTEM_DEPRECATED_NO_EXPORT
#  define DUMMYSUBSYSTEM_DEPRECATED_NO_EXPORT DUMMYSUBSYSTEM_NO_EXPORT DUMMYSUBSYSTEM_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define DUMMYSUBSYSTEM_NO_DEPRECATED
#endif

#endif
