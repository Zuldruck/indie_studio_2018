/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Includes
*/

#ifndef INCLUDES_HPP_
#define INCLUDES_HPP_

#ifdef __APPLE__
    #include <irrlicht/ISceneNodeAnimatorCollisionResponse.h>
    #include <irrlicht/irrlicht.h>
#elif __linux__
    #include <ISceneNodeAnimatorCollisionResponse.h>
    #include <irrlicht.h>
#elif _WIN32
    #include <ISceneNodeAnimatorCollisionResponse.h>
    #include <irrlicht.h>
#endif /** __APPLE__ **/

#include <iostream>
#include <string>
#include <memory>
#include <chrono>
#include <thread>
#include <ctime>
#include <vector>
#include <map>
#include <unordered_map>
#include <typeindex>

#ifdef _WIN32
    #include <stdlib.h>
    #include <io.h>
    #include <direct.h>
    #include <process.h>
    #define access _access
    #define dup2 _dup2
    #define execve _execve
    #define ftruncate _chsize
    #define unlink _unlink
    #define fileno _fileno
    #define getcwd _getcwd
    #define chdir _chdir
    #define isatty _isatty
    #define lseek _lseek
    #include "myDirent.h"
#else
    #include <dirent.h>
    #include <unistd.h>
#endif
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "Types.hpp"

/* EXCEPTION FOR SMART THROWING  */

#define COLOR(number) "\033[1;" #number "m"
#define CLEAR std::string("\033[0m")
#define IObject_ptr std::shared_ptr<IObject>



std::vector<std::string> getFilesFromDirectory(std::string directoryPath);

/**
 * @brief func which smart throw with line, func, file of the crash.
 * @tparam E type of the throw.
 * @param msg message of the throw
 * @param file filepath of the throw.
 * @param function name of the function which contains the crash.
 * @param line line number of the crash.
 */
template<class E>
void throw_func( std::string msg,
							  char const* file, char const* function,
							  std::size_t line
) {
	throw E( std::string{} +
			 std::string(std::string(COLOR(33)) + file + CLEAR) +
			 std::string(std::string(COLOR(31)) + "(" + std::to_string(line) + "):" + CLEAR) +
			 std::string(std::string(COLOR(34)) + " [" + std::string(function) + "] " + CLEAR + std::string("--> ")) +
			 std::string(std::string(COLOR(31)) + std::string("\x1B[1m") + msg + CLEAR));
}
#define EXCEPTION( TYPE, MESSAGE ) \
    throw_func<TYPE>( MESSAGE, __FILE__, __func__, __LINE__ )

#endif /* !INCLUDES_HPP_ */
