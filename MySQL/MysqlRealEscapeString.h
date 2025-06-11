
#ifndef Extensions_Mysql_MysqlRealEscapeString_h
#define Extensions_Mysql_MysqlRealEscapeString_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Mysql {


class MysqlRealEscapeString : public Extensions::ExtensionMethod
{
public:
	MysqlRealEscapeString()
	: ExtensionMethod(0, "mysql_real_escape_string", Designtime::StringType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("from", Designtime::StringType::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		int param_handle = (*it++).value().toInt();
		std::string param_from = (*it++).value().toStdString();

		MYSQL *myConn = mMysqlConnections[param_handle];
		if ( !myConn ) {
			throw Common::Exceptions::Exception("no valid mysql connection handle: " + std::to_string(param_handle));
		}

		char* to = new char[(param_from.length() * 2) + 1];

		mysql_real_escape_string(myConn, to, param_from.c_str(), param_from.length());

		*result = Runtime::StringType(std::string(to));

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
