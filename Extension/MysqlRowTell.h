
#ifndef Extensions_Mysql_MysqlRowTell_h
#define Extensions_Mysql_MysqlRowTell_h

// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Mysql {


class MysqlRowTell : public Extensions::ExtensionMethod
{
public:
	MysqlRowTell()
	: ExtensionMethod(0, "mysql_row_tell", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList::const_iterator it = params.begin();

		auto param_handle = (*it++).value().toInt();

		auto* myResult = mMysqlResults[param_handle];
		if ( !myResult ) {
			throw Common::Exceptions::Exception("no valid mysql result handle: " + std::to_string(param_handle));
		}

		*result = Runtime::Int32Type( mysql_row_tell( myResult ) );

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
