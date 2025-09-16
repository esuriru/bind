add_executable(bind 
    "src/main.cpp"

    "src/core/app.cpp"

    "src/dotnet/hostfxr_ctx.cpp"
    "src/dotnet/assembly.cpp"
)

add_subdirectory(deps/hostfxr)

target_include_directories(bind PRIVATE "include")
target_include_directories(bind PRIVATE ${BIND_NETHOST_INCLUDE_DIR})

message(STATUS "Linking nethost")
target_link_libraries(bind PRIVATE ${BIND_NETHOST_DLL_DIR})

if (WIN32)
    target_compile_definitions(bind PRIVATE "BIND_WIN")
endif()

install(TARGETS bind RUNTIME DESTINATION bin)

# Copy nethost.dll to build folder
add_custom_command(
    TARGET bind 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${BIND_NETHOST_DLL_DIR}" $<TARGET_FILE_DIR:bind>
    COMMAND_EXPAND_LISTS
)
