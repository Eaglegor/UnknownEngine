#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		class IComponent;
	}
	namespace GUI
	{
		class ICEGuiComponent
		{
		public:

			enum class State
			{
				CREATION,
				INITIALIZATION,
				WORK,
				SHUTTING_DOWN,
				DESTRUCTION
			};

			virtual State getState() const = 0;

			virtual void _init() = 0;
			virtual void _update() = 0;
			virtual void _shutdown() = 0;
			virtual void _destroy() = 0;

			typedef std::function<void(Core::IComponent*)> DestructionCallback;
			virtual void startDestruction (DestructionCallback destruction_callback) = 0;
		};
	}
}