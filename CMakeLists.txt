cmake_minimum_required(VERSION 3.7.2)  # CMake version check

set (PROJECT cgi_script.cgi)

project(${PROJECT})         
set(CMAKE_CXX_STANDARD 11)

set (HEADERS
			session.h
			cgi_class.h
			DB.h
			str_methods.h)

set(SOURCE_FILES 
			cgi.cpp
			session.cpp
			cgi_class.cpp
			DB.cpp
			str_methods.cpp)
add_executable (${PROJECT} ${SOURCE_FILES} ${HEADERS})

set_target_properties(${PROJECT} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT} cpp_redis)
target_link_libraries(${PROJECT} tacopie)
target_link_libraries(${PROJECT} pthread)
