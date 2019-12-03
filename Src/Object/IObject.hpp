/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IObject
*/

#ifndef IOBJECT_HPP_
#define IOBJECT_HPP_

#include "Includes.hpp"

namespace ind {

    class IScene;
    class IComponent;

    typedef std::unordered_map<std::type_index, std::shared_ptr<IComponent>> ComponentsTable;
    /**
     * @brief IComponent is the interface of a game Object
     * 
     */
    class IObject {
        public:
            virtual ~IObject() = default;

            /**
             * @brief Called when everythings has been created.
             * 
             */
            virtual void beginPlay(void) = 0;
            /**
             * @brief Call update of all component. Called every frames (/rate)
             * 
             * @param delta 
             */
            virtual void update(float delta) = 0;

            /**
             * @brief pause and unpause the object.
             * 
             */
            virtual void pause(void) = 0;

            /**
             * @brief Tell if the object has the tag
             * 
             * @param tag 
             * @return true 
             * @return false 
             */
            virtual bool hasTag(const std::string &tag) const noexcept = 0;

            /**
             * @brief Get the object's Id
             * 
             * @return unsigned 
             */
            virtual unsigned getId(void) const noexcept = 0;
            /**
             * @brief Get Tags of object
             * 
             * @return const std::vector<std::string>& 
             */
            virtual const std::vector<std::string> &getTags(void) const noexcept = 0;
            /**
             * @brief Get the Core from object
             * 
             * @return Core& 
             */
            virtual IScene &getScene(void) noexcept = 0;

            /**
             * @brief Get component matching template type passed. Throw if none so be sure.
             * 
             * @tparam T 
             * @return std::shared_ptr<T> 
             */
            template <class T>
            std::shared_ptr<T> getComponent(void)
            {
                auto iterator = _components.find(typeid(T));

                if (iterator != std::end(_components)) {
                    std::shared_ptr<T> convertor = std::static_pointer_cast<T>(iterator->second);
                    return convertor;
                }
                return nullptr;
            }

            /**
             * @brief Set the Id of the object
             * 
             * @param newId 
             */
            virtual void setId(unsigned newId) noexcept = 0;
            /**
             * @brief add a new tag to the object
             * 
             * @param newTag 
             */
            virtual void addTag(const std::string &newTag) noexcept = 0;
            /**
             * @brief add a component to the object. Should be called by the Factory
             * 
             * @tparam T 
             * @param newComponent 
             */
            template <class T>
            void addComponent(std::shared_ptr<T> newComponent)
            {
                auto iterator = _components.find(typeid(T));

                if (iterator == std::end(_components)) {
                    _components[typeid(T)] = newComponent;
                }
            }


        protected:
            ComponentsTable _components;
        private:
    };
}

#endif /* !IOBJECT_HPP_ */