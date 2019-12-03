/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** ScoreManager.hpp
*/

#ifndef __SCORE_MANAGER_HPP
#define __SCORE_MANAGER_HPP

#include "Includes.hpp"
#include "PersistantData.hpp"

namespace ind
{

    struct ScorePlayer
    {
        ScorePlayer(std::string name, std::time_t time, int score) : _name(name), _time(time), _score(score)
        {}

        std::string         _name;
        std::time_t         _time;
        int        _score;
    };
    /**
     * @brief ScoreManager is the class that will manage all things about the score, like save it in a file etc..
     *
     */
    class ScoreManager
    {
    public:

        /**
         * @brief Construct the ScoreManager
         *
         */
        ScoreManager();


        /**
         * @brief Destruct the ScoreManager
         *
         */
        ~ScoreManager();


        /**
         * @brief Assign a device for this object
         *
         * @param device The device
         */
        void setDevice(irr::IrrlichtDevice *device);


        /**
         * @brief This method is used to save all the content of the scoreManager in a file
         *
         */
        void saveOnFile(void);


        /**
         * @brief This method is used to load from file all the content for the scoreManager
         *
         */
        void loadFromFile(void);


        /**
         * @brief This method is used to add a score in the memory of this class
         *
         * @param name Name is the name of the player
         * @paran score Score is the score of the player
         */
        void addScore(std::string name, unsigned int score) noexcept;


        /**
         * @brief This method is used to reset all the data of the class
         *
         */
        void reset(void) noexcept;

        /**
         * @brief Get all scores.
         * @return return vector of all score with this type : name;timestamp:score
         */
        std::vector<ScorePlayer> &getScorePlayer();

    protected:

    private:
        PersistantData              _persistantData;
        std::string                 _path = "scores.data";
        std::vector<ScorePlayer>    _scorePlayer;

    private:
        irr::IrrlichtDevice        *_device;
    };
}

#endif /* !__SCORE_MANAGER_HPP */

