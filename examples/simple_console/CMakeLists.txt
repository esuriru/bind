add_executable(simple_console 
    "native/main.cpp")

target_link_libraries(simple_console PRIVATE bind)
message(STATUS ${BIND_NETHOST_DLL_DIR})
target_include_directories(simple_console PRIVATE "${CMAKE_SOURCE_DIR}/bind/include")

# Copy nethost.dll to build folder
add_custom_command(
    TARGET simple_console 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${BIND_NETHOST_DLL_DIR}" 
        "$<TARGET_FILE_DIR:simple_console>"
    COMMAND_EXPAND_LISTS
)
