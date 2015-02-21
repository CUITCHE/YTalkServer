#ifndef DEFS_H
#define DEFS_H
/********************************************************************
	created:	2015/02/21
	created:	21:2:2015   14:11
	file base:	defs
	author:		CHE
	
	purpose:	全局定义
*********************************************************************/
#define SETTER(Type,variable, name) void set##name(const Type val){this->variable = val;}
#define GETTER(Type,variable,name) const Type get##name()const{return variable;}
#define GET_SETTER(Type,variable, name)\
	SETTER(Type,variable, name)\
	GETTER(Type,variable,name)
#define QT_MOC_GET_SETTER(Type, variable, name)\
	GET_SETTER(Type, variable, name)\
	Q_PROPERTY(Type variable READ get##name WRITE set##name)

//把定义变量和宏声明结合在一起，
//呃，我是个大懒鬼-_-...
#define QT_MOC_MINE_DEFINITION(Type, variable, name)\
	private:Type variable;\
	public: QT_MOC_GET_SETTER(Type, variable, name)\


//在类声明处书写，称为prepare模式，它适用于有数据成员
//但不需要编译器或编码人员管理类对象的生命周期。
//此模式下，须将checkInstance()负责生成唯一实例。
//类的构造函数和析构函数的控制权限设为非public。
//instance()返回类对象。
//deleteInstance()删除对象。
//可以根据需要，自定义他们的实现，也可以在类的定义处。
//调用PREPARE_INSTANCE_DEFINITION宏实现默认定义。
#define PREPARE_INSTANCE_DECLARE(Class) static Class *g_instance;\
	static void checkInstance();\
	public: static Class* instance();static void deleteInstance();\

#define PREPARE_INSTANCE_DEFINITION(Class) Class* Class::g_instance=nullptr; \
	void Class::checkInstance(){if (g_instance == nullptr){g_instance = new Class;}}\
	Class* Class::instance(){ checkInstance(); return g_instance; }\
	void Class::deleteInstance(){ delete g_instance; g_instance = nullptr; }\

//获取指定类的实例，返回ins指针变量
#define GET_INSTANCE(Class) Class* ins = Class::instance()
//丢弃指定类的实例，在需要的时候，再生成新的实例
#define POP_INSTANCE(Class) Class::deleteInstance()
#endif // DEFS_H
