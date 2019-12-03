/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** ParticleComponent
*/

#ifndef PARTICLECOMPONENT_HPP_
#define PARTICLECOMPONENT_HPP_

#include "Component.hpp"

namespace ind {
    class IObject;

    /**
     * @brief ParticleComponent is a Class which allows to create and manipulate a IParticleSystemSceneNode
     * 
     */
    class ParticleComponent : public Component {
        public:
            /**
             * @brief Construct a new ParticleComponent
             * 
             * @param owner Object which own the component
             * @param isActivated If the component is activate by default
             */
            ParticleComponent(IObject *owner, bool isActivated = true);

            /**
             * @brief Destroy the ParticleComponent
             * 
             */
            ~ParticleComponent();

            /**
             * @brief Update the component
             * 
             * @param delta Time since the last update
             */
            void    update(float delta);

            /**
             * @brief pause the particle component
             * 
             */
            virtual void pause(void);

            /**
             * @brief Show the particles
             * 
             */
            void    activate(void) noexcept;

            /**
             * @brief Hide the particles
             * 
             */
            void    desactivate(void) noexcept;


            /**
             * @brief Create a box-haped emitter of particles
             * 
             * @param box The box for the emitter
             * @param direction Direction and speed of particle emission
             * @param minParticlesPerSecond Minimal amount of particles emitted per second
             * @param maxParticlesPerSecond Maximal amount of particles emitted per second
             * @param minStartColor Minimal initial start color of a particle. The real color of every particle is calculated as random interpolation between minStartColor and maxStartColor
             * @param maxStartColor Maximal initial start color of a particle. The real color of every particle is calculated as random interpolation between minStartColor and maxStartColor
             * @param lifeTimeMin Minimal lifetime of a particle, in milliseconds
             * @param lifeTimeMax Maximal lifetime of a particle, in milliseconds
             * @param maxAngleDegrees Maximal angle in degrees, the emitting direction of the particle will differ from the original direction
             * @param minStartSize Minimal initial start size of a particle. The real size of every particle is calculated as random interpolation between minStartSize and maxStartSize
             * @param maxStartSize Maximal initial start size of a particle. The real size of every particle is calculated as random interpolation between minStartSize and maxStartSize
             */
            void    addBoxEmitter(
                const irr::core::aabbox3df &    box = irr::core::aabbox3df(-10, 28, -10, 10, 30, 10),
                const irr::core::vector3df &    direction = irr::core::vector3df(0.0f, 0.03f, 0.0f),
                irr::u32                        minParticlesPerSecond = 5,
                irr::u32                        maxParticlesPerSecond = 10,
                const irr::video::SColor &      minStartColor = irr::video::SColor(255, 0, 0, 0),
                const irr::video::SColor &      maxStartColor = irr::video::SColor(255, 255, 255, 255),
                irr::u32                        lifeTimeMin = 2000,
                irr::u32                        lifeTimeMax = 4000,
                irr::s32                        maxAngleDegrees = 0,
                const irr::core::dimension2df & minStartSize = irr::core::dimension2df(5.0f, 5.0f),
                const irr::core::dimension2df & maxStartSize = irr::core::dimension2df(5.0f, 5.0f)) noexcept;

            /**
             * @brief Create a ring-haped emitter of particles
             * 
             * @param center Center of ring
             * @param radius Distance of points from center, points will be rotated around the Y axis at a random 360 degrees and will then be shifted by the provided ringThickness values in each axis.
             * @param ringThickness thickness of the ring or how wide the ring is
             * @param direction Direction and speed of particle emission.
             * @param minParticlesPerSecond Minimal amount of particles emitted per second.
             * @param maxParticlesPerSecond Maximal amount of particles emitted per second.
             * @param minStartColor Minimal initial start color of a particle. The real color of every particle is calculated as random interpolation between minStartColor and maxStartColor.
             * @param maxStartColor Maximal initial start color of a particle. The real color of every particle is calculated as random interpolation between minStartColor and maxStartColor.
             * @param lifeTimeMin Minimal lifetime of a particle, in milliseconds.
             * @param lifeTimeMax Maximal lifetime of a particle, in milliseconds.
             * @param maxAngleDegrees Maximal angle in degrees, the emitting direction of the particle will differ from the original direction.
             * @param minStartSize Minimal initial start size of a particle. The real size of every particle is calculated as random interpolation between minStartSize and maxStartSize.
             * @param maxStartSize Maximal initial start size of a particle. The real size of every particle is calculated as random interpolation between minStartSize and maxStartSize.
             */
            void    addRingEmitter(
                const irr::core::vector3df &    center,
                irr::f32                        radius,
                irr::f32                        ringThickness,
                const irr::core::vector3df &    direction = irr::core::vector3df(0.0f, 0.03f, 0.0f),
                irr::u32                        minParticlesPerSecond = 5,
                irr::u32                        maxParticlesPerSecond = 10,
                const irr::video::SColor &      minStartColor = irr::video::SColor(255, 0, 0, 0),
                const irr::video::SColor &      maxStartColor = irr::video::SColor(255, 255, 255, 255),
                irr::u32                        lifeTimeMin = 2000,
                irr::u32                        lifeTimeMax = 4000,
                irr::s32                        maxAngleDegrees = 0,
                const irr::core::dimension2df & minStartSize = irr::core::dimension2df(5.0f, 5.0f),
                const irr::core::dimension2df & maxStartSize = irr::core::dimension2df(5.0f, 5.0f)) noexcept;

            /**
             * @brief Add a gravity effect to particles
             * 
             * @param gravity Direction and force of gravity
             * @param timeForceLost Time in milli seconds when the force of the emitter is totally lost and the particle does not move any more. This is the time where gravity fully affects the particle
             */
            void    addGravityAffector(
                const irr::core::vector3df &    gravity = irr::core::vector3df(0.0f, -0.03f, 0.0f),
                irr::u32                        timeForceLost = 1000) noexcept;

            /**
             * @brief Add an attraction effect to particles
             * 
             * @param point Point to attract particles to.
             * @param speed Speed in units per second, to attract to the specified point.
             * @param attract Whether the particles attract or detract from this point.
             * @param affectX Whether or not this will affect the X position of the particle.
             * @param affectY Whether or not this will affect the Y position of the particle.
             * @param affectZ Whether or not this will affect the Z position of the particle.
             */
            void    addAttractionAffector(
                const irr::core::vector3df &    point,
                irr::f32                        speed = 1.0f,
                bool                            attract = true,
                bool                            affectX = true,
                bool                            affectY = true,
                bool                            affectZ = true) noexcept;

            /**
             * @brief Add a fade out effect to particles
             * 
             * @param targetColor Color where to the color of the particle is changed
             * @param timeNeededToFadeOut How much time in milli seconds should the affector need to change the color to the targetColor
             */
            void    addFadeOutAffector(
                const irr::video::SColor &  targetColor = irr::video::SColor(0, 0, 0, 0),
                irr::u32                    timeNeededToFadeOut = 1000) noexcept;

            /**
             * @brief Add the position offset to the current box position
             * 
             * @return irr::core::aabbox3df Newly adapted box position
             */
            irr::core::aabbox3df    addPositionOffsetToBox(void) noexcept;

            /**
             * @brief Set the Callback Function of the particleSystem
             * 
             * @param callbackFunction Callback Function of the particleSystem
             */
            void    setCallbackFunction(const std::function<irr::core::aabbox3df(void)> & callbackFunction) noexcept;

            /**
             * @brief Set a Position Offset to the particleSystem, in addition of the current owner's position
             * 
             * @param positionOffset Position Offset of the particleSystem
             */
            void    setPositionOffset(irr::core::vector3df positionOffset) noexcept;


            /**
             * @brief Get the Position Offset of the particleSystem
             * 
             * @return irr::core::vector3df Position Offset of the particleSystem
             */
            irr::core::vector3df                    getPositionOffset(void) const noexcept;

            /**
             * @brief Get the particleSystem
             * 
             * @return irr::scene::IParticleSystemSceneNode* particleSystem
             */
            irr::scene::IParticleSystemSceneNode *  getParticleSystem(void) const noexcept;

        protected:
            irr::scene::IParticleSystemSceneNode *      _particleSystem;

            std::function<irr::core::aabbox3df(void)>   _callbackFunction;
            irr::core::vector3df                        _positionOffset;
            int                                         _maxParticlesPerSecond;
    };
}

#endif /* !PARTICLECOMPONENT_HPP_ */
