/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include "Includes.hpp"

namespace ind {
    class IScene;
    class IObject;

    /**
     * @brief Factory contain static methods which are called to instanciate objects and component, adding them to their owner.
     * 
     */
    class Factory {
        public:
            Factory() = default;
            ~Factory() = default;

            /**
             * @brief Create a Object by the template and add it to the scene.
             * 
             * @tparam T 
             * @param scene 
             * @return std::shared_ptr<T> 
             */
            template <typename T>
            static std::shared_ptr<T> createObject(IScene &scene);

            /**
             * @brief Create a Component by the template and add it to the owner object.
             * 
             * @tparam T 
             * @param owner 
             * @param isActive 
             * @return std::shared_ptr<T> 
             */
            template <typename T>
            static std::shared_ptr<T> createComponent(
                IObject *owner,
                bool isActive = true);
    };
}

#endif /* !FACTORY_HPP_ */
