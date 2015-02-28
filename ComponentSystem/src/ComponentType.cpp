#include <ComponentSystem/ComponentType.h>

namespace UnknownEngine
{
	namespace Core
	{

		const size_t UNKNOWN_TYPE_ID = static_cast<size_t>(-1);
		const char* UNKNOWN_TYPE_NAME = "UnknownComponentType";

		ComponentType::ComponentType():
		name(UNKNOWN_TYPE_NAME),
		type_id(UNKNOWN_TYPE_ID)
		{
		}

		ComponentType::ComponentType(const char* name) :
		name(name),
		type_id(retrieveTypeId(name))
		{
		}

		ComponentType::ComponentType(const char* name, const ComponentType& base) :
		name(name),
		type_id(retrieveTypeId(name))
		{
			base_types.insert(base);
		}

		ComponentType::ComponentType(const ComponentType& type):
		base_types(type.getBases()),
		name(type.getTypeName()),
		type_id(type.getTypeId())
		{
		}

		ComponentType::ComponentType(const char* name, const std::set<ComponentType>& bases):
		base_types(bases),
		name(name),
		type_id(retrieveTypeId(name))
		{
		}

		ComponentType& ComponentType::operator=(const ComponentType& rhs)
		{
			name = rhs.getTypeName();
			type_id = rhs.getTypeId();
			base_types = rhs.getBases();
			return *this;
		}

		bool ComponentType::operator==(const ComponentType& rhs) const
		{
			return name == rhs.name;
		}

		bool ComponentType::operator!=(const ComponentType& rhs) const
		{
			return !(*this == rhs);
		}

		bool ComponentType::operator<(const ComponentType& rhs) const
		{
			return getTypeId() < rhs.getTypeId();
		}

		size_t ComponentType::getTypeId() const
		{
			return type_id;
		}

		const char* ComponentType::getTypeName() const
		{
			return name.c_str();
		}

		const std::set<ComponentType>& ComponentType::getBases() const
		{
			return base_types;
		}

		bool ComponentType::operator==(const char* type_name) const
		{
			return *this == Core::ComponentType(type_name);
		}
		
		bool ComponentType::is(const ComponentType& type) const
		{
			if (type.getTypeId() == getTypeId()) return true;
			if (!base_types.empty())
			{
				for (const ComponentType& base_type : base_types)
				{
					if (base_type.is(type))
					{
						return true;
					}
				}
			}
			return false;
		}

		std::string operator+(const std::string& str, const ComponentType &type)
		{
			return str + std::string(type.getTypeName());
		}

		std::string operator+(const ComponentType &type, const std::string& str)
		{
			return std::string(type.getTypeName()) + str;
		}

		size_t ComponentType::retrieveTypeId(const char* name)
		{
			return UNKNOWN_TYPE_ID;
		}

	}
}