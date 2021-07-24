cmake_minimum_required(VERSION 3.0)
project(Secure-Chat-Server-Application)

FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
add_subdirectory(lib/sha256)
add_subdirectory(lib/rsa)

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


set(SRCS src/server/server.cpp)

add_executable(
    server
    ${SRCS}
)
target_include_directories(server PRIVATE include/server/)
TARGET_LINK_LIBRARIES(server LINK_PUBLIC ${Boost_LIBRARIES} sha256 rsa)
