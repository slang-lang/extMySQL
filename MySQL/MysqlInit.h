
#ifndef Extensions_Mysql_MysqlInit_h
#define Extensions_Mysql_MysqlInit_h


// Library include

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Mysql {


class MysqlInit: public Extensions::ExtensionMethod
{
public:
	MysqlInit()
	: ExtensionMethod(0, "mysql_init", Designtime::Int32Type::TYPENAME, Mutability::Modify)
	{
		ParameterList params;

		setSignature(params);
	}


	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& /*params*/, Runtime::Object* result, const Token& token)
	{
		try {
			MYSQL *myHandle = mysql_init(0);

			int my_result = 0;
			if ( myHandle ) {
				my_result = ++mNumMysqlConnections;
				mMysqlConnections.insert(std::make_pair(my_result, myHandle));
			}

			*result = Runtime::Int32Type(my_result);
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
