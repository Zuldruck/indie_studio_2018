/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** PlayerCollisionComponent
*/

#include "PlayerCollisionComponent.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "AnimatedMeshComponent.hpp"
#include "MovementComponent.hpp"
#include "BombComponent.hpp"
#include "EventComponent.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "Bonus.hpp"
#include "BomberMan.hpp"
#include "GameScene.hpp"

namespace ind
{
    PlayerCollisionComponent::PlayerCollisionComponent(IObject *owner, bool isActivated)
    : Component(owner, isActivated), _offsetY(1)
    {
        _meshComponent = _owner->getComponent<AnimatedMeshComponent>();
        _owner->getScene().getCollisionManager()->addPlayerCollision(_meshComponent->getNode(), this);
    }

    PlayerCollisionComponent::~PlayerCollisionComponent()
    {
    }

    bool PlayerCollisionComponent::onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse &animator)
    {
        auto node = animator.getCollisionNode();
        int seconds = 0;
        GameScene *scene = dynamic_cast<GameScene *>(&_owner->getScene());
    
        if (strcmp(node->getName(), "fire") == 0
        || strcmp(node->getName(), "mobCollision") == 0) {
            scene->getEngineSound()->playSong("death");
            static_cast<Character *>(_owner)->die();
        } else if (strcmp(node->getName(), "bonus") == 0) {
            scene->getEngineSound()->playSong("bonus");
            scene->setScorePlayer(scene->getScorePlayer() + 100);
            std::vector<std::shared_ptr<IObject>> bonuss = _owner->getScene().getObjectsByTags("BONUS");
            for (unsigned int i = 0; i < bonuss.size(); i++) {
                if (bonuss[i]->getComponent<AnimatedMeshComponent>()->getNode() == node) {
                    Bonus *bonus = static_cast<Bonus *>(bonuss[i].get());
                    BomberMan *bomberman = static_cast<BomberMan *>(_owner);
                    if (bonus->getEffect() == BonusEffect::SPEED)
                        bomberman->modifyBonusSpeed(bonus->getType());
                    else if (bonus->getEffect() == BonusEffect::RANGE)
                        bomberman->modifyBonusRange(bonus->getType());
                    else if (bonus->getEffect() == BonusEffect::BOMB)
                        bomberman->modifyBonusBomb(bonus->getType());
                    bomberman->getScene().removeObject(bonus);
                    break;
                }
            }
            return true;
        } else if (strcmp(node->getName(), "exit") == 0) {
            if (!static_cast<Player *>(_owner)->hasWon()) {
                static_cast<Player *>(_owner)->win();
                seconds = scene->getGameUi()->getTimer()->getSeconds();
                scene->setScorePlayer(scene->getScorePlayer() + (120 - seconds) * 10);
                _owner->getComponent<AnimatedMeshComponent>()->playAnimation("bomberman_win", true);
                _owner->getComponent<AnimatedMeshComponent>()->setRotation(irr::core::vector3df(0, 0, 0));
                _owner->getComponent<MovementComponent>()->desactivate();
                _owner->getComponent<EventComponent>()->desactivate();
                _owner->getComponent<BombComponent>()->desactivate();
            }
            return true;
        }
        return false;
    }

    std::shared_ptr<AnimatedMeshComponent> &PlayerCollisionComponent::getMeshComponent(void) noexcept
    {
        return _meshComponent;
    }
}