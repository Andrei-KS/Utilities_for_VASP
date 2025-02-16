#[[-------------------------------------------------------------------------
                    Definition and description of function
]]#-------------------------------------------------------------------------
#[[
# This function make list of paths to everything that is determined by given extensions
# @name   : create_paths_list_to
# @param  : NONE
# @param  : SHOWE_INFO_MESSAGE  - option that allows showing of extra info of the paths making process
# @param  : DIRECTORIES         - will be involved to find files
# @param  : IGNORE_NAMES        - files that use these names is excluded
# @param  : EXTRA_FILES         - will be added to list
# @param  : EXTENSION           - These extensions determine necessary files
# @return : out_List_Path_To 
#
# @requirement cmake_minimum_required 8.0 
# @author Andrei-KS
]]#
function(create_paths_list_to out_Paths_List_To)
  set(options
    SHOWE_INFO_MESSAGE
  )
  set(args
  )
  set(list_Args
    DIRECTORIES
    IGNORE_NAMES
    EXTRA_FILES
    EXTENSION
  )
  cmake_parse_arguments(
    PARSE_ARGV 0
    create_paths_list_to
    "${options}"
    "${args}"
    "${list_Args}"
  )

  
  list(LENGTH create_paths_list_to_UNPARSED_ARGUMENTS amount_variable)
  if(NOT amount_variable EQUAL 1)
    message(FATAL_ERROR "Error : need only one variable for output of the paths list")
  endif()

  message(STATUS "Call create_paths_list_to(${out_Paths_List_To})")
  
  # make ignore List
  set(ignore_List)
  if(create_paths_list_to_IGNORE_NAMES)

    foreach(curr_Ign IN LISTS create_paths_list_to_IGNORE_NAMES)
      if(NOT ignore_List)
        set(ignore_List ${curr_Ign})
      else()
        set(ignore_List "${ignore_List}|${curr_Ign}")
      endif()
    endforeach()

    set(ignore_List "(${ignore_List})")
  endif()

  if(create_paths_list_to_SHOWE_INFO_MESSAGE)
    message("ignore_List: ${ignore_List}")
  endif()

  set(extensions_For_Search)
  if(create_paths_list_to_EXTENSION)

    set(is_Skip False)
    foreach(curr_Ext IN LISTS create_paths_list_to_EXTENSION)

      if(curr_Ext STREQUAL "*")

        set(extensions_For_Search "*")
        break()
      elseif(curr_Ext STREQUAL ".*")

        set(extensions_For_Search "*.*")
        set(is_Skip True)
        continue()
      else()

        if(is_Skip)
          continue()
        endif()

        string(REGEX REPLACE "([^.]+)" "*.\\1" replace_item "${curr_Ext}")
        list(APPEND extensions_For_Search
          "${replace_item}"
        )
      endif()

    endforeach()
  else()

    list(APPEND extensions_For_Search
    "*"
    )
  endif()

  if(create_paths_list_to_SHOWE_INFO_MESSAGE)
    message("extensions_For_Search : ${extensions_For_Search}")
  endif()

  set(paths_List_To)

  # walk given directories and make paths list
  if(create_paths_list_to_DIRECTORIES)

    foreach(curr_Ext IN LISTS extensions_For_Search)

      set(is_Find False)
      foreach(curr_Dir IN LISTS create_paths_list_to_DIRECTORIES)
        
        set(curr_Target)
        file(GLOB curr_Target "${curr_Dir}/${curr_Ext}")
        if(curr_Target)

          if(ignore_List)
            set(curr_Target "${curr_Target};")
            string(REGEX REPLACE "[^;]*/${ignore_List}([.][^.;]*)?[;]" "" curr_Target "${curr_Target}")
          endif()
          
          set(exist_files)
          foreach(file IN LISTS curr_Target)
            if(NOT IS_DIRECTORY "${file}")
              list(APPEND exist_files
                "${file}"
              )
            endif()
          endforeach()

          if(exist_files)
            set(is_Find TRUE)
          endif()

          list(APPEND paths_List_To ${exist_files})
        endif()

      endforeach()

      if(NOT is_Find)
        message(WARNING "Warrning: Not found files (with extension ${curr_Ext})")
      endif()

    endforeach()
  endif()


  # add extra files
  if(create_paths_list_to_EXTRA_FILES)

    set(default_Dir ${PROJECT_SOURCE_DIR})
    foreach(file_Name IN LISTS create_paths_list_to_EXTRA_FILES)
      
      if(NOT file_Name MATCHES "[^:]+:[^:]+")
        set(file_Name "${default_Dir}/${file_Name}")
      endif()

      set(curr_Target)
      if(file_Name MATCHES "[.][^./]*$")
        file(GLOB curr_Target "${file_Name}")
      else()
        foreach(curr_Ext IN LISTS create_paths_list_to_EXTENSION)
          file(GLOB curr_Target "${file_Name}.${curr_Ext}")
        endforeach()
      endif()

      if(NOT curr_Target)
        message(WARNING "Warrning: Not found files (with extensions: ${Extension}) ${file_Name}")
      else()
        list(APPEND paths_List_To ${curr_Target})
      endif()

    endforeach()
  endif()

  if(create_paths_list_to_SHOWE_INFO_MESSAGE)
    message("${out_Paths_List_To} : ")
    foreach( list_item IN LISTS paths_List_To)
      message("\t${list_item}")
    endforeach()
  endif()


  set(${out_Paths_List_To} ${paths_List_To} PARENT_SCOPE)
endfunction()