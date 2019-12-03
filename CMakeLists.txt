cmake_minimum_required(VERSION 3.10.2)

################################# NAME OF THE PROJECT #################################
project(bomberman)

################################# SET THE PATH TO OUR OWN FIND PACKAGE #################################
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")


################################# FIND PACKAGE / LIBRARY #################################

    ########## FIND BOOST
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)

    find_package(Boost 1.45.0 COMPONENTS system filesystem)

    ##########  FIND OPENGL / COCOA / IOKIT
    if (WIN32)
        message("Window compilation...")
    else (WIN32)
        find_package(OpenGL REQUIRED)
        find_package(Lua51 REQUIRED)

        if (APPLE)
            find_library(COCOA_LIBRARY Cocoa REQUIRED)
            find_library(IOKIT_LIBRARY IOKit REQUIRED)
        endif (APPLE)
    endif (WIN32)

    #TODO NEED TO BE CHECK
    link_directories(/usr/local/lib)

    ##########  FIND IRRLICHT
    if (WIN32)
        find_package(Irrlicht REQUIRED)
        find_package(SFML REQUIRED network audio graphics window system)
    else (WIN32)
        if (UNIX AND NOT APPLE)
            find_library(Irrlicht_LIBRARIES Irrlicht)
            find_path(Irrlicht_INCLUDE_DIRS irrlicht.h)
        endif(UNIX AND NOT APPLE)

        if (APPLE)
            find_path(Irrlicht_INCLUDE_DIRS irrlicht/irrlicht.h)
            find_library(IRRLICHT_LIBRARY Irrlicht REQUIRED)
        endif (APPLE)
    endif(WIN32)

################################# SET PARAMS CPP #################################
    if (UNIX)
        set(CMAKE_CXX_STANDARD 14)
        set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -Wno-unused-parameter -O3 -g3 -ldl")
    endif(UNIX)

##TODO NEED TO BE CHECK
include_directories(
        ${Irrlicht_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        ${IOKIT_INCLUDE_DIR}
        ${COCOA_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}
        ${Boost_INCLUDE_DIRS}
        ${LUA_INCLUDE_DIR}
)

################################# CPP OF THE PROJECT #################################
    if (WIN32)    
        file(GLOB_RECURSE GAME_SRCS "./Src/*.cpp" "./lua/*.c")
    else(WIN32)
        file(GLOB_RECURSE GAME_SRCS "./Src/*.cpp")
    endif(WIN32)
    
################################# CREATE THE EXECUTABLE #################################
    add_executable(${PROJECT_NAME} ${GAME_SRCS})

################################# INCLUDE HEADER PROJECT TO THE EXECUTABLE #################################

    ##########  FUNC WHICH GET ALL HEADER AND ADD THEIR PATHS TO A LIST
    set(HEADERS_PROJECT "")
    MACRO(HEADER_DIRECTORIES return_list)
        if (WIN32)
            file(GLOB_RECURSE new_list "./Src/*.hpp" "./lua/*.h")
        else (WIN32)
            file(GLOB_RECURSE new_list "./Src/*.hpp")
        endif(WIN32)
        set(dir_list "")
        FOREACH(file_path ${new_list})
            get_filename_component(dir_path ${file_path} PATH)

            set(dir_list ${dir_list} " " ${dir_path})

        ENDFOREACH()
        list(REMOVE_DUPLICATES dir_list)
        set(${return_list} ${dir_list})
    ENDMACRO()
    HEADER_DIRECTORIES(HEADERS_PROJECT)

    ##########  LINK ALL HEADERS TO THE EXECUTABLE
    target_include_directories(${PROJECT_NAME} PRIVATE
            ${HEADERS_PROJECT}
            ${Boost_INCLUDE_DIRS}
            ${Irrlicht_INCLUDE_DIRS}
            )

################################# LINK LIBRARIES TO THE EXECUTABLE #################################

    if (WIN32)
        ########## SET LIBRARIES WINDOWS
        set(LINK_LIBRARIES ${Irrlicht_LIBRARIES} ${OPENGL_LIBRARIES} ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${Boost_LIBRARIES} sfml-graphics sfml-window sfml-system sfml-audio)
    else (WIN32)

        ########## SET LIBRARIES LINUX
        if (UNIX AND NOT APPLE)
            set(LINK_LIBRARIES
                    ${Irrlicht_LIBRARIES} ${OPENGL_LIBRARIES} ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${LUA_LIBRARIES} ${CMAKE_DL_LIBS}
                    GL X11 Xxf86vm ${Boost_LIBRARIES}
                    sfml-graphics sfml-window sfml-system sfml-audio
                    )
        endif(UNIX AND NOT APPLE)

        ########## SET LIBRARIES APPLE
        if (APPLE)
            set(LINK_LIBRARIES
                    ${IRRLICHT_LIBRARY} ${OPENGL_LIBRARIES} ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${LUA_LIBRARIES} ${CMAKE_DL_LIBS}
                    sfml-graphics sfml-window sfml-system sfml-audio
                    )
        endif (APPLE)

    endif(WIN32)

        ########## LINK LIBRARIES OF YOUR CURRENT PLATEFORM TO THE EXECUTABLE
            target_link_libraries(${PROJECT_NAME}
                    ${LINK_LIBRARIES}
                    )

################################# DOCUMENTATION #################################

########## OPTION ON WILL CREATE A DOCUMENTATION / OFF WILL NOT CREATE A DOCUMENTATION
#[[option(BUILD_DOC "Build documentation" ${GENERATE_DOC})

if (${GENERATE_DOC} STREQUAL "ON")
    find_package(Doxygen)

    if (DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started")

        add_custom_target( doc_doxygen ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM )
    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endif (${GENERATE_DOC} STREQUAL "ON")]]
