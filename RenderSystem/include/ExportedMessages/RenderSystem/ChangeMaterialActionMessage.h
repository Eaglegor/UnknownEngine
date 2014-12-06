#pragma once

#include <MessageSystem/Message.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		struct ChangeMaterialActionMessage : public Core::Message
		{
			constexpr static const char* getTypeName(){return "Graphics.ChangeMaterialActionMessage";}
			
			std::string new_material_name;
		};

	} /* namespace Core */
} /* namespace UnknownEngine */
