message(STATUS "Config SUB_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}")

execute_process(
    COMMAND ls ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE SUB_DIR_FILES
)
string(REPLACE "\n" ";" SUB_DIR_FILES ${SUB_DIR_FILES})

foreach(item ${SUB_DIR_FILES})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${item})
        aux_source_directory(${item} ${item}_SRC)
        message(STATUS "add '${${item}_SRC}' to sources")
        list(APPEND SUB_DIR_SRCS ${${item}_SRC})
        list(APPEND SUB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${item})
    endif()
endforeach()

file(GLOB SUB_INCS *.h *.hpp */*.h */*.hpp)

target_sources(leetcodenotes_test
    PRIVATE
    ${SUB_DIR_SRCS}
    ${SUB_INCS}
)

target_include_directories(leetcodenotes_test
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SUB_INCLUDE_DIR}
)