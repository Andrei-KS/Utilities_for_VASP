# CMakeList.txt : CMake project for VASP_utility_Cpp, include source and define
# @author Andrei-KS
#
cmake_minimum_required (VERSION 3.8)

project(VASP_Utility_Cpp)

set(CMAKE_CXX_STANDARD 11)
enable_testing()
set(CTEST_PROJECT_NAME "VASP_Utility_Cpp")
set(CTEST_NIGHTLY_START_TIME "01:00:00 UTC")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_BUILD")

# connecting the necessary modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/_cmake")
include(CreatLibFromFiles)
include(CreatTestForLib)
include(CopyFolder)


###
# block of create libs
###

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	# create UTest lib
	# setting arguments for a function  CreatPackageFromFiles
	set(NameLib "LmyUTest")
	set(prefixDirectory)
	set(ListPathToInclude)
	set(ListPathToSrc)
	set(ListNamesSRCfiles)
	set(ListPathToLibs)

	set(prefixDirectory "_lib/UTest")
	List(APPEND ListPathToInclude 
 		"${prefixDirectory}/include"
 		)

	List(APPEND ListPathToSrc 
		"${prefixDirectory}/src"
		)

	List(APPEND ListNamesSRCfiles
		)

	List(APPEND ListPathToLibs
		)
	CreatLibFromFiles(${NameLib})
endif()

# create StringProcessingUtilits lib
# setting arguments for a function  CreatPackageFromFiles
set(NameLib "StringProcessingUtilits")
set(prefixDirectory)
set(ListPathToInclude)
set(ListPathToSrc)
set(ListNamesSRCfiles)
set(ListPathToLibs)

set(prefixDirectory "_lib/StringProcessingUtilits")
List(APPEND ListPathToInclude 
 	"${prefixDirectory}/include"
 	)

List(APPEND ListPathToSrc 
	"${prefixDirectory}/src"
	)

List(APPEND ListNamesSRCfiles
	)

List(APPEND ListPathToLibs
	)
CreatLibFromFiles(${NameLib})

#add test
if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set(NameTest UTestStringProcessingUtilits)
	set(ListPathToTestSrc)
	set(ListNamesTestSRCfiles)
	List(APPEND ListPathToInclude
		"_lib/UTest/include"
		)
	List(APPEND ListPathToTestSrc
		"${prefixDirectory}/test"
		)
	List(APPEND ListNamesTestSRCfiles
		"UTestSplitStringToVector"
		)

	List(APPEND ListPathToLibs
		"${PROJECT_BINARY_DIR}/${NameLib}"
		"${PROJECT_BINARY_DIR}/LmyUTest"
		)
	CreatTestForLib(${NameTest})
endif()

# create CLI lib
# setting arguments for a function  CreatPackageFromFiles
set(NameLib "CLI")
set(prefixDirectory)
set(ListPathToInclude)
set(ListPathToSrc)
set(ListNamesSRCfiles)
set(ListPathToLibs)

set(prefixDirectory "_lib/CLI")
List(APPEND ListPathToInclude 
 	"${prefixDirectory}/include"
 	)

List(APPEND ListPathToSrc 
	"${prefixDirectory}/src"
	)

List(APPEND ListNamesSRCfiles
	)

List(APPEND ListPathToLibs
	)
CreatLibFromFiles(${NameLib})

# create CLI lib
# setting arguments for a function  CreatPackageFromFiles
set(NameLib "FileProcessing")
set(prefixDirectory)
set(ListPathToInclude)
set(ListPathToSrc)
set(ListNamesSRCfiles)
set(ListPathToLibs)

set(prefixDirectory "_lib/FileProcessing")
List(APPEND ListPathToInclude 
 	"${prefixDirectory}/include"
	 "_lib/CLI/include"
 	)

List(APPEND ListPathToSrc 
	"${prefixDirectory}/src"
	)

List(APPEND ListNamesSRCfiles
	)

List(APPEND ListPathToLibs
	"${PROJECT_BINARY_DIR}/CLI"
	)
CreatLibFromFiles(${NameLib})

###
# end block of create libs
###


# include header to main function
include_directories(
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/_lib/CLI/include"
	"${PROJECT_SOURCE_DIR}/_lib/FileProcessing/include"
	"${PROJECT_SOURCE_DIR}/_lib/StringProcessingUtilits/include"
)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "main.cpp")



if(CMAKE_BUILD_TYPE STREQUAL Debug)
	if(NOT EXISTS "${PROJECT_BINARY_DIR}/exempl")
		file(WRITE "${PROJECT_BINARY_DIR}/exempl" "IS EMPTY")
	endif()
	CopyFolder("${PROJECT_SOURCE_DIR}/exemple" "${PROJECT_BINARY_DIR}/exemple")
endif()

target_link_libraries(${PROJECT_NAME} 
	PRIVATE "${PROJECT_BINARY_DIR}/CLI.lib"
	PRIVATE "${PROJECT_BINARY_DIR}/FileProcessing.lib"
	PRIVATE "${PROJECT_BINARY_DIR}/StringProcessingUtilits.lib"
	)