/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** MonsterCollisionComponent
*/

#include "MonsterCollisionComponent.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "AnimatedMeshComponent.hpp"
#include "Character.hpp"
#include "Map.hpp"
#include "GameScene.hpp"
#include "Bonus.hpp"
#include "BomberMan.hpp"
#include "Bomber.hpp"

namespace ind
{
    MonsterCollisionComponent::MonsterCollisionComponent(IObject *owner, bool isActivated)
    : Component(owner, isActivated)
    {
        _meshComponent = _owner->getComponent<AnimatedMeshComponent>();
        _owner->getScene().getCollisionManager()->addMonsterCollision(_meshComponent->getNode(), this);
    }

    MonsterCollisionComponent::~MonsterCollisionComponent()
    {
    }

    bool MonsterCollisionComponent::onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse &animator)
    {
        auto node = animator.getCollisionNode();
        GameScene *scene = dynamic_cast<GameScene *>(&_owner->getScene());

        if (strcmp(node->getName(), "fire") == 0) {
            scene->getEngineSound()->playSong("death");
            static_cast<Character *>(_owner)->die();
            auto map = std::static_pointer_cast<Map>(_owner->getScene().getObjectsByTags("MAP")[0]);
            map->setNbMob(map->getNbMob() - 1);
            scene->setScorePlayer(scene->getScorePlayer() + 200);
        } else if (strcmp(node->getName(), "bonus") == 0) {
            std::vector<std::shared_ptr<IObject>> bonuss = _owner->getScene().getObjectsByTags("BONUS");
            for (unsigned int i = 0; i < bonuss.size(); i++) {
                if (bonuss[i]->getComponent<AnimatedMeshComponent>()->getNode() == node) {
                    Bonus *bonus = static_cast<Bonus *>(bonuss[i].get());
                    if (dynamic_cast<Bomber *>(_owner)) {
                        if (bonus->getEffect() == BonusEffect::SPEED)
                            static_cast<BomberMan *>(dynamic_cast<Bomber *>(_owner))->modifyBonusSpeed(bonus->getType());
                        else if (bonus->getEffect() == BonusEffect::RANGE)
                            static_cast<BomberMan *>(dynamic_cast<Bomber *>(_owner))->modifyBonusRange(bonus->getType());
                        else if (bonus->getEffect() == BonusEffect::BOMB)
                            static_cast<BomberMan *>(dynamic_cast<Bomber *>(_owner))->modifyBonusBomb(bonus->getType());
                    }
                    _owner->getScene().removeObject(bonus);
                    break;
                }
            }
            return true;
        } else if (strcmp(node->getName(), "bomb") == 0)
            return true;
        return false;
    }

    std::shared_ptr<AnimatedMeshComponent> &MonsterCollisionComponent::getMeshComponent(void) noexcept
    {
        return _meshComponent;
    }
}