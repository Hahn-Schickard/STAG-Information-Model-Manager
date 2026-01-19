#include "ModelManager.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Information_Model_Manager::testing {
using namespace std;
using namespace ::testing;
using namespace Information_Model;
using namespace Technology_Adapter;

struct ManagerTests : public ::testing::Test {
  static void SetUpTestSuite() { tested = make_shared<ModelManager>(); }

  static void TearDownTestSuite() { tested.reset(); }

  static inline ModelManagerPtr tested = nullptr;
};

TEST_F(ManagerTests, canGetSnapshot) {
  EXPECT_NO_THROW(tested->getModelSnapshot());
}

struct MockTechnologyAdapter : public TechnologyAdapter {
  MockTechnologyAdapter() : TechnologyAdapter("mocked") {}

  MOCK_METHOD(void, interfaceSet, (), (final));
};

TEST_F(ManagerTests, canGetConnector) {
  EXPECT_NO_THROW(tested->getModelDataConnector());
}

TEST_F(ManagerTests, registrateAndDeregistrate) {
  auto mock = make_shared<MockTechnologyAdapter>();
  EXPECT_CALL(*mock, interfaceSet()).Times(Exactly(1));

  EXPECT_NO_THROW(tested->registerTechnologyAdapter(mock));

  EXPECT_NO_THROW(tested->deregisterTechnologyAdapter(mock));
}

TEST_F(ManagerTests, throwsAdapterRegistered) {
  auto mock = make_shared<MockTechnologyAdapter>();
  EXPECT_CALL(*mock, interfaceSet()).Times(Exactly(1));

  EXPECT_NO_THROW(tested->registerTechnologyAdapter(mock));
  EXPECT_THROW(
      tested->registerTechnologyAdapter(mock), TechnologyAdapterRegistered);
}

TEST_F(ManagerTests, throwsAdapterNotFound) {
  EXPECT_THROW(tested->deregisterTechnologyAdapter(
                   make_shared<TechnologyAdapter>("not_registered")),
      TechnologyAdapterNotFound);
}

TEST_F(ManagerTests, throwsInvalidArgument) {
  EXPECT_THAT([]() { tested->registerTechnologyAdapter(nullptr); },
      ThrowsMessage<invalid_argument>(
          HasSubstr("Can not register an empty adapter")));

  EXPECT_THAT([]() { tested->deregisterTechnologyAdapter(nullptr); },
      ThrowsMessage<invalid_argument>(
          HasSubstr("Can not deregister an empty adapter")));
}
} // namespace Information_Model_Manager::testing