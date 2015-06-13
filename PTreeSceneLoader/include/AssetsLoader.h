#pragma once

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
			AssetsLoader(ConstantsHolder& constants_holder);
			
			void loadAssets(const boost::property_tree::ptree &root_node);
			
		private:
			void loadAsset(const boost::property_tree::ptree &node);
			
			ConstantsHolder& constants_holder;
		};
	}
}