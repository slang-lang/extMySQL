
#ifndef Extensions_Mysql_MysqlErrno_h
#define Extensions_Mysql_MysqlErrno_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Mysql {


class MysqlErrno : public Extensions::ExtensionMethod
{
public:
	MysqlErrno()
	: ExtensionMethod(0, "mysql_errno", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_handle = (*it++).value().toInt();

		auto* myConn = mMysqlConnections[param_handle];
		if ( !myConn ) {
			throw Common::Exceptions::Exception("no valid mysql connection handle: " + std::to_string(param_handle));
		}

		*result = Runtime::Int32Type( static_cast<int>( mysql_errno(myConn) ) );

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
