
#ifndef DUMMYSUBSYSTEM_EXPORT_H
#define DUMMYSUBSYSTEM_EXPORT_H

#ifdef DUMMYSUBSYSTEM_STATIC_DEFINE
#  define DUMMYSUBSYSTEM_EXPORT
#  define DUMMYSUBSYSTEM_NO_EXPORT
#else
#  ifndef DUMMYSUBSYSTEM_EXPORT
#    ifdef DummySubsystem_EXPORTS
        /* We are building this library */
#      define DUMMYSUBSYSTEM_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define DUMMYSUBSYSTEM_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef DUMMYSUBSYSTEM_NO_EXPORT
#    define DUMMYSUBSYSTEM_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef DUMMYSUBSYSTEM_DEPRECATED
#  define DUMMYSUBSYSTEM_DEPRECATED __attribute__ ((__deprecated__))
#  define DUMMYSUBSYSTEM_DEPRECATED_EXPORT DUMMYSUBSYSTEM_EXPORT __attribute__ ((__deprecated__))
#  define DUMMYSUBSYSTEM_DEPRECATED_NO_EXPORT DUMMYSUBSYSTEM_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define DUMMYSUBSYSTEM_NO_DEPRECATED
#endif

#endif
