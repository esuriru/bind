add_executable(bind 
    "src/main.cpp"

    "src/core/app.cpp"

    "src/dotnet/hostfxr_ctx.cpp"
)

target_include_directories(bind PRIVATE "include")
target_include_directories(bind PRIVATE "deps/hostfxr/include")

target_link_libraries(bind PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/deps/hostfxr/runtime/nethost.dll")

# Copy nethost.dll to build folder
add_custom_command(
    TARGET bind 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/bind/deps/hostfxr/runtime" $<TARGET_FILE_DIR:bind>
    COMMAND_EXPAND_LISTS
)
