#include "include/jsengine_bridge.h"
#include "Timer.h"
namespace JSEngineNS
{
  class TimerManager
  {
  private:
    static TimerManager *singletonInstance;
    std::unordered_map<int, Timer *> _timerMap = {};

  public:
    OBJECT_INSTANCE(TimerManager);
    TimerManager();
    ~TimerManager();
    int setTimeout(int contextId, TimerCallback function, int delay);
    int setInterval(int contextId, TimerCallback function, int interval);
    void clearTimer(int contextId, int handle);
    void clearAllTimer(int contextId);
  };
}