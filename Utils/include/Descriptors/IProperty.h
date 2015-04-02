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
					REQUIRED_PROPERTY,
					OPTIONAL_PROPERTY
				};

				virtual operator std::string() = 0;
				virtual IProperty& operator=(const std::string &string_value_representation) = 0;
				virtual bool isValid() = 0;
		};
	}
}
