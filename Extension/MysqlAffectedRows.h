
#ifndef Extensions_Mysql_MysqlAffectedRows_h
#define Extensions_Mysql_MysqlAffectedRows_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include "Types.h"


// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Mysql {


class MysqlAffectedRows : public Extensions::ExtensionMethod
{
public:
	MysqlAffectedRows()
	: ExtensionMethod(0, "mysql_affected_rows", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		int param_handle = (*it++).value().toInt();

		MYSQL *myConn = mMysqlConnections[param_handle];
		if ( !myConn ) {
			throw Common::Exceptions::Exception("no valid mysql connection handle: " + std::to_string(param_handle));
		}

		*result = Runtime::Int32Type( static_cast<int>( mysql_affected_rows( myConn ) ) );

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
