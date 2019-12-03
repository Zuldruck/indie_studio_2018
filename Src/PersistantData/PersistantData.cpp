/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** Persitantdata.hpp
*/

#include "PersistantData.hpp"

namespace ind
{
    PersistantData::PersistantData() : _device(nullptr)
    {
    }

    void PersistantData::setDevice(irr::IrrlichtDevice *device)
    {
        _device = device;
    }

    void        PersistantData::reset(std::string path) const
    {
        std::ofstream ofs;
        ofs.open(path, std::ofstream::out | std::ofstream::trunc);
        ofs.close();
    }

    std::string PersistantData::getValueOfKey(std::string const &to_parse, std::string const &key) const
    {
        std::istringstream iss(to_parse);
        std::string tmp;
        std::string ret;

        while (getline(iss, tmp, '\n')) {
            if (tmp.substr(0, tmp.find(':')) == key) {
                ret = tmp.substr(tmp.find(':') + 1, std::string::npos);
            }
        }
        return ret;
    }

    std::string PersistantData::getDataFromFile(std::string const &path, std::string const &key) const
    {
        irr::io::IReadFile *file = nullptr;
        char buffer[4096];
        std::string to_parse;
        std::cout << (PERSISTANT_DATA_PATH + path).c_str() << std::endl;
        irr::io::path irrpath((PERSISTANT_DATA_PATH + path).c_str());
        int ret = 0;

        if (_device == nullptr)
            return "";

        file = _device->getFileSystem()->createAndOpenFile(irrpath);
        if (!file)
            return "";
        ret = file->read(buffer, 4096);
        buffer[ret] = 0;
        to_parse = buffer;
        return getValueOfKey(to_parse, key);
    }

    std::string PersistantData::readRawDataFromFile(std::string path)
    {
        irr::io::IReadFile *file = nullptr;
        char buffer[4096];
        int ret = 0;
        irr::io::path irrpath((PERSISTANT_DATA_PATH + path).c_str());

        if (_device == nullptr)
            return "";

        file = _device->getFileSystem()->createAndOpenFile(irrpath);

        if (!file)
            return "";

        ret = file->read(buffer, 4096);
        buffer[ret] = 0;
        std::string str(buffer);
        return str;
    }

    bool PersistantData::putDataOnFile(std::string const &path, std::string const &key, std::string const &value) const
    {
        irr::io::path irrpath((PERSISTANT_DATA_PATH + path).c_str());

        if (!_device->getFileSystem()) {
            std::cerr << "PersistantData Error : !_device->getFileSystem()" << std::endl;
            return false;
        }
        irr::io::IWriteFile *file = _device->getFileSystem()->createAndWriteFile(irrpath, true);
        std::string to_write = key + ":" + value + "\r\n";

        if (!file) {
            std::cerr << "PersistantData Error : !file " << std::endl;
            return false;
        }

        file->write(to_write.c_str(), to_write.size());
        delete file;
        return true;
    }

    void        PersistantData::putRawDataOnFile(std::string path, std::string data, bool append) const
    {
        irr::io::path irrpath((PERSISTANT_DATA_PATH + path).c_str());

        if (!_device) {
            std::cerr << "PersistantData Error : !_device" << std::endl;
            return;
        }

        if (!_device->getFileSystem()) {
            std::cerr << "PersistantData Error : !_device->getFileSystem()" << std::endl;
            return;
        }

        irr::io::IWriteFile *file = _device->getFileSystem()->createAndWriteFile(irrpath, append);
        if (!file) {
            std::cerr << "PersistantData Error : !file" << std::endl;
            return;
        }
        file->write(data.c_str(), data.size());
        delete file;
    }


}
