
#ifndef Extensions_Mysql_MysqlGetClientInfo_h
#define Extensions_Mysql_MysqlGetClientInfo_h


// Library includes
#include <mysql.h>

// Project includes
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Mysql {


class MysqlGetClientInfo : public Extensions::ExtensionMethod
{
public:
	MysqlGetClientInfo()
	: ExtensionMethod(0, "mysql_get_client_info", Designtime::StringType::TYPENAME)
	{
		ParameterList params;

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& /*params*/, Runtime::Object* result, const Token& token)
	{
		try {
			*result = Runtime::StringType(
				(std::string)mysql_get_client_info()
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
