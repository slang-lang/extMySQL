
#ifndef Extensions_Mysql_MysqlFetchRow_h
#define Extensions_Mysql_MysqlFetchRow_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/BoolType.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/BoolType.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Mysql {


class MysqlFetchRow : public Extensions::ExtensionMethod
{
public:
	MysqlFetchRow( const std::string& overrideName = "mysql_fetch_row", Slang::LanguageFeatureState::E languageFeatureState = Slang::LanguageFeatureState::Stable )
	: ExtensionMethod( 0, overrideName, Designtime::BoolType::TYPENAME, Mutability::Const, MemoryLayout::Static, languageFeatureState )
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

			MYSQL_RES *myResult = mMysqlResults[param_handle];
			if ( !myResult ) {
				throw Common::Exceptions::Exception("no valid mysql result handle: " + std::to_string(param_handle));
			}

			MYSQL_ROW myRow = mysql_fetch_row(myResult);

			*result = Runtime::BoolType(myRow != NULL);
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
