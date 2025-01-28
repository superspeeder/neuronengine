cmake_minimum_required(VERSION 3.30)
project(neuron_test_app)

option(NEURON_TEST_APP_WIN32_MODE OFF "Build the test application as a win32 program")

add_executable(neuron_test_app src/main.cpp)
target_include_directories(neuron_test_app PRIVATE src/)
target_link_libraries(neuron_test_app neuron::all)
target_compile_features(neuron_test_app PRIVATE cxx_std_23)

if (WIN32)
    if (NEURON_TEST_APP_WIN32_MODE)
        target_compile_definitions(neuron_test_app PRIVATE NTA_BUILD_AS_WIN32)
        set_target_properties(neuron_test_app PROPERTIES WIN32_EXECUTABLE TRUE)
    endif()

    target_compile_definitions(neuron_test_app PRIVATE UNICODE)
endif()

if (NOT EXISTS "${neuron_test_app_BINARY_DIR}/res")
    if (WIN32)
        # Windows requires elevation for creating symbolic links, so instead we are going to use mklink to create a junction
        get_filename_component(real_path "${CMAKE_CURRENT_SOURCE_DIR}/res" REALPATH)
        string(REPLACE "/" "\\" target_path "${real_path}")
        execute_process(COMMAND cmd /C mklink /J res "${target_path}"
                WORKING_DIRECTORY "${neuron_test_app_BINARY_DIR}")
    else ()
        file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/res ${neuron_test_app_BINARY_DIR}/res SYMBOLIC)
    endif ()
endif()

add_custom_target(nta_prep_run
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:neuron_test_app>/ $<TARGET_RUNTIME_DLLS:neuron_test_app>
        DEPENDS $<TARGET_PROPERTY:neuron_test_app,LINK_LIBRARIES>
        COMMAND_EXPAND_LISTS VERBATIM)
