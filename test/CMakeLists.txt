cmake_minimum_required(VERSION 3.5.1)

project(libnodes-tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/../include/libnodes/Node.h"
        "${PROJECT_SOURCE_DIR}/../include/libnodes/ImplicitConversionNode.h"
        "${PROJECT_SOURCE_DIR}/../include/libnodes/connection_container.h"
        "${PROJECT_SOURCE_DIR}/../include/libnodes/algorithms.h"
        "${PROJECT_SOURCE_DIR}/../include/libnodes/nod_signal.h"
        "${PROJECT_SOURCE_DIR}/../src/libnodes/Node.cpp"
        "${PROJECT_SOURCE_DIR}/../include/libnodes/xlet_iterator.h"
        "${PROJECT_SOURCE_DIR}/../include/libnodes/ValueNode.h"
        ../include/libnodes/BundleNode.h ../include/libnodes/operators.h)
set(TEST_FILES
        "${PROJECT_SOURCE_DIR}/main.cpp"
        "${PROJECT_SOURCE_DIR}/test_nodes.cpp"
        "${PROJECT_SOURCE_DIR}/test_xlet_iteration.cpp"
        test_value_node.cpp test_bundle_node.cpp)


include_directories("${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/../include")

add_executable(libnodes-tests "${TEST_FILES}" "${SOURCE_FILES}")
