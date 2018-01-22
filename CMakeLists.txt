cmake_minimum_required(VERSION 3.0)
project(snow-engine)

# Require -std=c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Require OpenGL
find_package(OpenGL REQUIRED)

# Require GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
string(STRIP ${GLEW_LIBRARIES} GLEW_LIBRARIES)

# Require SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

# Find SDL2_mixer
find_library(SDL2_MIXER_LIBRARIES
  NAMES SDL2_mixer
  PATH_SUFFIXES lib
)

# Inlcude dirs
include_directories("${PROJECT_SOURCE_DIR}/lib/include")

set(srcs AudioEngine.cpp AudioEngine.h Camera2D.cpp Camera2D.h CMakeLists.txt DebugRenderer.cpp DebugRenderer.h FrameBuffer.cpp FrameBuffer.h SnowEngine.cpp SnowEngine.h constants.h errors.h errors.cpp GLTexture.h IGameScreen.cpp IGameScreen.h ImageLoader.cpp ImageLoader.h IMainGame.cpp IMainGame.h InputManager.cpp InputManager.h IOManager.cpp IOManager.h ParticleBatch2D.cpp ParticleBatch2D.h ParticleEngine2D.cpp ParticleEngine2D.h picopng.cpp picopng.h ResourceManager.cpp ResourceManager.h ShaderProgram.cpp ShaderProgram.h SpriteAnimation.cpp SpriteAnimation.h SpriteBatch.cpp SpriteBatch.h Sprite.cpp SpriteFont.cpp SpriteFont.h Sprite.h SpriteSheet.cpp SpriteSheet.h TextureCache.cpp TextureCache.h timing.cpp timing.h VertexData.h Window.cpp Window.h)

add_subdirectory(src)