/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/

#ifndef BOMBERMAN_MAPANYTYPES_HPP
#define BOMBERMAN_MAPANYTYPES_HPP

#include <Menu.hpp>

namespace ind {

    typedef boost::variant<irr::gui::IGUIScrollBar *, irr::gui::IGUIEditBox *, irr::gui::IGUIListBox *> mapTypes;

    typedef boost::unordered_map<std::string, mapTypes> mapAnyType;

    /**
     * @brief A class for a map with any types that you want to add.
     */
    class MapAnyTypes {
    public:
        MapAnyTypes() = default;

        ~MapAnyTypes() = default;

        /**
         * @brief insert like the insert of std::map
         * @tparam T type of second pattern.
         * @param key key of the obj that we would like to add in the map.
         * @param value obj of the second pattern that we would like to add in the map.
         */
        template<typename T>
        void insert(const std::string &key, const T &value) {
            if (exists(key))
                EXCEPTION(std::runtime_error, "Duplicate key");

            _mapExtra[key] = value;
        }

        /**
         * @brief find like std::find
         * @tparam T type of value that we would like to get.
         * @param key key of the value that we would like to get.
         * @return return of the second pattern.
         */
        template<typename T>
        const T &find(const std::string &key) const {
            if (!exists(key))
                EXCEPTION(std::runtime_error, "Can't find" + key);

            return boost::get<T>(_mapExtra.find(key)->second);
        }

        /**
         * @brief check if key requested exist in the map.
         * @param key key that we would like to check.
         * @return true if key exist false otherwise.
         */
        bool exists(const std::string &key) const {
            return !(_mapExtra.end() == _mapExtra.find(key));
        }

        /**
         * @brief clear the map.
         */
        void clear() {
            _mapExtra.clear();
        }

        /**
         * @brief get the size of the map.
         * @return size of the map.
         */
        int size() const {
            return (_mapExtra.size());
        }

        /**
         * @brief get the map of extra types.
         * @return a map.
         */
        const mapAnyType &getMapExtra() const {
            return _mapExtra;
        }

    private:
        mapAnyType _mapExtra;

    };
}


#endif //BOMBERMAN_MAPANYTYPES_HPP
