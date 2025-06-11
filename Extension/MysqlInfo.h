
#ifndef Extensions_Mysql_MysqlInfo_h
#define Extensions_Mysql_MysqlInfo_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Mysql {


class MysqlInfo : public Extensions::ExtensionMethod
{
public:
	MysqlInfo()
	: ExtensionMethod(0, "mysql_info", Designtime::StringType::TYPENAME)
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

		std::string my_result;

		const char* my_info = mysql_info(myConn);
		if ( my_info ) {
			my_result = std::string(my_info);
		}

		*result = Runtime::StringType(my_result);

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
