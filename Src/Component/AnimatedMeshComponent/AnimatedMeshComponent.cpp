/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** AnimatedMeshComponent
*/

#include "AnimatedMeshComponent.hpp"
#include "IObject.hpp"
#include "Core.hpp"
#include "IScene.hpp"

namespace ind {
    AnimatedMeshComponent::AnimatedMeshComponent(IObject * owner, bool isActivated)
        : Component(owner, isActivated)
    {
        _node = _owner->getScene().getManager()->addAnimatedMeshSceneNode(
            0,
            0,
            -1,
            irr::core::vector3df(0, 0, 0),
            irr::core::vector3df(0, 0, 0),
            irr::core::vector3df(1.0f, 1.0f, 1.0f),
            true
        );

        _node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        _node->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
        _node->addShadowVolumeSceneNode();

        _owner->getScene().getManager()->setShadowColor(irr::video::SColor(150,0,0,0));
    }

    AnimatedMeshComponent::~AnimatedMeshComponent()
    {
        _node->remove();
    }

    void        AnimatedMeshComponent::activate(void) noexcept
    {
        _isActivated = true;
        _node->setVisible(true);
    }

    void        AnimatedMeshComponent::desactivate(void) noexcept
    {
        _isActivated = false;
        _node->setVisible(false);
    }

    void AnimatedMeshComponent::pause(void)
    {
        Component::pause();
        if (_paused) {
            _speed = _node->getAnimationSpeed();
            _node->setAnimationSpeed(0);
        } else {
            _node->setAnimationSpeed(_speed);
        }
    }

    std::string AnimatedMeshComponent::getName(void) const noexcept
    {
        return _node->getName();
    }

    void        AnimatedMeshComponent::setMesh(irr::scene::IAnimatedMesh * mesh) noexcept
    {
        _node->setMesh(mesh);
    }

    void        AnimatedMeshComponent::setMeshFromFile(const std::string & filename) noexcept
    {
        irr::scene::IAnimatedMesh * mesh;

        if (filename.empty() == true)
            return;
        _meshFilename = filename;
        mesh = _owner->getScene().getManager()->getMesh((MODELS_OFFSET + filename).c_str());
        setMesh(mesh);
    }

    void        AnimatedMeshComponent::setMaterialTexture(irr::video::ITexture * texture, int layer) noexcept
    {
        _node->setMaterialTexture(layer, texture);
    }

    void        AnimatedMeshComponent::setMaterialTextureFromFile(const std::string & filename, int layer) noexcept
    {
        irr::video::ITexture * texture;

        if (filename.empty() == true)
            return;
        _materialTextureFilename = filename;
        texture = _owner->getScene().getCore().getDriver()->getTexture((TEXTURES_OFFSET + filename).c_str());
        setMaterialTexture(texture, layer);
    }

    void        AnimatedMeshComponent::setParent(irr::scene::ISceneNode * parent) noexcept
    {
        _node->setParent(parent);
    }

    void        AnimatedMeshComponent::setID(int ID) noexcept
    {
        _node->setID(ID);
    }

    void        AnimatedMeshComponent::setPosition(const irr::core::vector3df & position) noexcept
    {
        _node->setPosition(position);
    }

    void        AnimatedMeshComponent::setRotation(const irr::core::vector3df & rotation) noexcept
    {
        _node->setRotation(rotation);
    }

    void        AnimatedMeshComponent::setScale(const irr::core::vector3df & scale) noexcept
    {
        _node->setScale(scale);
    }

    irr::scene::IAnimatedMeshSceneNode *    AnimatedMeshComponent::getNode(void) const noexcept
    {
        return _node;
    }

    irr::scene::IAnimatedMesh *             AnimatedMeshComponent::getMesh(void) const noexcept
    {
        return _node->getMesh();
    }

    std::string                             AnimatedMeshComponent::getMeshFilename(void) const noexcept
    {
        return _meshFilename;
    }

    std::string                             AnimatedMeshComponent::getMaterialTextureFilename(void) const noexcept
    {
        return _materialTextureFilename;
    }

    irr::scene::ISceneNode *                AnimatedMeshComponent::getParent(void) const noexcept
    {
        return _node->getParent();
    }

    int                                     AnimatedMeshComponent::getID(void) const noexcept
    {
        return _node->getID();
    }

    irr::core::vector3df                    AnimatedMeshComponent::getPosition(void) const noexcept
    {
        return _node->getPosition();
    }

    irr::core::vector3df                    AnimatedMeshComponent::getRotation(void) const noexcept
    {
        return _node->getRotation();
    }

    irr::core::vector3df                    AnimatedMeshComponent::getScale(void) const noexcept
    {
        return _node->getScale();
    }

    void        AnimatedMeshComponent::addAnimation(std::string name, Animation anim) noexcept
    {
        _animations.insert({name, anim});
    }

    void        AnimatedMeshComponent::playAnimation(std::string name, bool loop)
    {
        if (_currentAnimation != name) {
            Animation anim = _animations[name];
            _node->setFrameLoop(anim._start, anim._end);
            _node->setAnimationSpeed(anim._speed);
            _node->setLoopMode(loop);
            _currentAnimation = name;
        }
    }

    void        AnimatedMeshComponent::stopAnimation(void) noexcept
    {
        _node->setFrameLoop(0, 0);
        _node->setAnimationSpeed(0);
        _node->setLoopMode(false);
        _currentAnimation = "";
    }
}
