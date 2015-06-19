#pragma once

#include <unordered_map>

namespace UnknownEngine
{
	namespace Resources
	{
		class ResourceGroup
		{
		public:
			virtual ~ResourceGroup(){}

			ResourceGroup* createNestedResourceGroup(const char* name);
			ResourceGroup* getNestedResourceGroup(const char* name);

			void addResourceHandle(const char* name, IResourceHandle* handle);
			IResourceHandle* findResourceHandle(const char* name);

			void removeResourceHandle(const char* name);

		private:
			std::unordered_map<std::string, ResourceGroup> nestedResourceGroups;
			std::unordered_map<std::string, IResourceHandle*> resourceHandles;

		};
	}
}
