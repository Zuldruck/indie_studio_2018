/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Leeroy
*/

#ifndef LEEROY_HPP_
#define LEEROY_HPP_

#include "AI.hpp"

#define DEFAULT_LEEROY_SPEED 0.02

namespace ind {

class Leeroy : public AI {
	public:
		Leeroy(IScene &scene, std::vector<std::string> tags = {"LEEROY", "AI", "CHARACTER"});
		~Leeroy() = default;

	protected:
	private:
};

}

#endif /* !LEEROY_HPP_ */
