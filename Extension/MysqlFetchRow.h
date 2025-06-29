
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

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_handle = (*it++).value().toInt();

		auto* myResult = mMysqlResults[param_handle];
		if ( !myResult ) {
			throw Common::Exceptions::Exception("no valid mysql result handle: " + std::to_string(param_handle));
		}

		MYSQL_ROW myRow = mysql_fetch_row(myResult);

		*result = Runtime::BoolType(myRow != NULL);

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
