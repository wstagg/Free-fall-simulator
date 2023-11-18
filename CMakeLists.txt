cmake_minimum_required(VERSION 3.21)
project(free-fall-simulator LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB SOURCES src/*.cpp)
add_executable(free-fall-simulator ${SOURCES})

target_link_libraries(free-fall-simulator PRIVATE sfml-graphics sfml-window)
target_compile_features(free-fall-simulator PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET free-fall-simulator  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:free-fall-simulator> $<TARGET_FILE_DIR:free-fall-simulator> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS free-fall-simulator)