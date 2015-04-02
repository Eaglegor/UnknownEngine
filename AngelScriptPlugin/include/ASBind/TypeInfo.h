#pragma once

namespace UnknownEngine
{
	namespace ASBind
	{
		enum class ClassType
		{
			REF_TYPE,
			VALUE_TYPE
		};

		struct TypeInfo
		{
			std::string name;
			ClassType type;
		};
	}
}
