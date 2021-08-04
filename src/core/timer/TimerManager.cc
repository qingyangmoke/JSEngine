#include "TimerManager.h"
using namespace JSEngineNS;

TimerManager *TimerManager::singletonInstance = NULL;

TimerManager::TimerManager()
{
}

TimerManager::~TimerManager() {}

int TimerManager::setInterval(int contextId, TimerCallback function, int interval)
{
  Timer *timer = new Timer(contextId);
  timer->setInterval(function, interval);
  this->_timerMap[timer->getHandle()] = timer;
  return timer->getHandle();
}

int TimerManager::setTimeout(int contextId, TimerCallback function, int delay)
{
  Timer *timer = new Timer(contextId);
  timer->setTimeout(function, delay);
  this->_timerMap[timer->getHandle()] = timer;
  return timer->getHandle();
}

void TimerManager::clearAllTimer(int contextId)
{
  for (auto it = _timerMap.begin(); it != _timerMap.end(); ++it)
  {
    if (it->second->getContextId() == contextId)
    {
      it->second->stop();
      delete it->second;
      _timerMap.erase(it);
    }
  }
}

void TimerManager::clearTimer(int contextId, int handle)
{
  if (_timerMap.count(handle) == 1)
  {
    Timer *timer = _timerMap[contextId];
    if (timer->getContextId() == contextId)
    {
      _timerMap[handle]->stop();
      delete _timerMap[handle];
      _timerMap.erase(handle);
    }
  }
}