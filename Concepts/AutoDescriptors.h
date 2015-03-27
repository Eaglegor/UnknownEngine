#include <string>
#include <iostream>

#define PASS_DESC_PROPERTY(property_name) {"property_name", &property_name}
#define PASS_DESC_PROPERTY_CUSTOM_NAME(string_name, property_name) {"string_name", &property_name}

class IProperty
{
	public:
		enum Optionality
		{
			REQUIRED,
			OPTIONAL
		};
};


template<typename T, IProperty::Optionality optionality>
class Property : public IProperty
{
	public:
		Property<T, optionality> operator=(const std::string &value){
			//value = boost::lexical_cast<T>(value);
			return *this;
		}
		operator T() {return value;}

	private:
		T value;
};

class Descriptor
{
	public:
		Descriptor(std::initializer_list<std::pair<std::string, IProperty*>> props)
		{
			// Filling local properties list
		}
		
		virtual bool isValid()
		{
			
		}
		
		/*Descriptor& operator=(const Core::Properties& props)
		{
			// Parsing properties
		}
		
		Core::Properties operator Core::Properties()
		{
			// Packing properties
		}*/
};

class ObjectDesc : public Descriptor
{
	public:
		Property<int, IProperty::REQUIRED> prop1;
		Property<int, IProperty::REQUIRED> prop2;
		Property<int, IProperty::OPTIONAL> prop3;
		Property<std::string, IProperty::OPTIONAL> prop4;
		
		ObjectDesc():
		Descriptor({
		PASS_DESC_PROPERTY(prop1),
		PASS_DESC_PROPERTY(prop2),
		PASS_DESC_PROPERTY(prop3),
		PASS_DESC_PROPERTY(prop4)
		})
		{};
};


int main()
{
	return 0;
}