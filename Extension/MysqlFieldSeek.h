
#ifndef Extensions_Mysql_MysqlFieldSeek_h
#define Extensions_Mysql_MysqlFieldSeek_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Mysql {


class MysqlFieldSeek : public Extensions::ExtensionMethod
{
public:
	MysqlFieldSeek()
	: ExtensionMethod(0, "mysql_field_seek", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("offset", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_handle = (*it++).value().toInt();
		auto param_offset = (*it++).value().toInt();

		auto* myResult = mMysqlResults[param_handle];
		if ( !myResult ) {
			throw Common::Exceptions::Exception("no valid mysql result!");
		}

		*result = Runtime::Int32Type( static_cast<int>( mysql_field_seek(myResult, (MYSQL_FIELD_OFFSET) param_offset) ) );

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
