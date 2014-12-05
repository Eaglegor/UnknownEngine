#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		class ILogger
		{
		public:
			virtual ILogger& operator<<(const char* text) = 0;
			virtual const char* getName() const = 0;
			virtual ~ILogger(){}
		};
	}
}