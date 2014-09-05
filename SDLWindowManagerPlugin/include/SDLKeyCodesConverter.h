#pragma once
#include <unordered_map>
#include <SDL_keycode.h>
#include <Keys.h>

namespace UnknownEngine
{
	namespace IO
	{
		
		class SDLKeyCodesConverter
		{
		public:
			SDLKeyCodesConverter();
			Key getUnknownEngineKey(const SDL_Keycode &sdl_key);
			KeyModifier getUnknownEngineKeyModifier(const SDL_Keymod &sdl_key_modifier);
			
		private:
			std::unordered_map<SDL_Keycode, Key, std::hash<int> > keys_mapping;
			std::unordered_map<SDL_Keymod, KeyModifier, std::hash<int> > key_modifiers_mapping;
		};
		
	}
}