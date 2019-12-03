/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** MapBackground
*/

#ifndef MAPBACKGROUND_HPP_
#define MAPBACKGROUND_HPP_

#include "Object.hpp"

namespace ind {
    class MapBackground : public Object {
    public:
        MapBackground(
                IScene &scene,
                std::vector<std::string> tags = {"MAPBACKGROUND"});
    };
}

#endif /* !MAPBACKGROUND_HPP_ */
