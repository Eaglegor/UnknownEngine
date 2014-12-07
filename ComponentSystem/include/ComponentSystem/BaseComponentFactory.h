#pragma once

#include <ComponentSystem/IComponentFactory.h>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <ComponentSystem/IComponent.h>

namespace UnknownEngine
{
	namespace Core
	{
		class BaseComponentFactory : public IComponentFactory
		{
		public:
			virtual IComponent* createObject ( const ComponentDesc& desc ) override;
			
			virtual void destroyObject ( IComponent* object ) override;

			virtual bool supportsType ( const ComponentType& object_type ) const override;
			
		protected:
			struct CreatableObjectDesc
			{
				ComponentType type;
				std::function< IComponent* (const ComponentDesc&) > creator;
				std::function< void (IComponent*) > deleter;
				
				CreatableObjectDesc():
				deleter( std::default_delete<IComponent>() ){}
			};

			COMPONENTSYSTEM_EXPORT
			void registerCreator(const CreatableObjectDesc& creatable_object_desc);
			
		private:
			std::unordered_set<ComponentType> supported_types;
			std::unordered_map<ComponentType, CreatableObjectDesc> creators;
		};
	}
}