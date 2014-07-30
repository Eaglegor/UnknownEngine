
#ifndef CONSOLELOGGER_EXPORT_H
#define CONSOLELOGGER_EXPORT_H

#ifdef CONSOLELOGGER_STATIC_DEFINE
#  define CONSOLELOGGER_EXPORT
#  define CONSOLELOGGER_NO_EXPORT
#else
#  ifndef CONSOLELOGGER_EXPORT
#    ifdef ConsoleLogger_EXPORTS
        /* We are building this library */
#      define CONSOLELOGGER_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define CONSOLELOGGER_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef CONSOLELOGGER_NO_EXPORT
#    define CONSOLELOGGER_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef CONSOLELOGGER_DEPRECATED
#  define CONSOLELOGGER_DEPRECATED __attribute__ ((__deprecated__))
#  define CONSOLELOGGER_DEPRECATED_EXPORT CONSOLELOGGER_EXPORT __attribute__ ((__deprecated__))
#  define CONSOLELOGGER_DEPRECATED_NO_EXPORT CONSOLELOGGER_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define CONSOLELOGGER_NO_DEPRECATED
#endif

#endif
