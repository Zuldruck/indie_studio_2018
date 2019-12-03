/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** Utils.cpp
*/


#include "Utils.hpp"

namespace ind
{

std::vector<std::string> Utils::getFilesFromDirectory(std::string directoryPath)
{
    std::vector<std::string> filesNames;
    DIR *dir = opendir(directoryPath.c_str());
    struct dirent *dirent = nullptr;

    if (dir == nullptr)
        EXCEPTION(std::runtime_error, "getFilesFromDirectory Failed" + directoryPath);

    while ((dirent = readdir(dir)) != nullptr) {
        if (dirent->d_name[0] != '.')
            filesNames.push_back(std::string(dirent->d_name));
    }

    std::sort(filesNames.begin(), filesNames.end(), [](std::string s1, std::string s2) {
        return s1 < s2;
    });
    return filesNames;
}

int Utils::generateRandomNumber(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

}
