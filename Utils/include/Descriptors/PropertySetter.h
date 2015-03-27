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
                field(field),
                name(name)
                {
                }

                virtual void parseValue(const Core::Properties &props) override{
                    const std::string* val = props.get_pointer<std::string>(name);
                    if(val)
                    {
                        field = *val;
                    }
                }

                virtual void writeValue(Core::Properties &props) override
                {
                    props.set<std::string>(name, field);
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
