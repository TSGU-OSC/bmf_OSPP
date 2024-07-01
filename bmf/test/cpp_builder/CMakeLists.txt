
file(GLOB SRCS *.cpp *.h)

include_directories(/root/workspace/bmf_OSPP/bmf/engine/c_engine/include)
include_directories(/root/workspace/bmf_OSPP/output/bmf/include)
link_directories(/root/workspace/bmf_OSPP/output/bmf/lib)

include_directories(/root/workspace/bmf_OSPP/bmf/hml/third_party/gtest/googletest/include)
link_directories(/root/workspace/bmf_OSPP/bmf/hml/third_party/gtest/build/lib)

include_directories(/root/workspace/bmf_OSPP/output/bmf/include/nlohmann)
link_directories(/root/workspace/bmf_OSPP/output/bmf/bin)

SET(CMAKE_CXX_FLAGS "-std=c++17")

add_executable(test_cpp_builder ${SRCS})

#find_package(nlohmann_json 3.11.2 REQUIRED HINTS /root/workspace/bmf_OSPP/3rd_party/json/build)

target_link_libraries(test_cpp_builder
    PRIVATE 
        bmf_module_sdk engine hmp
        gtest pthread
)

if(WIN32)
    target_link_directories(test_cpp_builder PRIVATE $ENV{WIN_XCOMPILE_ROOT}/$ENV{WIN_XCOMPILE_ARCH}/usr/lib)
    target_link_libraries(test_cpp_builder
        PRIVATE
        libcrypto libssl
    )
else()
    target_link_libraries(test_cpp_builder
        PRIVATE
        crypto ssl
    )
endif()

target_link_libraries(test_cpp_builder PRIVATE gtest_main)

install(TARGETS test_cpp_builder
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
)
