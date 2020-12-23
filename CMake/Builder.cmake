
function(build_shared_lib target modules)

    _handle_modules_pre_linker("${modules}")

    add_library(${target} SHARED ${SOURCES} ${HEADERS})

    LIST(LENGTH DEPENDENCIES num_dependencies)
    if ( num_dependencies GREATER 0 )
        target_link_libraries(${target} ${DEPENDENCIES})
    endif()

    _handle_modules_post_linker("${modules}" ${target})

endfunction()


function(build_static_lib target modules)

    _handle_modules_pre_linker("${modules}")

    add_library(${target} STATIC ${SOURCES} ${HEADERS})

    LIST(LENGTH DEPENDENCIES num_dependencies)
    if ( num_dependencies GREATER 0 )
        target_link_libraries(${target} ${DEPENDENCIES})
    endif()

    _handle_modules_post_linker("${modules}" ${target})

endfunction()


function(build_app target modules)

    _handle_modules_pre_linker("${modules}")

    SET(CMAKE_CXX_FLAGS "-Wl,--as-needed")
    LIST(LENGTH HEADERS num_headers)

    add_executable(${target} ${SOURCES} ${HEADERS})

    # link against specified libs
    target_link_libraries(${target} ${DEPENDENCIES})

    _handle_modules_post_linker("${modules}" ${target})

endfunction()


function(_handle_modules_pre_linker modules)

    list(FIND modules "json" found)
    if ( ${found} GREATER -1 )
        _handle_pre_json()
    endif()

    list(FIND modules "mariadb" found)
    if ( ${found} GREATER -1 )
        _handle_pre_mariadb()
    endif()

    list(FIND modules "mysql" found)
    if ( ${found} GREATER -1 )
        _handle_pre_mysql()
    endif()

    list(FIND modules "slang" found)
    if ( ${found} GREATER -1 )
        _handle_pre_slang()
    endif()

    list(FIND modules "sqlite3" found)
    if ( ${found} GREATER -1 )
        _handle_pre_sqlite3()
    endif()

endfunction()


function(_handle_modules_post_linker modules target)

    list(FIND modules "json" found)
    if ( ${found} GREATER -1 )
        _handle_post_json(${target})
    endif()

    list(FIND modules "mariadb" found)
    if ( ${found} GREATER -1 )
        _handle_post_mariadb(${target})
    endif()

    list(FIND modules "mysql" found)
    if ( ${found} GREATER -1 )
        _handle_post_mysql(${target})
    endif()

    list(FIND modules "slang" found)
    if ( ${found} GREATER -1 )
        _handle_post_slang(${target})
    endif()

    list(FIND modules "sqlite3" found)
    if ( ${found} GREATER -1 )
        _handle_post_sqlite3()
    endif()

endfunction()



###############################
### APACHE

function(_apache_check_existence)

    # make sure the appropriate environment variable is set!
    if("${BUILD_APACHE_INC}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_APACHE_INC needed for mysql!")
    endif()

    if("${BUILD_APACHE_LIB}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_APACHE_LIB needed for mysql!")
    endif()

endfunction()


function(_handle_post_apache target)

    _apache_check_existence()
    #target_link_libraries(${target} mysqlclient)

endfunction()


function(_handle_pre_apache)

    _apache_check_existence()
    include_directories(${BUILD_APACHE_INC})
    link_directories(${BUILD_APACHE_LIB})

endfunction()

### APACHE
###############################


###############################
### CURL

function(_curl_check_existence)

    # make sure the appropriate environment variable is set!
    if("${BUILD_CURL_INC}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_CURL_INC needed for curl!")
    endif()

    if("${BUILD_CURL_LIB}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_CURL_LIB needed for curl!")
    endif()

endfunction()


function(_handle_post_curl target)

    _curl_check_existence()
    target_link_libraries(${target} curl)

endfunction()


function(_handle_pre_curl)

    _curl_check_existence()
    include_directories(${BUILD_CURL_INC})

endfunction()

### CURL
###############################

###############################
### JSON

function(_could_not_find_json)
    MESSAGE(STATUS "Could not find (the correct version of) Json.")
    MESSAGE(STATUS "Slang currently requires ${JSON_PACKAGE_NAME}\n")
    MESSAGE(FATAL_ERROR "You can download from ${JSON_DOWNLOAD_URL}")
endfunction()


function(_json_check_existence)

    # make sure the appropriate environment variable is set!
    if(NOT BUILD_JSON_INC)
        _could_not_find_json()
    else()

        if("${BUILD_JSON_INC}" STREQUAL "")
            MESSAGE(FATAL_ERROR "BUILD_JSON_INC needed for json!")
        endif()

        if("${BUILD_JSON_LIB}" STREQUAL "")
            MESSAGE(FATAL_ERROR "BUILD_JSON_LIB needed for json!")
        endif()

    endif()

endfunction()


function(_handle_post_json target)

    _json_check_existence()
    target_link_libraries(${target} Json)

endfunction()


function(_handle_pre_json)

    _json_check_existence()
    include_directories(${BUILD_JSON_INC})
    link_directories(${BUILD_JSON_LIB})

endfunction()

### JSON
###############################


###############################
### MARIADB

function(_mariadb_check_existence)

    # make sure the appropriate environment variable is set!
    if("${BUILD_MARIA_INC}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_MARIA_INC needed for mariadb!")
    endif()

    if("${BUILD_MARIA_LIB}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_MARIA_LIB needed for mariadb!")
    endif()

endfunction()


function(_handle_post_mariadb target)

    _mariadb_check_existence()
    target_link_libraries(${target} mariadb)

endfunction()


function(_handle_pre_mariadb)

    _mariadb_check_existence()
    include_directories(${BUILD_MARIA_INC})
    link_directories(${BUILD_MARIA_LIB})

endfunction()

### MARIADB
###############################


###############################
### MYSQL

function(_mysql_check_existence)

    # make sure the appropriate environment variable is set!
    if("${BUILD_MYSQL_INC}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_MYSQL_INC needed for mysql!")
    endif()

    if("${BUILD_MYSQL_LIB}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_MYSQL_LIB needed for mysql!")
    endif()

endfunction()


function(_handle_post_mysql target)

    _mysql_check_existence()
    target_link_libraries(${target} mysqlclient)

endfunction()


function(_handle_pre_mysql)

    _mysql_check_existence()
    include_directories(${BUILD_MYSQL_INC})
    link_directories(${BUILD_MYSQL_LIB})

endfunction()

### MYSQL
###############################


###############################
### Slang

function(_slang_check_existence)

    # make sure the appropriate environment variable is set!
    if("${BUILD_SLANG_INC}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_SLANG_INC needed for Slang!")
    endif()

    if("${BUILD_SLANG_LIB}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_SLANG_LIB needed for Slang!")
    endif()

endfunction()


function(_handle_post_slang target)

    _slang_check_existence()
    target_link_libraries(${target} UtilsTools)
    target_link_libraries(${target} Utils)
    target_link_libraries(${target} CoreVirtualMachine)
    target_link_libraries(${target} CoreRuntimeBuildInTypes)
    target_link_libraries(${target} CoreRuntime)
    target_link_libraries(${target} CoreExtensions)
    target_link_libraries(${target} CoreDesigntimeParser)
    target_link_libraries(${target} CoreDesigntimeBuildInTypes)
    target_link_libraries(${target} CoreDesigntime)
    target_link_libraries(${target} CoreDebugger)
    target_link_libraries(${target} CoreCommon)
    target_link_libraries(${target} CoreAttributes)
    target_link_libraries(${target} CoreAST)
    target_link_libraries(${target} Core)

endfunction()


function(_handle_pre_slang)

    _slang_check_existence()
    include_directories(${BUILD_SLANG_INC})
    link_directories(${BUILD_SLANG_LIB})

endfunction()

### Slang
###############################

###############################
### sqlite3

function(_sqlite3_check_existence)

    # make sure the appropriate environment variable is set!
    if("${BUILD_SQLITE3_INC}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_SQLITE3_INC needed for sqlite3!")
    endif()

    if("${BUILD_SQLITE3_LIB}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_SQLITE3_LIB needed for sqlite3!")
    endif()

endfunction()


function(_handle_post_sqlite3 target)

    _sqlite3_check_existence()
    target_link_libraries(${target} sqlite)

endfunction()


function(_handle_pre_sqlite3)

    _sqlite3_check_existence()
    include_directories(${BUILD_SQLITE3_INC})
    link_directories(${BUILD_SQLITE3_LIB})

endfunction()

### sqlite3
###############################

