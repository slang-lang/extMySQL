
#ifndef Extensions_Mysql_MysqlGetFieldName_h
#define Extensions_Mysql_MysqlGetFieldName_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Mysql {


class MysqlGetFieldName : public Extensions::ExtensionMethod
{
public:
	MysqlGetFieldName()
	: ExtensionMethod(0, "mysql_get_field_name", Designtime::StringType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("field_index", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_handle = (*it++).value().toInt();
		auto param_field_index = (*it++).value().toInt();

		auto* myResult = mMysqlResults[param_handle];
		if ( !myResult ) {
			throw Common::Exceptions::Exception("no valid result handle: " + std::to_string(param_handle));
		}

		std::string my_result;
		if ( myResult->fields[param_field_index].name ) {
			my_result = std::string(myResult->fields[param_field_index].name);
		}

		*result = Runtime::StringType(my_result);

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
