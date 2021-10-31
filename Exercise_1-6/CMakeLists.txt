project(HelloSRE)
add_executable(HelloSre HelloSRE.cpp)
# Link our library to all other libraries. Not sure if we need to link to all or just specific ones
target_link_libraries(HelloSre ${all_libs})
# Copy the image file to different build directories.
file(COPY "test.png" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY "test.png" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY "test.png" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

IF (WIN32)
	## Copy dll's to output path
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
ENDIF(WIN32)