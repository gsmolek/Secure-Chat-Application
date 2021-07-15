cmake_minimum_required(VERSION 3.0)
project(Secure-Chat-Server-Application)

set(SRCS src/sha256.cpp)

add_executable(
	sha256
	${SRCS}
)
target_include_directories(sha256 PUBLIC include/)
