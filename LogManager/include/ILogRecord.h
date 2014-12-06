#pragma once
#include <LogSeverity.h>

namespace UnknownEngine
{
	namespace Core
	{
		class ILogRecord
		{
		public:
			virtual Core::LogSeverity getSeverity() const = 0;
			virtual const char* toString() const = 0;
		};
	}
}