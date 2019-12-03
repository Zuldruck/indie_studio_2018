/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Dodger
*/

#ifndef DODGER_HPP_
#define DODGER_HPP_

#include "AI.hpp"

#define DEFAULT_DODGER_SPEED 0.025

namespace ind {

class Dodger : public AI {
	public:
		Dodger(IScene &scene, std::vector<std::string> tags = {"DODGER", "AI", "CHARACTER"});
		~Dodger() = default;

	protected:
	private:
};

}

#endif /* !DODGER_HPP_ */
