#ifndef __LISTENER__HPP
#define __LISTENER__HPP

#include "Device.hpp"

namespace Notifier {
class Listener {
public:
  virtual ~Listener();
  virtual void handleEvent(Information_Model::Device *device) = 0;
};
}

#endif //__LISTENER__HPP