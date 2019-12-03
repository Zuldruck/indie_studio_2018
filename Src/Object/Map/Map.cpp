/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Map
*/

#include "Map.hpp"
#include "Factory.hpp"
#include "AnimatedMeshComponent.hpp"
#include "MovementComponent.hpp"
#include "EventComponent.hpp"
#include "Block.hpp"
#include "Fence.hpp"
#include "Wall.hpp"
#include "Box.hpp"
#include "Bomb.hpp"
#include "Fire.hpp"
#include "Player.hpp"
#include "Bomber.hpp"
#include "Blob.hpp"
#include "Leeroy.hpp"
#include "Dodger.hpp"
#include "IScene.hpp"
#include "Exit.hpp"
#include "GameScene.hpp"
#include "Character.hpp"

#ifdef __APPLE__
    #define MAP_PATH "OOP_indie_studio_2018/Maps/"
#elif __linux__
    #define MAP_PATH "Maps/"
#elif _WIN32
    #define MAP_PATH "Maps/"
#endif /* __APPLE__ */

static const std::vector<levelProbability> probabilityVec =
    {
        {
            5, {
                    {BLOB, 100},
               }, 3
        },
        {
            10, {
                    {BLOB, 50},
                    {DODGER, 25},
                    {LEEROY, 25},
               }, 4
        },
        {
            15, {
                    {BLOB, 30},
                    {DODGER, 35},
                    {LEEROY, 35},
               }, 5
        },
        {
            20, {
                    {BLOB, 10},
                    {DODGER, 40},
                    {LEEROY, 40},
                    {BOMBER, 10},
               }, 6
        },
        {
            21, {
                    {BOMBER, 100},
               }, 3
        },
    };

namespace ind {

    Map::Map(IScene &scene, std::vector<std::string> tags) :
            Object(scene, tags), _nbMob(0)
    {
        std::vector<std::shared_ptr<BombermanLobby>> settings = static_cast<GameScene *>(&scene)->getSettings();
        unsigned size = settings.size();
        std::map<std::string, std::string> mapTextureBomberman;
        std::string texture = "";
        unsigned count = 0;

        mapTextureBomberman.insert(std::make_pair("default", "Bomberman/bomberman.png"));
        mapTextureBomberman.insert(std::make_pair("black", "Bomberman/bomberman-black.png"));
        mapTextureBomberman.insert(std::make_pair("yellow", "Bomberman/bomberman-yellow.png"));
        mapTextureBomberman.insert(std::make_pair("blue", "Bomberman/bomberman-blue.png"));
        mapTextureBomberman.insert(std::make_pair("red", "Bomberman/bomberman-jordan.png"));

        _levelsName = Utils::getFilesFromDirectory(MAP_PATH);
        _nbPlayers = static_cast<GameScene *>(&_scene)->getNbPlayer();
        _isMulti = _nbPlayers == 1 ? false : true;
        count = _isMulti ? 4 : _nbPlayers;
        for (irr::u32 i = 0; i < count; i++) {
            if (size == 0) {
                _players.push_back(Factory::createObject<Player>(_scene));
                _players[i]->getComponent<EventComponent>()->setInputs(INPUTS_KEYS[i]);
            } else {
                texture = settings[i]->getPlayerTexture();
                if (settings[i]->getPlayerMode() == "PLAYER") {
                    _players.push_back(Factory::createObject<Player>(_scene));
                    _players[i]->getComponent<EventComponent>()->setInputs(INPUTS_KEYS[i]);
                    _players[i]->getComponent<AnimatedMeshComponent>()->setMaterialTextureFromFile(mapTextureBomberman[texture]);
                } else if (settings[i]->getPlayerMode() == "IA") {
                    _players.push_back(std::static_pointer_cast<AI>(Factory::createObject<Bomber>(_scene)));
                    _players[i]->getComponent<AnimatedMeshComponent>()->setMaterialTextureFromFile(mapTextureBomberman[texture]);
                }
            }
        }
        openMapFile(_levelsName[_scene.getCore().getCurrentLevel() - 1]);
        generateMap();
        drawMap();
    }

    Map::~Map()
    {
    }

    void Map::update(float delta)
    {
        if (_players.empty() || (_players.size() == 1 && _isMulti)) {
            static_cast<GameScene *>(&_scene)->getEngineSound()->playSong("gameOver");
            static_cast<GameScene *>(&_scene)->gameOver();
        }
        static_cast<void>(delta);
    }

    bool        Map::checkCornerMap(int x, int z) noexcept
    {
        std::vector<std::vector<int>> corners = {
                {1, 1, 1, 1},
                {1, getHeight() - 2, 1, -1},
                {getWidth() - 2, 1, -1, 1},
                {getWidth() - 2, getHeight() - 2, -1, -1}};
        int nbCornersToCheck = _isMulti == true ? corners.size() : 1;

        for (int corner = 0; corner < nbCornersToCheck; corner++) {
            if ((x == corners[corner][0] && z == corners[corner][1]) ||
                (x == corners[corner][0] + corners[corner][2] && z == corners[corner][1]) ||
                (x == corners[corner][0] && z == corners[corner][1] + corners[corner][3]))
                return (false);
        }
        return (true);
    }

    bool        Map::checkCornerMapExtremity(int x, int z) noexcept
    {
        if ((x == 3 && z == 1)
        || (x == 1 && z == 3))
            return (true);
        return (false);
    }

    bool        Map::checkPutBox(int x, int z) noexcept
    {
        if (_isMulti == true)
            return (checkCornerMap(x, z));
        return ((static_cast<double>(rand()) / RAND_MAX < BOX_SPAWNRATE && checkCornerMap(x, z))
        || checkCornerMapExtremity(x, z));
    }

    levelProbability Map::getLevelProbability() const
    {
        levelProbability level;

        for (auto &i: probabilityVec) {
            if (static_cast<short>(_scene.getCore().getCurrentLevel()) - 1 < i.maxLevel) {
                level = i;
                break;
            }
        }
        return level;
    }

    std::shared_ptr<Object> Map::pickAI(levelProbability level)
    {
        std::shared_ptr<Object> ai;
        unsigned random = 0;
        unsigned probability = 0;

        random = rand() % 100 + 1;
        probability = 0;
        for (auto &i: level.mobs) {
            probability += i.second;
            if (random <= probability) {
                if (i.first == BLOB) {
                    ai = Factory::createObject<Blob>(getScene());
                } else if (i.first == DODGER) {
                    ai = Factory::createObject<Dodger>(getScene());
                } else if (i.first == LEEROY) {
                    ai = Factory::createObject<Leeroy>(getScene());
                } else if (i.first == BOMBER) {
                    ai = std::static_pointer_cast<AI>(Factory::createObject<Bomber>(getScene()));
                }
                break;
            }
        }
        return ai;
    }

    void        Map::putMob(void) noexcept
    {
        unsigned x;
        unsigned z;
        std::shared_ptr<Object> mob;

        if (_isMulti)
            return;
        levelProbability level = getLevelProbability();
        for (int i = 0; i < level.maxMobs; i++) {
            mob = pickAI(level);
            do {
                x = rand() % getWidth();
                z = rand() % getHeight();
            } while (_map[z][x] != BlockType::EMPTY || checkCornerMap(x, z) != true);
            mob->getComponent<AnimatedMeshComponent>()->setPosition(mob->getComponent<AnimatedMeshComponent>()->getPosition() + irr::core::vector3df(x, 0, z) * 10);
            _nbMob++;
        }
    }

    void        Map::putExit(void) noexcept
    {
        unsigned int x;
        unsigned int z;

        do {
            x = rand() % getWidth();
            z = rand() % getHeight();
        } while (_map[z][x] != BlockType::EMPTY);
        auto exitObject = Factory::createObject<Exit>(getScene());
        exitObject->getComponent<AnimatedMeshComponent>()->setPosition(irr::core::vector3df(x, 0, z) * 10);
    }

    void        Map::putPlayers() noexcept
    {
        for (unsigned i = 0; i < _nbPlayers; i++) {
            if (i == 0) {
                _players[i]->setUsername("Player1");
                _players[i]->getComponent<AnimatedMeshComponent>()->setPosition(irr::core::vector3df(10, 0, 10));
            } else if (i == 1) {
                _players[i]->setUsername("Player2");
                _players[i]->getComponent<AnimatedMeshComponent>()->setPosition(irr::core::vector3df(130, 0, 110));
            } else if (i == 2) {
                _players[i]->setUsername("Player3");
                _players[i]->getComponent<AnimatedMeshComponent>()->setPosition(irr::core::vector3df(10, 0, 110));
            } else if (i == 3) {
                _players[i]->setUsername("Player4");
                _players[i]->getComponent<AnimatedMeshComponent>()->setPosition(irr::core::vector3df(130, 0, 10));
            }
        }
    }

    void        Map::setFenceRotation(int x, int z, std::shared_ptr<Block> block) noexcept
    {
        int rotation = 0;

        if (x == 0 && z == 0)
            rotation = 90;
        else if (x == 0 && z == getHeight() - 1)
            rotation = -90;
        else if (x == getWidth() - 1 && z == 0)
            rotation = 90;
        else if (x == getWidth() - 1 && z == getHeight() - 1)
            rotation = -90;
        else if (x == 0)
            rotation = 180;
        else if (x == getWidth() - 1)
            rotation = 0;
        else if (z == 0)
            rotation = 90;
        else if (z == getHeight() - 1)
            rotation = -90;
        block->getComponent<AnimatedMeshComponent>()->setRotation(irr::core::vector3df(0, rotation, 0));
    }

    void        Map:: openMapFile(const std::string & filename) noexcept
    {
        if (!_isMulti)
            boost::property_tree::read_json(std::string(MAP_OFFSET) + filename, _root);
        else
            boost::property_tree::read_json(std::string(MAP_MULTI_OFFSET) + "map.json", _root);
        std::vector<BlockType> tmp;
        int index = 0;

        _height = _root.get<int>("height");
        _width = _root.get<int>("width");
        _name = _root.get<std::string>("name");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &block, _root.get_child("data")) {
            if (index != 0 && index % getWidth() == 0) {
                _map.push_back(tmp);
                tmp.clear();
            }
            tmp.push_back(static_cast<BlockType>(std::stoi(block.second.data())));
            index++;
        }
        _map.push_back(tmp);
    }

    void        Map::generateMap() noexcept
    {
        int x = 0;
        int z = 0;

        BOOST_FOREACH(auto & row, _map) {
            BOOST_FOREACH(BlockType & block, row) {
                if (block == BlockType::EMPTY && checkPutBox(x, z))
                    block = BlockType::BOX;
                x++;
            }
            x = 0;
            z++;
        }
        putPlayers();
        putMob();
    }

    void        Map::drawMap(void) noexcept
    {
        std::shared_ptr<Block> newBlock;
        int x = 0;
        int z = 0;

        BOOST_FOREACH(auto & row, _map) {
            BOOST_FOREACH(BlockType block, row) {
                if (block != BlockType::EMPTY) {
                    if (block == BlockType::FENCE) {
                        newBlock = Factory::createObject<Fence>(_scene);
                        setFenceRotation(x, z, newBlock);
                    } else if (block == BlockType::WALL) {
                        newBlock = Factory::createObject<Wall>(_scene);
                    } else if (block == BlockType::BOX) {
                        newBlock = Factory::createObject<Box>(_scene);
                    } else if (block == BlockType::EXIT) {
                        newBlock = Factory::createObject<Box>(_scene);
                    }
                    newBlock->getComponent<AnimatedMeshComponent>()->setPosition(irr::core::vector3df(x * 10, 0, z * 10));
                }
                x++;
            }
            x = 0;
            z++;
        }
    }

    std::vector<std::vector<Map::BlockType>> &  Map::getMap(void) noexcept
    {
        return _map;
    }

    int         Map::getHeight(void) const noexcept
    {
        return (_height);
    }

    int         Map::getWidth(void) const noexcept
    {
        return (_width);
    }

    std::string Map::getName(void) const noexcept
    {
        return (_name);
    }

    unsigned int    Map::getNbMob(void) const noexcept
    {
        return _nbMob;
    }

    void        Map::setNbMob(int nbMob) noexcept
    {
        _nbMob = nbMob;
        if (_nbMob == 0)
            putExit();
    }

    void        Map::removePlayer(Character * player) noexcept
    {
        for (std::vector<std::shared_ptr<Character>>::iterator it = _players.begin(); it != _players.end(); ++it) {
            if (static_cast<Character *>(player) == (*it).get()) {
                _players.erase(it);
                break;
            }
        }
    }

    void        Map::reset()
    {
        auto walls = getScene().getObjectsByTags("WALL");
        auto boxes = getScene().getObjectsByTags("BOX");
        auto bombs = getScene().getObjectsByTags("BOMB");
        auto fires = getScene().getObjectsByTags("FIRE");
        auto bonuses = getScene().getObjectsByTags("BONUS");

        for (auto &it : walls)
            getScene().removeObject(it);
        for (auto &it : boxes)
            getScene().removeObject(it);
        for (auto &it : bonuses)
            getScene().removeObject(it);
        for (auto it : bombs)
            std::static_pointer_cast<Bomb>(it)->explode(false);
        for (auto it : fires)
            std::static_pointer_cast<Fire>(it)->extinguish();
        getScene().removeObject(getScene().getObjectsByTags("EXIT")[0]);
        _map.clear();
    }

    void        Map::nextLevel(void)
    {
        auto gameScene = dynamic_cast<GameScene *>(&_scene);

        if (_scene.getCore().getCurrentLevel() == 21) {
            gameScene->gameOver();
            return;
        }
        _scene.getCore().setCurrentLevel(_scene.getCore().getCurrentLevel() + 1);
        reset();
        dynamic_cast<GameScene *>(&_scene)->getGameUi()->getTimer()->startTimer(this->getScene().getCore().getDevice(), 120000);
        openMapFile(_levelsName[_scene.getCore().getCurrentLevel() - 1]);
        generateMap();
        drawMap();
    }

    void        Map::debugShowMap(void) const noexcept
    {
        BOOST_FOREACH(auto row, _map) {
            BOOST_FOREACH(BlockType block, row) {
                std::cout << block << ", ";
            }
            std::cout << std::endl;
        }
    }
}
