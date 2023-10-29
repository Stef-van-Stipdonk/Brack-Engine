cmake_minimum_required(VERSION 3.26)
project(Brack_Engine)

set(CMAKE_CXX_STANDARD 17)

add_library(Brack_Engine ../src/library.cpp
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
        outfacingInterfaces/IComponentStorage.hpp)
