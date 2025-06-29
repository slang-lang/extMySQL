
#ifndef Extensions_Mysql_MysqlRealConnect_h
#define Extensions_Mysql_MysqlRealConnect_h


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
using namespace Slang;


namespace Mysql {


class MysqlRealConnect: public Extensions::ExtensionMethod
{
public:
	MysqlRealConnect()
	: ExtensionMethod(0, "mysql_real_connect", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("host", Designtime::StringType::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("port", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("user", Designtime::StringType::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("passwd", Designtime::StringType::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("db", Designtime::StringType::TYPENAME, VALUE_NONE, true));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_handle = (*it++).value().toInt();
		auto param_host = (*it++).value().toStdString();
		auto param_port = (*it++).value().toInt();
		auto param_user = (*it++).value().toStdString();
		auto param_passwd = (*it++).value().toStdString();
		auto param_db = (*it++).value().toStdString();

		std::string param_socket;
		long param_clientflag = 0;

		auto* myConn = mMysqlConnections[param_handle];
		if ( !myConn ) {
			throw Common::Exceptions::Exception("no valid mysql connection handle: " + std::to_string(param_handle));
		}

		if ( param_port == 0 ) {	// use default port
			param_port = MYSQL_PORT_DEFAULT;
		}

		myConn = mysql_real_connect(
				myConn,
				param_host.c_str(),
				param_user.c_str(),
				param_passwd.c_str(),
				param_db.c_str(),
				(unsigned int) param_port,
				param_socket.c_str(),
				(unsigned long) param_clientflag
		);

		mMysqlConnections[param_handle] = myConn;

		int my_result = 0;
		if ( myConn ) {
			my_result = param_handle;
		}

		*result = Runtime::Int32Type(my_result);

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
