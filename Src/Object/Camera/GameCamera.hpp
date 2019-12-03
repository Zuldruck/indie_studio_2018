/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** GameCamera
*/

#ifndef GAMECAMERA_HPP_
#define GAMECAMERA_HPP_

#include "Object.hpp"

namespace ind {

/**
 * @brief simple topdown camera ingame
 * 
 */
class GameCamera : public Object {
	public:
	/**
	 * @brief Construct a new Game Camera object
	 * 
	 * @param scene 
	 * @param tags 
	 */
		GameCamera(IScene &scene, std::vector<std::string> tags = {"Camera"});
		~GameCamera();

	protected:
        irr::scene::ICameraSceneNode *      _camera;
	private:
};

}
#endif /* !GAMECAMERA_HPP_ */
