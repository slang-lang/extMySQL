
#ifndef Extensions_Mysql_MysqlStat_h
#define Extensions_Mysql_MysqlStat_h


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


class MysqlStat : public Extensions::ExtensionMethod
{
public:
	MysqlStat()
	: ExtensionMethod(0, "mysql_stat", Designtime::StringType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			int param_handle = (*it++).value().toInt();

			MYSQL *myConn = mMysqlConnections[param_handle];

			const char* mysql_result = mysql_stat(myConn);

			*result = Runtime::StringType(
				mysql_result ? std::string(mysql_result) : ""
			);
		}
		catch ( std::exception &e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringType::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringType(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
