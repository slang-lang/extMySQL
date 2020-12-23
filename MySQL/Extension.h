
#ifndef Mysql_Extension_h
#define Mysql_Extension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Mysql {


class Extension : public Slang::Extensions::AExtension
{
public:
	Extension();

public:
	void initialize( Slang::IScope* scope );
	void provideMethods( Slang::Extensions::ExtensionMethods& methods );
};


}



#endif

