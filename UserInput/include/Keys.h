#pragma once

namespace UnknownEngine
{
	namespace IO
	{
		enum class Key
		{
			NONE,
			BACKSPACE,
			TAB,
			CLEAR,
			RETURN,
			PAUSE,
			ESCAPE,
			SPACE,
			EXCLAIM,
			QUOTEDBL,
			HASH,
			DOLLAR,
			AMPERSAND,
			QUOTE,
			LEFTPAREN,
			RIGHTPAREN,
			ASTERISK,
			PLUS,
			COMMA,
			MINUS,
			PERIOD,
			SLASH,
			_0,
			_1,
			_2,
			_3,
			_4,
			_5,
			_6,
			_7,
			_8,
			_9,
			COLON,
			SEMICOLON,
			LESS,
			EQUALS,
			GREATER,
			QUESTION,
			AT,
			LEFTBRACKET,
			BACKSLASH,
			RIGHTBRACKET,
			CARET,
			UNDERSCORE,
			BACKQUOTE,
			A,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			DELETE,
			KP0,
			KP1,
			KP2,
			KP3,
			KP4,
			KP5,
			KP6,
			KP7,
			KP8,
			KP9,
			KP_PERIOD,
			KP_DIVIDE,
			KP_MULTIPLY,
			KP_MINUS,
			KP_ENTER,
			KP_EQUALS,
			UP,
			DOWN,
			RIGHT,
			LEFT,
			INSERT,
			HOME,
			END,
			PAGEUP,
			PAGEDOWN,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			F13,
			F14,
			F15,
			NUMLOCK,
			CAPSLOCK,
			SCROLLLOCK,
			RSHIFT,
			LSHIFT,
			RCTRL,
			LCTRL,
			RALT,
			LALT,
			RMETA,
			LMETA,
			LSUPER,
			RSUPER,
			MODE,
			HELP,
			PRINTSCREEN,
			SYSREQ,
			BREAK,
			MENU,
			POWER,
			EURO
		};
		
		enum class KeyModifier
		{
			NONE = 0x0000,
			NUMLOCK = 0x0001,
			CAPSLOCK = 0x0002,
			LCTRL = 0x0040,
			RCTRL = 0x0080,
			RSHIFT = 0x0100,
			LSHIFT = 0x0200,
			RALT = 0x0400,
			LALT = 0x0800
		};
		
	}
}