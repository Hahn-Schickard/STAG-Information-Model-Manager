#ifndef __LISTENER_MOCK_HPP
#define __LISTENER_MOCK_HPP

#include "Listener.hpp"
#include "Notifier_Event.hpp"

#include "gmock/gmock.h"

class MockListener : public Model_Event_Handler::Listener {
 public:
  MOCK_METHOD(void,
      handleEvent,
      (std::shared_ptr<Model_Event_Handler::NotifierEvent> event),
      (override));
};

#endif   //__LISTENER_MOCK_HPP