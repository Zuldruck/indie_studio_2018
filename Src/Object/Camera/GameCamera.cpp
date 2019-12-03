/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** GameCamera
*/

#include "GameCamera.hpp"
#include "IScene.hpp"

namespace ind {
    GameCamera::GameCamera(IScene &scene, std::vector<std::string> tags)
    : Object (scene, tags)
    {
        _camera = scene.getManager()->addCameraSceneNode(
            0,
            irr::core::vector3df(75.0f, 110.0f, 0.0f),
            irr::core::vector3df(75.0f, 0.0f, 55.0f));
    }

    GameCamera::~GameCamera()
    {
    }
}
