#pragma once

#include <string>
#include <memory>

#include <ComponentSystem_export.h>
#include <Singleton.h>
#include <ComponentSystem/IComponentFactory_fwd.h>

namespace UnknownEngine
{
	namespace Utils
	{
		class NameGenerator;
	}

	namespace Core
	{

		class ILogger;

		class IComponent;
		struct ComponentDesc;
		struct SubsystemDesc;
		class IEntity;

		class ComponentsManager : public Singleton<ComponentsManager>
		{
			public:

				COMPONENTSYSTEM_EXPORT
				ComponentsManager ();

				COMPONENTSYSTEM_EXPORT
				virtual ~ComponentsManager ();

				COMPONENTSYSTEM_EXPORT
				virtual void addComponentFactory ( IComponentFactory* factory );

				COMPONENTSYSTEM_EXPORT
				virtual void removeComponentFactory ( IComponentFactory* factory );

				COMPONENTSYSTEM_EXPORT
				virtual IEntity* createEntity ( const std::string &name );

				COMPONENTSYSTEM_EXPORT
				virtual void removeEntity ( IEntity* entity );

				COMPONENTSYSTEM_EXPORT
				virtual void clearEntities ( );

				COMPONENTSYSTEM_EXPORT
				virtual Utils::NameGenerator* getNameGenerator();
				
				COMPONENTSYSTEM_EXPORT
				virtual IComponent* findComponent(const char* name);
				
				COMPONENTSYSTEM_EXPORT
				virtual void reserveComponent(IComponent* component);
				
				COMPONENTSYSTEM_EXPORT
				virtual void releaseComponent(IComponent* component);
				
			private:
				friend class Entity;

				struct ComponentWrapper
				{
					IComponent* component;
					std::string factory_name;
					size_t ref_counter = 1;
				};
				
				COMPONENTSYSTEM_EXPORT
				virtual IComponent* createComponent ( IEntity* parent, const ComponentDesc &desc ) ;

				COMPONENTSYSTEM_EXPORT
				virtual void removeComponent ( std::unordered_map<std::string, ComponentWrapper>::iterator iter );

				std::unordered_map<std::string, IComponentFactory*> component_factories;
				std::unordered_map<std::string, IEntity*> entities;
				std::unordered_map<std::string, ComponentWrapper> components;
				
				std::unique_ptr<Utils::NameGenerator> name_generator;
				ILogger* logger;
		};

#ifdef _MSC_VER
#ifndef ComponentSystem_EXPORTS
		extern template class COMPONENTSYSTEM_EXPORT Singleton<ComponentsManager>;
#else
		template class COMPONENTSYSTEM_EXPORT Singleton<ComponentsManager>;
#endif
#endif

	} /* namespace Core */
} /* namespace UnknownEngine */
