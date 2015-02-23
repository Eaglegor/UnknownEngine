#include <InputContextMapperFactory.h>
#include <InputContextMapperDescriptorGetter.h>
#include <InputContextMapper.h>
#include <ComponentSystem/ComponentDesc.h>

namespace UnknownEngine
{
	namespace IO
	{
		
		static InputContextMapperDescriptorGetter descriptor_getter;
        
		
		InputContextMapperFactory::InputContextMapperFactory():
		mapper(nullptr)
		{
			CreatableObjectDesc creatable_object;
			creatable_object.creator = std::bind(&InputContextMapperFactory::createInputContextMapper, this, std::placeholders::_1);
			creatable_object.deleter = std::bind(&InputContextMapperFactory::destroyInputContextMapper, this, std::placeholders::_1);
			creatable_object.type = InputContextMapper::getTypeName();
			registerCreator(creatable_object);
		}

		Core::IComponent* InputContextMapperFactory::createInputContextMapper ( const Core::ComponentDesc& desc )
		{
			if(mapper) return mapper;
			InputContextMapperDescriptor mapper_descriptor = desc.descriptor.apply_visitor(descriptor_getter);
			mapper = new InputContextMapper(desc.name.c_str(), mapper_descriptor);
			return mapper;
		}

		void InputContextMapperFactory::destroyInputContextMapper ( Core::IComponent* component )
		{
			delete component;
			mapper = nullptr;
		}
	
	}
}