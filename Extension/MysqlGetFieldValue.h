
#ifndef Extensions_Mysql_MysqlGetFieldValue_h
#define Extensions_Mysql_MysqlGetFieldValue_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;



namespace Mysql {


class MysqlGetFieldValueByIndex : public Extensions::ExtensionMethod
{
public:
	MysqlGetFieldValueByIndex()
	: ExtensionMethod(0, "mysql_get_field_value", Designtime::StringType::TYPENAME)
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
		auto param_field_id = (*it++).value().toInt();

		auto* myResult = mMysqlResults[param_handle];
		if ( !myResult ) {
			throw Common::Exceptions::Exception("no valid result handle: " + std::to_string(param_handle));
		}

		MYSQL_ROW row = myResult->current_row;
		if ( !row ) {
			throw Common::Exceptions::Exception("no valid row");
		}

		std::string my_result;
		if ( row[param_field_id] ) {
			my_result = std::string(row[param_field_id]);
		}

		*result = Runtime::StringType(my_result);

		return Runtime::ControlFlow::Normal;
	}
};


class MysqlGetFieldValueByName : public Extensions::ExtensionMethod
{
public:
	MysqlGetFieldValueByName()
	: ExtensionMethod(0, "mysql_get_field_value", Designtime::StringType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("field_name", Designtime::StringType::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_handle = (*it++).value().toInt();
		auto param_field_name = (*it++).value().toStdString();

		auto* myResult = mMysqlResults[param_handle];
		if ( !myResult ) {
			throw Common::Exceptions::Exception("no valid result handle: " + std::to_string(param_handle));
		}

		bool foundField = false;
		std::string my_result;

		for ( unsigned int idx = 0; idx < myResult->field_count; ++idx ) {
			if ( !myResult->fields[idx].name ) {
				throw Common::Exceptions::Exception("invalid field name detected at field index: " + std::to_string(idx));
			}

			if ( std::string(myResult->fields[idx].name) == param_field_name ) {
				foundField = true;
				if ( myResult->current_row[idx] ) {
					my_result = std::string(myResult->current_row[idx]);
				}
			}
		}

		if ( !foundField ) {
			throw Common::Exceptions::Exception("invalid field name '" + param_field_name + "' provided!");
		}

		*result = Runtime::StringType(my_result);

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
