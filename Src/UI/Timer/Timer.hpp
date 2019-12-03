/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/


#ifndef BOMBERMAN_TIMER_HPP
#define BOMBERMAN_TIMER_HPP

#include "Includes.hpp"

namespace ind {

    class Timer
    {
    public:
        virtual ~Timer();
        Timer();

        /**
         * @brief get a ITimer.
         * @return Itimer.
         */
        irr::ITimer *getTimer() const;

        /**
         * @brief set the timer.
         * @param timer
         */
        void setTimer(irr::ITimer *timer);

        /**
         * @brief get the time end.
         * @return AN integer of the end time.
         */
        unsigned int getTimeEnd() const;

        /**
         * @brief set the end time.
         * @param timeEnd
         */
        void setTimeEnd(unsigned int timeEnd);

        /**
         * @brief Like the name the function get the actual time.
         * @return u32 type like int.
         */
        irr::u32 getActualTime();
        /**
         * @brief set actual time. [USELESS]
         * @param actualTime
         */
        void setActualTime(irr::u32 actualTime);

        /**
         * @brief start the time of a game.
         * @param _saveDevice savedevice to get something on it.
         * @param endTime endTime
         */
        void startTimer(irr::IrrlichtDevice *_saveDevice, unsigned int endTime);

        /**
         * @brief get the begin time.
         * @return
         */
        irr::u32 getBeginTime() const;
        /**
         * @brief set the begin time.
         * @param beginTime
         */
        void setBeginTime(irr::u32 beginTime);

        /**
         * @brief check if is finished.
         * @return
         */
        bool isFinished();

        /**
         * @brief get the actual time in seconds.
         * @return
         */
        double getSeconds();

        /**
         * @brief get how many seconds remains.
         * @return
         */
        int getSecondsRemains();


    protected:

    private:
        irr::ITimer *_timer{};
        unsigned int _timeEnd{};
        irr::u32 _beginTime{};

    private:
        irr::u32 _actualTime{};
    };
}


#endif //BOMBERMAN_TIMER_HPP
