/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** ScoreManager.cpp
*/

#include "Includes.hpp"
#include "ScoreManager.hpp"
#include <boost/range/algorithm.hpp>


namespace ind
{
    ScoreManager::ScoreManager() : _device(nullptr)
    {
    }

    ScoreManager::~ScoreManager()
    {
    }

    void    ScoreManager::setDevice(irr::IrrlichtDevice *device)
    {
        _device = device;
        _persistantData.setDevice(_device);
    }

    void    ScoreManager::saveOnFile(void)
    {
        if (_device != nullptr) {
            for (auto &it : _scorePlayer) {
                _persistantData.putRawDataOnFile(_path, it._name + ";" + std::to_string(it._time) + ":" +
                                                        std::to_string(it._score) + "\r\n", true);
            }
        }
    }

    void    ScoreManager::loadFromFile(void)
    {
        std::string to_parse = _persistantData.readRawDataFromFile(_path);
        std::istringstream iss(to_parse);
        std::string tmp;
        ScorePlayer sp("", 0, 0);

        _scorePlayer.clear();
        while (getline(iss, tmp, '\n')) {
            sp._name = tmp.substr(0, tmp.find(';'));
            sp._time = std::atoi((tmp.substr(tmp.find(';') + 1, tmp.find(':')).c_str()));
            sp._score = std::atoi((tmp.substr(tmp.find(':') + 1, std::string::npos)).c_str());
            _scorePlayer.push_back(sp);
        }
    }

    void    ScoreManager::addScore(std::string name, unsigned int score) noexcept
    {
        ScorePlayer ps(name, std::time(nullptr), score);
        _scorePlayer.push_back(ps);
    }

    void    ScoreManager::reset(void)  noexcept
    {
        _persistantData.reset(_path);
    }

    std::vector<ScorePlayer> &ScoreManager::getScorePlayer()
    {
        std::sort( _scorePlayer.begin(), _scorePlayer.end(),
              []( ScorePlayer &left, ScorePlayer &right )
                 { return ( left._score > right._score ); } );

        return _scorePlayer;
    }
}
