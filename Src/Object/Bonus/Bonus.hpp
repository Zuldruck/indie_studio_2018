/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** Bonus.hpp
*/

#ifndef BOMBERMAN_BONUS_HPP
#define BOMBERMAN_BONUS_HPP

#include "Includes.hpp"
#include "Object.hpp"
#include "Box.hpp"
#include "Utils.hpp"

#define BONUS_SPAWNRATE 0.12
#define CHANCE_TO_GET_MALUS 0.15

namespace ind
{
    enum BonusType {
        MALUS = -1,
        BONUS = 1
    };

    enum BonusEffect {
        SPEED = 0,
        RANGE = 1,
        BOMB = 2
    };

    class Bonus : public Object
    {
        public:
            Bonus                   (IScene &scene, std::vector<std::string> tags = {"BONUS"});
            virtual ~               Bonus();
            virtual void            beginPlay(void);
            virtual void            update(float delta);
            virtual void            setToBoxPosition(Box *box);
            virtual BonusType       getType(void) const noexcept;
            virtual BonusEffect     getEffect(void) const noexcept;
        protected:
            BonusType           _type;
            BonusEffect         _effect;
        private:
    };
}

#endif //BOMBERMAN_BONUS_HPP
