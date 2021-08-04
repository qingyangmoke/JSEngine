#include "Timer.h"
using namespace CPlusDemo;

int Timer::handleSeed = 1;

Timer::Timer(int contextId)
{
  this->handle = Timer::handleSeed++;
  this->contextId = contextId;
}

Timer::~Timer()
{
  this->stop();
}

void Timer::setTimeout(TimerCallback function, int delay)
{
  this->clear = false;
  std::thread t([=]()
                {
                  if (this->clear)
                    return;
                  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                  if (this->clear)
                    return;
                  function();
                });
  t.detach();
}

void Timer::setInterval(TimerCallback function, int interval)
{
  this->clear = false;
  std::thread t([=]()
                {
                  while (true)
                  {
                    if (this->clear)
                      return;
                    std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                    if (this->clear)
                      return;
                    function();
                  }
                });
  t.detach();
}

void Timer::stop()
{
  this->clear = true;
}

int Timer::getHandle()
{
  return this->handle;
}

int Timer::getContextId()
{
  return this->contextId;
}