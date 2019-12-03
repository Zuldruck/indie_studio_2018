/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** Persitantdata.hpp
*/

#ifndef PERSISTANT_DATA_HPP
#define PERSISTANT_DATA_HPP

#include "Includes.hpp"

#ifdef __APPLE__
    #define PERSISTANT_DATA_PATH "OOP_indie_studio_2018/data/persistantData/"
#else
    #define PERSISTANT_DATA_PATH "data/persistantData/"
#endif /* __APPLE__ */

namespace ind {
    /**
     * @brief PersistantData is the class for persist data in files and get data from them
     */
    class PersistantData
    {
        public:
            /**
             * @brief Constructor
             */
            PersistantData                          ();

            /**
             * @brief getValueOfKey is used to know the value of the key
             *
             * @param to_parse std::string that we need to parse
             * @param key the key we want to get the value of
             */
            std::string                             getValueOfKey(std::string const &to_parse, std::string const &key) const;

            /**
             * @brief setDevice is used to update the private _device attribute of the class
             *
             * @param device the new device
             */
            void                                    setDevice(irr::IrrlichtDevice *device);

            /**
             * @brief This method is used to get a data from file 'path' with a key
             *
             * @param path path is the path of the file
             * @param key is the key that we want the value
             */
            std::string                             getDataFromFile(std::string const &path, std::string const &key) const;

            /**
             * @brief This method is used to set a data in file with a key
             *
             * @param path path is the path of the file
             * @param key
             */
            bool                                    putDataOnFile(std::string const &path, std::string const &key, std::string const &value) const;

            /**
             * @brief This method is used to reset the content of a file
             *
             * @param path The path of the file that we will reset
             */
            void                                    reset(std::string path) const;


            /**
             * @brief This method is used to store raw data like parsed scores etc..
             * 
             * @param path The path of the file
             * @param data The string that represents data
             */
            void                                    putRawDataOnFile(std::string path, std::string data, bool append) const;


            /**
             * @brief This method is used to read raw data like parsed scores etc..
             *
             * @param path The path of the file
             * @return The content of the file as an std::string
             */
            std::string                             readRawDataFromFile(std::string path);

        protected:
            irr::IrrlichtDevice*                    _device;

        private:
    };
}

#endif /* !PERSISTANT_DATA_HPP */
