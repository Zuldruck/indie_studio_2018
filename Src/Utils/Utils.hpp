/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** Utils.hpp
*/

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include "Includes.hpp"
#include <boost/random.hpp>

namespace ind
{
    class Utils
    {
        public:
            static std::vector<std::string> getFilesFromDirectory(std::string directoryPath);
            static int generateRandomNumber(int min, int max);
    };
}

#endif /* !__UTILS_HPP */
