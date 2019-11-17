//数字配置类
#include "framework.h"
//宏定义set.get
#define ATTRIBUTE_MEMBER_FUNC(argType, arg)\
	public:\
	void set_##arg(const argType& v) {\
	arg = v;\
	}\
	argType get_##arg() {\
	return arg;\
	}

class  DigitalConfig
{
public:
	 DigitalConfig();
	~ DigitalConfig();
	ATTRIBUTE_MEMBER_FUNC(int, digital);
	ATTRIBUTE_MEMBER_FUNC(int, digitalSize);
	ATTRIBUTE_MEMBER_FUNC(int, digitalColor);
	ATTRIBUTE_MEMBER_FUNC(HBRUSH, digitalBk);
	
private:
	int digital;
	int digitalSize;
	int digitalColor;
	HBRUSH digitalBk;


};

 
