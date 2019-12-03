/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Object
*/

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include "IObject.hpp"

namespace ind {
    /**
     * @brief Object is a simple implementation of IObject
     *
     */
    class Object : public IObject {
        public:

            /**
             * @brief Construct a new Object. should be called by Factory
             *
             * @param core
             * @param tags
             */
            Object(
                IScene &scene,
                std::vector<std::string> tags);
            virtual ~Object();
            /**
             * @brief Simple Implementation of IObject (doing nothing)
             *
             */
            virtual void    beginPlay(void);

            /**
             * @brief Simple Implementation of IObject (calling components update)
             *
             */
            virtual void    update(float delta);

            /**
             * @brief pause and unpause the object.
             * 
             */
            virtual void pause(void);

            /**
             * @brief Simple Implementation of IObject
             *
             */
            virtual void    addTag(const std::string &newTag) noexcept;

            /**
             * @brief Simple Implementation of IObject
             *
             */
            virtual void    setId(unsigned newId) noexcept;

            /**
             * @brief Simple Implementation of IObject
             *
             */
            virtual IScene &                            getScene(void) noexcept;

            /**
             * @brief Simple Implementation of IObject
             *
             */
            virtual const std::vector<std::string> &getTags(void) const noexcept;

            /**
             * @brief Simple Implementation of IObject
             *
             */
            virtual unsigned                            getId(void) const noexcept;

            /**
             * @brief Simple Implementation of IObject
             *
             */
            virtual bool    hasTag(const std::string &tag) const noexcept;

        protected:
            bool _paused = false;
            IScene &                    _scene;
            std::vector<std::string>    _tags;
            unsigned                    _id;
    };
}

#endif /* !OBJECT_HPP_ */
