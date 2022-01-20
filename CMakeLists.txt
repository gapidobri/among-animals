cmake_minimum_required(VERSION 3.21)
project(among_animals)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        /opt/homebrew/opt/sdl2/include
        /opt/homebrew/opt/sdl2_image/include
        /opt/homebrew/opt/sdl2_ttf/include
        /opt/homebrew/opt/sdl2/include/SDL2
        /opt/homebrew/opt/sdl2_image/include/SDL2
)
link_directories(
        /opt/homebrew/opt/sdl2/lib
        /opt/homebrew/opt/sdl2_image/lib
        /opt/homebrew/opt/sdl2_ttf/lib
)

add_executable(
        among_animals
        main.cpp
        engine/Game/Game.cpp
        engine/Game/Game.h
        engine/GameObject/GameObject.cpp
        engine/GameObject/GameObject.h
        engine/Component/Component.cpp
        engine/Component/Component.h
        engine/components/NavigationComponent/NavigationComponent.cpp
        engine/components/NavigationComponent/NavigationComponent.h
        engine/components/TextureComponent/TextureComponent.cpp
        engine/components/TextureComponent/TextureComponent.h
        engine/Position/Position.h
        engine/components/FixedPositionComponent/FixedPositionComponent.cpp
        engine/components/FixedPositionComponent/FixedPositionComponent.h
        engine/components/CameraComponent/CameraComponent.cpp
        engine/components/CameraComponent/CameraComponent.h
        engine/Size/Size.h
        engine/Size/Size.cpp
        engine/Position/Position.cpp
        engine/components/CollisionComponent/CollisionComponent.cpp
        engine/components/CollisionComponent/CollisionComponent.h
        engine/components/PhysicsComponent/PhysicsComponent.cpp
        engine/components/PhysicsComponent/PhysicsComponent.h
        engine/components/TileComponent/TileComponent.cpp
        engine/components/TileComponent/TileComponent.h
        engine/Bounds/Bounds.cpp
        engine/Bounds/Bounds.h
        engine/components/BackgroundComponent/BackgroundComponent.cpp engine/components/BackgroundComponent/BackgroundComponent.h)

target_link_libraries(among_animals SDL2main SDL2 SDL2_image SDL2_ttf)
