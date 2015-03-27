#pragma once

namespace UnknownEngine
{
	namespace Utils
	{
		class IProperty
		{
			public:
				enum Optionality
				{
					REQUIRED,
					OPTIONAL
				};

				virtual operator std::string() = 0;
				virtual IProperty& operator=(const char* string_value_representation) = 0;
				virtual bool isValid() = 0;
		};
	}
}
