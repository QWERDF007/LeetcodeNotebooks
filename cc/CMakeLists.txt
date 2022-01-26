message(STATUS "Config SUB_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}")

set(TARGET_NAME leetcodenotes)

execute_process(
    COMMAND ls ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE SUB_DIR_FILES
)
string(REPLACE "\n" ";" SUB_DIR_FILES ${SUB_DIR_FILES})

foreach(item ${SUB_DIR_FILES})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${item})
        aux_source_directory(${item} ${item}_SRC)
        message(STATUS "add '${${item}_SRC}' to '${TARGET_NAME}'")
        list(APPEND SUB_DIR_SRCS ${${item}_SRC})
        list(APPEND SUB_DIR_INCS ${CMAKE_CURRENT_SOURCE_DIR}/${item})
    endif()
endforeach()

target_sources(${TARGET_NAME}
    PRIVATE
    ${SUB_DIR_SRCS}
)

target_include_directories(${TARGET_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SUB_DIR_INCS}
)