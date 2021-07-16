#[[
cmake_minimum_required(VERSION 3.0)
project(Secure-Chat-Server-Application)


set(LIBS src/sha256.cpp)
set(SRCS src/server.cpp)

add_library(sha256 ${LIBS})
tar

add_executable(
	server
	${SRCS}
)
target_include_directories(server PUBLIC include/)
target_include_directories(sha256 PUBLIC include/)

target_link_libraries(server sha256)
]]
# cmake_minimum_required(VERSION 3.0)
# project(Secure-Chat-Server-Application)

# set(SRCS src/rsa.cpp)

# add_executable(
# 	rsa
# 	${SRCS}
# )
# target_include_directories(rsa PUBLIC include/)

cmake_minimum_required(VERSION 3.0)
project(Secure-Chat-Server-Application)

add_subdirectory(lib/sha256)

add_executable(server src/server/server.cpp)
target_include_directories(server PRIVATE include/server/)
target_link_libraries(server sha256)