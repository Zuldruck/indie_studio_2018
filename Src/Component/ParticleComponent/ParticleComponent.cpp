/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** ParticleComponent
*/

#include "ParticleComponent.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "AnimatedMeshComponent.hpp"

namespace ind {
    ParticleComponent::ParticleComponent(IObject * owner, bool isActivated)
        : Component(owner, isActivated)
    {
        _particleSystem = _owner->getScene().getManager()->addParticleSystemSceneNode(true);
        _positionOffset = irr::core::vector3df(0, 0, 0);
    }

    ParticleComponent::~ParticleComponent()
    {
        _particleSystem->remove();
    }

    void    ParticleComponent::update(float delta)
    {
        static_cast<void>(delta);
        if (isActivate() == true && _particleSystem->getEmitter()) {
            if (_particleSystem->getEmitter()->getType() == irr::scene::EPET_BOX) {
                static_cast<irr::scene::IParticleBoxEmitter *>(_particleSystem->getEmitter())->setBox(
                    addPositionOffsetToBox()
                );
            } else if (_particleSystem->getEmitter()->getType() == irr::scene::EPET_RING) {
                static_cast<irr::scene::IParticleRingEmitter *>(_particleSystem->getEmitter())->setCenter(
                    _callbackFunction().getCenter() + _positionOffset
                );
            }
        }
    }
    
    void ParticleComponent::pause(void)
    {
        Component::pause();
    }


    void    ParticleComponent::activate(void) noexcept
    {
        static_cast<irr::scene::IParticleBoxEmitter *>(_particleSystem->getEmitter())->setMaxParticlesPerSecond(_maxParticlesPerSecond);
        _isActivated = true;
    }

    void    ParticleComponent::desactivate(void) noexcept
    {
        static_cast<irr::scene::IParticleBoxEmitter *>(_particleSystem->getEmitter())->setMaxParticlesPerSecond(0);
        _isActivated = false;
    }


    void    ParticleComponent::addBoxEmitter(
        const irr::core::aabbox3df &    box,
        const irr::core::vector3df &    direction,
        irr::u32                        minParticlesPerSecond,
        irr::u32                        maxParticlesPerSecond,
        const irr::video::SColor &      minStartColor,
        const irr::video::SColor &      maxStartColor,
        irr::u32                        lifeTimeMin,
        irr::u32                        lifeTimeMax,
        ind_int                         maxAngleDegrees,
        const irr::core::dimension2df & minStartSize,
        const irr::core::dimension2df & maxStartSize) noexcept
    {
        irr::scene::IParticleEmitter * emitter = _particleSystem->createBoxEmitter(
            box,
            direction,
            minParticlesPerSecond,
            maxParticlesPerSecond,
            minStartColor,
            maxStartColor,
            lifeTimeMin,
            lifeTimeMax,
            maxAngleDegrees,
            minStartSize,
            maxStartSize);
        _particleSystem->setEmitter(emitter);
        emitter->drop();
        _particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _maxParticlesPerSecond = maxParticlesPerSecond;
    }

    void    ParticleComponent::addRingEmitter(
        const irr::core::vector3df &    center,
        irr::f32                        radius,
        irr::f32                        ringThickness,
        const irr::core::vector3df &    direction,
        irr::u32                        minParticlesPerSecond,
        irr::u32                        maxParticlesPerSecond,
        const irr::video::SColor &      minStartColor,
        const irr::video::SColor &      maxStartColor,
        irr::u32                        lifeTimeMin,
        irr::u32                        lifeTimeMax,
        irr::s32                        maxAngleDegrees,
        const irr::core::dimension2df & minStartSize,
        const irr::core::dimension2df & maxStartSize) noexcept
    {
        irr::scene::IParticleEmitter * emitter = _particleSystem->createRingEmitter(
            center,
            radius,
            ringThickness,
            direction,
            minParticlesPerSecond,
            maxParticlesPerSecond,
            minStartColor,
            maxStartColor,
            lifeTimeMin,
            lifeTimeMax,
            maxAngleDegrees,
            minStartSize,
            maxStartSize);
        _particleSystem->setEmitter(emitter);
        emitter->drop();
        _particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _maxParticlesPerSecond = maxParticlesPerSecond;
    }

    void    ParticleComponent::addGravityAffector(
        const irr::core::vector3df &    gravity,
        irr::u32                        timeForceLost) noexcept
    {
        irr::scene::IParticleAffector* affector = _particleSystem->createGravityAffector(
            gravity,
            timeForceLost);
        _particleSystem->addAffector(affector);
        affector->drop();
    }

    void    ParticleComponent::addAttractionAffector(
        const irr::core::vector3df &    point,
        irr::f32                        speed,
        bool                            attract,
        bool                            affectX,
        bool                            affectY,
        bool                            affectZ) noexcept
    {
        irr::scene::IParticleAffector* affector = _particleSystem->createAttractionAffector(
            point,
            speed,
            attract,
            affectX,
            affectY,
            affectZ);
        _particleSystem->addAffector(affector);
        affector->drop();
    }

    void    ParticleComponent::addFadeOutAffector(
        const irr::video::SColor &  targetColor,
        irr::u32                    timeNeededToFadeOut) noexcept
    {
        irr::scene::IParticleAffector* affector = _particleSystem->createFadeOutParticleAffector(
            targetColor,
            timeNeededToFadeOut);
        _particleSystem->addAffector(affector);
        affector->drop();
    }

    irr::core::aabbox3df    ParticleComponent::addPositionOffsetToBox(void) noexcept
    {
        irr::core::aabbox3df position = _callbackFunction();

        position.MinEdge += _positionOffset;
        position.MaxEdge += _positionOffset;
        return (position);
    }

    void    ParticleComponent::setCallbackFunction(const std::function<irr::core::aabbox3df(void)> & callbackFunction) noexcept
    {
        _callbackFunction = callbackFunction;
    }

    void    ParticleComponent::setPositionOffset(irr::core::vector3df positionOffset) noexcept
    {
        _positionOffset = positionOffset;
    }

    irr::core::vector3df                    ParticleComponent::getPositionOffset(void) const noexcept
    {
        return _positionOffset;
    }

    irr::scene::IParticleSystemSceneNode *  ParticleComponent::getParticleSystem(void) const noexcept
    {
        return _particleSystem;
    }
}