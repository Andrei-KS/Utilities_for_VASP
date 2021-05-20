
include(CreatListSRC)

## This function make unit test for lib
## Name : CreatTestForLib
## Param : NameTest
## External params :
##  ListPathToInclude - paths to necessary include`s folders
##  ListPathToLibs - paths to necessary libs
##  ListPathToTestSrc - paths (if set path, this is only name cpp file) to necessary cpp file folder
##  ListNamesTestSRCfiles - names necessary test cpp file
## Output : None
## @author Andrei-KS
function(CreatTestForLib NameTest)
	message(STATUS "Name test is ${NameTest}")
	message("ListPathToInclude: ${ListPathToInclude}")
	message("ListPathToLibs: ${ListPathToLibs}")
	message("ListPathToTestSrc: ${ListPathToTestSrc}")
	message("ListNamesTestSRCfiles: ${ListNamesTestSRCfiles}")

	# Local Paths to sources files of package
    set(PathsToSRC)
    set(SearchDirectory ${ListPathToTestSrc})
    set(SearchSourceFilenames ${ListNamesTestSRCfiles})
    # Get all paths of files for source of packege
    CreatListPathToSRC(PathsToSRC)
    message("PathsToSRC: ${PathsToSRC}")

	#Creat Test
    if(PathsToSRC)
        add_executable(${NameTest}_test ${PathsToSRC})
        
        foreach(includePath IN LISTS ListPathToInclude)
            target_include_directories(${NameTest}_test PUBLIC "${includePath}/")
        endforeach()
        foreach(includePath IN LISTS ListPathToTestSrc)
            target_include_directories(${NameTest}_test PUBLIC "${includePath}/")
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
            target_link_libraries(${NameTest}_test PRIVATE ${UsingLibs})
        endif()
        add_test(NAME ${NameTest}_test COMMAND ${NameTest}_test)
    endif()

endfunction()