/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/

#include "BombermanLobby.hpp"

namespace ind {

    BombermanLobby::BombermanLobby(int id, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        this->_id = id;
        this->_saveDevice = device;
        this->_saveDriver = driver;
        this->_path = getcwd(nullptr, 0);
#ifdef __APPLE__
        _path += "/OOP_indie_studio_2018";
#endif /* !__APPLE__ */
        irr::scene::IAnimatedMesh *meshBomberman = this->_saveDevice->getSceneManager()->getMesh(
                std::string(std::string(_path) + "/Assets/bomberman/bomberman-test.b3d").c_str());
        this->_playerNode = this->_saveDevice->getSceneManager()->addAnimatedMeshSceneNode(
                meshBomberman, 0, -1,
                irr::core::vector3df(((this->_id - 1) * 2.5f) - 1, 0.0f, -8),
                irr::core::vector3df(0.0f, 0.0f, 0.0f));
        this->_playerNode->setMaterialTexture(0, this->_saveDriver->getTexture(
                std::string(std::string(_path) + "/" + "Assets/Textures/Bomberman/bomberman.png").c_str()));
        this->_playerNode->setAnimationSpeed(10);
        this->_playerNode->setFrameLoop(185, 235);
        this->_playerNode->setCurrentFrame(180 + (rand() % 30));
        this->initTextureBomberman();
        this->_playerMode = "PLAYER";
        this->setPlayerName();
    }

    BombermanLobby::~BombermanLobby()
    {
    }

    void BombermanLobby::initTextureBomberman()
    {
        _mapTextureBomberman.insert(std::make_pair("default", _path + "/Assets/Textures/Bomberman/bomberman.png"));
        _mapTextureBomberman.insert(std::make_pair("black", _path + "/Assets/Textures/Bomberman/bomberman-black.png"));
        _mapTextureBomberman.insert(std::make_pair("yellow", _path + "/Assets/Textures/Bomberman/bomberman-yellow.png"));
        _mapTextureBomberman.insert(std::make_pair("blue", _path + "/Assets/Textures/Bomberman/bomberman-blue.png"));
        _mapTextureBomberman.insert(std::make_pair("red", _path + "/Assets/Textures/Bomberman/bomberman-jordan.png"));
    }

    void BombermanLobby::setPlayerMode(std::string playerMode)
    {
        this->_playerMode = playerMode;
        setPlayerName();
    }

    void BombermanLobby::setPlayerName()
    {
        this->_playerName = this->_playerMode + " " + std::to_string(_id);
    }

    void BombermanLobby::setPlayerTexture(std::string playerTexture)
    {
        this->_playerNode->setMaterialTexture(0, this->_saveDriver->getTexture(
                std::string(_mapTextureBomberman.find(playerTexture)->second).c_str()));
        this->_playerTexture = playerTexture;
    }

    std::string BombermanLobby::getPlayerName()
    {
        return this->_playerName;
    }

    std::string BombermanLobby::getPlayerTexture()
    {
        return this->_playerTexture;
    }

    std::string BombermanLobby::getPlayerMode()
    {
        return this->_playerMode;
    }

}