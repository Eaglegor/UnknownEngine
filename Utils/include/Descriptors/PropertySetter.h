#pragma once

#include <Descriptors/IDescriptorPropertySetter.h>
#include <Descriptors/IProperty.h>

namespace UnknownEngine
{
    namespace Utils
    {
        class PropertySetter : public IDescriptorPropertySetter
        {
            public:
                PropertySetter(const char* name, IProperty &field):
                name(name),
                field(field)
                {
                }

                virtual Result parseValue(Core::Properties &props){
                    std::string* val = props.get_pointer<std::string>(name);
                    if(val)
                    {
                        field = val->c_str();
                    }
                }

                virtual void writeValue(Core::Properties &props)
                {
                    props.set<std::string>(desc);
                }

                virtual bool isValid()
                {
                    return field.isValid();
                }

            private:
                IProperty &field;
                std::string name;
        };
    }
}
