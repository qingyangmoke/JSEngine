#include "include/jsengine_bridge.h"
namespace JSEngineNS
{
  class Timer
  {
  private:
    static int handleSeed;
    bool clear = false;
    int handle = 0;    
    int contextId;

  public:
    Timer(int contextId);
    ~Timer();
    int getHandle();
    int getContextId();
    void setTimeout(TimerCallback function, int delay);
    void setInterval(TimerCallback function, int interval);
    void stop();
  };
}