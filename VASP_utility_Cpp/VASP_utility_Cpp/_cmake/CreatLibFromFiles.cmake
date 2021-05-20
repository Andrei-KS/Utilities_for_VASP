

include(CreatListSRC)

## This function creat a lib from files. Also, so that there are no problems during the first assembly, instead of the created library, it creates a stub.
## Name : CreatLibFromFiles
## Param : NamePackege
## External params : 
##  ListPathToInclude - paths to necessary include`s folders
##  ListPathToSrc - paths (if set path, this is only name cpp file) to necessary cpp file folder
##  ListNamesSRCfiles - names necessary cpp file
##  ListPathToLibs - paths to necessary libs
## Output : None
## @author Andrei-KS
function(CreatLibFromFiles NamePackege)
    #Since the library will be built after the build process has started, a stub file will be created in the absence of this library file. 
    if(NOT EXISTS "${PROJECT_BINARY_DIR}/${NamePackege}.lib")
	    file(WRITE "${PROJECT_BINARY_DIR}/${NamePackege}.lib" "IS EMPTY")
    endif()

	message(STATUS "Name package is ${NamePackege}")
    message("ListPathToInclude: ${ListPathToInclude}")
    message("ListPathToSrc: ${ListPathToSrc}")
    message("ListNamesSRCfiles: ${ListNamesSRCfiles}")
    message("ListPathToLibs: ${ListPathToLibs}")

    # Local Paths to sources files of package
    set(PathsToSRC)
    set(SearchDirectory ${ListPathToSrc})
    set(SearchSourceFilenames ${ListNamesSRCfiles})
    # Get all paths of files for source of packege
    CreatListPathToSRC(PathsToSRC)
    message("PathsToSRC: ${PathsToSRC}")

    #Creat lib
    if(PathsToSRC)
        add_library(${NamePackege} STATIC ${PathsToSRC})
        foreach(includePath IN LISTS ListPathToInclude)
            target_include_directories(${NamePackege} PUBLIC "${includePath}/")
        endforeach()

        set(UsingLibs)
        foreach(curNameLib IN LISTS ListPathToLibs)
            file(GLOB NameLib "${curNameLib}.lib")
			if(NOT NameLib)
                message(WARNING "Warrning: Not found ${nameSrc}.lib")
            endif()
            list(APPEND UsingLibs ${NameLib})
        endforeach()
        if(UsingLibs)
            target_link_libraries(${NamePackege} PRIVATE ${UsingLibs})
        endif()
    else()
        message(WARNING "Warrning: PathsToSRC does not constened anything")
    endif()

endfunction()