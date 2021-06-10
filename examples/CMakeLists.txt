cmake_minimum_required(VERSION 3.17)

project(inl_examples)

macro(package_add_example EXAMPLE_NAME)
    add_executable(${EXAMPLE_NAME} ${ARGN})
    target_link_libraries(${EXAMPLE_NAME} inl Threads::Threads)
    set_target_properties(${EXAMPLE_NAME}
        PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
    )
endmacro()

find_package(Threads REQUIRED)

package_add_example(socket socket.cpp)
package_add_example(udp_server udp_server.cpp)
package_add_example(udp_client udp_client.cpp)
package_add_example(tcp_server tcp_server.cpp)
package_add_example(tcp_client tcp_client.cpp)

