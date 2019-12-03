/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/


#ifndef BOMBERMAN_IMENU_H
#define BOMBERMAN_IMENU_H


#ifdef __APPLE__
#include <irrlicht/irrlicht.h>
#endif /* __APPLE__*/

#ifdef __linux__
#include <irrlicht.h>
#endif /* __linux__ */

#include "Includes.hpp"
#include "Object.hpp"
#include <boost/unordered_map.hpp>
#include <SFML/Audio.hpp>
#include <boost/variant.hpp>
#include "DjControl.hpp"
#include "Core.hpp"
#include "MapAnyTypes.hpp"


namespace ind {

    /**
     * @brief Interface for generic menu.
     */
    class IMenu {
    public:

        /**
         * @brief Draw GUI menu.
         */
        virtual void drawGUi(float delta) = 0;

        /**
         * @brief Test if this menu is _active.
         * @return return true if the menu is _active, false otherwise.
         */
        virtual bool isActive() const = 0;

        /**
         * @brief set the menu to _active or false.
         * @param _active
         */
        virtual void setActive(bool _active) = 0;

        /**
         * @brief create all the GUI that this menu needed.
         * @param device device of the current window.
         * @param driver driver of the current window.
         */
        virtual void createGUI(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) = 0;

        /**
         * @brief create all imagines for this menu.
         * @param device device of the current window.
         * @param driver driver of the current window.
         */
        virtual void createImages(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) = 0;

        /**
         * @brief create all buttons for this menu.
         * @param device device of the current window.
         * @param driver driver of the current window.
         */
        virtual void createButtons(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) = 0;

        /**
         * @brief create all texts for this menu.
         * @param device device of the current window.
         * @param driver driver of the current window.
         */
        virtual void createTexts(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) = 0;

        /**
         * @brief create all extra guy for this menu.
         * @param device drive of the current window.
         * @param driver driver of te current window.
         */
        virtual void createExtra(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) = 0;

        /**
         * @brief clean all map of this menu.
         */
        virtual void cleanScope() = 0;

        /**
         * @brief update all gui things(button hover..)
         */
        virtual void updateGUI(float delta) = 0;

        /**
         * @brief get the username.
         * @return a string.
         */
        virtual std::string getUsername() = 0;


    private:
    protected:
    };
}

#endif //BOMBERMAN_IMENU_H
