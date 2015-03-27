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
                NestedDescriptorSetter(const char* name, IDescriptor &desc):
                name(name),
                desc(desc)
                {
                }

                virtual void parseValue(Core::Properties &props){
                    Core::Properties* prop = props.get_pointer<Core::Properties>(name);
                    if(prop)
                    {
                        desc = *prop;
                    }
                }

                virtual void writeValue(Core::Properties &props)
                {
                    props.set<Core::Properties>(desc);
                }

                virtual bool isValid(){
                    return desc.isValid();
                }

            private:
                IDescriptor &desc;
                std::string name;

        };
    }
}
