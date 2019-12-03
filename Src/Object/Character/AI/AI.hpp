/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** AI
*/

#ifndef AI_HPP_
#define AI_HPP_

#include "Character.hpp"
#include "Map.hpp"
#include "LuaAPI.hpp"
#include "AnimatedMeshComponent.hpp"
#include "IScene.hpp"
#include <algorithm>
#include "Includes.hpp"
#include "EventComponent.hpp"
#include "MovementComponent.hpp"
#include "CollisionComponent.hpp"
#include "BombComponent.hpp"
#include "BomberMan.hpp"
#include "ParticleComponent.hpp"
#include "Factory.hpp"

#ifdef __APPLE__
    #define AI_PATH "OOP_indie_studio_2018/Src/Artificial Intelligences/"
#elif __linux__
    #define AI_PATH "Src/Artificial Intelligences/"
#elif _WIN32
    #define AI_PATH "Artificial Intelligences/"
#endif /* __APPLE__ */

namespace ind {

    /**
     * @brief AI Class is the parent class of all the AIs for the SoloPlayer (and multi)
     * It pushes all the functions needed for AI into the stack.
     * It calls luaDoFile function to execute the script.
     * 
     */
    class AI : public Character {
        public:
            /**
             * @brief Construct a new AI object
             * 
             * @param scene The scene we will add this object
             * @param tags Tags that AI object will have
             */
            AI(IScene &scene, std::vector<std::string> tags = {"AI", "CHARACTER"});
            
            /**
             * @brief Destroy the AI object
             * 
             */
            ~AI();

            /**
             * @brief Overriden update
             * 
             * @param delta 
             */
            void update(float delta);

            /**
             * @brief Get the Map object
             * 
             * @return std::shared_ptr<Map> 
             */
            std::vector<std::vector<Map::BlockType>> getMap() const;

            /**
             * @brief Method to be called to ask the ai to do an action.
             * It calls the lua Script
             * 
             */
            void makeDecision();

            /**
             * @brief Set the Prev Direction object
             * 
             * @param prevDirection 
             */
            void setPrevDirection(const std::string &prevDirection);

            /**
             * @brief Get the Prev Direction object
             * 
             * @return const std::string& 
             */
            std::string getPrevDirection() const;

            /**
             * @brief Set the File Name object
             * 
             */
            void setFileName(const std::string &fileName);

            /**
             * @brief Get the File Name object
             * 
             * @return std::string 
             */
            std::string getFileName() const;

        private:
            /**
             * @brief Replace AI when his position is too far from his destination point 
             * 
             * @param pos 
             */
            void replaceAI(irr::core::vector3df pos);
        
            std::string _aiFileName = "";
            lua_State *_luaState = nullptr;
            std::string _prevDirection = "none";
            irr::core::vector3df _destination = {-1, 0, -1};
            float _lastAction = 0;
    };

}

#endif /* !AI_HPP_ */
