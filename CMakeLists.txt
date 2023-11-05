cmake_minimum_required(VERSION 3.25.1)
project(Brack_Engine)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")


if (WIN32 OR WIN64)
    set(SDL2_PATH "${CMAKE_SOURCE_DIR}/lib/SDL")
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})
else ()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    include_directories(${SDL2_INCLUDE_DIRS})
    link_directories(${SDL2_LIBRARY_DIRS})
endif ()

include_directories(${CMAKE_SOURCE_DIR}/lib/FMod/include)

add_library(${PROJECT_NAME} SHARED ../src/library.cpp
        outfacingInterfaces/Components/IComponent.hpp
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
        src/Wrappers/RenderWrapper.cpp
        outfacingInterfaces/Components/ChildComponent.hpp
        outfacingInterfaces/Components/ParentComponent.hpp
        outfacingInterfaces/Components/ObjectInfoComponent.hpp
        outfacingInterfaces/Components/RigidBodyComponent.hpp
        outfacingInterfaces/Components/AIComponent.hpp
        outfacingInterfaces/Components/AudioComponent.hpp
        outfacingInterfaces/Components/TransformComponent.hpp
        outfacingInterfaces/Helpers/Vector2.cpp
        outfacingInterfaces/Components/VelocityComponent.hpp
        outfacingInterfaces/Components/CollisionComponent.hpp
        outfacingInterfaces/Components/BoxCollisionComponent.hpp
        outfacingInterfaces/Components/CircleCollisionComponent.hpp
        outfacingInterfaces/Components/CameraComponent.hpp
        outfacingInterfaces/Helpers/Color.hpp
        outfacingInterfaces/Components/SpriteComponent.hpp
        outfacingInterfaces/Components/AnimationComponent.hpp
        outfacingInterfaces/Components/ParticleComponent.hpp
        outfacingInterfaces/Components/ParticleEmitterComponent.hpp
        outfacingInterfaces/Components/BehaviourScript.hpp
        outfacingInterfaces/Components/InputTag.hpp
        outfacingInterfaces/Components/PersistenceTag.hpp
        src/Systems/RenderingSystem.cpp
        src/Systems/AnimationSystem.cpp
        src/Systems/MovementSystem.cpp
        src/Systems/BehaviourScriptSystem.cpp
        src/Systems/ParticleSystem.cpp
        src/Systems/ReplaySystem.cpp
        src/Systems/AISystem.cpp
        src/Systems/LoadSystem.cpp
        src/Systems/SaveSystem.cpp
        src/Systems/InputSystem.cpp
        src/Wrappers/InputWrapper.cpp
        src/Systems/CollisionSystem.cpp
        src/Systems/PhysicsSystem.cpp
        src/Systems/TimerSystem.cpp
        src/Systems/AudioSystem.cpp
        src/Wrappers/AudioWrapper.cpp
        src/Wrappers/PhysicsWrapper.cpp
        outfacingInterfaces/Components/UIComponent.hpp
        outfacingInterfaces/Components/ButtonComponent.hpp
        outfacingInterfaces/Components/TextComponent.hpp
        outfacingInterfaces/Objects/GameObject.cpp
        outfacingInterfaces/Objects/Camera.cpp
        outfacingInterfaces/Objects/Scene.cpp
        outfacingInterfaces/Objects/UIObject.cpp
        outfacingInterfaces/test.cpp
        outfacingInterfaces/Objects/Button.cpp
        outfacingInterfaces/Objects/Text.cpp
        "outfacingInterfaces/Engine Managers/SceneManager.cpp"
        "outfacingInterfaces/Engine Managers/ReplayManager.cpp"
        "outfacingInterfaces/Engine Managers/InputManager.cpp"
        outfacingInterfaces/Helpers/InputState.hpp
        outfacingInterfaces/BrackEngine.cpp
        src/GameObjectConverter.cpp
)


target_include_directories(Brack_Engine PUBLIC outfacingInterfaces)

set(LIBRARY_FILES ${CMAKE_SOURCE_DIR}/lib/dll)

if (WIN32 OR WIN64)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARY})
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_custom_command(
            TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${LIBRARY_FILES}
            ${CMAKE_BINARY_DIR}
    )
else ()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
endif ()

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/FMod)
target_link_libraries(${PROJECT_NAME} PRIVATE fmod)