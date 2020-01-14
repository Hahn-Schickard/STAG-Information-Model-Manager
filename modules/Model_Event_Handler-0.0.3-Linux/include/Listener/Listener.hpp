#ifndef __LISTENER__HPP
#define __LISTENER__HPP

#include "Notifier_Event.hpp"

#include <memory>

namespace Model_Event_Handler {
  class Listener {
   public:
    virtual ~Listener() = default;

    virtual void handleEvent(std::shared_ptr<NotifierEvent> event) = 0;
  };
}   // namespace Model_Event_Handler

#endif   //__LISTENER__HPP