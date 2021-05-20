## This function copies the contents of a folder
## Name : CopyFolder
## Param : 
##	srcDir - directory from where the content will be copied
##	destDir - place where will be copied
## @author Andrei-KS
##
## @see https://stackoverflow.com/questions/697560/how-to-copy-directory-from-source-tree-to-binary-tree
function(CopyFolder srcDir destDir)
	set(IsCopiedFiles False)
	if(NOT EXISTS "${destDir}")
		make_directory(${destDir})
	endif()

	file(GLOB_RECURSE filesToCopy RELATIVE ${srcDir} ${srcDir}/*)
	foreach(fileToCopy ${filesToCopy})
		# Get destination directory
		set(DirectoryString "${fileToCopy}")
		string(REGEX REPLACE "([^/\\]+$)" "" DirectoryString ${DirectoryString})
		set(DirectoryString "${destDir}/${DirectoryString}")
		if(NOT EXISTS "${DirectoryString}")
			make_directory(${DirectoryString})
		endif()

		# Copy file if it is not at destination directory or is not equal source file
		if(NOT EXISTS "${destDir}/${fileToCopy}")
			file(COPY "${srcDir}/${fileToCopy}" DESTINATION "${DirectoryString}/")
			set(IsCopiedFiles True)
		else()
			set(sizeSource)
			file(SIZE "${srcDir}/${fileToCopy}" sizeSource)
			set(sizeDestination)
			file(SIZE "${destDir}/${fileToCopy}" sizeDestination)
			if(NOT sizeSource  EQUAL sizeDestination)
				file(COPY "${srcDir}/${fileToCopy}" DESTINATION "${DirectoryString}/")
				set(IsCopiedFiles True)
			endif()
		endif()
	endforeach()
	if(IsCopiedFiles)
		message(STATUS "CopyFolder: source Directory: ${srcDir} --> destination Directory: ${destDir}")
	endif()

endfunction()