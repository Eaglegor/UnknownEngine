#pragma once

#include <ResourceManager/IResourceLoadersFactory.h>
#include <functional>
#include <unordered_map>

namespace UnknownEngine
{
	namespace Resources
	{
		class BaseResourceLoadersFactory : public IResourceLoadersFactory
		{
			public:
				virtual bool supportsType(const ResourceLoaderType &type);
				virtual IResourceLoader *createLoader(const ResourceLoaderType &type, const ResourceLoaderOptions &options);
				virtual void destroyLoader(IResourceLoader *loader);

			protected:
				struct SupportedTypeInfo
				{
					typedef std::function< IResourceLoader* (ResourceLoaderType &type, const ResourceLoaderOptions &options) > CreatorFunc;
					typedef std::function< void (IResourceLoader*) > DeleterFunc;

					ResourceLoaderType type;
					CreatorFunc creator;
					DeleterFunc deleter;

					SupportedTypeInfo():
					deleter( std::default_delete<IResourceLoader>() ){}
				};

				void registerSupportedType(const SupportedTypeInfo &supported_type_info)
				{
					creators.emplace(supported_type_info.type, supported_type_info);
				}

			private:
				std::unordered_map<ResourceLoaderType, SupportedTypeInfo> creators;

		};
	}
}
