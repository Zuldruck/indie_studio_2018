/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/

#ifndef BOMBERMAN_SOLO_H
#define BOMBERMAN_SOLO_H


#include "Menu.hpp"

namespace ind {

    /**
     * @brief A class which contains all elem to run a solo mode of our bomberman.
     */
    class SoloMode : public IMenu {

    public:
        virtual ~SoloMode();

        SoloMode(Core &core, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver);

        /**
         * @brief Draw GUI of this scene?
         */

        void drawGUi(float delta) override;

        /**
         * @brief Test if this menu is _active.
         * @return return true if the menu is _active, false otherwise.
         */
        bool isActive() const override;

        /**
         * @brief set the menu to _active or false.
         * @param _active
         */
        void setActive(bool _active) override;

        /**
         * @brief create all the GUI that this menu needed.
         * @param device device of the current window.
         * @param driver driver of the current window.
         */
        void createGUI(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) override;

        /**
         * @brief create all imagines for this menu.
         * @param device device of the current window.
         * @param driver driver of the current window.
         */
        void createImages(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) override;

        /**
         * @brief create all buttons for this menu.
         * @param device device of the current window.
         * @param driver driver of the current window.
         */
        void createButtons(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) override;

        /**
         * @brief create all texts for this menu.
         * @param device device of the current window.
         * @param driver driver of the current window.
         */
        void createTexts(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) override;

        /**
         * @brief create all extra guy for this menu.
         * @param device drive of the current window.
         * @param driver driver of te current window.
         */
        void createExtra(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) override;

        /**
         * @brief clean all map of this menu.
         */
        void cleanScope() override;

        /**
         * @brief update all gui things(button hover..)
         */
        void updateGUI(float delta) override;

        /**
         * @brief Override of getUsername. Get the username entry in the field of username in solo scene.
         * @return the username entry by the user.
         */
        std::string getUsername() override;
        void setUsername(const std::string& newValue);

        std::string capString(std::string value, unsigned int numberMax);
    private:

        irr::scene::ISceneManager *_SoloSceneManager;
        irr::gui::IGUIEnvironment *_guiScene;
        EventReceiverMenu _receiver;
        irr::IrrlichtDevice *_saveDevice;
        irr::video::IVideoDriver *_saveDriver;

        boost::unordered_map<std::string, irr::gui::IGUIButton *> _mapButtons;
        boost::unordered_map<std::string, irr::gui::IGUIStaticText *> _mapTexts;
        boost::unordered_map<std::string, irr::gui::IGUIImage *> _mapImages;
        MapAnyTypes _mapExtra;

        boost::unordered_map<std::string, irr::video::ITexture *> _mapTextures;

        ind::Core &_core;

        std::string path;
        bool _active;
        bool _hoverPlay;
        bool _hoverLoad;
        bool _hoverBack;

    protected:
    };
}


#endif //BOMBERMAN_PLAYMENU_H
