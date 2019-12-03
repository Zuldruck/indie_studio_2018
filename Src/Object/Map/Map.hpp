/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include "Object.hpp"
#include "Includes.hpp"
#include "Utils.hpp"
#include "BomberMan.hpp"

#ifdef __APPLE__
    #define MAP_OFFSET "OOP_indie_studio_2018/Maps/"
    #define MAP_MULTI_OFFSET "OOP_indie_studio_2018/Maps/Multi/"
#elif __linux__
    #define MAP_OFFSET "Maps/"
    #define MAP_MULTI_OFFSET "Maps/Multi/"
#elif _WIN32
    #define MAP_OFFSET "Maps/"
    #define MAP_MULTI_OFFSET "Maps/Multi/"
#endif /* __APPLE__ */

#include "Exit.hpp"

#define BOX_SPAWNRATE 0.3

enum mobType {
    BLOB = 0,
    DODGER = 1,
    LEEROY = 2,
    BOMBER = 3,
};

struct levelProbability {
    short maxLevel;
    std::vector<std::pair<mobType, short>> mobs;
    short maxMobs;
};

namespace ind {
    class Wall;
    class Box;
    class Player;
    class Character;

    /**
     * @brief Map object open, generate and draw the Map and all of its content
     * 
     */
    class Map : public Object {
    public:
        /**
         * @brief All the Types of Block which can be contained in the Map
         *
         */
        enum BlockType {
            EMPTY = 0,
            FENCE = 1,
            WALL = 2,
            BOX = 3,
            EXIT = 4,
            BOMB = 5,
            FIRE = 6,
            BONUS = 7,
        };

        /**
         * @brief Construct a new Map object
         *
         * @param scene
         * @param tags
         */
        Map(
                IScene &scene,
                std::vector<std::string> tags = {"MAP"});
        /**
         * @brief Destroy the Map object
         *
         */
        ~Map();

        void        update(float delta) override;

        /**
         * @brief Check if the position checked belongs to a corner of the Map
         *
         * @param x position X
         * @param z position Z
         * @return true the position belongs to a corner
         * @return false the position do not belongs to a corner
         */
        bool        checkCornerMap(int x, int z) noexcept;

        /**
         * @brief Check if the position checked belongs to the extremity of corner of the Map
         * 
         * @param x position X
         * @param z position Z
         * @return true the position belongs to the extremity of a corner
         * @return false the position do not belongs to the extremity of a corner
         */
        bool        checkCornerMapExtremity(int x, int z) noexcept;

        /**
         * @brief Check if a box can be placed to the position
         * A Box is placed if:
         * - a randomly generated number is under a certain percentage
         * - the position is not in corner of the Map
         *
         * @param x position X
         * @param z position Z
         * @return true the box can be placed
         * @return false the box canno't be placed
         */
        bool        checkPutBox(int x, int z) noexcept;

        /**
         * @brief Generate random positions until it placed a certain number of Mob on EMPTY position of the Map
         *
         */
        void        putMob(void) noexcept;

        /**
         * @brief Generate random positions until it placed the Exit portal on EMPTY position of the Map
         *
         */
        void        putExit(void) noexcept;

        /**
         * @brief Place all the players to their belonged position
         *
         */
        void        putPlayers(void) noexcept;

        /**
         * @brief Set the Fence Rotation in fonction of their position
         *
         * @param x position X
         * @param z position Z
         * @param block Fence's object
         */
        void        setFenceRotation(int x, int z, std::shared_ptr<Block> block) noexcept;

        /**
         * @brief Open The file which contains the pattern of the Map ans stock it
         *
         * @param filename Name of the file which contains the pattern of the Map
         */
        void        openMapFile(const std::string & filename) noexcept;

        /**
         * @brief Generate the Boxes and the Mobs of the Map
         *
         */
        void        generateMap(void) noexcept;

        /**
         * @brief Draw all the objects of the Map
         *
         */
        void        drawMap(void) noexcept;


        /**
         * @brief Get the Map pattern
         *
         * @return std::vector<std::vector<BlockType>>& Map pattern
         */
        std::vector<std::vector<BlockType>> &   getMap(void) noexcept;

        /**
         * @brief Get the Height of the Map
         *
         * @return int Height of the Map
         */
        int             getHeight(void) const noexcept;

        /**
         * @brief Get the Width of the Map
         *
         * @return int Width of the Map
         */
        int             getWidth(void) const noexcept;

        /**
         * @brief Get the Name of the Map
         *
         * @return std::string Name of the Map
         */
        std::string     getName(void) const noexcept;

        /**
         * @brief Get the Number of mob on the Map
         *
         * @return unsigned int Number of mob on the Map
         */
        unsigned int    getNbMob(void) const noexcept;


        /**
         * @brief Set the number of mob on the Map
         * 
         * @param nbMob number of mob on the Map
         */
        void            setNbMob(int nbMob) noexcept;

        /**
         * @brief Remove a player of the Map
         *
         * @param player Player to remove
         */
        void            removePlayer(Character * player) noexcept;

        /**
         * @brief Reset the Map.
         * Destroy all the Walls, Boxes and Exit portal of the Map
         *
         */
        void            reset(void);

        /**
         * @brief Pass to the next Level
         * Reset the Map
         * Load the new Map
         *
         */
        void            nextLevel(void);

        void            debugShowMap(void) const noexcept;

    private:
        /**
         * @brief Pick an ai randomly through the level probabilities
         *
         * @param level
         * @return std::shared_ptr<AI>
         */
        std::shared_ptr<Object> pickAI(levelProbability level);

        /**
         * @brief Get the Level Probability object
         *
         * @return levelProbability
         */
        levelProbability    getLevelProbability() const;

        std::vector<std::vector<BlockType>> _map;

        int                                 _height;
        int                                 _width;
        std::string                         _name;

        std::vector<std::shared_ptr<Character>>    _players;

        boost::property_tree::ptree         _root;

        std::vector<std::string>            _nameMaps;

        std::vector<std::string>            _levelsName;
        unsigned int                        _nbPlayers;
        unsigned int                        _nbMob;
        bool                                _isMulti;
    };
}

#endif /* !MAP_HPP_ */
