class IPropertyLink;

struct IProperty()
{
	virtual ~IProperty(){}
	virtual const char* getName() = 0;
	virtual IComponent* getOwner() = 0;
	virtual void addLink(IPropertyLink* link) = 0;
	virtual void removeLink(IPropertyLink* link) = 0;
}

struct IPropertyLink
{
	void ~IPropertyLink(){}
	
	virtual void onPropertyChanged(IProperty* property) = 0;
}

template<typename T>
struct PropertyLink : public IPropertyLink
{
	std::function<void (const T&)> callback;
	
	void onPropertyChanged(IProperty* property)
	{
		T* value = property.cast<T>();
		if(value == nullptr) return;
		else callback(*value);
	}
}

struct BaseProperty
{
	IPropertyTypeMetaInfo *meta_info;
	
	BaseProperty(const char* name):
	name(name)
	{}
	
	template<typename T>
	T* cast()
	{
		PropertyTypeMetaInfo<T> to_type_meta_info;
		if(meta_info->getName() == to_type_meta_info.getName())
		{
			return static_cast<T*>(getRawData());
		}
		return nullptr;
	}
	
	const char* getName()
	{
		return name.c_str();
	}
	
	private:
		std::string name;
		virtual void* getRawData() = 0;
}

template<typename T>
struct Property : public BaseProperty
{
	Property(const char* name):
	BaseProperty(name)
	{}
	
	T payload;
	
	void* getRawData()
	{
		return &payload;
	}
}

struct IPropertyTypeMetaInfo
{
	virtual ~IPropertyTypeMetaInfo(){}
	virtual const char* getName();
	virtual bool isComposite();
}

template<typename T>
struct PropertyTypeMetaInfo<T> : public IPropertyTypeMetaInfo
{
	const char* getName(){return "<UnknownPropertyType>";}
	bool isComposite(){return false;}
}

template<>
struct PropertyTypeMetaInfo<float> : public PropertyTypeMetaInfoBase
{
	const char* getName(){return "float";}
	bool isComposite(){return false;}
}

template<>
struct PropertyTypeMetaInfo<Math::Vector3> : public PropertyTypeMetaInfoBase
{
	const char* getName(){return "Math::Vector3";}
	bool isComposite(){return true;}
	
	PropertyTypeMetaInfo<float> x;
	PropertyTypeMetaInfo<float> y;
	PropertyTypeMetaInfo<float> z;
	
	PropertyTypeMetaInfo()
	{
		FIELD(&x, "x",
			[](Math::Vector3& vector3, const float &x){vector3.setX(x);}
			[](Math::Vector3& vector3){vector3.getX(x);}
			);
			
		FIELD(&y, "y",
			[](Math::Vector3& vector3, const float &y){vector3.setY(y);}
			[](Math::Vector3& vector3){vector3.getY(y);}
			);
			
		FIELD(&z, "z",
			[](Math::Vector3& vector3, const float &z){vector3.setZ(z);}
			[](Math::Vector3& vector3){vector3.getZ(z);}
			);
	}
	
}

template<>
struct PropertyTypeMetaInfo<Math::Quaternion> : public PropertyTypeMetaInfoBase
{
	const char* getName(){return "Math::Quaternion";}
	bool isComposite(){return true;}
	
	PropertyTypeMetaInfo<float> x;
	PropertyTypeMetaInfo<float> y;
	PropertyTypeMetaInfo<float> z;
	PropertyTypeMetaInfo<float> w;
	
	PropertyTypeMetaInfo()
	{
		FIELD(&x, "x",
			[](Math::Quaternion& quat, const float &x){quat.setX(x);}
			[](Math::Quaternion& quat){quat.getX(x);}
			);
			
		FIELD(&y, "y",
			[](Math::Quaternion& quat, const float &y){quat.setY(y);}
			[](Math::Quaternion& quat){quat.getY(y);}
			);
			
		FIELD(&z, "z",
			[](Math::Quaternion& quat, const float &z){quat.setZ(z);}
			[](Math::Quaternion& quat){quat.getZ(z);}
			);
		
		FIELD(&w, "w",
			[](Math::Quaternion& quat, const float &w){quat.setW(w);}
			[](Math::Quaternion& quat){quat.getW(w);}
			);
	}
	
}

template<>
struct PropertyTypeMetaInfo<Math::Transform> : public PropertyTypeMetaInfoBase
{
	const char* getName(){return "Math::Transform";}	
	bool isComposite(){return true;}
	
	PropertyTypeMetaInfo<Math::Vector3> position;
	PropertyTypeMetaInfo<Math::Quaternion> orientation;
	
	PropertyTypeMetaInfo()
	{
		FIELD(&position, "position",
			[](Math::Transform& transform, const Math::Vector3 &position){transform.setPosition(position);}
			[](Math::Transform& transform){transform.getPosition();}
			);
			
		FIELD(&orientation, "orientation",
			[](Math::Transform& transform, const Math::Quaternion &orientation){transform.setOrientation(orientation);}
			[](Math::Transform& transform){transform.getOrientation();}
			);
	}
}

class RenderableComponent : public BaseComponent
{
	public:
		RenderableComponent(const char* name):
		BaseComponent(name)
		{
			registerProperty(current_transform, "current_transform");
			
			registerPropertyLinkHandler(std::bind(&RenderableComponent::setTransform, this, std::placeholders::_1), "setTransform");
		}
	
		void setTransform(const Math::Transform& transform);
	
	private:
		Property<Math::Transform> current_transform;
}