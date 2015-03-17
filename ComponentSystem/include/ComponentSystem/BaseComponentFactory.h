#pragma once

#include <ComponentSystem/IComponentFactory.h>
#include <ComponentSystem/IComponent.h>

#include <memory>
#include <unordered_map>
#include <functional>


namespace UnknownEngine
{
	namespace Core
	{
		class BaseComponentFactory : public IComponentFactory
		{
		public:
			COMPONENTSYSTEM_EXPORT
			virtual IComponent* createObject ( const ComponentDesc& desc ) override;
			
			COMPONENTSYSTEM_EXPORT
			virtual void destroyObject ( IComponent* object ) override;

			COMPONENTSYSTEM_EXPORT
			virtual bool supportsType ( const ComponentType& object_type ) const override;
			
		protected:
			typedef std::function< IComponent* (const ComponentDesc&) > CreationFunctor;
			typedef std::function< void (IComponent*) > DestructionFunctor;
			
			typedef std::default_delete<IComponent> DefaultDestructionFunctor;
			
			struct CreatableObjectDesc
			{
				ComponentType type;
				CreationFunctor creator;
				DestructionFunctor deleter;
				
				CreatableObjectDesc():
				deleter( DefaultDestructionFunctor() ){}
			};

			COMPONENTSYSTEM_EXPORT
			void registerCreator(const CreatableObjectDesc& creatable_object_desc);
			
		private:
			std::unordered_map<ComponentType, CreatableObjectDesc> creators;
		};
	}
}