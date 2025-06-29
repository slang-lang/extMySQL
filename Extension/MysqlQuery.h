
#ifndef Extensions_Mysql_MysqlQuery_h
#define Extensions_Mysql_MysqlQuery_h


// Library include

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace Mysql {


class MysqlQuery: public Extensions::ExtensionMethod
{
public:
	MysqlQuery()
	: ExtensionMethod(0, "mysql_query", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("query", Designtime::StringType::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_handle = (*it++).value().toInt();
		std::string query = (*it++).value().toStdString();

		auto* myConn = mMysqlConnections[param_handle];
		if ( !myConn ) {
			throw Common::Exceptions::Exception("no valid mysql connection handle: " + std::to_string(param_handle));
		}

		*result = Runtime::Int32Type( mysql_query(myConn, query.c_str()) );

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
