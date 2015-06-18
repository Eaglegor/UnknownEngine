#pragma once

#include <ResourceManager/Revisited/IResourceLoadersFactory.h>
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
				template<typename T>
				struct CreatableObjectDesc
				{
					ResourceLoaderType type;

					typedef std::function< T* (ResourceLoaderType &type, const ResourceLoaderOptions &options) > CreatorFunc;
					typedef std::function< void (T*) > DeleterFunc;

					CreatorFunc creator;
					DeleterFunc deleter;

					CreatableObjectDesc():
					deleter( std::default_delete<IResourceLoader>() ){}
				};

				template<typename T>
				void registerSupportedType(CreatableObjectDesc<T>::CreatorFunc creator, CreatableObjectDesc<T>::DeleterFunc deleter)
				{

				}

			private:
				std::unordered_map<ResourceLoaderType, CreatableObjectDesc> creators;

		};
	}
}
