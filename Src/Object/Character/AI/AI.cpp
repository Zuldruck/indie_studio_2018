/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** AI
*/

#include "AI.hpp"

namespace ind {

AI::AI(IScene &scene, std::vector<std::string> tags) : Character(scene, tags)
{
    _luaState = LuaApi::newState();
    LuaApi::pushFunction(_luaState, &LuaApi::getAIPosition, "getAIPosition");
    LuaApi::pushFunction(_luaState, &LuaApi::getPlayerPosition, "getPlayerPosition");
    LuaApi::pushFunction(_luaState, &LuaApi::getBombsAvailable, "getBombsAvailable");
    LuaApi::pushFunction(_luaState, &LuaApi::getMap, "getMap");
    LuaApi::pushFunction(_luaState, &LuaApi::putDownBomb, "putDownBomb");
    LuaApi::pushFunction(_luaState, &LuaApi::setDirection, "setDirection");
    LuaApi::pushFunction(_luaState, &LuaApi::getMapHeight, "getMapHeight");    
    LuaApi::pushFunction(_luaState, &LuaApi::getMapWidth, "getMapWidth");    
    LuaApi::pushFunction(_luaState, &LuaApi::getNearestEnemyPosition, "getNearestEnemyPosition");
    LuaApi::pushFunction(_luaState, &LuaApi::getPreviousDirection, "getPreviousDirection");
    LuaApi::pushFunction(_luaState, &LuaApi::getBombRange, "getBombRange");
    lua_pushlightuserdata(_luaState, this);
    lua_setglobal(_luaState, "AI");
    getComponent<AnimatedMeshComponent>()->getNode()->setName("AI");
}

    AI::~AI()
    {
        lua_gc(_luaState , LUA_GCCOLLECT, 0);
        lua_close(_luaState);
    }

    void AI::replaceAI(irr::core::vector3df pos)
    {
        if (_prevDirection == "up" && pos.Z > _destination.Z + 5)
            getComponent<AnimatedMeshComponent>()->setPosition(_destination);
        else if (_prevDirection == "down" && pos.Z < _destination.Z - 5)
            getComponent<AnimatedMeshComponent>()->setPosition(_destination);
        else if (_prevDirection == "left" && pos.X < _destination.X - 5)
            getComponent<AnimatedMeshComponent>()->setPosition(_destination);
        else if (_prevDirection == "right" && pos.X > _destination.X + 5)
            getComponent<AnimatedMeshComponent>()->setPosition(_destination);
    }

    void AI::update(float delta)
    {
        irr::core::vector3df pos = getComponent<AnimatedMeshComponent>()->getPosition();

        Character::update(delta);
        _lastAction += delta;
        if ((_prevDirection == "up" && pos.Z >= _destination.Z)
        || (_prevDirection == "down" && pos.Z <= _destination.Z)
        || (_prevDirection == "left" && pos.X <= _destination.X)
        || (_prevDirection == "right" && pos.X >= _destination.X)
        || _prevDirection == "none"
        || (_lastAction > 2000 && isAlive())) {
            if (_prevDirection != "none")
                replaceAI(pos);
            setPrevDirection(_prevDirection);
            makeDecision();
            _lastAction = 0;
        }
    }

    std::vector<std::vector<Map::BlockType>> AI::getMap() const
    {
        auto map = std::static_pointer_cast<Map>(_scene.getObjectsByTags({"MAP"})[0])->getMap();

        std::reverse(map.begin(), map.end());
        return map;
    }

    void AI::makeDecision()
    {
        if (_luaState)
            luaL_dofile(_luaState, _aiFileName.c_str());
    }

    void AI::setPrevDirection(const std::string &prevDirection)
    {
        irr::core::vector3df pos = getComponent<AnimatedMeshComponent>()->getPosition();
        irr::f32 x = static_cast<int>(pos.X / 10.0 + 0.5) * 10;
        irr::f32 z = static_cast<int>(pos.Z / 10.0 + 0.5) * 10;
        
        _prevDirection = prevDirection;
        if (prevDirection == "up")
            _destination = {x, 0, z + 10};
        else if (prevDirection == "down")
            _destination = {x, 0, z - 10};
        else if (prevDirection == "right")
            _destination = {x + 10, 0, z};
        else if (prevDirection == "left")
            _destination = {x - 10, 0, z};
    }

    std::string AI::getPrevDirection() const
    {
        return _prevDirection;
    }

    void AI::setFileName(const std::string &fileName)
    {
        _aiFileName = fileName;
    }

    std::string AI::getFileName() const
    {
        return _aiFileName;
}

}
