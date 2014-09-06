#pragma once
#include <Properties/Properties.h>
#include <boost/lexical_cast.hpp>
#include <boost/optional/optional.hpp>

namespace UnknownEngine
{
	namespace Utils
	{
		class PropertiesParser
		{

			public:

				class PropertiesValue
				{
					public:
						virtual void setOutputValue ( const Core::Properties& properties, const std::string& property_name ) = 0;
						virtual ~PropertiesValue() {};
				};

			private:
				class PropertiesValueHolder
				{
					public:
						template<typename T>
						PropertiesValueHolder ( T value )
						{
							this->value = std::make_shared<T>( std::move ( value ) );
						}

						void setOutputValue ( const Core::Properties& properties, const std::string& property_name )
						{
							value->setOutputValue ( properties, property_name );
						}

					private:
						std::shared_ptr<PropertiesValue> value;
				};


			public:
				template<typename T>
				class OptionalValue : public PropertiesValue
				{
					public:
						OptionalValue ( T& out_value ) :
							out_value ( out_value )
						{
						}

						virtual void setOutputValue ( const Core::Properties& properties, const std::string& property_name )
						{
							boost::optional<const std::string&> string_value = properties.get_optional<std::string> ( property_name );
							if ( string_value )
							{
								out_value = boost::lexical_cast<T> ( string_value.get() );
							}
						}

					private:
						T& out_value;
				};

				template<typename T>
				class RequiredValue : public PropertiesValue
				{
					public:
						RequiredValue ( T& out_value ) :
							out_value ( out_value )
						{
						}

						virtual void setOutputValue ( const Core::Properties& properties, const std::string& property_name )
						{
							std::string string_value = properties.get<std::string> ( property_name );
							out_value = boost::lexical_cast<T> ( string_value );
						}

					private:
						T& out_value;
				};

				class OptionalNestedValue : public PropertiesValue
				{
					public:
						OptionalNestedValue ( std::initializer_list < std::pair< std::string, PropertiesValueHolder > > nested ) :
							nested_definitions ( nested )
						{
						}

						virtual void setOutputValue ( const Core::Properties& properties, const std::string& property_name )
						{
							boost::optional<const Core::Properties&> section = properties.get_optional<Core::Properties> ( property_name );
							if ( section )
							{
								PropertiesParser::parse ( section.get(), nested_definitions );
							}
						}

					private:
						std::initializer_list < std::pair <std::string, PropertiesValueHolder> > nested_definitions;
				};
				
				class RequiredNestedValue : public PropertiesValue
				{
					public:
						RequiredNestedValue ( std::initializer_list < std::pair < std::string, PropertiesValueHolder > > nested ) :
							nested_definitions ( nested )
						{
						}

						virtual void setOutputValue ( const Core::Properties& properties, const std::string& property_name )
						{
							const Core::Properties& section = properties.get<Core::Properties> ( property_name );
							PropertiesParser::parse ( section, nested_definitions );
						}

					private:
						std::initializer_list < std::pair <std::string, PropertiesValueHolder > > nested_definitions;
				};
				
				template<typename T, typename ParserType>
				class ExternalParserOptionalNestedValue : public PropertiesValue
				{
					public:
						ExternalParserOptionalNestedValue ( T &out_value ) :
						out_value(out_value)
						{
						}

						virtual void setOutputValue ( const Core::Properties& properties, const std::string& property_name )
						{
							boost::optional<const Core::Properties&> section = properties.get_optional<Core::Properties> ( property_name );
							if ( section )
							{
								out_value = ParserType::parse(section.get());
							}
						}

					private:
						T &out_value;
				};
				
				template<typename T, typename ParserType>
				class ExternalParserRequiredNestedValue : public PropertiesValue
				{
					public:
						ExternalParserRequiredNestedValue ( T &out_value ) :
						out_value(out_value)
						{
						}

						virtual void setOutputValue ( const Core::Properties& properties, const std::string& property_name )
						{
							const Core::Properties& section = properties.get<Core::Properties> ( property_name );
							out_value = ParserType::parse(section);
						}

					private:
						T &out_value;
				};

			public:
				static void parse ( const Core::Properties& properties, std::initializer_list< std::pair< std::string, PropertiesValueHolder > > const &rules )
				{
					for ( auto & rule : rules )
					{
						const_cast<PropertiesValueHolder&> ( rule.second ).setOutputValue ( properties, rule.first );
					}
				}
		};
	};
}
