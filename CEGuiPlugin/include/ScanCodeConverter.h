#pragma once

#include <CEGUI/InputEvent.h>
#include <Keys.h>
#include <InlineSpecification.h>

namespace UnknownEngine
{
	namespace GUI
	{
		class ScanCodeConverter
		{
			public:

				UNKNOWNENGINE_INLINE
				static CEGUI::Key::Scan toCeguiScancode ( const IO::Key &key )
				{
					switch ( key )
					{
					case IO::Key::NONE: return CEGUI::Key::Unlabeled;
					case IO::Key::BACKSPACE: return CEGUI::Key::Backspace;
					case IO::Key::TAB: return CEGUI::Key::Tab;
					case IO::Key::RETURN: return CEGUI::Key::Return;
					case IO::Key::PAUSE: return CEGUI::Key::Pause;
					case IO::Key::ESCAPE: return CEGUI::Key::Escape;
					case IO::Key::SPACE: return CEGUI::Key::Space;
					case IO::Key::COMMA: return CEGUI::Key::Comma;
					case IO::Key::MINUS: return CEGUI::Key::Minus;
					case IO::Key::PERIOD: return CEGUI::Key::Period;
					case IO::Key::SLASH: return CEGUI::Key::Slash;
					case IO::Key::_0: return CEGUI::Key::Zero;
					case IO::Key::_1: return CEGUI::Key::One;
					case IO::Key::_2: return CEGUI::Key::Two;
					case IO::Key::_3: return CEGUI::Key::Three;
					case IO::Key::_4: return CEGUI::Key::Four;
					case IO::Key::_5: return CEGUI::Key::Five;
					case IO::Key::_6: return CEGUI::Key::Six;
					case IO::Key::_7: return CEGUI::Key::Seven;
					case IO::Key::_8: return CEGUI::Key::Eight;
					case IO::Key::_9: return CEGUI::Key::Nine;
					case IO::Key::COLON: return CEGUI::Key::Colon;
					case IO::Key::SEMICOLON: return CEGUI::Key::Semicolon;
					case IO::Key::EQUALS: return CEGUI::Key::Equals;
					case IO::Key::AT: return CEGUI::Key::At;
					case IO::Key::LEFTBRACKET: return CEGUI::Key::LeftBracket;
					case IO::Key::BACKSLASH: return CEGUI::Key::Backslash;
					case IO::Key::RIGHTBRACKET: return CEGUI::Key::RightBracket;
					case IO::Key::UNDERSCORE: return CEGUI::Key::Underline;
					case IO::Key::A: return CEGUI::Key::A;
					case IO::Key::B: return CEGUI::Key::B;
					case IO::Key::C: return CEGUI::Key::C;
					case IO::Key::D: return CEGUI::Key::D;
					case IO::Key::E: return CEGUI::Key::E;
					case IO::Key::F: return CEGUI::Key::F;
					case IO::Key::G: return CEGUI::Key::G;
					case IO::Key::H: return CEGUI::Key::H;
					case IO::Key::I: return CEGUI::Key::I;
					case IO::Key::J: return CEGUI::Key::J;
					case IO::Key::K: return CEGUI::Key::K;
					case IO::Key::L: return CEGUI::Key::L;
					case IO::Key::M: return CEGUI::Key::M;
					case IO::Key::N: return CEGUI::Key::N;
					case IO::Key::O: return CEGUI::Key::O;
					case IO::Key::P: return CEGUI::Key::P;
					case IO::Key::Q: return CEGUI::Key::Q;
					case IO::Key::R: return CEGUI::Key::R;
					case IO::Key::S: return CEGUI::Key::S;
					case IO::Key::T: return CEGUI::Key::T;
					case IO::Key::U: return CEGUI::Key::U;
					case IO::Key::V: return CEGUI::Key::V;
					case IO::Key::W: return CEGUI::Key::W;
					case IO::Key::X: return CEGUI::Key::X;
					case IO::Key::Y: return CEGUI::Key::Y;
					case IO::Key::Z: return CEGUI::Key::Z;
					case IO::Key::_DELETE: return CEGUI::Key::Delete;
					case IO::Key::KP0: return CEGUI::Key::Numpad0;
					case IO::Key::KP1: return CEGUI::Key::Numpad1;
					case IO::Key::KP2: return CEGUI::Key::Numpad2;
					case IO::Key::KP3: return CEGUI::Key::Numpad3;
					case IO::Key::KP4: return CEGUI::Key::Numpad4;
					case IO::Key::KP5: return CEGUI::Key::Numpad5;
					case IO::Key::KP6: return CEGUI::Key::Numpad6;
					case IO::Key::KP7: return CEGUI::Key::Numpad7;
					case IO::Key::KP8: return CEGUI::Key::Numpad8;
					case IO::Key::KP9: return CEGUI::Key::Numpad9;
					case IO::Key::KP_PERIOD: return CEGUI::Key::NumpadComma;
					case IO::Key::KP_ENTER: return CEGUI::Key::NumpadEnter;
					case IO::Key::KP_EQUALS: return CEGUI::Key::NumpadEquals;
					case IO::Key::UP: return CEGUI::Key::ArrowUp;
					case IO::Key::DOWN: return CEGUI::Key::ArrowDown;
					case IO::Key::RIGHT: return CEGUI::Key::ArrowRight;
					case IO::Key::LEFT: return CEGUI::Key::ArrowLeft;
					case IO::Key::INSERT: return CEGUI::Key::Insert;
					case IO::Key::HOME: return CEGUI::Key::Home;
					case IO::Key::END: return CEGUI::Key::End;
					case IO::Key::PAGEUP: return CEGUI::Key::PageUp;
					case IO::Key::PAGEDOWN: return CEGUI::Key::PageDown;
					case IO::Key::F1: return CEGUI::Key::F1;
					case IO::Key::F2: return CEGUI::Key::F2;
					case IO::Key::F3: return CEGUI::Key::F3;
					case IO::Key::F4: return CEGUI::Key::F4;
					case IO::Key::F5: return CEGUI::Key::F5;
					case IO::Key::F6: return CEGUI::Key::F6;
					case IO::Key::F7: return CEGUI::Key::F7;
					case IO::Key::F8: return CEGUI::Key::F8;
					case IO::Key::F9: return CEGUI::Key::F9;
					case IO::Key::F10: return CEGUI::Key::F10;
					case IO::Key::F11: return CEGUI::Key::F11;
					case IO::Key::F12: return CEGUI::Key::F12;
					case IO::Key::F13: return CEGUI::Key::F13;
					case IO::Key::F14: return CEGUI::Key::F14;
					case IO::Key::F15: return CEGUI::Key::F15;
					case IO::Key::NUMLOCK: return CEGUI::Key::NumLock;
					case IO::Key::SCROLLLOCK: return CEGUI::Key::ScrollLock;
					case IO::Key::RSHIFT: return CEGUI::Key::RightShift;
					case IO::Key::LSHIFT: return CEGUI::Key::LeftShift;
					case IO::Key::RCTRL: return CEGUI::Key::RightControl;
					case IO::Key::LCTRL: return CEGUI::Key::LeftControl;
					case IO::Key::RALT: return CEGUI::Key::RightAlt;
					case IO::Key::LALT: return CEGUI::Key::LeftAlt;
					case IO::Key::RMETA: return CEGUI::Key::RightWindows;
					case IO::Key::LMETA: return CEGUI::Key::LeftWindows;
					case IO::Key::LSUPER: return CEGUI::Key::LeftWindows;
					case IO::Key::RSUPER: return CEGUI::Key::RightWindows;
					case IO::Key::SYSREQ: return CEGUI::Key::SysRq;
					case IO::Key::BREAK: return CEGUI::Key::Pause;
					case IO::Key::MENU: return CEGUI::Key::AppMenu;
					case IO::Key::POWER: return CEGUI::Key::Power;
					default: return CEGUI::Key::Unknown;
					};
				}

		};
	}
}
