/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "Includes.hpp"
#include "CollisionManager.hpp"
#include <DjControl.hpp>

#include "PersistantData.hpp"
#include "BombermanLobby.hpp"

#ifdef __APPLE__
#define WINDOW_WIDTH 1920
    #define WINDOW_HEIGHT 1080
#elif __linux__
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#elif _WIN32
#define WINDOW_WIDTH 1920
    #define WINDOW_HEIGHT 1080
#endif /** __APPLE__ **/

#ifdef _WIN32
    #define VIDEO_MODE irr::video::EDT_OPENGL
#else
    #define VIDEO_MODE irr::video::EDT_OPENGL
#endif /** WIN32 **/


namespace ind {
    class EventReceiver;
    class IObject;
    class IScene;
    class DjControl;

    /**
     * @brief The Core class init a window using irrlicht, instanciate a scene, update and draw it. It also handle the link of the event with the scene, the sound and the data of the players
     *
     *
     */
    class Core {

    public:
        /**
         * @brief Construct a new Core object and init a window
         *
         */
        Core();
        /**
         * @brief Destroy the Core object
         *
         */
        ~Core();

        /**
         * @brief load and init a scene
         *
         */
        template <class T>
        std::shared_ptr<T> loadScene(void);

        template <class T>
        std::shared_ptr<T> loadScene(bool firstTime);

        template <class T>
        void loadScene(std::shared_ptr<T> scene);

        void setUp(void);

        /**
         * @brief update all objects. Update is threaded and called every frame (/rate)
         *
         */
        void update(void);
        /**
         * @brief draw all objects. Draw is threaded and called every frame (/rate)
         *
         */
        void draw(void);
        /**
         * @brief Launch the game.
         *
         */
        void run(void);

        /**
         * @brief Stop and clear the engine.
         * 
         */
        void stop(void) noexcept;

        /**
         * @brief Set the number of player
         *
         */
        void setNumberPlayer(unsigned int nbPlayer) noexcept;
        /**
         * @brief Get the number of player
         *
         */
        unsigned int getNumberPlayer(void) noexcept;

        /**
         * @brief Set the Current Level
         * 
         * @param currentLevel 
         */
        void setCurrentLevel(unsigned int currentLevel) noexcept;

        /**
         * @brief Get the Current Level
         * 
         * @return unsigned int 
         */
        unsigned int getCurrentLevel(void) const noexcept;

        /**
         * @brief Get the Device 
         * 
         * @return irr::IrrlichtDevice* 
         */
        irr::IrrlichtDevice *getDevice(void) const noexcept;

        /**
         * @brief Get the Driver
         * 
         * @return irr::video::IVideoDriver* 
         */
        irr::video::IVideoDriver *getDriver(void) const noexcept;

        /**
         * @brief Get the Engine Sound
         * 
         * @return const std::shared_ptr<DjControl>& 
         */
        const std::shared_ptr<DjControl> &getEngineSound() const;

        /**
         * @brief Get the actual Scene
         * 
         * @return const std::shared_ptr<IScene>& 
         */
        const std::shared_ptr<IScene> &getScene() const;

        /**
         * @brief Get joysticks
         * 
         * @return irr::core::array<irr::SJoystickInfo> 
         */
        irr::core::array<irr::SJoystickInfo> getJoysticks(void) const;


        /**
         * @brief Save the current game
         *
         */
        void saveGame() const;


        /**
         * @brief Load a given game, the core need to have his pointer pointing to a GameScene
         *
         */
        void loadGame(const std::string& username, unsigned int level, unsigned int score, unsigned int speed, unsigned int range, unsigned int bomb);

        std::vector<std::string> getSaveGame();

        bool isLoadRequested() const;

        void setLoadRequested(bool loadRequested);

    protected:

        irr::IrrlichtDevice *               _device;
        irr::video::IVideoDriver *          _driver;
        std::shared_ptr<IScene>             _scene;

        unsigned int                        _nbPlayer = 1;
        unsigned int                        _currentLevel;
        std::shared_ptr<DjControl>          _engineSound;
        irr::core::array<irr::SJoystickInfo> _joysticks;

        float                               _fps = 120;
        bool								_isRunning = false;

        PersistantData                      _persistantData;

        bool                                _loadRequested;

        unsigned int                        _saveScore;
        std::string                         _saveUsername;
        std::string                         _path;
    };
}

#endif /* !CORE_HPP_ */
