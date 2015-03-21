#include <stdafx.h>
#include <Parsers/KeycodeParser.h>

namespace UnknownEngine
{
	namespace IO
	{
		KeycodeParser::KeycodeParser()
		{
			mapping.emplace ( "NONE", Key::NONE );
			
			mapping.emplace ( "BACKSPACE", Key::BACKSPACE );
			
			mapping.emplace ( "TAB", Key::TAB );
			
			mapping.emplace ( "CLEAR", Key::CLEAR );
			
			mapping.emplace ( "RETURN", Key::RETURN );
			mapping.emplace ( "ENTER", Key::RETURN );
			
			mapping.emplace ( "PAUSE", Key::PAUSE );
			
			mapping.emplace ( "ESC", Key::ESCAPE );
			mapping.emplace ( "ESCAPE", Key::ESCAPE );
			
			mapping.emplace ( "SPACE", Key::SPACE );
			
			mapping.emplace ( "EXCLAIM", Key::EXCLAIM );
			
			mapping.emplace ( "QUOTEDBL", Key::QUOTEDBL );
			
			mapping.emplace ( "HASH", Key::HASH );
			
			mapping.emplace ( "DOLLAR", Key::DOLLAR );
			
			mapping.emplace ( "AMPERSAND", Key::AMPERSAND );
			
			mapping.emplace ( "QUOTE", Key::QUOTE );
			
			mapping.emplace ( "LEFTPAREN", Key::LEFTPAREN );
			
			mapping.emplace ( "RIGHTPAREN", Key::RIGHTPAREN );
			
			mapping.emplace ( "ASTERISK", Key::ASTERISK );
			
			mapping.emplace ( "PLUS", Key::PLUS );
			
			mapping.emplace ( "COMMA", Key::COMMA );
			
			mapping.emplace ( "MINUS", Key::MINUS );
			
			mapping.emplace ( "PERIOD", Key::PERIOD );
			
			mapping.emplace ( "SLASH", Key::SLASH );
			
			mapping.emplace ( "0", Key::_0 );
			
			mapping.emplace ( "1", Key::_1 );
			
			mapping.emplace ( "2", Key::_2 );
			
			mapping.emplace ( "3", Key::_3 );
			
			mapping.emplace ( "4", Key::_4 );
			
			mapping.emplace ( "5", Key::_5 );
			
			mapping.emplace ( "6", Key::_6 );
			
			mapping.emplace ( "7", Key::_7 );
			
			mapping.emplace ( "8", Key::_8 );
			
			mapping.emplace ( "9", Key::_9 );
			
			mapping.emplace ( "COLON", Key::COLON );
			
			mapping.emplace ( "SEMICOLON", Key::SEMICOLON );
			
			mapping.emplace ( "LESS", Key::LESS );
			
			mapping.emplace ( "EQUALS", Key::EQUALS );
			
			mapping.emplace ( "GREATER", Key::GREATER );
			
			mapping.emplace ( "QUESTION", Key::QUESTION );
			
			mapping.emplace ( "AT", Key::AT );
			
			mapping.emplace ( "LEFTBRACKET", Key::LEFTBRACKET );
			
			mapping.emplace ( "BACKSLASH", Key::BACKSLASH );
			
			mapping.emplace ( "RIGHTBRACKET", Key::RIGHTBRACKET );

			mapping.emplace ( "CARET", Key::CARET );
			
			mapping.emplace ( "UNDERSCORE", Key::UNDERSCORE );
			
			mapping.emplace ( "BACKQUOTE", Key::BACKQUOTE );
			
			mapping.emplace ( "A", Key::A );
			
			mapping.emplace ( "B", Key::B );
			
			mapping.emplace ( "C", Key::C );
			
			mapping.emplace ( "D", Key::D );
			
			mapping.emplace ( "E", Key::E );
			
			mapping.emplace ( "F", Key::F );
			
			mapping.emplace ( "G", Key::G );
			
			mapping.emplace ( "H", Key::H );
			
			mapping.emplace ( "I", Key::I );
			
			mapping.emplace ( "J", Key::J );
			
			mapping.emplace ( "K", Key::K );
			
			mapping.emplace ( "L", Key::L );
			
			mapping.emplace ( "M", Key::M );
			
			mapping.emplace ( "N", Key::N );
			
			mapping.emplace ( "O", Key::O );
			
			mapping.emplace ( "P", Key::P );
			
			mapping.emplace ( "Q", Key::Q );
			
			mapping.emplace ( "R", Key::R );
			
			mapping.emplace ( "S", Key::S );
			
			mapping.emplace ( "T", Key::T );
			
			mapping.emplace ( "U", Key::U );
			
			mapping.emplace ( "V", Key::V );
			
			mapping.emplace ( "W", Key::W );
			
			mapping.emplace ( "X", Key::X );
			
			mapping.emplace ( "Y", Key::Y );
			
			mapping.emplace ( "Z", Key::Z );
			
			mapping.emplace ( "_DELETE", Key::_DELETE);
			
			mapping.emplace ( "KP0", Key::KP0 );
			
			mapping.emplace ( "KP1", Key::KP1 );
			
			mapping.emplace ( "KP2", Key::KP2 );
			
			mapping.emplace ( "KP3", Key::KP3 );
			
			mapping.emplace ( "KP4", Key::KP4 );
			
			mapping.emplace ( "KP5", Key::KP5 );
			
			mapping.emplace ( "KP6", Key::KP6 );
			
			mapping.emplace ( "KP7", Key::KP7 );
			
			mapping.emplace ( "KP8", Key::KP8 );
			
			mapping.emplace ( "KP9", Key::KP9 );
			
			mapping.emplace ( "KP_PERIOD", Key::KP_PERIOD );
			
			mapping.emplace ( "KP_DIVIDE", Key::KP_DIVIDE );
			
			mapping.emplace ( "KP_MULTIPLY", Key::KP_MULTIPLY );
			
			mapping.emplace ( "KP_MINUS", Key::KP_MINUS );
			
			mapping.emplace ( "KP_ENTER", Key::KP_ENTER );
			
			mapping.emplace ( "KP_EQUALS", Key::KP_EQUALS );
			
			mapping.emplace ( "UP", Key::UP );
			
			mapping.emplace ( "DOWN", Key::DOWN );
			
			mapping.emplace ( "RIGHT", Key::RIGHT );
			
			mapping.emplace ( "LEFT", Key::LEFT );
			
			mapping.emplace ( "INSERT", Key::INSERT );
			
			mapping.emplace ( "HOME", Key::HOME );
			
			mapping.emplace ( "END", Key::END );
			
			mapping.emplace ( "PAGEUP", Key::PAGEUP );
			
			mapping.emplace ( "PAGEDOWN", Key::PAGEDOWN );
			
			mapping.emplace ( "F1", Key::F1 );
			
			mapping.emplace ( "F2", Key::F2 );
			
			mapping.emplace ( "F3", Key::F3 );
			
			mapping.emplace ( "F4", Key::F4 );
			
			mapping.emplace ( "F5", Key::F5 );
			
			mapping.emplace ( "F6", Key::F6 );
			
			mapping.emplace ( "F7", Key::F7 );
			
			mapping.emplace ( "F8", Key::F8 );
			
			mapping.emplace ( "F9", Key::F9 );
			
			mapping.emplace ( "F10", Key::F10 );
			
			mapping.emplace ( "F11", Key::F11 );
			
			mapping.emplace ( "F12", Key::F12 );
			
			mapping.emplace ( "F13", Key::F13 );
			
			mapping.emplace ( "F14", Key::F14 );
			
			mapping.emplace ( "F15", Key::F15 );
			
			mapping.emplace ( "NUMLOCK", Key::NUMLOCK );
			
			mapping.emplace ( "CAPSLOCK", Key::CAPSLOCK );
			
			mapping.emplace ( "SCROLLLOCK", Key::SCROLLLOCK );
			
			mapping.emplace ( "RSHIFT", Key::RSHIFT );
			
			mapping.emplace ( "LSHIFT", Key::LSHIFT );
			
			mapping.emplace ( "RCTRL", Key::RCTRL );
			
			mapping.emplace ( "LCTRL", Key::LCTRL );
			
			mapping.emplace ( "RALT", Key::RALT );
			
			mapping.emplace ( "LALT", Key::LALT );
			
			mapping.emplace ( "RMETA", Key::RMETA );
			
			mapping.emplace ( "LMETA", Key::LMETA );
			
			mapping.emplace ( "LSUPER", Key::LSUPER );
			
			mapping.emplace ( "RSUPER", Key::RSUPER );
			
			mapping.emplace ( "MODE", Key::MODE );
			
			mapping.emplace ( "HELP", Key::HELP );
			
			mapping.emplace ( "PRINTSCREEN", Key::PRINTSCREEN );
			
			mapping.emplace ( "SYSREQ", Key::SYSREQ );
			
			mapping.emplace ( "BREAK", Key::BREAK );
			
			mapping.emplace ( "MENU", Key::MENU );
			
			mapping.emplace ( "POWER", Key::POWER );
			
			mapping.emplace ( "EURO", Key::EURO );
			
			mapping.emplace ( "~", Key::BACKQUOTE );
		}

		Key KeycodeParser::parse ( const std::string& value ) const
		{
			const auto iter = mapping.find(value);
			if(iter == mapping.end()) throw UnknownStringKeyCode("Unknown keycode found while parsing: " + value);
			return iter->second;
		}
	}
}
