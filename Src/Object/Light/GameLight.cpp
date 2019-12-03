/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** GameLight
*/

#include "GameLight.hpp"
#include "IScene.hpp"

namespace ind {
    GameLight::GameLight(IScene &scene, std::vector<std::string> tags)
    : Object(scene, tags)
    {
        scene.getManager()->setAmbientLight(irr::video::SColorf(0.3f, 0.3f, 0.3f, 1.0f));
        _light = scene.getManager()->addLightSceneNode(nullptr, irr::core::vector3df(75, 70, 65), irr::video::SColorf(0.8f, 0.8f, 0.8f, 1.0f));
    }

    GameLight::~GameLight()
    {
    }
}
