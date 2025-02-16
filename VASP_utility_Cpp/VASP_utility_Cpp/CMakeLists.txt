# CMakeList.txt : CMake project for Сpp, include source and define
# project specific logic here.
#

#[[----------------------------------------------------------------------------
                    Configuration cmake project
]]#----------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.8)

project(VASP_Utility_Cpp)
set(CMAKE_CXX_STANDARD 11)
enable_testing()
set(CTEST_PROJECT_NAME "VASP_Utility_Cpp")
set(CTEST_NIGHTLY_START_TIME "01:00:00 UTC")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_BUILD")

# connecting the necessary modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/_cmake")
include(create_lib_from_files)
include(create_test_for_lib)
include(copy_folder)
cmake_minimum_required (VERSION 3.8)

#[[-------------------------------------------------------------------------
                    The builder's configuration of main program
]]#-------------------------------------------------------------------------
# Setting main program
# Setting SRC
set(list_Path_To_Src)
List(APPEND list_Path_To_Src
   "${PROJECT_SOURCE_DIR}/src/main.cpp"
)

# Setting header
set(list_Path_To_Include)
List(APPEND list_Path_To_Include
   "${PROJECT_SOURCE_DIR}/include"
)

# include header to main function
include_directories(${list_Path_To_Include})

# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${list_Path_To_Src})

#[[----------------------------------------------------------------------------
                    The builder's configurations of libs
]]#----------------------------------------------------------------------------

option(SHOWE_STATUS_MESSAGE "" TRUE)
option(SHOWE_INFO_MESSAGE "" TRUE)

#[[------------------------------------
                    LmyUTest lib 
]]#------------------------------------
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  # set default setting
  set(name_Lib "LmyUTest")
  set(includes_Directories)
  set(src_Directories)
  set(src_Ignore_Names)
  set(src_Extra_Files)
  set(lib_Directories)
  set(lib_Ignore_Names)
  set(lib_Extra_Files)
  
  # setup lib
  set(prefixDirectory "_lib/UTest")
  List(APPEND includes_Directories 
    "${prefixDirectory}/include"
  )
  List(APPEND src_Directories 
    "${prefixDirectory}/src"
  )

  create_lib_from_files(
    SHOWE_INFO_MESSAGE
    NAME_LIB ${name_Lib}
    NAME_TARGET ${PROJECT_NAME}
    INCLUDES_DIRECTORIES ${includes_Directories}
    SRC_DIRECTORIES ${src_Directories}
    SRC_IGNORE_NAMES ${src_Ignored_Names}
    SRC_EXTRA_FILES ${src_Extra_Files}
    LIB_DIRECTORIES ${lib_Directories}
    LIB_IGNORE_NAMES ${lib_Ignore_Names}
    EXTRA_LIBS ${lib_Extra_Files}
  )
endif()

#[[------------------------------------
                    StringProcessingUtilits lib 
]]#------------------------------------
# set default setting
set(name_Lib "StringProcessingUtilits")
set(includes_Directories)
set(src_Directories)
set(src_Ignore_Names)
set(src_Extra_Files)
set(lib_Directories)
set(lib_Ignore_Names)
set(lib_Extra_Files)
  
# setup lib
set(prefixDirectory "_lib/StringProcessingUtilits")
List(APPEND includes_Directories 
  "${prefixDirectory}/include"
)
List(APPEND src_Directories 
  "${prefixDirectory}/src"
)

create_lib_from_files(
  SHOWE_INFO_MESSAGE
  NAME_LIB ${name_Lib}
  NAME_TARGET ${PROJECT_NAME}
  INCLUDES_DIRECTORIES ${includes_Directories}
  SRC_DIRECTORIES ${src_Directories}
  SRC_IGNORE_NAMES ${src_Ignored_Names}
  SRC_EXTRA_FILES ${src_Extra_Files}
  LIB_DIRECTORIES ${lib_Directories}
  LIB_IGNORE_NAMES ${lib_Ignore_Names}
  EXTRA_LIBS ${lib_Extra_Files}
)

#add test
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  # set default setting
  set(name_Test "UTestStringProcessingUtilits")
  set(includes_Directories)
  set(src_Directories)
  set(src_Ignore_Names)
  set(src_Extra_Files)
  set(lib_Directories)
  set(lib_Ignore_Names)
  set(lib_Extra_Files)

  # setup lib
  set(prefixUTestDirectory "_lib/UTest")
  set(prefixLibDirectory "_lib/StringProcessingUtilits/")
  List(APPEND includes_Directories 
    "${prefixUTestDirectory}/include"
    "${prefixLibDirectory}/test"
  )
  List(APPEND src_Directories 
    "${prefixLibDirectory}/test"
  )
  List(APPEND lib_Directories 
    "${PROJECT_BINARY_DIR}/${name_Lib}"
    "${PROJECT_BINARY_DIR}/LmyUTest"
  )

  create_test_for_lib(
    SHOWE_INFO_MESSAGE
    NAME_TEST ${name_Test}
    INCLUDES_DIRECTORIES ${includes_Directories}
    SRC_DIRECTORIES ${src_Directories}
    SRC_IGNORE_NAMES ${src_Ignored_Names}
    SRC_EXTRA_FILES ${src_Extra_Files}
    LIB_DIRECTORIES ${lib_Directories}
    LIB_IGNORE_NAMES ${lib_Ignore_Names}
    EXTRA_LIBS ${lib_Extra_Files}
  )
endif()

#[[------------------------------------
                    CLI lib 
]]#------------------------------------
# set default setting
set(name_Lib "CLI")
set(includes_Directories)
set(src_Directories)
set(src_Ignore_Names)
set(src_Extra_Files)
set(lib_Directories)
set(lib_Ignore_Names)
set(lib_Extra_Files)
  
# setup lib
set(prefixDirectory "_lib/CLI")
List(APPEND includes_Directories 
  "${prefixDirectory}/include"
)
List(APPEND src_Directories 
  "${prefixDirectory}/src"
)

create_lib_from_files(
  SHOWE_INFO_MESSAGE
  NAME_LIB ${name_Lib}
  NAME_TARGET ${PROJECT_NAME}
  INCLUDES_DIRECTORIES ${includes_Directories}
  SRC_DIRECTORIES ${src_Directories}
  SRC_IGNORE_NAMES ${src_Ignored_Names}
  SRC_EXTRA_FILES ${src_Extra_Files}
  LIB_DIRECTORIES ${lib_Directories}
  LIB_IGNORE_NAMES ${lib_Ignore_Names}
  EXTRA_LIBS ${lib_Extra_Files}
)

#[[------------------------------------
                    FileProcessing lib 
]]#------------------------------------
# set default setting
set(name_Lib "FileProcessing")
set(includes_Directories)
set(src_Directories)
set(src_Ignore_Names)
set(src_Extra_Files)
set(lib_Directories)
set(lib_Ignore_Names)
set(lib_Extra_Files)
  
# setup lib
set(prefixDirectory "_lib/FileProcessing")
List(APPEND includes_Directories 
  "${prefixDirectory}/include"
  "_lib/StringProcessingUtilits/include"
)
List(APPEND src_Directories 
  "${prefixDirectory}/src"
)

create_lib_from_files(
  SHOWE_INFO_MESSAGE
  NAME_LIB ${name_Lib}
  NAME_TARGET ${PROJECT_NAME}
  INCLUDES_DIRECTORIES ${includes_Directories}
  SRC_DIRECTORIES ${src_Directories}
  SRC_IGNORE_NAMES ${src_Ignored_Names}
  SRC_EXTRA_FILES ${src_Extra_Files}
  LIB_DIRECTORIES ${lib_Directories}
  LIB_IGNORE_NAMES ${lib_Ignore_Names}
  EXTRA_LIBS ${lib_Extra_Files}
)


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

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  if(NOT EXISTS "${PROJECT_BINARY_DIR}/exempl")
    file(WRITE "${PROJECT_BINARY_DIR}/exempl" "IS EMPTY")
  endif()
  copy_folder("${PROJECT_SOURCE_DIR}/exemple" "${PROJECT_BINARY_DIR}/exemple")
endif()

target_link_libraries(${PROJECT_NAME} 
  PRIVATE "${PROJECT_BINARY_DIR}/CLI.lib"
  PRIVATE "${PROJECT_BINARY_DIR}/FileProcessing.lib"
  PRIVATE "${PROJECT_BINARY_DIR}/StringProcessingUtilits.lib"
)