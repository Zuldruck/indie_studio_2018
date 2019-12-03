/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/

#ifndef BOMBERMAN_settings_H
#define BOMBERMAN_settings_H

#include "Menu.hpp"

namespace ind {

    /**
     * @brief settings of our game.
     */
    class Settings : public IMenu {

    public:
        virtual ~Settings();

        Settings(Core &core, irr::IrrlichtDevice *device, std::shared_ptr<DjControl> _engineSound,
                 irr::video::IVideoDriver *driver);

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
         * @brief Override of getUsername. Useless in this scene.
         * @return empty.
         */
        std::string getUsername() override;

    private:

        irr::scene::ISceneManager *_settingsSceneManager;
        irr::gui::IGUIEnvironment *_guiScene;
        EventReceiverMenu _receiver;
        std::shared_ptr<DjControl> _saveEngineSound;

        boost::unordered_map<std::string, irr::gui::IGUIButton *> _mapButtons;
        boost::unordered_map<std::string, irr::gui::IGUIStaticText *> _mapTexts;
        boost::unordered_map<std::string, irr::gui::IGUIImage *> _mapImages;
        MapAnyTypes _mapExtra;
        boost::unordered_map<std::string, irr::video::ITexture *> _mapTextures;

        bool _active;
        std::string path;
        irr::IrrlichtDevice *_saveDevice;
        irr::video::IVideoDriver *_saveDriver;

        bool _hoverBack;
        bool _hoverControl;

        Core &_core;


    protected:
    };
}

#endif //BOMBERMAN_settings_H
