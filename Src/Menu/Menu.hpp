/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/


#ifndef BOMBERMAN_MENU_H
#define BOMBERMAN_MENU_H

#ifdef __APPLE__
#include <irrlicht/irrlicht.h>
#endif /* __APPLE__*/

#ifdef __linux__
#include <irrlicht.h>
#endif /* __linux__ */

#include "Includes.hpp"
#include "IMenu.hpp"
#include "BombermanLobby.hpp"

namespace ind {

    class MapAnyTypes;

    class DjControl;

    class GameScene;

/**
 * @brief ENUM which contains all id button that we treat in the program.
 */
    enum {
        GUI_ID_QUIT_BUTTON = 101,
        GUI_ID_RUN_SETTINGS,
        GUI_ID_RUN_LOAD,
        GUI_ID_RUN_LOAD_GAME,
        GUI_ID_RUN_CREDITS,
        GUI_ID_RUN_PRINCIPAL,
        GUI_ID_RUN_SOLO,
        GUI_ID_RUN_MULTI,
        GUI_ID_VOLUME_SCROLL_BAR,
        GUI_ID_RUN_CONTROL_KEY,
        GUI_ID_RUN_PLAY,
        GUI_ID_RUN_PLAY_MULTI,
        GUI_ID_RUN_PAUSE,
        GUI_ID_NULL,
    };

    extern std::string _activeMenu;
#define FIRSTSCENE "principal"
#define MAX_FRAME_INTRO 203

    /**
     * @brief A class which handle all menu and his drawing.
     */
    class Menu {

    public:
        Menu(Core &core, bool firstTime);

        ~Menu();

        /**
         * @brief draw all the menu and sub menu.
         */
        void draw(float delta);

        /**
         * @brief find on a map with an exception if something has gone wrong.
         * @tparam T template to find everything that we want.
         * @param obj map
         * @param key key that we want to find.
         * @param errorMessage error message if something has gone wrong.
         * @return return the second pattern.
         */
        template<typename T>
        static T inline
        findWithExcept(boost::unordered_map<std::string, T> obj, std::string key, std::string errorMessage) {
            if (obj.empty())
                EXCEPTION(std::runtime_error, "map empty. Please, don't give an empty map.");

            auto keyObj = obj.find(key);

            if (keyObj == obj.end())
                EXCEPTION(std::runtime_error, errorMessage);

            return keyObj->second;
        }

        /**
         * @brief get a texture with an exception if something has gone wrong.
         * @param driver driver Irrlicht.
         * @param path path to the texture.
         * @param errorMessage error message if something has gone wrong.
         * @return return a pointer on an ITexture *.
         */
        static irr::video::ITexture *getTextureWithExcept(irr::video::IVideoDriver *driver, const std::string &path,
                                                          const std::string &errorMessage);

        /**
         * @brief player the video game intro.
         */
        void playVideo(float delta);

        /**
         * @brief detect if we need to switch into the solo or multi scene.
         * @return true if yes, false if not.
         */
        bool detectSoloMultiMode();


        void createBomberman(irr::u32 idx);

        /**
         * @brief clean the meshnode of the map and the gui.
         */
        void clean();

        /**
         * @brief Parsing of the listBox of game Saved and return the correct argument to play a choosen saved.
         */
        void prepareLoadGame();

        /**
         * @brief create Lobby for the menu.
         */
        void createLobbySolo();

        /**
         * @brief Epur a string.
         */
        void epur(std::string &);

        /**
         * @brief create UI for n players for the specific position of their hud and their texts...
         * @param numberPlayer number of players you want to create in GUI.
         * @param username username of your player in solo mode.
         */
        void createUIForNPlayers(std::shared_ptr<ind::GameScene> gameScene, unsigned int numberPlayer, const std::string& username = "");

        const boost::unordered_map<std::string, std::shared_ptr<IMenu>> &getSceneMenu() const;

    private:
        boost::unordered_map<std::string, std::shared_ptr<IMenu>> _sceneMenu;
        irr::IrrlichtDevice *_saveDevice;
        irr::video::IVideoDriver *_saveDriver;
        std::shared_ptr<DjControl> _engineSound;
        irr::core::dimension2d<irr::u32> _saveScreenSize;
        irr::scene::IAnimatedMeshSceneNode *_meshNodeMap;
        Core &_core;
        size_t _currentFrame;
        std::string path;
        bool _firstTime;
        std::string _usernameLoad;
        unsigned int _scoreLoad;
        unsigned int _levelLoad;
        unsigned int _speedLoad;
        unsigned int _rangeLoad;
        unsigned int _bombLoad;
        bool _runLoad;

        std::vector<std::shared_ptr<BombermanLobby>> _vectBomberman;

        void showAndRunScene();
    };

    class EventReceiverMenu : public irr::IEventReceiver {
    public:
        EventReceiverMenu(Core &core, std::shared_ptr<DjControl> _engineSound = nullptr);

        virtual ~EventReceiverMenu() = default;

        /**
         * @brief onEvent of the event Receivent
         * @param event event of the user.
         * @return true or false if the user event are detected.
         */
        virtual bool OnEvent(const irr::SEvent &event);

    private:
        irr::IrrlichtDevice *_saveDevice;
        std::shared_ptr<DjControl> _saveEngineSound;
        Core &_core;
    };

}



#endif //BOMBERMAN_MENU_H
