/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Blob
*/

#ifndef BLOB_HPP_
#define BLOB_HPP_

#include "AI.hpp"

#define DEFAULT_BLOB_SPEED 0.015

namespace ind {

class Blob : public AI {
	public:
		Blob(IScene &scene, std::vector<std::string> tags = {"BLOB", "AI", "CHARACTER"});
		~Blob() = default;

	protected:
	private:
};

}

#endif /* !BLOB_HPP_ */
