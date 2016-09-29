# Minimum cmake version
cmake_minimum_required (VERSION 3.0.0)

# Name of project and that it is C++ only.
project (ZEBRA CXX)

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/seqan-library-2.2.0/share/cmake/Modules/")
# ----------------------------------------------------------------------------
# Dependencies
# ----------------------------------------------------------------------------

# Search for zlib as a dependency for SeqAn.
find_package (ZLIB)

# Load the SeqAn module and fail if not found.
find_package (SeqAn REQUIRED)

# ----------------------------------------------------------------------------
# Build Setup
# ----------------------------------------------------------------------------

SET(SEQAN_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/seqan-library-2.2.0/include/")

# Add include directories.
include_directories (${SEQAN_INCLUDE_PATH})

# Add definitions set by find_package (SeqAn).
add_definitions (${SEQAN_DEFINITIONS})

# Add CXX flags found by find_package (SeqAn).
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SEQAN_CXX_FLAGS}")

# Add executable and link against SeqAn dependencies.
add_executable (ZEBRA buildIndexMain.cpp)
target_link_libraries (ZEBRA ${SEQAN_LIBRARIES})
