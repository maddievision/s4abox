set(PROJECT_NAME "agbplay")
set(VERSION "1.0")

cmake_minimum_required(VERSION 3.20)
project(${PROJECT_NAME} VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
	src/agbplay.cpp
	src/CGBChannel.cpp
	src/CGBPatterns.cpp
	src/ConfigManager.cpp
	src/Debug.cpp
	src/GameConfig.cpp
	src/LoudnessCalculator.cpp
	src/OS.cpp
	src/PlayerContext.cpp
	src/PlayerInterface.cpp
	src/Resampler.cpp
	src/ReverbEffect.cpp
	src/Ringbuffer.cpp
	src/Rom.cpp
	src/SequenceReader.cpp
	src/SongEntry.cpp
	src/SoundChannel.cpp
	src/SoundData.cpp
	src/SoundMixer.cpp
	src/Types.cpp
	src/Xcept.cpp
)

include_directories(
  src
  modules/jsoncpp/include
)

add_subdirectory(modules/jsoncpp)

find_package(Boost 1.56 REQUIRED COMPONENTS
 math)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
# add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE jsoncpp_lib Boost::math)

add_definitions(-DANSIC_LIBS_ENABLED)
