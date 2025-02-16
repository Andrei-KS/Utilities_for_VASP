#[[-------------------------------------------------------------------------
                    Definition and description of function
]]#-------------------------------------------------------------------------
#[[
# This function make list of paths to source files (cpp files)
# @name             : create_list_path_to_src
# @param            : none
# @external params  : EP_CLP_Directories    - the directory containing the source files where the search will be performed 
# @external params  : EP_CLP_FileNames      - Name file of sources that will be searched for and added to the list
# @return           : outListPathToSRC 
#
# @author Andrei-KS
]]#
function(create_list_path_to_src outListPathToSRC)
    set(listPathToSRC)
    if(EP_CLP_Directories AND EP_CLP_FileNames)
        foreach(SrcDir IN LISTS EP_CLP_Directories)
            foreach(fileName IN LISTS EP_CLP_FileNames)
                file(GLOB TARGET_SRC "${SrcDir}/${fileName}.cpp")
                if(NOT TARGET_SRC)
                    message(WARNING "Warrning: Not found ${SrcDir}/${fileName}.cpp")
                endif()
                list(APPEND listPathToSRC ${TARGET_SRC})
            endforeach()
        endforeach()
    elseif(EP_CLP_Directories)
        foreach(SrcDir IN LISTS EP_CLP_Directories)
            file(GLOB TARGET_SRC "${SrcDir}/*.cpp")
            if(NOT TARGET_SRC)
                message(WARNING "Warrning: Directory [${SrcDir}] is not contained cpp file")
            endif()
            list(APPEND listPathToSRC ${TARGET_SRC})
        endforeach()
    else()
        foreach(fileName IN LISTS EP_CLP_FileNames)
            file(GLOB TARGET_SRC "${fileName}.cpp")
            if(NOT TARGET_SRC)
                message(WARNING "Warrning: Not found ${fileName}.cpp")
            endif()
            list(APPEND listPathToSRC ${TARGET_SRC})
        endforeach()
    endif()
    set(${outListPathToSRC} ${listPathToSRC} PARENT_SCOPE)
endfunction()