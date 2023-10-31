cmake_minimum_required(VERSION 3.25.1)
project(Brack_Engine)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")


if(WIN32 OR WIN64)
    set(SDL2_PATH "${CMAKE_SOURCE_DIR}/lib/SDL")
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})
else ()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    include_directories(${SDL2_INCLUDE_DIRS})
    link_directories(${SDL2_LIBRARY_DIRS})
endif()

add_library(${PROJECT_NAME} SHARED ../src/library.cpp
        outfacingInterfaces/IComponent.hpp
        outfacingInterfaces/ISystem.hpp
        src/Managers/Entities/EntityManager.cpp
        src/includes/EntityManager.hpp
        src/Managers/Components/ComponentStore.cpp
        src/includes/ComponentStore.hpp
        src/Managers/Systems/SystemManager.cpp
        src/includes/SystemManager.hpp
        src/Managers/Components/SparseSet.cpp
        src/includes/SparseSet.hpp
        outfacingInterfaces/IComponentStorage.hpp
        src/Wrappers/SDL2Wrapper.cpp
        outfacingInterfaces/GameEngine.cpp
)


target_include_directories(Brack_Engine PUBLIC outfacingInterfaces)

if(WIN32 OR WIN64)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARY})
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    file(COPY lib/SDL/bin/SDL2.dll DESTINATION ${CMAKE_BINARY_DIR})
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
endif()