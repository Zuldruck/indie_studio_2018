/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/


#include "DjControl.hpp"

namespace ind {
    DjControl::DjControl() = default;

    DjControl::~DjControl()
    {
        for (const auto& obj : _songMap)
            obj.second->stop();
        this->_songMap.clear();
    }

    void DjControl::playSong(const std::string& name)
    {
        if (_songMap.empty())
            EXCEPTION(std::runtime_error, "Sound can't be found");

        if (_songMap.find(name) == _songMap.end())
            EXCEPTION(std::runtime_error, name + " key can't be found");

        auto song = _songMap.find(name)->second;

        if (!song)
            EXCEPTION(std::runtime_error, name + " second pattern was null");

        song->play();
    }

    void DjControl::addSong(const std::string& path, const std::string& name)
    {
        if (_songMap.find(name) != _songMap.end())
            EXCEPTION(std::runtime_error, name + " key can't be found");

        auto song = std::make_shared<sf::Music>();

        if (!song->openFromFile(path))
            EXCEPTION(std::runtime_error, path + " can't be open.");

        _songMap.insert(std::make_pair(name, song));
    }

    void DjControl::controlVolumeSong(const std::string& name, ind_int volume)
    {
        if (_songMap.find(name) == _songMap.end())
            EXCEPTION(std::runtime_error, name + " key can't be found");

        auto song = _songMap.find(name)->second;

        if (!song)
            EXCEPTION(std::runtime_error, name + " second pattern was null.");

        if (volume < 0 || volume > 100)
            EXCEPTION(std::runtime_error, "You can't set up the volume more than 100 and no less than 0");

        song->setVolume(volume);
    }

    void DjControl::stopSong(const std::string& name)
    {
        if (_songMap.find(name) == _songMap.end())
            EXCEPTION(std::runtime_error, name + " key can't be found");

        auto song = _songMap.find(name)->second;

        if (!song)
            EXCEPTION(std::runtime_error, name + " second pattern can't be found");

        if (song->getStatus() != sf::Sound::Status::Stopped)
            song->stop();
    }

    void DjControl::removeSong(const std::string& name)
    {
        if (_songMap.find(name) == _songMap.end())
            EXCEPTION(std::runtime_error, name + " key can't be found");

        _songMap.erase(name);
    }

    void DjControl::pauseSong(const std::string& name)
    {
        if (_songMap.find(name) == _songMap.end())
            EXCEPTION(std::runtime_error, name + " key can't be found");

        auto song = _songMap.find(name)->second;

        if (!song)
            EXCEPTION(std::runtime_error, name + " second pattern was null.");

        if (song->getStatus() == sf::Sound::Status::Playing)
            song->pause();
    }

    void DjControl::setLoopToASong(const std::string& name)
    {
        if (_songMap.find(name) == _songMap.end())
            EXCEPTION(std::runtime_error, name + " key can't be found");

        auto song = _songMap.find(name)->second;

        if (!song)
            EXCEPTION(std::runtime_error, name + " second pattern was null.");

        song->setLoop(true);
    }

    float DjControl::getVolumeOfASong(const std::string& name)
    {
        if (_songMap.find(name) == _songMap.end())
            EXCEPTION(std::runtime_error, name + " key can't be found");

        auto song = _songMap.find(name)->second;

        if (!song)
            EXCEPTION(std::runtime_error, name + " second pattern was null.");

        return (song->getVolume());
    }
}
