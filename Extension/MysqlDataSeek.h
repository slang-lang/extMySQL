
#ifndef Extensions_Mysql_MysqlDataSeek_h
#define Extensions_Mysql_MysqlDataSeek_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/VoidType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/BuildInTypes/VoidType.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include "Types.h"

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace Mysql {


class MysqlDataSeek : public Extensions::ExtensionMethod
{
public:
	MysqlDataSeek()
	: ExtensionMethod(0, "mysql_data_seek", Designtime::VoidType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("rowIdx", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* /*result*/ )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		int param_handle = (*it++).value().toInt();
		int param_rowIdx = (*it++).value().toInt();

		MYSQL_RES *myResult = mMysqlResults[param_handle];
		if ( !myResult ) {
			throw Common::Exceptions::Exception("no valid mysql result!");
		}

		mysql_data_seek(myResult, (my_ulonglong)param_rowIdx);

		return Runtime::ControlFlow::Normal;
	}
};


}


#endif
