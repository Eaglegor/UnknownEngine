#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		struct SenderInfo
		{
				explicit SenderInfo(std::string){}
				bool operator==(const SenderInfo&){return true;}
		};

		//typedef int /*std::string*/ SenderInfo;
	}
}
