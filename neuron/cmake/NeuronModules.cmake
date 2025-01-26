if (NOT EXISTS Python3_EXECUTABLE)
    find_package(Python3 COMPONENTS Interpreter)
else()
    set(Python3_FOUND TRUE)
endif()

find_package(Doxygen
        COMPONENTS dot
        OPTIONAL_COMPONENTS mscgen dia)

function(Neuron_Setup)
endfunction()

define_property(GLOBAL PROPERTY NEURON_MODULES_SRC_LIST)

function(Neuron_PrepModule targetname modulename maindir)
    if (BUILD_SHARED_LIBS)
        target_compile_definitions(${targetname} PUBLIC NEURON_${modulename}_SHARED)
        target_compile_definitions(${targetname} PRIVATE NEURON_${modulename}_SHARED_EXPORTS)
    endif()

    if (Python3_FOUND)
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/generated/${targetname}/generated/${maindir}/"
            COMMAND ${Python3_EXECUTABLE} "${neuron_SOURCE_DIR}/tools/generate_module_complinfoheader.py" "${modulename}" "${CMAKE_BINARY_DIR}/generated/${targetname}/generated/${maindir}/compile_mode.hpp" ${PROJECT_VERSION_MAJOR} ${PROJECT_VERSION_MINOR} ${PROJECT_VERSION_PATCH} "${PROJECT_VERSION}"
            WORKING_DIRECTORY ${neuron_SOURCE_DIR})

        target_include_directories(${targetname} PUBLIC "${CMAKE_BINARY_DIR}/generated/${targetname}/generated/")
    else()
        message(FATAL_ERROR "Cannot properly build ${targetname} without a python3 executable installed.")
    endif()

    set_property(GLOBAL APPEND PROPERTY NEURON_MODULES_SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/")
endfunction()

function(Neuron_MakeDocsTarget)
    if (Doxygen_FOUND)
        get_property(NEURON_MODULES_LIST GLOBAL PROPERTY NEURON_MODULES_SRC_LIST)
        if (NEURON_MODULES_LIST)
            set(DOXYGEN_STRIP_FROM_PATH ${NEURON_MODULES_LIST})
            set(DOXYGEN_INCLUDE_GRAPH YES)
            set(DOXYGEN_CALL_GRAPH YES)
            set(DOXYGEN_CALLER_GRAPH YES)
            set(DOXYGEN_DISABLE_INDEX NO)
            set(DOXYGEN_FULL_SIDEBAR NO)
            set(DOXYGEN_HTML_EXTRA_STYLESHEET "${neuron_SOURCE_DIR}/docs_theme/doxygen-awesome-css/doxygen-awesome.css")
            set(DOXYGEN_HTML_COLORSTYLE LIGHT)
            set(DOXYGEN_EXTRACT_ALL YES)
            set(DOXYGEN_EXTRACT_PRIVATE YES)
            set(DOXYGEN_SHOW_NAMESPACES YES)
            doxygen_add_docs(neuron_docs ${NEURON_MODULES_LIST})
            message(STATUS "Documentation will be generated for files in: ${NEURON_MODULES_LIST}")
        else()
            message(WARNING "-- Cannot generate documentation: No modules are present")
        endif()
    else()
        message(WARNING "-- Doxygen is MISSING: Documentation cannot be generated)")
    endif()
endfunction()