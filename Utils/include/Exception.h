#pragma once

#include <string>

namespace UnknownEngine
{
	namespace Core
	{
		/**
		 * @brief Base exception class
		 */
		class Exception : public std::exception
		{
			public:
				/**
				 * @brief Constructor
				 * @param reason - Error message string
				 */
				Exception ( const std::string &reason ) : reason ( reason ) {}
				virtual const char* what() const throw() override
				{
					return reason.c_str();
				}
			private:
				std::string reason; ///< Error message string
		};

	}
}

/// Macros for creating simple exceptions with string reason message
#define UNKNOWNENGINE_SIMPLE_EXCEPTION(ExceptionTypeName) class ExceptionTypeName : public Core::Exception { public: ExceptionTypeName(const std::string &reason): Core::Exception(reason){} }
