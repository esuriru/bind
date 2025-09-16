add_library(bind STATIC
    "src/core/app.cpp"

    "src/dotnet/hostfxr_ctx.cpp"
    "src/dotnet/assembly.cpp"
)

add_subdirectory(deps/hostfxr)

target_include_directories(bind PRIVATE "include")
target_include_directories(bind INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(bind PUBLIC ${BIND_NETHOST_INCLUDE_DIR})

# Forward it again to the top-level scope
set(BIND_NETHOST_DLL_DIR ${BIND_NETHOST_DLL_DIR} PARENT_SCOPE)

message(STATUS "Linking nethost")
target_link_libraries(bind PRIVATE ${BIND_NETHOST_DLL_DIR})

if (WIN32)
    target_compile_definitions(bind PUBLIC "BIND_WIN")
endif()
