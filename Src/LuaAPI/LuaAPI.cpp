/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** LuaAPI
*/

#include "LuaAPI.hpp"
#include "AnimatedMeshComponent.hpp"
#include "MovementComponent.hpp"
#include "BombComponent.hpp"
#include "IScene.hpp"
#include "Bomber.hpp"

namespace ind {

lua_State *LuaApi::newState()
{
    lua_State *L;

    L = luaL_newstate();
    luaL_openlibs(L);
    return (L);
}

int LuaApi::mirrorCoordX(int actualX, int height)
{
    return (height - 1) - actualX;
}

int LuaApi::getPlayerPosition(lua_State *L)
{
    AI *aiPointer = static_cast<AI *>(lua_touserdata(L, 1));
    std::shared_ptr<IObject> player = aiPointer->getScene().getObjectsByTags("PLAYER")[0];
    irr::core::vector3df playerPos = player->getComponent<AnimatedMeshComponent>()->getPosition();
    int x = 0;
    int y = 0;

    y = static_cast<int>(playerPos.X / 10.0 + 0.5);
    x = static_cast<int>(playerPos.Z / 10.0 + 0.5);
    x = mirrorCoordX(x, aiPointer->getMap().size());
    lua_newtable(L);
    lua_pushstring(L, "x");
    lua_pushinteger(L, x);
    lua_settable(L, -3);
    lua_pushstring(L, "y");
    lua_pushinteger(L, y);
    lua_settable(L, -3);
    return 1;
}

int LuaApi::getAIPosition(lua_State *L)
{
    AI *aiPointer = static_cast<AI *>(lua_touserdata(L, 1));
    irr::core::vector3df pos = aiPointer->getComponent<AnimatedMeshComponent>()->getPosition();
    int x = 0;
    int y = 0;

    y = static_cast<int>(pos.X / 10.0 + 0.5);
    x = static_cast<int>(pos.Z / 10.0 + 0.5);
    x = mirrorCoordX(x, aiPointer->getMap().size());
    lua_newtable(L);
    lua_pushstring(L, "x");
    lua_pushinteger(L, x);
    lua_settable(L, -3);
    lua_pushstring(L, "y");
    lua_pushinteger(L, y);
    lua_settable(L, -3);
    return 1;
}

int LuaApi::getNearestEnemyPosition(lua_State *L)
{
    AI *aiPointer = static_cast<AI *>(lua_touserdata(L, 1));
    std::vector<std::shared_ptr<IObject>> enemies = aiPointer->getScene().getObjectsByTags("CHARACTER");
    irr::core::vector3df pos = aiPointer->getComponent<AnimatedMeshComponent>()->getPosition();
    irr::core::vector3df enemyPos;
    int x = 0;
    int y = 0;
    int xDistance = 0;
    int yDistance = 0;
    int oldDistance = -1;

    pos.Y = static_cast<int>(pos.X / 10.0 + 0.5);
    pos.X = static_cast<int>(pos.Z / 10.0 + 0.5);
    pos.X = mirrorCoordX(pos.X, aiPointer->getMap().size());
    for (auto &i: enemies) {
        if (i->getId() == aiPointer->getId())
            continue;
        enemyPos = i->getComponent<AnimatedMeshComponent>()->getPosition();
        enemyPos.Y = static_cast<int>(enemyPos.X / 10.0 + 0.5);
        enemyPos.X = static_cast<int>(enemyPos.Z / 10.0 + 0.5);
        enemyPos.X = mirrorCoordX(enemyPos.X, aiPointer->getMap().size());
        xDistance = enemyPos.X > pos.X ? enemyPos.X - pos.X : pos.X - enemyPos.X;
        yDistance = enemyPos.Y > pos.Y ? enemyPos.Y - pos.Y : pos.Y - enemyPos.Y;
        if (oldDistance == -1
        || xDistance + yDistance < oldDistance) {
            oldDistance = xDistance + yDistance;
            x = enemyPos.X;
            y = enemyPos.Y;
        }
    }
    lua_newtable(L);
    lua_pushstring(L, "x");
    lua_pushinteger(L, x);
    lua_settable(L, -3);
    lua_pushstring(L, "y");
    lua_pushinteger(L, y);
    lua_settable(L, -3);
    return 1;
}

int LuaApi::getMap(lua_State *L)
{
    AI *aiPointer = static_cast<AI *>(lua_touserdata(L, 1));
    std::vector<std::vector<ind::Map::BlockType>> map = aiPointer->getMap();
    int x = 0;
    int y = 0;

    lua_newtable(L);
    for (auto &row: map) {
        lua_pushinteger(L, x);
        lua_newtable(L);
        for (auto &col: row) {
            static_cast<void>(col);
            lua_pushinteger(L, y);
            lua_pushinteger(L, map[x][y]);
            lua_settable(L, -3);
            ++y;
        }
        lua_settable(L, -3);
        ++x;
        y = 0;
    }
    return 1;
}

void LuaApi::pushFunction(lua_State *luaState, int (*ptr)(lua_State *L), const std::string &name)
{
    lua_register(luaState, name.c_str(), ptr);
}

int LuaApi::setDirection(lua_State *luaState)
{
    AI *aiPointer = static_cast<AI *>(lua_touserdata(luaState, 1));
    std::string direction = lua_tostring(luaState, 2);
    std::shared_ptr<MovementComponent> mov = aiPointer->getComponent<MovementComponent>();

    if (direction == "none")
        mov->setDirection({0, 0, 0});
    else if (direction == "left")
        mov->setDirection({-1, 0, 0});
    else if (direction == "right")
        mov->setDirection({1, 0, 0});
    else if (direction == "down")
        mov->setDirection({0, 0, -1});
    else if (direction == "up")
        mov->setDirection({0, 0, 1});
    mov->updateMovement();
    aiPointer->setPrevDirection(direction);
    return 0;
}

int LuaApi::putDownBomb(lua_State *luaState)
{
    Bomber *aiPointer = static_cast<Bomber *>(lua_touserdata(luaState, 1));
    std::shared_ptr<BombComponent> bombComponent = static_cast<BomberMan *>(aiPointer)->getComponent<BombComponent>();

    bombComponent->arm();
    return 0;
}

int LuaApi::getMapWidth(lua_State *luaState)
{
    AI *aiPointer = static_cast<AI *>(lua_touserdata(luaState, 1));
    std::vector<std::vector<ind::Map::BlockType>> map = aiPointer->getMap();

    lua_pushinteger(luaState, map[0].size());
    return 1;
}

int LuaApi::getMapHeight(lua_State *luaState)
{
    AI *aiPointer = static_cast<AI *>(lua_touserdata(luaState, 1));
    std::vector<std::vector<ind::Map::BlockType>> map = aiPointer->getMap();

    lua_pushinteger(luaState, map.size());
    return 1;
}

int LuaApi::getBombsAvailable(lua_State *luaState)
{
    Bomber *aiPointer = static_cast<Bomber *>(lua_touserdata(luaState, 1));
    std::shared_ptr<BombComponent> bombComponent = static_cast<BomberMan *>(aiPointer)->getComponent<BombComponent>();
   
    lua_pushinteger(luaState, bombComponent->getAvailableBombs());
    return 1;
}

int LuaApi::getPreviousDirection(lua_State *luaState)
{
    AI *aiPointer = static_cast<AI *>(lua_touserdata(luaState, 1));
    std::string dir = aiPointer->getPrevDirection();

    lua_pushstring(luaState, dir.c_str());
    return 1;
}

int LuaApi::getBombRange(lua_State *luaState)
{
    Bomber *aiPointer = static_cast<Bomber *>(lua_touserdata(luaState, 1));

    lua_pushinteger(luaState, aiPointer->getRange());
    return 1;
}

}
