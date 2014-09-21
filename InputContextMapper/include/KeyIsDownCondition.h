#pragma once

#include <ActionCondition.h>

namespace UnknownEngine
{
	namespace IO
	{
		class KeyIsDownCondition : public ActionCondition
		{
		public:
			KeyIsDownCondition(const Key& key):
			key(key)
			{
			}
			
			virtual Math::Scalar getState()
			{
				return 0;
			}
			
			virtual bool isTrue()
			{
				return is_down;
			}
			
			virtual void reset()
			{
			}
			
			virtual void update ( const Key& key, const KeyState& state )
			{
				if(key == this->key)
				{
					switch(state)
					{
						case KeyState::KEY_PRESSED:
						{
							is_down = true;
							break;
						}
						case KeyState::KEY_UNPRESSED:
						{
							is_down = false;
							break;
						}
					}
				}
			}
			
		private:
			Key key;
			bool is_down;
		};
	}
}