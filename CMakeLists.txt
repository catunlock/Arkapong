#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.8)
project(Arkapong)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

# Setting the cmake modules dir
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

#Checking for a c++11 compiler
include(CXX11)
check_for_cxx11_compiler(CPP_11)
if(CPP_11)
	enable_cxx11()
endif()

# Set version information in a config.h file
set(Arkapong_VERSION_MAJOR 1)
set(Arkapong_VERSION_MINOR 0)
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)
include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(SOURCE_FILES 
	src/Main.cpp
	src/Game.cpp
)
	
set(HEADER_FILES
	src/Ball.h
	src/Brick.h
	src/constants.h
	src/Map.h
	src/Paddle.h
	src/Game.h
)

set(EXECUTABLE_NAME "Arkapong")
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES} ${HEADER_FILES})


# Detect and add SFML
set( SFML_ROOT "C:/SFML" CACHE FILEPATH "Path to the SFML directory")

# Find any version 2.X of SFML
# See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

# Copy the resources files
file( COPY resources DESTINATION ${PROJECT_BINARY_DIR} )

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${myproject_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${myproject_VERSION_MINOR}")
include(CPack)