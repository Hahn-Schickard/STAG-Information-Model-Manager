#include "Builder.hpp"
#include "ModelRepository.hpp"

#include <algorithm>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Information_Model_Manager::testing {
using namespace std;
using namespace ::testing;
using namespace Information_Model;
using namespace Data_Consumer_Adapter;

struct RepositoryTests : public ::testing::Test {
  static void SetUpTestSuite() { tested = make_shared<ModelRepository>(); }

  static void TearDownTestSuite() { tested.reset(); }

  DataConnectionPtr connect() {
    auto connector = tested->getModelDataConnector();
    return connector(mock_connection.AsStdFunction());
  }

  static inline ModelRepositoryPtr tested = nullptr;
  MockFunction<void(RegistryChangePtr)> mock_connection;
};

DevicePtr makeDevice(const string& id) {
  auto builder = make_shared<Builder>();

  builder->setDeviceInfo(id, BuildInfo{"Testy", "Repository Test Device"});
  builder->addReadable(BuildInfo{"Ready", "Test readable"},
      DataType::Boolean,
      []() { return true; });

  return builder->result();
}

TEST_F(RepositoryTests, canGetSnapshot) {
  EXPECT_NO_THROW(tested->getModelSnapshot());
}

TEST_F(RepositoryTests, canConnect) { EXPECT_NE(connect(), nullptr); }

bool existsInSnapshot(const string& id, const vector<DevicePtr>& snapshot) {
  return any_of(snapshot.begin(),
      snapshot.end(),
      [&id](const DevicePtr& device) { return id == device->id(); });
}

TEST_F(RepositoryTests, canAdd) {
  EXPECT_CALL(mock_connection, Call(_)).Times(Exactly(1));
  auto connection = connect();

  EXPECT_TRUE(tested->add(makeDevice("1")));
  EXPECT_TRUE(existsInSnapshot("1", tested->getModelSnapshot()))
      << "No device with id 1 found in model snapshot";
}

TEST_F(RepositoryTests, canNotAddExisting) {
  EXPECT_CALL(mock_connection, Call(_)).Times(Exactly(1));
  auto connection = connect();

  EXPECT_TRUE(tested->add(makeDevice("2")));
  EXPECT_TRUE(existsInSnapshot("2", tested->getModelSnapshot()))
      << "No device with id 2 found in model snapshot";
  EXPECT_FALSE(tested->add(makeDevice("2")));
}

TEST_F(RepositoryTests, canRemove) {
  EXPECT_CALL(mock_connection, Call(_)).Times(Exactly(1));
  EXPECT_CALL(mock_connection, Call(Pointee(RegistryChange{"3"})))
      .Times(Exactly(1));
  auto connection = connect();

  EXPECT_TRUE(tested->add(makeDevice("3")));
  EXPECT_TRUE(existsInSnapshot("3", tested->getModelSnapshot()))
      << "No device with id 3 found in model snapshot";
  EXPECT_TRUE(tested->remove("3"));
  EXPECT_FALSE(existsInSnapshot("3", tested->getModelSnapshot()))
      << "Device with id 3 still exists in model snapshot";
}

TEST_F(RepositoryTests, canNotRemoveNonExisting) {
  EXPECT_CALL(mock_connection, Call(_)).Times(Exactly(0));
  auto connection = connect();

  EXPECT_FALSE(tested->remove("DoesNotExist"));
  EXPECT_FALSE(existsInSnapshot("DoesNotExist", tested->getModelSnapshot()));
}

} // namespace Information_Model_Manager::testing