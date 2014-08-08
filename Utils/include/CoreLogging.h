#pragma once

#ifdef ENABLE_CORE_SUBSYSTEM_INFO_LOG
#define CORE_SUBSYSTEM_INFO(msg) std::cout << "[INFO] Core: " << msg << std::endl
#else
#define CORE_SUBSYSTEM_INFO(msg)
#endif

#ifdef ENABLE_CORE_SUBSYSTEM_WARNING_LOG
#define CORE_SUBSYSTEM_WARNING(msg) std::cout << "[WARNING] Core: " << msg << std::endl
#else
#define CORE_SUBSYSTEM_WARNING(msg)
#endif

#ifdef ENABLE_CORE_SUBSYSTEM_DEBUG_LOG
#define CORE_SUBSYSTEM_DEBUG(msg) std::cout << "[DEBUG] Core: " << msg << std::endl
#else
#define CORE_SUBSYSTEM_DEBUG(msg)
#endif

#ifdef ENABLE_CORE_SUBSYSTEM_ERROR_LOG
#define CORE_SUBSYSTEM_ERROR(msg) std::cout << "[ERROR] Core: " << msg << std::endl
#else
#define CORE_SUBSYSTEM_ERROR(msg)
#endif
