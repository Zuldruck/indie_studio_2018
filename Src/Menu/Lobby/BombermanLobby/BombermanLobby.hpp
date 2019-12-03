/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/

#ifndef BOMBERMAN_BOMBERMANLOBBY_H
#define BOMBERMAN_BOMBERMANLOBBY_H

#include "Includes.hpp"

namespace ind {

    class BombermanLobby {
    public:
        BombermanLobby(int id, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver);
        virtual ~BombermanLobby();

        /**
         * @brief init all textures bomberman
         */
        void initTextureBomberman();

        /**
         * @brief Set if the Bomberman is a Player or an IA
         * @param Player mode
         */
        void setPlayerMode(std::string playerMode);

        /**
        * @brief Set player Name according to its mode
        */
        void setPlayerName();

        /**
        * @brief Update texture bomberman
        * @param texture color
        */
        void setPlayerTexture(std::string playerTexture);

        /**
        * @brief get player name
        * @return player name
        */
        std::string getPlayerName();

        /**
        * @brief get player Texture
        * @return texture path
        */
        std::string getPlayerTexture();

        /**
        * @brief get player Mode
        * @return player mode
        */
        std::string getPlayerMode();

    private:
        irr::IrrlichtDevice *_saveDevice;
        irr::video::IVideoDriver *_saveDriver;

        int _id;
        std::string _playerMode = "PLAYER";
        std::string _playerName;
        std::string _playerTexture = "default";
        irr::scene::IAnimatedMeshSceneNode *_playerNode;

        std::map<std::string, std::string> _mapTextureBomberman;

        std::string _path;
    };
}

#endif //BOMBERMANLOBBY_credits_H
