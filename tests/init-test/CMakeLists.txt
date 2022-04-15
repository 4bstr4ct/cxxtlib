cmake_minimum_required(VERSION 3.3.0)
project(init-test VERSION 0.0.1 LANGUAGES C CXX)
add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		cxxtlib
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
	PRIVATE
		cxxtlib
)
