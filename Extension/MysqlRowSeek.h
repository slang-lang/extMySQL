
#ifndef Extensions_Mysql_MysqlRowSeek_h
#define Extensions_Mysql_MysqlRowSeek_h

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


class MysqlRowSeek : public Extensions::ExtensionMethod
{
public:
	MysqlRowSeek()
	: ExtensionMethod(0, "mysql_row_seek", Designtime::Int32Type::TYPENAME)
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
		long param_offset = (*it++).value().toInt();

		auto* myResult = mMysqlResults[param_handle];
		if ( !myResult ) {
			throw Common::Exceptions::Exception("no valid mysql result!");
		}

		*result = Runtime::Int32Type( mysql_row_seek(myResult, (MYSQL_ROW_OFFSET)param_offset) );

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
