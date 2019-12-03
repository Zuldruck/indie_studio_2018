/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** AnimatedMeshComponent
*/

#ifndef ANIMATEDMESHCOMPONENT_HPP_
#define ANIMATEDMESHCOMPONENT_HPP_

#include "Component.hpp"

#ifdef __APPLE__
        #define MODELS_OFFSET "OOP_indie_studio_2018/Assets/Models/"
        #define TEXTURES_OFFSET "OOP_indie_studio_2018/Assets/Textures/"
#elif __linux__
        #define MODELS_OFFSET "Assets/Models/"
        #define TEXTURES_OFFSET "Assets/Textures/"
#elif _WIN32
        #define MODELS_OFFSET "Assets/Models/"
        #define TEXTURES_OFFSET "Assets/Textures/"
#endif /* __APPLE__ */

namespace ind {
    class IObject;

    /**
     * @brief Animation is a structure which stock the start and end Frame of the Animation as well as the speed of this one
     * 
     */
    struct Animation
    {
        /**
         * @brief Construct a new Animation structure with everything at 0 by default
         * 
         */
        Animation() : _start(0), _end(0), _speed(0)
        {}

        /**
         * @brief Construct a new Animation structure
         * 
         * @param start Frame at which the Animation start
         * @param end Frame at which the Animation end
         * @param speed Speed of the animation
         */
        Animation(int start, int end, int speed) : _start(start), _end(end), _speed(speed)
        {}

        int     _start;
        int     _end;
        int     _speed;
    };

    /**
     * @brief AnimatedMeshComponent is a class which allows the creation and the manipulation of an IAnimatedMeshSceneNode
     * 
     */
    class AnimatedMeshComponent : public Component {
        public:
            /**
             * @brief Construct a new AnimatedMeshComponent
             * 
             * @param owner Object which own the component
             * @param isActivated If the component is activate by default
             */
            AnimatedMeshComponent(IObject *owner, bool isActivated = true);

            /**
             * @brief Destroy the AnimatedMeshComponent
             * 
             */
            ~AnimatedMeshComponent();

            /**
             * @brief Show the animatedMeshSceneNode
             * 
             */
            void        activate(void) noexcept;

            /**
             * @brief Hide the animatedMeshSceneNode
             * 
             */
            void        desactivate(void) noexcept;

            /**
             * @brief Pause the animation
             * 
             */
            virtual void pause(void);

            /**
             * @brief Set the Mesh of the animatedMeshSceneNode
             * 
             * @param mesh Mesh of the animatedMeshSceneNode
             */
            void        setMesh(irr::scene::IAnimatedMesh * mesh) noexcept;

            /**
             * @brief Set the Mesh of the animatedMeshSceneNode from a file
             * 
             * @param filename Filename of the file which load the Mesh of the animatedMeshSceneNode
             */
            void        setMeshFromFile(const std::string & filename) noexcept;

            /**
             * @brief Set the Material Texture of the animatedMeshSceneNode
             * 
             * @param texture Material Texture of the animatedMeshSceneNode
             * @param layer Layer of the Material Texture
             */
            void        setMaterialTexture(irr::video::ITexture * texture, int layer = 0) noexcept;

            /**
             * @brief Set the Material Texture of the animatedMeshSceneNode from a file
             * 
             * @param filename Filename of the file which load the Material Texture of the animatedMeshSceneNode
             * @param layer Layer of the Material Texture
             */
            void        setMaterialTextureFromFile(const std::string & filename, int layer = 0) noexcept;

            /**
             * @brief Sets the parent node of the animatedMeshSceneNode
             * 
             * @param parent Parent node of the animatedMeshSceneNode
             */
            void        setParent(irr::scene::ISceneNode * parent) noexcept;

            /**
             * @brief Set the ID of the animatedMeshSceneNode
             * 
             * @param ID ID of the animatedMeshSceneNode
             */
            void        setID(int ID) noexcept;

            /**
             * @brief Set the Position of the animatedMeshSceneNode
             * 
             * @param position Position of the animatedMeshSceneNode
             */
            void        setPosition(const irr::core::vector3df & position) noexcept;

            /**
             * @brief Set the Rotation of the animatedMeshSceneNode
             * 
             * @param rotation Rotation of the animatedMeshSceneNode
             */
            void        setRotation(const irr::core::vector3df & rotation) noexcept;

            /**
             * @brief Set the Scale of the animatedMeshSceneNode
             * 
             * @param scale Scale of the animatedMeshSceneNode
             */
            void        setScale(const irr::core::vector3df & scale) noexcept;


            /**
             * @brief Get the Name of the animatedMeshSceneNode
             * 
             * @return std::string Name of the animatedMeshSceneNode
             */
            std::string                             getName(void) const noexcept;

            /**
             * @brief Get the animatedMeshSceneNode
             * 
             * @return irr::scene::IAnimatedMeshSceneNode* animatedMeshSceneNode
             */
            irr::scene::IAnimatedMeshSceneNode *    getNode(void) const noexcept;

            /**
             * @brief Get the Mesh of the animatedMeshSceneNode
             * 
             * @return irr::scene::IAnimatedMesh* Mesh of the animatedMeshSceneNode
             */
            irr::scene::IAnimatedMesh *             getMesh(void) const noexcept;

            /**
             * @brief Get the Filename of the Mesh of the animatedMeshSceneNode
             * 
             * @return std::string Filename of the Mesh of the animatedMeshSceneNode
             */
            std::string                             getMeshFilename(void) const noexcept;

            /**
             * @brief Get the Filename of the Material Texture of the animatedMeshSceneNode
             * 
             * @return std::string Filename of the Material Texture of the animatedMeshSceneNode
             */
            std::string                             getMaterialTextureFilename(void) const noexcept;

            /**
             * @brief Get the Parent node of the animatedMeshSceneNode
             * 
             * @return irr::scene::ISceneNode* Parent node of the animatedMeshSceneNode
             */
            irr::scene::ISceneNode *                getParent(void) const noexcept;

            /**
             * @brief Get the ID of the animatedMeshSceneNode
             * 
             * @return int ID of the animatedMeshSceneNode
             */
            int                                     getID(void) const noexcept;

            /**
             * @brief Get the Position of the animatedMeshSceneNode
             * 
             * @return irr::core::vector3df Position of the animatedMeshSceneNode
             */
            irr::core::vector3df                    getPosition(void) const noexcept;

            /**
             * @brief Get the Rotation of the animatedMeshSceneNode
             * 
             * @return irr::core::vector3df Rotation of the animatedMeshSceneNode
             */
            irr::core::vector3df                    getRotation(void) const noexcept;

            /**
             * @brief Get the Scale of the animatedMeshSceneNode
             * 
             * @return irr::core::vector3df Scale of the animatedMeshSceneNode
             */
            irr::core::vector3df                    getScale(void) const noexcept;


            /**
             * @brief Add the Animation passed as parameter in the Animations map.
             * 
             * @param name Name of the Animation to be added
             * @param anim Animation to be added
             */
            void                                    addAnimation(std::string name, Animation anim) noexcept;

            /**
             * @brief Play the Animation passed as parameter
             * 
             * @param name Name of the Animation to be played
             * @param loop Animation to be played
             */
            void                                    playAnimation(std::string name, bool loop);

            /**
             * @brief Stop the Animation currently played
             * 
             */
            void                                    stopAnimation(void) noexcept;

        private:
            irr::f32 _speed = 0;
            irr::scene::IAnimatedMeshSceneNode *        _node;
            std::string                                 _meshFilename;
            std::string                                 _materialTextureFilename;
            std::unordered_map<std::string, Animation>  _animations;
            std::string                                 _currentAnimation;
    };
}

#endif /* !ANIMATEDMESHCOMPONENT_HPP_ */
