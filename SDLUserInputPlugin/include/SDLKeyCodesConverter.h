#pragma once
#include <unordered_map>
#include <SDL_keysym.h>
#include <Keys.h>

namespace UnknownEngine
{
	namespace IO
	{
		
		class SDLKeyCodesConverter
		{
		public:
			SDLKeyCodesConverter();
			Key getUnknownEngineKey(const SDLKey &sdl_key);
			KeyModifier getUnknownEngineKeyModifier(const SDLMod &sdl_key_modifier);
			
		private:
			std::unordered_map<SDLKey, Key, std::hash<int> > keys_mapping;
			std::unordered_map<SDLMod, KeyModifier, std::hash<int> > key_modifiers_mapping;
		};
		
	}
}