/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** LuaAPI
*/

#ifndef LUAAPI_HPP_
#define LUAAPI_HPP_

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include "AI.hpp"

namespace ind {

/**
 * @brief LuaApi is the api to do the link between LUA and C++.
 * It communicates thanks to the stack by pushing C++ variables into it.
 * Lua gets it and uses it to compute the ai movements.
 * 
 */
class LuaApi {
	public:
		LuaApi() = default;
		~LuaApi() = default;
        
        /**
         * @brief Get the Player Position object
         * 
         * @param L 
         * @return int 
         */
        static int getPlayerPosition(lua_State *L);

        /**
         * @brief Get the Map Object
         * 
         * @param L lua_state
         * @return int number of variables returned
         */
        static int getMap(lua_State *L);

        /**
         * @brief Get the Bombs Available object
         * 
         * @param L 
         * @return int 
         */
        static int getBombsAvailable(lua_State *L);

        /**
         * @brief Get the AI Position
         * 
         * @param L 
         * @return int 
         */
        static int getAIPosition(lua_State *L);

        /**
         * @brief Get the Nearest Enemy Position
         * 
         * @param L 
         * @return int 
         */
        static int getNearestEnemyPosition(lua_State *L);

        /**
         * @brief Push a C++ function to the stack
         * 
         * @param luaState 
         * @param ptr function pointer
         * @param name name of the function (for Lua)
         */
        static void pushFunction(lua_State *L, int (*ptr)(lua_State *L), const std::string &name);
        
        /**
         * @brief Create a new luaState to communicate between C++ and Lua with the stack
         * 
         * @return lua_State* new state
         */
        static lua_State *newState();

        /**
         * @brief Set the Direction object
         * 
         * @param L 
         * @return int 
         */
        static int setDirection(lua_State *L);

        /**
         * @brief tells the ai to put down a bomb
         * 
         * @param L luaState 
         * @return int number of variables returned
         */
        static int putDownBomb(lua_State *L);

        /**
         * @brief Get the Width of the map
         * 
         * @param L 
         * @return int 
         */
        static int getMapWidth(lua_State *L);

        /**
         * @brief Get the Height of the map
         * 
         * @param L 
         * @return int 
         */
        static int getMapHeight(lua_State *L);

        /**
         * @brief Get the Previous Direction object
         * 
         * @param L 
         * @return int 
         */
        static int getPreviousDirection(lua_State *L);

        /**
         * @brief Get the Bombe Range object
         * 
         * @param L 
         * @return int 
         */
        static int getBombRange(lua_State *L);
    
    private:
        /**
         * @brief Mirror the X coordinate 
         * 
         * @param actualX 
         * @param height 
         * @return int 
         */
        static int mirrorCoordX(int actualX, int height);
};

}

#endif /* !LUAAPI_HPP_ */
