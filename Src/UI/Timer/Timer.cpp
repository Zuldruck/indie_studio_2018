/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/


#include "Timer.hpp"

ind::Timer::Timer()
= default;

ind::Timer::~Timer()
= default;


irr::ITimer *ind::Timer::getTimer() const
{
    return _timer;
}

void ind::Timer::setTimer(irr::ITimer *timer)
{
    _timer = timer;
}

unsigned int ind::Timer::getTimeEnd() const
{
    return _timeEnd;
}

void ind::Timer::setTimeEnd(unsigned int timeEnd)
{
    _timeEnd = timeEnd;
}

irr::u32 ind::Timer::getActualTime()
{
    this->setActualTime(_timer->getTime());
    return _actualTime;
}

void ind::Timer::setActualTime(irr::u32 actualTime)
{
    _actualTime = actualTime;
}

irr::u32 ind::Timer::getBeginTime() const
{
    return _beginTime;
}

void ind::Timer::setBeginTime(irr::u32 beginTime)
{
    _beginTime = beginTime;
}

void ind::Timer::startTimer(irr::IrrlichtDevice *_saveDevice, unsigned int endTime)
{
    if (!_saveDevice)
        EXCEPTION(std::runtime_error, "_saveDevice was null");
    setTimer(_saveDevice->getTimer());
    setBeginTime(_timer->getTime());
    setTimeEnd(endTime);
}

bool ind::Timer::isFinished()
{
    return getActualTime() - getBeginTime() >= getTimeEnd();
}

double ind::Timer::getSeconds()
{
   return (getActualTime() - getBeginTime()) / 1000.0;
}

int ind::Timer::getSecondsRemains()
{
    auto timeEnd = getTimeEnd() / 1000.0;
    auto actualSeconds = getSeconds();

    return (static_cast<int>(timeEnd - actualSeconds));
}
