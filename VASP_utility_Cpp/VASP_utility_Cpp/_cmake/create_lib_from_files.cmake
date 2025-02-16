#[[-------------------------------------------------------------------------
                    Connecting the necessary modules
]]#-------------------------------------------------------------------------
include(create_paths_list_to)

#[[-------------------------------------------------------------------------
                    Definition and description of function
]]#-------------------------------------------------------------------------
#[[
# This function creat a lib from files. Also, so that there are no problems during
# the first assembly, instead of the created library, it creates a stub.
# 
# @name   : create_lib_from_files
# @param  : SHOWE_INFO_MESSAGE    - option that allows showing of extra info of the paths making process
# @param  : NAME_LIB              - will be title of the lib that will be made
# @param  : NAME_TARGET           - will depend on target of this lib to ensure that it build before name_target does.
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
# @requirement cmake_minimum_required 8.0 
# @author Andrei-KS
]]#
function(create_lib_from_files)
  set(options
    SHOWE_INFO_MESSAGE
  )
  set(args
    NAME_LIB
    NAME_TARGET
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
    create_lib_from_files
    "${options}"
    "${args}"
    "${list_Args}"
  )

  if(NOT DEFINED create_lib_from_files_NAME_LIB)
    message(FATAL_ERROR "Error : NAME_LIB is not defined")
  endif()

  if(create_lib_from_files_UNPARSED_ARGUMENTS)
    message(FATAL_ERROR "Error : Unparsed argument: ${create_lib_from_files_UNPARSED_ARGUMENTS}")
  endif()

  message(STATUS "Call create_lib_from_files(NAME_LIB ${create_lib_from_files_NAME_LIB} ...)")

  if(create_lib_from_files_SHOWE_INFO_MESSAGE)
    message(STATUS "Name lib will be ${create_lib_from_files_NAME_LIB}")
    message(STATUS "${create_lib_from_files_NAME_TARGET} depend on ${create_lib_from_files_NAME_LIB}")
      
    message("Directories List To Include: ${create_lib_from_files_INCLUDES_DIRECTORIES}")

    message("Directories List To Src: ${create_lib_from_files_SRC_DIRECTORIES}")
    message("Ignore List To Src: ${create_lib_from_files_SRC_IGNORE_NAMES}")
    message("Extra Src Files: ${create_lib_from_files_SRC_EXTRA_FILES}")

    message("Directories List To Lib: ${create_lib_from_files_LIB_DIRECTORIES}")
    message("Ignore List To Lib: ${create_lib_from_files_LIB_IGNORE_NAMES}")
    message("Extra Libs: ${create_lib_from_files_EXTRA_LIBS}")
    message("Dependencies on: ${create_lib_from_files_DEPENDENCIES_ON}")
  endif()


  # Local Paths to sources files of lib
  set(paths_To_SRC)
  # Get all paths of files for source of packege
  create_paths_list_to(
    paths_To_SRC
    DIRECTORIES   ${create_lib_from_files_SRC_DIRECTORIES}
    IGNORE_NAMES  ${create_lib_from_files_SRC_IGNORE_NAMES}
    EXTRA_FILES   ${create_lib_from_files_SRC_EXTRA_FILES}
    EXTENSION     "cpp" "c"
  )

  # Local Paths to additional libs of current lib
  set(paths_To_Lib)
  # Get all paths of files for source of packege
  create_paths_list_to(
    paths_To_Lib
    DIRECTORIES   ${create_lib_from_files_LIB_DIRECTORIES}
    IGNORE_NAMES  ${create_lib_from_files_LIB_IGNORE_NAMES}
    EXTRA_FILES   ${create_lib_from_files_SRC_EXTRA_FILES}
    EXTENSION     "lib"
  )

  if(create_lib_from_files_SHOWE_INFO_MESSAGE)
    message("paths_To_SRC: ${paths_To_SRC}")
    message("paths_To_Lib: ${paths_To_Lib}")
  endif()

  # Creat lib
  if(paths_To_SRC)
    add_library(${create_lib_from_files_NAME_LIB} STATIC ${paths_To_SRC})
    foreach(include_Path IN LISTS create_lib_from_files_INCLUDES_DIRECTORIES)
      target_include_directories(${create_lib_from_files_NAME_LIB} PUBLIC "${include_Path}/")
    endforeach()

    if(paths_To_Lib)
      target_link_libraries(${create_lib_from_files_NAME_LIB} PRIVATE ${paths_To_Lib})
    endif()
  else()
      message(WARNING "Warrning: paths_To_SRC does not constened anything")
  endif()

  # make dependence
  if(create_lib_from_files_NAME_TARGET)
    add_dependencies(${create_lib_from_files_NAME_TARGET} ${create_lib_from_files_NAME_LIB})
  endif()
  if(create_lib_from_files_DEPENDENCIES_ON)
    add_dependencies(${create_lib_from_files_NAME_LIB} ${create_lib_from_files_DEPENDENCIES_ON})
  endif()

endfunction()