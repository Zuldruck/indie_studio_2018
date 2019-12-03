/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/


#include <Menu/Menu.hpp>
#include "MenuScene.hpp"
#include "BomberMan.hpp"
#include "Factory.hpp"
#include "Map.hpp"
#include "Player.hpp"

namespace ind
{
    ind::MenuScene::MenuScene(ind::Core &core, bool firstTime) : _core(core)
    {
        _manager = core.getDevice()->getSceneManager();
        _manager->clear();
        _firstTime = firstTime;
        _mainMenu = std::make_unique<Menu>(core, firstTime);
    }

    ind::MenuScene::~MenuScene()
    {

    }

    void ind::MenuScene::draw(float delta) noexcept
    {
        _core.getDriver()->beginScene(true, true, irr::video::SColor(255, 40, 44, 52));

        _mainMenu->draw(delta);
    }

    void ind::MenuScene::update(float delta)
    {
        for (unsigned int i = 0; i < _objects.size(); i++)
            _objects[i]->update(delta);
    }

    void ind::MenuScene::beginPlay(void)
    {
        Factory::createObject<Player>(*this);
    }

    void ind::MenuScene::pause(void)
    {
        
    }

    ind::Core &ind::MenuScene::getCore(void) noexcept
    {
        return _core;
    }

    std::unique_ptr<ind::EventReceiver> &ind::MenuScene::getEventReceiver(void) noexcept
    {
        return _evtReceiver;
    }

    irr::scene::ISceneManager *ind::MenuScene::getManager(void) const noexcept
    {
        return _manager;
    }

    std::shared_ptr<ind::CollisionManager> ind::MenuScene::getCollisionManager(void) noexcept
    {
        return _collisionManager;
    }

    const std::vector<std::shared_ptr<ind::IObject>> &ind::MenuScene::getObjects(void) const noexcept
    {
        return _objects;
    }

    std::vector<std::shared_ptr<ind::IObject>> ind::MenuScene::getObjectsByTags(const std::string &tag) const noexcept
    {
        std::vector<IObject_ptr > objects;

        for (auto &obj : _objects)
        {
            if (obj->hasTag(tag) == true)
            {
                objects.push_back(obj);
            }
        }
        return objects;
    }

    std::shared_ptr<ind::IObject> ind::MenuScene::getObjectByID(unsigned ID) const noexcept
    {
        for (auto &obj : _objects)
            if (obj->getId() == ID)
                return (obj);
        return nullptr;
    }

    void ind::MenuScene::addObject(std::shared_ptr<ind::IObject> newObject) noexcept
    {
        _objects.push_back(newObject);
        newObject->setId(_IDs);
        _IDs++;
    }

    void ind::MenuScene::removeObject(IObject_ptr toRemove) noexcept
    {
        for (auto it = _objects.begin(); it != _objects.end(); it++) {
            if (it->get() == toRemove.get()) {
                _objects.erase(it);
                break;
            }
        }
    }

    void ind::MenuScene::removeObject(IObject *toRemove) noexcept
    {
        for (auto it = _objects.begin(); it != _objects.end(); it++) {
            if (it->get() == toRemove) {
                _objects.erase(it);
                break;
            }
        }

    }

    void ind::MenuScene::generateLobby()
    {
        Factory::createObject<Player>(*this);
    }
    const std::unique_ptr<Menu> &MenuScene::getMainMenu() const
    {
        return _mainMenu;
    }
}