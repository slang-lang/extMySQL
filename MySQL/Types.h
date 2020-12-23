
#ifndef Extensions_Mysql_Types_h
#define Extensions_Mysql_Types_h


// Library includes
#include <map>
#include <mysql.h>

// Project includes

// Forward declarations

// Namespace declarations


namespace Mysql {


typedef std::map<int /*connection handle*/, MYSQL*> MysqlConnectionMap;
typedef std::map<int /*result handle*/, MYSQL_RES*> MysqlResultMap;

extern MysqlConnectionMap mMysqlConnections;
extern int mNumMysqlConnections;

extern MysqlResultMap mMysqlResults;
extern int mNumMysqlResults;


}


#endif
