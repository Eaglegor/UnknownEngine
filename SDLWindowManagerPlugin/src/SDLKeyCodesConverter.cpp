#include <stdafx.h>
#include <SDLKeyCodesConverter.h>

namespace UnknownEngine
{
	namespace IO
	{

		SDLKeyCodesConverter::SDLKeyCodesConverter()
		{
			keys_mapping.emplace(SDLK_BACKSPACE, Key::BACKSPACE);
			keys_mapping.emplace(SDLK_TAB, Key::TAB);
			keys_mapping.emplace(SDLK_CLEAR, Key::CLEAR);
			keys_mapping.emplace(SDLK_RETURN, Key::RETURN);
			keys_mapping.emplace(SDLK_PAUSE, Key::PAUSE);
			keys_mapping.emplace(SDLK_ESCAPE, Key::ESCAPE);
			keys_mapping.emplace(SDLK_SPACE, Key::SPACE);
			keys_mapping.emplace(SDLK_EXCLAIM, Key::EXCLAIM);
			keys_mapping.emplace(SDLK_QUOTEDBL, Key::QUOTEDBL);
			keys_mapping.emplace(SDLK_HASH, Key::HASH);
			keys_mapping.emplace(SDLK_DOLLAR, Key::DOLLAR);
			keys_mapping.emplace(SDLK_AMPERSAND, Key::AMPERSAND);
			keys_mapping.emplace(SDLK_QUOTE, Key::QUOTE);
			keys_mapping.emplace(SDLK_LEFTPAREN, Key::LEFTPAREN);
			keys_mapping.emplace(SDLK_RIGHTPAREN, Key::RIGHTPAREN);
			keys_mapping.emplace(SDLK_ASTERISK, Key::ASTERISK);
			keys_mapping.emplace(SDLK_PLUS, Key::PLUS);
			keys_mapping.emplace(SDLK_COMMA, Key::COMMA);
			keys_mapping.emplace(SDLK_MINUS, Key::MINUS);
			keys_mapping.emplace(SDLK_PERIOD, Key::PERIOD);
			keys_mapping.emplace(SDLK_SLASH, Key::SLASH);
			keys_mapping.emplace(SDLK_0, Key::_0);
			keys_mapping.emplace(SDLK_1, Key::_1);
			keys_mapping.emplace(SDLK_2, Key::_2);
			keys_mapping.emplace(SDLK_3, Key::_3);
			keys_mapping.emplace(SDLK_4, Key::_4);
			keys_mapping.emplace(SDLK_5, Key::_5);
			keys_mapping.emplace(SDLK_6, Key::_6);
			keys_mapping.emplace(SDLK_7, Key::_7);
			keys_mapping.emplace(SDLK_8, Key::_8);
			keys_mapping.emplace(SDLK_9, Key::_9);
			keys_mapping.emplace(SDLK_COLON, Key::COLON);
			keys_mapping.emplace(SDLK_SEMICOLON, Key::SEMICOLON);
			keys_mapping.emplace(SDLK_LESS, Key::LESS);
			keys_mapping.emplace(SDLK_EQUALS, Key::EQUALS);
			keys_mapping.emplace(SDLK_GREATER, Key::GREATER);
			keys_mapping.emplace(SDLK_QUESTION, Key::QUESTION);
			keys_mapping.emplace(SDLK_AT, Key::AT);
			keys_mapping.emplace(SDLK_LEFTBRACKET, Key::LEFTBRACKET);
			keys_mapping.emplace(SDLK_BACKSLASH, Key::BACKSLASH);
			keys_mapping.emplace(SDLK_RIGHTBRACKET, Key::RIGHTBRACKET);
			keys_mapping.emplace(SDLK_CARET, Key::CARET);
			keys_mapping.emplace(SDLK_UNDERSCORE, Key::UNDERSCORE);
			keys_mapping.emplace(SDLK_BACKQUOTE, Key::BACKQUOTE);
			keys_mapping.emplace(SDLK_a, Key::A);
			keys_mapping.emplace(SDLK_b, Key::B);
			keys_mapping.emplace(SDLK_c, Key::C);
			keys_mapping.emplace(SDLK_d, Key::D);
			keys_mapping.emplace(SDLK_e, Key::E);
			keys_mapping.emplace(SDLK_f, Key::F);
			keys_mapping.emplace(SDLK_g, Key::G);
			keys_mapping.emplace(SDLK_h, Key::H);
			keys_mapping.emplace(SDLK_i, Key::I);
			keys_mapping.emplace(SDLK_j, Key::J);
			keys_mapping.emplace(SDLK_k, Key::K);
			keys_mapping.emplace(SDLK_l, Key::L);
			keys_mapping.emplace(SDLK_m, Key::M);
			keys_mapping.emplace(SDLK_n, Key::N);
			keys_mapping.emplace(SDLK_o, Key::O);
			keys_mapping.emplace(SDLK_p, Key::P);
			keys_mapping.emplace(SDLK_q, Key::Q);
			keys_mapping.emplace(SDLK_r, Key::R);
			keys_mapping.emplace(SDLK_s, Key::S);
			keys_mapping.emplace(SDLK_t, Key::T);
			keys_mapping.emplace(SDLK_u, Key::U);
			keys_mapping.emplace(SDLK_v, Key::V);
			keys_mapping.emplace(SDLK_w, Key::W);
			keys_mapping.emplace(SDLK_x, Key::X);
			keys_mapping.emplace(SDLK_y, Key::Y);
			keys_mapping.emplace(SDLK_z, Key::Z);
			keys_mapping.emplace(SDLK_DELETE, Key::DELETE);
			keys_mapping.emplace(SDLK_KP_0, Key::KP0);
			keys_mapping.emplace(SDLK_KP_1, Key::KP1);
			keys_mapping.emplace(SDLK_KP_2, Key::KP2);
			keys_mapping.emplace(SDLK_KP_3, Key::KP3);
			keys_mapping.emplace(SDLK_KP_4, Key::KP4);
			keys_mapping.emplace(SDLK_KP_5, Key::KP5);
			keys_mapping.emplace(SDLK_KP_6, Key::KP6);
			keys_mapping.emplace(SDLK_KP_7, Key::KP7);
			keys_mapping.emplace(SDLK_KP_8, Key::KP8);
			keys_mapping.emplace(SDLK_KP_9, Key::KP9);
			keys_mapping.emplace(SDLK_KP_PERIOD, Key::KP_PERIOD);
			keys_mapping.emplace(SDLK_KP_DIVIDE, Key::KP_DIVIDE);
			keys_mapping.emplace(SDLK_KP_MULTIPLY, Key::KP_MULTIPLY);
			keys_mapping.emplace(SDLK_KP_MINUS, Key::KP_MINUS);
			keys_mapping.emplace(SDLK_KP_ENTER, Key::KP_ENTER);
			keys_mapping.emplace(SDLK_KP_EQUALS, Key::KP_EQUALS);
			keys_mapping.emplace(SDLK_UP, Key::UP);
			keys_mapping.emplace(SDLK_DOWN, Key::DOWN);
			keys_mapping.emplace(SDLK_RIGHT, Key::RIGHT);
			keys_mapping.emplace(SDLK_LEFT, Key::LEFT);
			keys_mapping.emplace(SDLK_INSERT, Key::INSERT);
			keys_mapping.emplace(SDLK_HOME, Key::HOME);
			keys_mapping.emplace(SDLK_END, Key::END);
			keys_mapping.emplace(SDLK_PAGEUP, Key::PAGEUP);
			keys_mapping.emplace(SDLK_PAGEDOWN, Key::PAGEDOWN);
			keys_mapping.emplace(SDLK_F1, Key::F1);
			keys_mapping.emplace(SDLK_F2, Key::F2);
			keys_mapping.emplace(SDLK_F3, Key::F3);
			keys_mapping.emplace(SDLK_F4, Key::F4);
			keys_mapping.emplace(SDLK_F5, Key::F5);
			keys_mapping.emplace(SDLK_F6, Key::F6);
			keys_mapping.emplace(SDLK_F7, Key::F7);
			keys_mapping.emplace(SDLK_F8, Key::F8);
			keys_mapping.emplace(SDLK_F9, Key::F9);
			keys_mapping.emplace(SDLK_F10, Key::F10);
			keys_mapping.emplace(SDLK_F11, Key::F11);
			keys_mapping.emplace(SDLK_F12, Key::F12);
			keys_mapping.emplace(SDLK_F13, Key::F13);
			keys_mapping.emplace(SDLK_F14, Key::F14);
			keys_mapping.emplace(SDLK_F15, Key::F15);
			keys_mapping.emplace(SDLK_NUMLOCKCLEAR, Key::NUMLOCK);
			keys_mapping.emplace(SDLK_CAPSLOCK, Key::CAPSLOCK);
			keys_mapping.emplace(SDLK_SCROLLLOCK, Key::SCROLLLOCK);
			keys_mapping.emplace(SDLK_RSHIFT, Key::RSHIFT);
			keys_mapping.emplace(SDLK_LSHIFT, Key::LSHIFT);
			keys_mapping.emplace(SDLK_RCTRL, Key::RCTRL);
			keys_mapping.emplace(SDLK_LCTRL, Key::LCTRL);
			keys_mapping.emplace(SDLK_RALT, Key::RALT);
			keys_mapping.emplace(SDLK_LALT, Key::LALT);
			keys_mapping.emplace(SDLK_RGUI, Key::RMETA);
			keys_mapping.emplace(SDLK_LGUI, Key::LMETA);
			keys_mapping.emplace(SDLK_MODE, Key::MODE);
			keys_mapping.emplace(SDLK_HELP, Key::HELP);
			keys_mapping.emplace(SDLK_PRINTSCREEN, Key::PRINTSCREEN);
			keys_mapping.emplace(SDLK_SYSREQ, Key::SYSREQ);
			keys_mapping.emplace(SDLK_MENU, Key::MENU);
			keys_mapping.emplace(SDLK_POWER, Key::POWER);
			
			key_modifiers_mapping.emplace(KMOD_NONE, KeyModifier::NONE);
			key_modifiers_mapping.emplace(KMOD_NUM, KeyModifier::NUMLOCK);
			key_modifiers_mapping.emplace(KMOD_CAPS, KeyModifier::CAPSLOCK);
			key_modifiers_mapping.emplace(KMOD_LCTRL, KeyModifier::LCTRL);
			key_modifiers_mapping.emplace(KMOD_RCTRL, KeyModifier::RCTRL);
			key_modifiers_mapping.emplace(KMOD_RSHIFT, KeyModifier::RSHIFT);
			key_modifiers_mapping.emplace(KMOD_LSHIFT, KeyModifier::LSHIFT);
			key_modifiers_mapping.emplace(KMOD_RALT, KeyModifier::RALT);
			key_modifiers_mapping.emplace(KMOD_LALT, KeyModifier::LALT);
		}
		
		Key SDLKeyCodesConverter::getUnknownEngineKey ( const SDL_Keycode& sdl_key )
		{
			auto iter = keys_mapping.find(sdl_key);
			if(iter == keys_mapping.end()) return Key::NONE;
			return iter->second;
		}
		
		KeyModifier SDLKeyCodesConverter::getUnknownEngineKeyModifier ( const SDL_Keymod& sdl_key_modifier )
		{
			auto iter = key_modifiers_mapping.find(sdl_key_modifier);
			if(iter == key_modifiers_mapping.end()) return KeyModifier::NONE;
			return iter->second;
		}

		
	}
}