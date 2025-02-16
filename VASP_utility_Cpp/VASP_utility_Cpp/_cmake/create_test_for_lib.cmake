#[[-------------------------------------------------------------------------
                    Connecting the necessary modules
]]#-------------------------------------------------------------------------
include(create_list_path_to_src)

#[[-------------------------------------------------------------------------
                    Definition and description of function
]]#-------------------------------------------------------------------------
#[[
# This function make unit test for lib
#
# @name   : creat_test_for_lib
# @param  : SHOWE_INFO_MESSAGE    - option that allows showing of extra info of the paths making process
# @param  : NAME_TEST             - will be title of the test that will be made
# @param  : INCLUDES_DIRECTORIES  - will be involved to find include files
# @param  : SRC_DIRECTORIES       - will be involved to find source files
# @param  : SRC_IGNORE_NAMES      - source files that use these names is excluded
# @param  : SRC_EXTRA_FILES       - will be added
# @param  : LIB_DIRECTORIES       - will be involved to find lib files
# @param  : LIB_IGNORE_NAMES      - lib files that use these names is excluded
# @param  : EXTRA_LIBS            - will be added
# @param  : DEPENDENCIES_ON       - this library will be depended on these target
# @return : NONE
#
# @author Andrei-KS
]]#
function(create_test_for_lib)
  set(options
    SHOWE_INFO_MESSAGE
  )
  set(args
    NAME_TEST
  )
  set(list_Args
    INCLUDES_DIRECTORIES
    SRC_DIRECTORIES
    SRC_IGNORE_NAMES
    SRC_EXTRA_FILES
    LIB_DIRECTORIES
    LIB_IGNORE_NAMES
    EXTRA_LIBS
    DEPENDENCIES_ON
  )
  cmake_parse_arguments(
    PARSE_ARGV 0
    create_test_for_lib
    "${options}"
    "${args}"
    "${list_Args}"
  )

  if(NOT DEFINED create_test_for_lib_NAME_TEST)
    message(FATAL_ERROR "Error : NAME_TEST is not defined")
  endif()

  if(create_test_for_lib_UNPARSED_ARGUMENTS)
    message(FATAL_ERROR "Error : Unparsed argument: ${create_test_for_lib_UNPARSED_ARGUMENTS}")
  endif()

  message(STATUS "Call creat_lib_from_files(NAME_LIB ${create_test_for_lib_NAME_TEST} ...)")

  if(create_test_for_lib_SHOWE_INFO_MESSAGE)
    message(STATUS "Test name will be ${create_test_for_lib_NAME_TEST}")

    message("Directories List To Include: ${create_test_for_lib_INCLUDES_DIRECTORIES}")

    message("Directories List To Src: ${create_test_for_lib_SRC_DIRECTORIES}")
    message("Ignore List To Src: ${create_test_for_lib_SRC_IGNORE_NAMES}")
    message("Extra Src Files: ${create_test_for_lib_SRC_EXTRA_FILES}")

    message("Directories List To Lib: ${create_test_for_lib_LIB_DIRECTORIES}")
    message("Ignore List To Lib: ${create_test_for_lib_LIB_IGNORE_NAMES}")
    message("Extra Libs: ${create_test_for_lib_EXTRA_LIBS}")
    message("Dependencies on: ${create_test_for_lib_DEPENDENCIES_ON}")
  endif()

  # Local Paths to sources files of lib
  set(paths_To_SRC)
  # Get all paths of files for source of packege
  create_paths_list_to(
    paths_To_SRC
    DIRECTORIES   ${create_test_for_lib_SRC_DIRECTORIES}
    IGNORE_NAMES  ${create_test_for_lib_SRC_IGNORE_NAMES}
    EXTRA_FILES   ${create_test_for_lib_SRC_EXTRA_FILES}
    EXTENSION     "cpp" "c"
  )

  # Local Paths to additional libs of current lib
  set(paths_To_Lib)
  # Get all paths of files for source of packege
  create_paths_list_to(
    paths_To_Lib
    DIRECTORIES   ${create_test_for_lib_LIB_DIRECTORIES}
    IGNORE_NAMES  ${create_test_for_lib_LIB_IGNORE_NAMES}
    EXTRA_FILES   ${create_test_for_lib_SRC_EXTRA_FILES}
    EXTENSION     "lib"
  )

   # Creat lib
  if(paths_To_SRC)
    set(name_Test ${create_test_for_lib_NAME_TEST}_test)
    add_executable(${name_Test} ${paths_To_SRC})
    foreach(include_Path IN LISTS create_test_for_lib_INCLUDES_DIRECTORIES)
      target_include_directories(${name_Test} PUBLIC "${include_Path}/")
    endforeach()

    if(paths_To_Lib)
      target_link_libraries(${name_Test} PRIVATE ${paths_To_Lib})
    endif()
    add_test(NAME ${name_Test} COMMAND ${name_Test})
  else()
      message(WARNING "Warrning: paths_To_SRC does not constened anything")
  endif()
endfunction()