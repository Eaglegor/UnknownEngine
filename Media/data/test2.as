void init(const std::string &in name)
{
	DummyClass cls("Basic");
	DummyClass cls2("Basic2");
	cls.method1(); 
	cls.method2(cls);
	cls.method3(cls);
	cls.method4(cls);
	cls.method5(cls, 5);
	
	DummyClass cls3 = cls2.method6(cls, 4);
	
	DummyClass::method7();
}

void shutdown()
{
}
