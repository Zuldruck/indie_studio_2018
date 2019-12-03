/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** GameLight
*/

#ifndef GAMELIGHT_HPP_
#define GAMELIGHT_HPP_

#include "Object.hpp"

namespace ind {

/**
 * @brief Light object ingame
 * 
 */
class GameLight : public Object {
	public:
		/**
		 * @brief Construct a new Game Light object
		 * 
		 * @param scene 
		 * @param tags 
		 */
		GameLight(
                IScene &scene,
                std::vector<std::string> tags = {"Light"});
		virtual ~GameLight();

	protected:
        irr::scene::ILightSceneNode *_light;
	private:
};

}
#endif /* !GAMELIGHT_HPP_ */
