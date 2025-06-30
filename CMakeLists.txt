cmake_minimum_required(VERSION 3.10)
project(RTIOW)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(main src/main.cc src/Color.h src/Vector3d.h src/Ray.h src/Object.h src/Sphere.h src/Scene.h src/global.h 
               src/Interval.h src/Renderer.h src/Material.h src/AABB.h src/BVH.h) 