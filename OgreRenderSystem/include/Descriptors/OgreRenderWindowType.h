#pragma once

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace UnknownEngine
{
	namespace Graphics
	{
		enum class OgreRenderWindowType
		{
			OWN,
			EXTERNAL,
			PARENT
		};
	}
}

namespace boost
{
	template<>
	UNKNOWNENGINE_INLINE
	UnknownEngine::Graphics::OgreRenderWindowType lexical_cast<UnknownEngine::Graphics::OgreRenderWindowType, std::string>(const std::string &value)
	{
		std::string converted_value = value;
		boost::to_lower(converted_value);
		boost::trim(converted_value);
		if(converted_value=="own") return UnknownEngine::Graphics::OgreRenderWindowType::OWN;
		if(converted_value=="parent" || converted_value=="external") 
		{
			#ifdef _MSC_VER
				return UnknownEngine::Graphics::OgreRenderWindowType::EXTERNAL;
			#else
				return UnknownEngine::Graphics::OgreRenderWindowType::PARENT;
			#endif
		}

		return UnknownEngine::Graphics::OgreRenderWindowType::OWN;
	}
	
	template<>
	UNKNOWNENGINE_INLINE
	std::string lexical_cast<std::string, UnknownEngine::Graphics::OgreRenderWindowType>(const UnknownEngine::Graphics::OgreRenderWindowType &value)
	{
		switch(value)
		{
			case UnknownEngine::Graphics::OgreRenderWindowType::OWN: return "own";
			case UnknownEngine::Graphics::OgreRenderWindowType::PARENT: return "parent";
			case UnknownEngine::Graphics::OgreRenderWindowType::EXTERNAL: return "external";
			default: return "own";
		}
	}
}