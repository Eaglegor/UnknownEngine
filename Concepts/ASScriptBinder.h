#include <iostream>

#include <string>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

static std::unordered_map<std::type_index, std::string> bindings;

template<typename T>
struct FormattedTypeName
{
	std::string operator()()
	{
		auto iter = bindings.find(std::type_index(typeid(T)));
		if(iter != bindings.end())
		{
			return iter->second;
		}
		return "???";
	}
};

template<typename T>
struct DecoratedTypeName
{
	std::string operator()()
	{
		return FormattedTypeName<T>()();
	}
};

template<typename T>
struct DecoratedTypeName<const T&>
{
	std::string operator()()
	{
		return "const " + FormattedTypeName<T>()() + "&";
	}
};

template<typename T>
struct DecoratedTypeName<T&>
{
	std::string operator()()
	{
		return FormattedTypeName<T>()() + "&";
	}
};

template<typename T>
struct DecoratedTypeName<const T*>
{
	std::string operator()()
	{
		return "const " + FormattedTypeName<T>()() + "*";
	}
};

template<typename T>
struct DecoratedTypeName<T*>
{
	std::string operator()()
	{
		return FormattedTypeName<T>()() + "*";
	}
};

template<typename Arg, typename... Args>
struct FormattedArgumentsString
{
	std::string operator()()
	{
		return DecoratedTypeName<Arg>()() + ", " + FormattedArgumentsString<Args...>()();
	}
};

template<typename Arg>
struct FormattedArgumentsString<Arg>
{
	std::string operator()()
	{
		return DecoratedTypeName<Arg>()();
	}
};


template<typename RetVal, typename... Args>
std::string format_signature(RetVal (*f)(Args...), const std::string &name)
{
	return DecoratedTypeName<RetVal>()() + " " + name + "(" + FormattedArgumentsString<Args...>()() + ")";
}

template<typename RetVal>
std::string format_signature(RetVal (*f)(), const std::string &name)
{
	return DecoratedTypeName<RetVal>()() + " " + name + "()";
}

template<typename RetVal, typename T, typename... Args>
std::string format_member_signature(RetVal (T::*f)(Args...), const std::string &name)
{
	return DecoratedTypeName<RetVal>()() + " " + FormattedTypeName<T>()() + "::" + name + "(" + FormattedArgumentsString<Args...>()() + ")";
}

template<typename RetVal, typename T>
std::string format_member_signature(RetVal (T::*f)(), const std::string &name)
{
	return DecoratedTypeName<RetVal>()() + " " + FormattedTypeName<T>()() + "::" + name + "()";
}

template<typename T>
void bind_type_name(const std::string &name)
{
	bindings.emplace(std::type_index(typeid(T)), name);
};

class A
{
public:
	int func1(const char* a){};
	int func2(const char* b){};
};

class B
{
public:
	A* getValue(){};
};

int f1(int a, float b)
{
	
}

int f2(int& a)
{
	
}

int f3(int a, const float& b)
{
	
}

float f4(const A& a)
{
	
}

B& f5(A& a, B b)
{
	
}

B& f6(const A* a, B* b)
{
	
}

int f7(const int* a, float* b)
{
	
}

template<typename T>
struct ASClass
{
	ASClass(const std::string &name):
	name(name)
	{
		bind_type_name<T>(name);
	}
	
	template<typename Retval, typename... Args>
	ASClass& method(Retval (T::*f)(Args...), const std::string &name)
	{
		std::cout << "Binding: " + format_member_signature<Retval, T, Args...>(f, name) << std::endl;
		engine->RegisterObjectMethod(name, format_signature<Retval, Args...>(), asSMethodPtr<sizeof(void (T::*)())>::Convert(AS_METHOD_AMBIGUITY_CAST(Retval (T::*)p)(f)), asCALL_THISCALL);
		return *this;
	}
	
	template<typename Retval, typename... Args>
	ASClass& static_method(Retval (T::*f)(Args...), const std::string &name)
	{
		
	}
	
	template<typename... Args>
	ASClass& constructor()
	{
		engine->RegisterObjectBehaviour(name, asBEHAVE_FACTORY, name + "@ f(" + FormattedArgumentsString<Args...>()() + ")", asFUNCTION(ASClass<T>::defaultFactoryFunc), asCALL_CDECL);
	}
	
private:
	template<typename... Args>
	static T* defaultFactoryFunc(Args&& ...args)
	{
		return new T(std::forward<Args>(args)...);
	}

	std::string name;
	IASScriptEngine* engine;
	
};

int main(int argc, char **argv) {
	
	bind_type_name<int>("int");
	bind_type_name<float>("float");
	bind_type_name<char>("char");
	
	ASClass<A>("A")
	.method(&A::func1, "func1")
	.method(&A::func2, "func2");
	
	ASClass<B>("B")
	.method(&B::getValue, "getValue");
	
	std::cout << "These are function signatures:" << std::endl;
	std::cout << format_signature(f1, "f1") << std::endl;
	std::cout << format_signature(f2, "f2") << std::endl;
	std::cout << format_signature(f3, "f3") << std::endl;
	std::cout << format_signature(f4, "f4") << std::endl;
	std::cout << format_signature(f5, "f5") << std::endl;
	std::cout << format_signature(f6, "f6") << std::endl;
	std::cout << format_signature(f7, "f7") << std::endl;
	return 0;
}
