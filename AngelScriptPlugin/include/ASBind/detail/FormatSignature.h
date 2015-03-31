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
                    return as_subsystem->getTypeName<T>();
                }
        };

        template<typename T>
        struct DecoratedTypeName
        {
                std::string operator()(Behavior::AngelScriptSubsystem* as_subsystem)
                {
                        return FormattedTypeName<T>()(as_subsystem);
                }
        };

        template<typename T>
        struct DecoratedTypeName<const T&>
        {
                std::string operator()(Behavior::AngelScriptSubsystem* as_subsystem)
                {
                        return "const " + FormattedTypeName<T>()(as_subsystem) + "&";
                }
        };

        template<typename T>
        struct DecoratedTypeName<T&>
        {
                std::string operator()(Behavior::AngelScriptSubsystem* as_subsystem)
                {
                        return FormattedTypeName<T>()(as_subsystem) + "&";
                }
        };

        template<typename T>
        struct DecoratedTypeName<const T*>
        {
                std::string operator()(Behavior::AngelScriptSubsystem* as_subsystem)
                {
                        return "const " + FormattedTypeName<T>()(as_subsystem) + "*";
                }
        };

        template<typename T>
        struct DecoratedTypeName<T*>
        {
                std::string operator()(Behavior::AngelScriptSubsystem* as_subsystem)
                {
                        return FormattedTypeName<T>()(as_subsystem) + "*";
                }
        };

        template<typename Arg, typename... Args>
        struct FormattedArgumentsString
        {
                std::string operator()(Behavior::AngelScriptSubsystem* as_subsystem)
                {
                        return DecoratedTypeName<Arg>()(as_subsystem) + ", " + FormattedArgumentsString<Args...>()(as_subsystem);
                }
        };

        template<typename Arg>
        struct FormattedArgumentsString<Arg>
        {
                std::string operator()(Behavior::AngelScriptSubsystem* as_subsystem)
                {
                        return DecoratedTypeName<Arg>()(as_subsystem);
                }
        };


        template<typename RetVal, typename... Args>
        std::string format_signature(RetVal (*f)(Args...), const std::string &name, Behavior::AngelScriptSubsystem* as_subsystem)
        {
                return DecoratedTypeName<RetVal>()(as_subsystem) + " " + name + "(" + FormattedArgumentsString<Args...>()(as_subsystem) + ")";
        }

        template<typename RetVal>
        std::string format_signature(RetVal (*f)(), const std::string &name, Behavior::AngelScriptSubsystem* as_subsystem)
        {
                return DecoratedTypeName<RetVal>()(as_subsystem) + " " + name + "()";
        }

        template<typename RetVal, typename T, typename... Args>
        std::string format_member_signature(RetVal (T::*f)(Args...), const std::string &name, Behavior::AngelScriptSubsystem* as_subsystem)
        {
                return DecoratedTypeName<RetVal>()(as_subsystem) + " " + FormattedTypeName<T>()(as_subsystem) + "::" + name + "(" + FormattedArgumentsString<Args...>()(as_subsystem) + ")";
        }

        template<typename RetVal, typename T>
        std::string format_member_signature(RetVal (T::*f)(), const std::string &name, Behavior::AngelScriptSubsystem* as_subsystem)
        {
                return DecoratedTypeName<RetVal>()(as_subsystem) + " " + FormattedTypeName<T>()(as_subsystem) + "::" + name + "()";
        }
    }
}
