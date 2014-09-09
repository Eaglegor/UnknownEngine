#pragma once

#include <boost/variant/static_visitor.hpp>
#include <Properties/Properties_fwd.h>
#include <DescriptorContainer.h>

namespace UnknownEngine
{
	namespace Graphics
	{
		template<typename DescriptorClass, typename DescriptorParserClass>
		class OgreGetDescriptorVisitor : public boost::static_visitor<DescriptorClass>
		{
		public:
			DescriptorClass operator()(const Core::DescriptorContainer& descriptor_container) const
			{
				return descriptor_container.get<DescriptorClass>();
			}
			
			DescriptorClass operator()(const Core::Properties& creation_options) const
			{
				return DescriptorParserClass::parse(creation_options);
			}
		};
	}
}