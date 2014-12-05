#pragma once

#include <ILogger.h>

namespace UnknownEngine
{
	namespace Core
	{
		class ProxyLogger : public ILogger
		{
		public:
			ProxyLogger(const char* name):
				name(name)
			{}

			ILogger& operator<<(const char* text) override;
			const char* getName() const override;

		private:
			std::string name;
		};
	}
}