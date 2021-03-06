#pragma once

#include <string>
#include <memory>

#include <ComponentSystem_export.h>
#include <Singleton.h>
#include <ComponentSystem/IComponentFactory_fwd.h>
#include <condition_variable>
#include <unordered_map>
#include <unordered_set>

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
				virtual void reserveComponent(IComponent* component);
				
				COMPONENTSYSTEM_EXPORT
				virtual void releaseComponent(IComponent* component);
				
				COMPONENTSYSTEM_EXPORT
				virtual IComponent* findComponent(const char* name);
				
				COMPONENTSYSTEM_EXPORT
				virtual void waitUntilAllComponentsReleased();

			private:
				friend class Entity;
				
				COMPONENTSYSTEM_EXPORT
				virtual IComponent* createComponent ( const ComponentDesc &desc ) ;

				COMPONENTSYSTEM_EXPORT
				virtual void removeComponent ( IComponent* component );
				
				std::unordered_map<std::string, IComponentFactory*> component_factories;
				std::unordered_map<std::string, IEntity*> entities;
				std::unordered_set<IEntity*> entities_set;
				
				std::unordered_map<std::string, IComponent*> components;
			
				std::unique_ptr<Utils::NameGenerator> name_generator;
				ILogger* logger;
				
				typedef std::mutex LockPrimitive;
				
				LockPrimitive lock;
				std::condition_variable cv;
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
