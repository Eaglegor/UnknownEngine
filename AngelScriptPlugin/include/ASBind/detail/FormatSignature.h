#pragma once

#include <string>
#include <AngelScriptSubsystem.h>

namespace UnknownEngine
{
    namespace ASBind
    {
        template<typename T>
        struct FormattedTypeName
        {
                std::string operator()(Behavior::AngelScriptSubsystem* as_subsystem)
                {
					return as_subsystem->getTypeInfo<T>().name;
                }
        };

		enum class DecorationMode
		{
			RETVAL,
			ARGUMENT
		};

        template<typename T>
        struct DecoratedTypeName
        {
				std::string operator()(Behavior::AngelScriptSubsystem* as_subsystem, DecorationMode decoration_mode)
                {
                        return FormattedTypeName<T>()(as_subsystem);
                }
        };

        template<typename T>
        struct DecoratedTypeName<const T&>
        {
				std::string operator()(Behavior::AngelScriptSubsystem* as_subsystem, DecorationMode decoration_mode)
                {
					switch(decoration_mode)
					{
						case DecorationMode::ARGUMENT:
							{
								return "const " + FormattedTypeName<T>()(as_subsystem) + "&in";
							}
						case DecorationMode::RETVAL:
						{
								return "const " + FormattedTypeName<T>()(as_subsystem) + "&";
						}
					}

                }
        };

        template<typename T>
        struct DecoratedTypeName<T&>
        {
				std::string operator()(Behavior::AngelScriptSubsystem* as_subsystem, DecorationMode decoration_mode)
                {
					switch(decoration_mode)
					{
						case DecorationMode::ARGUMENT:
							{
								return FormattedTypeName<T>()(as_subsystem) + "&out";
							}
						case DecorationMode::RETVAL:
							{
								return FormattedTypeName<T>()(as_subsystem) + "&";
							}
					}
                }
        };

        template<typename T>
        struct DecoratedTypeName<const T*>
        {
				std::string operator()(Behavior::AngelScriptSubsystem* as_subsystem, DecorationMode decoration_mode)
                {
					switch(as_subsystem->getTypeInfo<T>().type)
					{
						case ClassType::REF_TYPE:
							{
								return "const " + FormattedTypeName<T>()(as_subsystem) + "@+";
							}
						case ClassType::VALUE_TYPE:
							{
								switch(decoration_mode)
								{
									case DecorationMode::ARGUMENT:
										{
											return "const " + FormattedTypeName<T>()(as_subsystem) + "&in";
										}
									case DecorationMode::RETVAL:
										{
											return "const " + FormattedTypeName<T>()(as_subsystem) + "&";
										}
								}
							}
					}
                }
        };

        template<typename T>
        struct DecoratedTypeName<T*>
        {
				std::string operator()(Behavior::AngelScriptSubsystem* as_subsystem, DecorationMode decoration_mode)
                {
					switch(as_subsystem->getTypeInfo<T>().type)
					{
						case ClassType::REF_TYPE:
							{
								return FormattedTypeName<T>()(as_subsystem) + "@+";
							}
						case ClassType::VALUE_TYPE:
							{
								switch(decoration_mode)
								{
									case DecorationMode::ARGUMENT:
										{
											return "const " + FormattedTypeName<T>()(as_subsystem) + "&out";
										}
									case DecorationMode::RETVAL:
										{
											return "const " + FormattedTypeName<T>()(as_subsystem) + "&";
										}
								}
							}
					}

					return FormattedTypeName<T>()(as_subsystem) + "@+";
                }
        };

        template<typename Arg, typename... Args>
        struct FormattedArgumentsString
        {
                std::string operator()(Behavior::AngelScriptSubsystem* as_subsystem)
                {
						return DecoratedTypeName<Arg>()(as_subsystem, DecorationMode::ARGUMENT) + ", " + FormattedArgumentsString<Args...>()(as_subsystem);
                }
        };

        template<typename Arg>
        struct FormattedArgumentsString<Arg>
        {
                std::string operator()(Behavior::AngelScriptSubsystem* as_subsystem)
                {
						return DecoratedTypeName<Arg>()(as_subsystem, DecorationMode::ARGUMENT);
                }
        };

        template<typename RetVal, typename... Args>
        std::string format_signature(RetVal (*f)(Args...), const std::string &name, Behavior::AngelScriptSubsystem* as_subsystem)
        {
				return DecoratedTypeName<RetVal>()(as_subsystem, DecorationMode::RETVAL) + " " + name + "(" + FormattedArgumentsString<Args...>()(as_subsystem) + ")";
        }

        template<typename RetVal>
        std::string format_signature(RetVal (*f)(), const std::string &name, Behavior::AngelScriptSubsystem* as_subsystem)
        {
				return DecoratedTypeName<RetVal>()(as_subsystem, DecorationMode::RETVAL) + " " + name + "()";
        }

        template<typename RetVal, typename T, typename... Args>
        std::string format_member_signature(RetVal (T::*f)(Args...), const std::string &name, Behavior::AngelScriptSubsystem* as_subsystem)
        {
				return DecoratedTypeName<RetVal>()(as_subsystem, DecorationMode::RETVAL) + " " + name + "(" + FormattedArgumentsString<Args...>()(as_subsystem) + ")";
        }

        template<typename RetVal, typename T>
        std::string format_member_signature(RetVal (T::*f)(), const std::string &name, Behavior::AngelScriptSubsystem* as_subsystem)
        {
				return DecoratedTypeName<RetVal>()(as_subsystem, DecorationMode::RETVAL) + " " + name + "()";
        }
    }
}
