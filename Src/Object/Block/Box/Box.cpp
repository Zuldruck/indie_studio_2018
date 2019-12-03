/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Box
*/

#include "Box.hpp"
#include "Factory.hpp"
#include "IScene.hpp"
#include "AnimatedMeshComponent.hpp"
#include "CollisionComponent.hpp"
#include "Map.hpp"
#include "Utils.hpp"
#include "Bonus.hpp"

namespace ind {
    Box::Box(IScene &scene, std::vector<std::string> tags) :
        Block(scene, tags)
    {
        getComponent<AnimatedMeshComponent>()->setMeshFromFile("Box/box.3ds");
        getComponent<AnimatedMeshComponent>()->setMaterialTextureFromFile("Box/material_SPEC.png");
        getComponent<AnimatedMeshComponent>()->getNode()->setName("box");
        Factory::createComponent<StaticCollisionComponent>(this);
    }

    void    Box::destroy(void) noexcept
    {
        auto position = getComponent<AnimatedMeshComponent>()->getPosition() / 10;
        auto random = static_cast<double>(Utils::generateRandomNumber(0, 100)) / 100;

        if (random < BONUS_SPAWNRATE) {
            std::shared_ptr<Bonus> bonus = Factory::createObject<Bonus>(getScene());
            bonus->setToBoxPosition(this);
            std::static_pointer_cast<Map>(getScene().getObjectsByTags(
                    "MAP")[0])->getMap()[position.Z][position.X] = Map::BlockType::BONUS;
        } else {
            std::static_pointer_cast<Map>(getScene().getObjectsByTags(
                    "MAP")[0])->getMap()[position.Z][position.X] = Map::BlockType::EMPTY;
        }
        _scene.removeObject(this);
    }
}