cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
set(TARGET_NAME video_processing)
project(${TARGET_NAME} LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

# string(APPEND CMAKE_CXX_FLAGS " -Wall")
# string(APPEND CMAKE_CXX_FLAGS " -Wbuiltin-macro-redefined")
# string(APPEND CMAKE_CXX_FLAGS " -pedantic")
# string(APPEND CMAKE_CXX_FLAGS " -Werror")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
include(FetchContent)

add_subdirectory(deps/FFmpeg)

set(GLFW_BUILD_EXAMPLES     OFF CACHE BOOL "Build Examples" FORCE)
set(GLFW_BUILD_TESTS        OFF CACHE BOOL "Build tests" FORCE)
set(GLFW_BUILD_DOCS         OFF CACHE BOOL "Build docs" FORCE)
set(GLFW_INSTALL            OFF CACHE BOOL "Configure an install" FORCE)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.9
)
FetchContent_MakeAvailable(glfw)
message("glfw_SOURCE_DIR: " ${glfw_SOURCE_DIR})
message("glfw_BINARY_DIR: " ${glfw_BINARY_DIR})

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v0.1.34
)
FetchContent_MakeAvailable(glad)
message("glad_SOURCE_DIR: " ${glad_SOURCE_DIR})
message("glad_BINARY_DIR: " ${glad_BINARY_DIR})

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)
message("glm_SOURCE_DIR: " ${glm_SOURCE_DIR})
message("glm_BINARY_DIR: " ${glm_BINARY_DIR})

set(ASSIMP_BUILD_ASSIMP_TOOLS   OFF CACHE BOOL "Build ASSIMP tools" FORCE)
set(ASSIMP_BUILD_TESTS          OFF CACHE BOOL "Build tests" FORCE)
set(ASSIMP_INSTALL              OFF CACHE BOOL "Configure an install for ASSIMP" FORCE)
FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG v5.3.1
)
FetchContent_MakeAvailable(assimp)
message("assimp_INCLUDE_DIR: " ${ASSIMP_INCLUDE_DIRS})
message("assimp_SOURCE_DIR: " ${assimp_SOURCE_DIR})
message("assimp_BINARY_DIR: " ${assimp_BINARY_DIR})

# FetchContent_Declare(
#     stb
#     GIT_REPOSITORY https://github.com/nothings/stb.git
#     GIT_TAG "origin/master"
#     # f4a71b13373436a2866c5d68f8f80ac6f0bc1ffe
#     # b42009b3b9d4ca35bc703f5310eedc74f584be58
# )
# FetchContent_MakeAvailable(stb)
# message("${stb_SOURCE_DIR}: " ${stb_SOURCE_DIR})
# message("${stb_BINARY_DIR}: " ${stb_BINARY_DIR})

FetchContent_Declare(
	freetype2
	URL https://download.savannah.gnu.org/releases/freetype/freetype-2.9.1.tar.gz
)
FetchContent_MakeAvailable(freetype2)
message("freetype2_SOURCE_DIR: " ${freetype2_SOURCE_DIR})
message("freetype2_BINARY_DIR: " ${freetype2_BINARY_DIR})

if(APPLE)
    list (APPEND EXTRA_LIBS
        "-framework OpenGL"
    )
elseif(WIN32)
    list(APPEND EXTRA_LIBS
        "-lglu32 -lopengl32"
    )
    set(CMAKE_EXE_LINKER_FLAG "-stf=gun99 -static -static-libgcc -static-libstdc++ -mwindows")
else()
    list(APPEND EXTRA_LIBS
        "-lGL -lGLU -lX11"
    )
endif()

set(
    SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/math.cpp
    ${CMAKE_SOURCE_DIR}/src/window.cpp
    ${CMAKE_SOURCE_DIR}/src/shape.cpp
    ${CMAKE_SOURCE_DIR}/main2.cpp
)

add_executable(${TARGET_NAME} ${SOURCE_FILES})

message(${CMAKE_SOURCE_DIR})

# target_include_directories(target_name
#     PRIVATE    # Headers are visible only to this target.
#     PUBLIC     # Headers are visible to this target and targets that link to it.
#     INTERFACE  # Headers are visible to targets that link to this target, but not directly to this target.
#     directories...
# )

target_include_directories( ${TARGET_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
)

target_link_libraries(${TARGET_NAME}
    FFmpeg
    glad
    glfw
    glm
    assimp
    # stb
    freetype
    ${EXTRA_LIBS}
)


#[[
Add followinf libs in the project:

Boost               brew install boost
OpenGL              
GLFW                https://github.com/glfw/glfw.git
GLM                 https://github.com/g-truc/glm.git
GLAD                https://github.com/Dav1dde/glad.git
stb_image           https://github.com/nothings/stb.git
imgui               
assimp              
freetype            
soil (Simple OpenGL Image Library )


ModernJSON          https://github.com/nlohmann/json.git
Eigen               https://github.com/libigl/eigen.git
OpenCV              brew install opencv
mongocxxdriver      brew install
mysql connector     brew install

]]
