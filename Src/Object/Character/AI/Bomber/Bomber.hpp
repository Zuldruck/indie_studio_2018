/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomber
*/

#ifndef BOMBER_HPP_
#define BOMBER_HPP_

#include "AI.hpp"
#include "BomberMan.hpp"

namespace ind {

class Bomber : public AI, public BomberMan {
	public:
		Bomber(IScene &scene, std::vector<std::string> tags = {"BOMBER", "AI", "CHARACTER", "BOMBERMAN"});
		~Bomber() = default;

	protected:
	private:
};

}

#endif /* !BOMBER_HPP_ */
