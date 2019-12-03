/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Object
*/

#include "Object.hpp"
#include "IComponent.hpp"
#include "IScene.hpp"
#include "AnimatedMeshComponent.hpp"
#include "EventComponent.hpp"

namespace ind {
    Object::Object(IScene &scene, std::vector<std::string> tags)
        : _scene(scene),
        _tags(tags)
    {
    }

    Object::~Object()
    {
        if (getComponent<EventComponent>() != nullptr) {
            getScene().getEventReceiver()->removeComponent(getComponent<EventComponent>());
        }

        _components.clear();
    }

    void    Object::beginPlay(void)
    {
        BOOST_FOREACH(auto &component, _components)
            component.second->beginPlay();
    }

    void    Object::update(float delta)
    {
        BOOST_FOREACH(auto &component, _components)
            component.second->update(delta);
    }

    void Object::pause(void)
    {
        if (_paused) {
            _paused = false;
        } else {
            _paused = true;
        }
        BOOST_FOREACH(auto &component, _components)
            component.second->pause();
    }

    void    Object::addTag(const std::string &newTag) noexcept
    {
        _tags.push_back(newTag);
    }

    void    Object::setId(unsigned newId) noexcept
    {
        _id = newId;
    }

    IScene &Object::getScene(void) noexcept
    {
        return _scene;
    }

    const std::vector<std::string> &Object::getTags(void) const noexcept
    {
        return _tags;
    }

    unsigned Object::getId(void) const noexcept
    {
        return _id;
    }

    bool    Object::hasTag(const std::string &tag) const noexcept
    {
        for (auto &e : _tags)
            if (e == tag)
                return true;
        return false;
    }
}