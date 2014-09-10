#pragma once
#include <Properties/Properties.h>
#include <boost/lexical_cast.hpp>
#include <boost/optional/optional.hpp>
#include <functional>

namespace UnknownEngine
{
	namespace Utils
	{
		class PropertiesParser
		{

			public:

				template<typename T>
				struct Setter
				{
				public:
					typedef std::function<void(const T&)> type;
				};
				
				template<typename T>
				class DefaultSetter
				{
				public:
					DefaultSetter(T &t):t(t){}
					
					void operator()(const T& value)
					{
						t = value;
					}
					
				private:
					T &t;
				};
				
				template<typename T>
				class BoostOptionalSetter
				{
				public:
					BoostOptionalSetter(boost::optional<T> &t):t(t){}
					
					void operator()(const T& value)
					{
						t = value;
					}
					
				private:
					boost::optional<T> &t;
				};
				
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
				class OptionalRawValue : public PropertiesValue
				{
					public:
						OptionalRawValue ( T& out_value ) :
							setter ( DefaultSetter<T>(out_value) )
						{
						}

						OptionalRawValue ( typename Setter<T>::type setter ) :
							setter ( setter )
						{
						}
						
						OptionalRawValue ( boost::optional<T> &out_value ) :
							setter ( BoostOptionalSetter<T>(out_value) )
						{
						}
						
						virtual void setOutputValue ( const Core::Properties& properties, const std::string& property_name )
						{
							boost::optional<const T&> value = properties.get_optional<T> ( property_name );
							if ( value )
							{
								setter( value.get() );
							}
						}

					private:
						typename Setter<T>::type setter;
				};
				
				template<typename T>
				class RequiredRawValue : public PropertiesValue
				{
					public:
						RequiredRawValue ( T& out_value ) :
							setter ( DefaultSetter<T>(out_value) )
						{
						}

						RequiredRawValue ( typename Setter<T>::type setter ) :
							setter ( setter )
						{
						}
						
						virtual void setOutputValue ( const Core::Properties& properties, const std::string& property_name )
						{
							const T& value = properties.get<T> ( property_name );
							setter( value );
						}

					private:
						typename Setter<T>::type setter;
				};
				
				template<typename T>
				class OptionalValue : public PropertiesValue
				{
					public:
						OptionalValue ( T& out_value ) :
							setter ( DefaultSetter<T>(out_value) )
						{
						}

						OptionalValue ( typename Setter<T>::type setter ) :
							setter ( setter )
						{
						}
						
						OptionalValue ( boost::optional<T> &out_value ) :
							setter ( BoostOptionalSetter<T>(out_value) )
						{
						}
						
						virtual void setOutputValue ( const Core::Properties& properties, const std::string& property_name )
						{
							boost::optional<const std::string&> string_value = properties.get_optional<std::string> ( property_name );
							if ( string_value )
							{
								setter(boost::lexical_cast<T> ( string_value.get() ));
							}
						}

					private:
						typename Setter<T>::type setter;
				};

				template<typename T>
				class RequiredValue : public PropertiesValue
				{
					public:
						RequiredValue ( T& out_value ) :
							setter ( DefaultSetter<T>(out_value) )
						{
						}

						RequiredValue ( typename Setter<T>::type setter ) :
							setter(setter)
						{
						}
						
						virtual void setOutputValue ( const Core::Properties& properties, const std::string& property_name )
						{
							std::string string_value = properties.get<std::string> ( property_name );
							setter( boost::lexical_cast<T> ( string_value ) );
						}

					private:
						typename Setter<T>::type setter;
				};

				class OptionalNestedValue : public PropertiesValue
				{
					public:
						OptionalNestedValue ( std::vector < std::pair< std::string, PropertiesValueHolder > > nested ) :
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
						std::vector < std::pair <std::string, PropertiesValueHolder> > nested_definitions;
				};
				
				class RequiredNestedValue : public PropertiesValue
				{
					public:
						RequiredNestedValue ( std::vector < std::pair < std::string, PropertiesValueHolder > > nested ) :
							nested_definitions ( nested )
						{
						}

						virtual void setOutputValue ( const Core::Properties& properties, const std::string& property_name )
						{
							const Core::Properties& section = properties.get<Core::Properties> ( property_name );
							PropertiesParser::parse ( section, nested_definitions );
						}

					private:
						std::vector < std::pair <std::string, PropertiesValueHolder > > nested_definitions;
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
				static void parse ( const Core::Properties& properties, std::vector< std::pair< std::string, PropertiesValueHolder > > const &rules )
				{
					for ( auto & rule : rules )
					{
						const_cast<PropertiesValueHolder&> ( rule.second ).setOutputValue ( properties, rule.first );
					}
				}
		};
	};
}


