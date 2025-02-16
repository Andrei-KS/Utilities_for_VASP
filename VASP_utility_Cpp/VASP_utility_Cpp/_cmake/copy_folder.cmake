#[[-------------------------------------------------------------------------
                    Definition and description of function
]]#-------------------------------------------------------------------------
#[[
# This function copies the contents of a folder
# @name		: copy_folder
# @param	: srcDir		- Whence the content will be copied
# @param	: destDir		- Where the content will be copied
#
# @author Andrei-KS
# @see https://stackoverflow.com/questions/697560/how-to-copy-directory-from-source-tree-to-binary-tree
]]#
function(copy_folder srcDir destDir)
	set(isCopiedFiles False)
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
			set(isCopiedFiles True)
		else()
			set(sizeSource)
			file(SIZE "${srcDir}/${fileToCopy}" sizeSource)
			set(sizeDestination)
			file(SIZE "${destDir}/${fileToCopy}" sizeDestination)
			if(NOT sizeSource  EQUAL sizeDestination)
				file(COPY "${srcDir}/${fileToCopy}" DESTINATION "${DirectoryString}/")
				set(isCopiedFiles True)
			endif()
		endif()

		if(isCopiedFiles)
			message(STATUS "copy_folder: source Directory: ${srcDir} --> destination Directory: ${destDir}")
		endif()

	endforeach()

endfunction()