include(FetchContent)

FetchContent_GetProperties(nativefiledialog)
if(NOT nativefiledialog_POPULATED)
    FetchContent_Populate(
            nativefiledialog
            GIT_REPOSITORY https://github.com/mlabbe/nativefiledialog.git
            GIT_TAG        master
    )
endif()

set(NFD_SRC "${nativefiledialog_SOURCE_DIR}/src")

if(WIN32)
    set(NFD_PLATFORM_SRC "${NFD_SRC}/nfd_win.cpp")
elseif(APPLE)
    set(NFD_PLATFORM_SRC "${NFD_SRC}/nfd_cocoa.m")
elseif(UNIX)
    set(NFD_PLATFORM_SRC "${NFD_SRC}/nfd_gtk.c")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
endif()

add_library(nfd STATIC
        "${NFD_SRC}/nfd_common.c"
        "${NFD_PLATFORM_SRC}"
)

target_include_directories(nfd PUBLIC "${NFD_SRC}/include")

if(APPLE)
    target_link_libraries(nfd PRIVATE "-framework AppKit")
elseif(UNIX)
    target_include_directories(nfd PRIVATE ${GTK3_INCLUDE_DIRS})
    target_link_libraries(nfd PRIVATE ${GTK3_LIBRARIES})
endif()

# Suppress warnings from third-party code
target_compile_options(nfd PRIVATE
        $<$<C_COMPILER_ID:GNU,Clang,AppleClang>:-w>
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-w>
)

add_library(nfd::nfd ALIAS nfd)
