cmake_minimum_required(VERSION 3.10)
project(OpenMedia)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

find_package(Boost COMPONENTS filesystem iostreams REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIRS} ./src )

message(STATUS "Using OpenSSL ${OPENSSL_INCLUDE_DIRS}")

add_executable(find-duplicates src/Aggregator.cpp src/Filter.cpp src/Finder.cpp src/MD5Comparator.cpp src/MemcmpComparator.cpp src/ComparatorFactory.cpp src/main.cpp)
target_link_libraries(find-duplicates PRIVATE ${Boost_LIBRARIES} ${OPENSSL_CRYPTO_LIBRARY})
