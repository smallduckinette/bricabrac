#ifndef __CHAPITRE7_SIGNAL_H__
#define __CHAPITRE7_SIGNAL_H__

#include <functional>
#include <vector>


template<typename ...ARGS>
class Signal
{
public:
  void emit(ARGS... args)
  {
    for(auto && callback : _callbacks)
    {
      callback(args...);
    }
  }
  
  void connect(std::function<void(ARGS...)> f)
  {
    _callbacks.push_back(f);
  }
  
private:
  std::vector<std::function<void(ARGS...)> > _callbacks;
};

#endif
