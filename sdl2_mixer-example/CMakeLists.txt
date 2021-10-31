add_executable(SRE-sdl2_mixer-example sdl2_mixer-example.cpp)

target_link_libraries(SRE-sdl2_mixer-example ${all_libs})


# Copy project data to output path
file(COPY project_data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY project_data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY project_data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


IF (WIN32)
    ## Copy dll's to output path
    file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
    file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
    file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
ENDIF(WIN32)