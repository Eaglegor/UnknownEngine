#pragma once

#include <vector>

namespace boost
{
	namespace property_tree
	{
		class ptree;
	}
}

namespace UnknownEngine
{
	namespace Core
	{
		class IEntity;
		class IComponent;
	}
	
	namespace Loader
	{
		class ConstantsHolder;
		
		class EntitiesLoader
		{
		public:
			EntitiesLoader(ConstantsHolder& constants_holder);
			
			std::vector<Core::IEntity*> loadEntities(const boost::property_tree::ptree &root_node);
			
		private:
			Core::IEntity* loadAssetEntity(const boost::property_tree::ptree &node);
			Core::IEntity* loadEntity(const boost::property_tree::ptree &node);
			Core::IComponent* loadComponent(const boost::property_tree::ptree &node);
			
			ConstantsHolder& constants_holder;
		};
	}
}