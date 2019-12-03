/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/

#ifndef BOMBERMAN_DJCONTROL_H
#define BOMBERMAN_DJCONTROL_H

#include "Menu.hpp"

namespace ind {

    /**
     * @brief djControl which control all song of our game.
     */
    class DjControl {
    public:
        virtual ~DjControl();

        DjControl();

        /**
         * @brief add song to the map.
         * @param path path to the file song.
         * @param name name of the song.
         */
        void addSong(const std::string &path, const std::string &name);

        /**
         * @brief play a song by this name.
         * @param name name of the song in the map.
         */
        void playSong(const std::string &name);

        /**
         * @brief control the volume of a song by this name in the name.
         * @param name name in the map.
         * @param volume volume of this menu (between 0 and 100).
         */
        void controlVolumeSong(const std::string &name, ind_int volume);

        /**
         * @brief stop the song by this name in the map.
         * @param name name of the song in the map.
         */
        void stopSong(const std::string &name);

        /**
         * @brief pause the song by this name.
         * @param name name of the song in the map.
         */
        void pauseSong(const std::string &name);

        /**
         * @brief remove song of the map by this name.
         * @param name name of the song in the map.
         */
        void removeSong(const std::string &name);

        /**
         * @brief set to true a song in the name by this name.
         * @param name name of the song in the map.
         */
        void setLoopToASong(const std::string &name);

        /**
         * @brief get the volume of a song by this name.
         * @param name name of the song in the map.
         * @return return the volume of the song in float
         */
        float getVolumeOfASong(const std::string &name);

    private:
        boost::unordered_map<std::string, std::shared_ptr<sf::Music>> _songMap;

    protected:
    };
}

#endif //BOMBERMAN_DJCONTROL_H
