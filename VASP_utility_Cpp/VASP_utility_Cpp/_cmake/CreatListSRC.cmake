

## This function make list of paths to source files (cpp files)
## Name : CreatListPathToSRC
## Param : none
## External params :
##  SearchDirectory - the directory containing the source files where the search will be performed 
##  SearchSourceFilenames - name file of sources that will be searched for and added to the list 
## Output : OutListPathToSRC
## @author Andrei-KS
function(CreatListPathToSRC OutListPathToSRC)
    set(ListPathToSRC)
    if(SearchDirectory AND SearchSourceFilenames)
        foreach(SrcDir IN LISTS SearchDirectory)
            foreach(SearchSourceFilename IN LISTS SearchSourceFilenames)
                file(GLOB TARGET_SRC "${SrcDir}/${SearchSourceFilename}.cpp")
                if(NOT TARGET_SRC)
                    message(WARNING "Warrning: Not found ${SrcDir}/${SearchSourceFilename}.cpp")
                endif()
                list(APPEND ListPathToSRC ${TARGET_SRC})
            endforeach()
        endforeach()
    elseif(SearchDirectory)
        foreach(SrcDir IN LISTS SearchDirectory)
            file(GLOB TARGET_SRC "${SrcDir}/*.cpp")
            if(NOT TARGET_SRC)
                message(WARNING "Warrning: Directory [${SrcDir}] is not contained cpp file")
            endif()
            list(APPEND ListPathToSRC ${TARGET_SRC})
        endforeach()
    else()
        foreach(SearchSourceFilename IN LISTS SearchSourceFilenames)
            file(GLOB TARGET_SRC "${SearchSourceFilename}.cpp")
            if(NOT TARGET_SRC)
                message(WARNING "Warrning: Not found ${SearchSourceFilename}.cpp")
            endif()
            list(APPEND ListPathToSRC ${TARGET_SRC})
        endforeach()
    endif()
    set(${OutListPathToSRC} ${ListPathToSRC} PARENT_SCOPE)
endfunction()