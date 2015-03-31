DummyClass @cls;

void init(const std::string &in name)
{
	//DummyClass();
	@cls = DummyClass();
	cls.method1();
	//cls.method2(cls);
	cls.method3(cls);
	//cls.method4(cls);
	@cls = null;
	
}

void shutdown()
{
}
