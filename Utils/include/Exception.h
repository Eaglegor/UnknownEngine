#pragma once

#include <string>

namespace UnknownEngine
{
	namespace Core
	{
		class Exception : public std::exception
		{
			public:
				Exception ( const std::string &reason ) : reason ( reason ) {}
				virtual const char* what() const throw() override
				{
					return reason.c_str();
				}
			private:
				std::string reason;
		};

	}
}

/// Macros for creating simple exceptions with string reason message
#define UNKNOWNENGINE_SIMPLE_EXCEPTION(ExceptionTypeName) class ExceptionTypeName : public Core::Exception { public: ExceptionTypeName(const std::string &reason): Core::Exception(reason){} }
