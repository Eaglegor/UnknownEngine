#pragma once

#include <Descriptors/IDescriptorPropertySetter.h>
#include <Descriptors/IDescriptor.h>

namespace UnknownEngine
{
	namespace Utils
	{
		class NestedDescriptorSetter : public IDescriptorPropertySetter
		{
			public:
				NestedDescriptorSetter ( const char* name, IDescriptor &desc ) :
					desc ( desc ),
					name ( name )
				{
				}

				virtual void parseValue ( const Core::Properties &props ) override
				{
					const Core::Properties* prop = props.get_pointer<Core::Properties> ( name );
					if ( prop )
					{
						desc = *prop;
					}
				}

				virtual void writeValue ( Core::Properties &props ) override
				{
					props.set<Core::Properties> ( name, desc );
				}

				virtual bool isValid()
				{
					return desc.isValid();
				}

			private:
				IDescriptor &desc;
				std::string name;

		};
	}
}
