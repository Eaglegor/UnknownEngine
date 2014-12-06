#pragma once

#include <string>
#include <list>
#include <vector>
#include <memory>

#include <ComponentSystem_export.h>
#include <Singleton.h>
#include <ComponentType.h>
#include <Exception.h>
#include <NumericIdentifierType.h>
#include <Dictionary.h>
#include <NoSuitableFactoryFoundException.h>

#include <IComponentFactory_fwd.h>

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
		class Entity;

		class ComponentsManager : public Singleton<ComponentsManager>
		{
			private:
				typedef Utils::Dictionary<NumericIdentifierType, std::string> InternalDictionaryType;
				typedef std::unordered_map<NumericIdentifierType, IComponentFactory*> ComponentFactoriesMap;
				
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
				virtual Entity* createEntity ( const std::string &name );

				COMPONENTSYSTEM_EXPORT
				virtual void removeEntity ( Entity* entity );

				COMPONENTSYSTEM_EXPORT
				virtual void clearEntities ( );

				COMPONENTSYSTEM_EXPORT
				virtual Utils::NameGenerator* getNameGenerator();
				
			private:
				friend class Entity;

				COMPONENTSYSTEM_EXPORT
				virtual IComponent* createComponent ( const ComponentDesc &desc ) ;

				COMPONENTSYSTEM_EXPORT
				virtual void removeComponent ( IComponent* component );
				
				ComponentFactoriesMap component_factories;
				InternalDictionaryType internal_dictionary;
				std::vector<Entity*> entities;
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

	}
}
