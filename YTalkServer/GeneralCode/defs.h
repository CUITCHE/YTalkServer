#ifndef DEFS_H
#define DEFS_H

#define SETTER(Type,variable, name) void set##name(const Type val){this->variable = val;}
#define GETTER(Type,variable,name) const Type get##name()const{return variable;}
#define GET_SETTER(Type,variable, name)\
	SETTER(Type,variable, name)\
	GETTER(Type,variable,name)
#define QT_MOC_GET_SETTER(Type, variable, name)\
	GET_SETTER(Type, variable, name)\
	Q_PROPERTY(Type variable READ get##name WRITE set##name)


#endif // DEFS_H
