# Copyright OpenSearch Contributors
# SPDX-License-Identifier: Apache-2.0

project(itodbc_connection)

# Source, headers, and include dirs
set(SOURCE_FILES test_odbc_connection.cpp)
include_directories(	${UT_HELPER}
						${IT_HELPER}
						${OPENSEARCHODBC_SRC}
						${VLD_SRC}  )

# Generate executable
add_executable(itodbc_connection ${SOURCE_FILES})

# Library dependencies
target_code_coverage(itodbc_connection PUBLIC AUTO ALL)
target_link_libraries(itodbc_connection sqlodbc itodbc_helper ut_helper gtest_main)
target_compile_definitions(itodbc_connection PUBLIC _UNICODE UNICODE)

