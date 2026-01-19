#include "Builder.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Information_Model_Manager::testing {
using namespace std;
using namespace ::testing;
using namespace Information_Model;

TEST(BuilderTests, throwsDeviceBuildInProgress) {
  DeviceBuilderPtr builder = make_shared<Builder>();

  EXPECT_NO_THROW(builder->setDeviceInfo(
      "base_id", BuildInfo{"device_name", "device description"}));

  EXPECT_THROW(
      builder->setDeviceInfo("another_id",
          BuildInfo{"another_device_name", "another device description"}),
      DeviceBuildInProgress);
}

constexpr auto RETURNS_TRUE = []() { return true; };
constexpr auto WRITES_NOTHING = [](const DataVariant&) {};
constexpr auto ENABLES_OBSERVATION = [](bool) {};
constexpr auto EXECUTES_NOTHING = [](const Parameters&) {};
constexpr auto CALLS_NOTHING = [](const Parameters&) {
  promise<DataVariant> promised_result;
  auto result_future =
      ResultFuture(make_shared<uintmax_t>(0), promised_result.get_future());
  promised_result.set_exception(
      make_exception_ptr(runtime_error("Test exception")));
  return result_future;
};
constexpr auto CANCELS_NOTHING = [](uintmax_t) {};

TEST(BuilderTests, throwsDeviceInfoNotSet) {
  auto builder = make_shared<Builder>();

  EXPECT_THROW(builder->addGroup(BuildInfo{"group_name"}), DeviceInfoNotSet);

  EXPECT_THROW(builder->addGroup("group_id", BuildInfo{}), DeviceInfoNotSet);

  EXPECT_THROW(builder->addReadable(
                   BuildInfo{"readable_name"}, DataType::Boolean, RETURNS_TRUE),
      DeviceInfoNotSet);

  EXPECT_THROW(builder->addReadable(
                   "group_id", BuildInfo{}, DataType::Boolean, RETURNS_TRUE),
      DeviceInfoNotSet);

  EXPECT_THROW(
      builder->addWritable(
          BuildInfo{}, DataType::Boolean, WRITES_NOTHING, RETURNS_TRUE),
      DeviceInfoNotSet);

  EXPECT_THROW(builder->addWritable("group_id",
                   BuildInfo{},
                   DataType::Boolean,
                   WRITES_NOTHING,
                   RETURNS_TRUE),
      DeviceInfoNotSet);

  EXPECT_THROW(
      builder->addObservable(
          BuildInfo{}, DataType::Boolean, RETURNS_TRUE, ENABLES_OBSERVATION),
      DeviceInfoNotSet);

  EXPECT_THROW(builder->addObservable("group_id",
                   BuildInfo{},
                   DataType::Boolean,
                   RETURNS_TRUE,
                   ENABLES_OBSERVATION),
      DeviceInfoNotSet);

  EXPECT_THROW(builder->addCallable(BuildInfo{},
                   DataType::Boolean,
                   EXECUTES_NOTHING,
                   CALLS_NOTHING,
                   CANCELS_NOTHING,
                   ParameterTypes{}),
      DeviceInfoNotSet);

  EXPECT_THROW(builder->addCallable("group_id",
                   BuildInfo{},
                   DataType::Boolean,
                   EXECUTES_NOTHING,
                   CALLS_NOTHING,
                   CANCELS_NOTHING,
                   ParameterTypes{}),
      DeviceInfoNotSet);

  EXPECT_THROW(
      builder->addCallable(BuildInfo{}, EXECUTES_NOTHING, ParameterTypes{}),
      DeviceInfoNotSet);

  EXPECT_THROW(builder->addCallable(
                   "group_id", BuildInfo{}, EXECUTES_NOTHING, ParameterTypes{}),
      DeviceInfoNotSet);

  EXPECT_THROW(builder->result(), DeviceInfoNotSet);
}

TEST(BuilderTests, throwsGroupEmpty) {
  DeviceBuilderPtr builder = make_shared<Builder>();

  EXPECT_NO_THROW(builder->setDeviceInfo(
      "base_id", BuildInfo{"device_name", "device description"}));

  auto* builder_ptr = builder.get();
  EXPECT_THAT([builder_ptr]() { builder_ptr->result(); },
      ThrowsMessage<GroupEmpty>(
          HasSubstr("Device base_id root group is empty")));

  string group_id;
  EXPECT_NO_THROW(group_id = builder->addGroup(
                      BuildInfo{"group_name", "group description"}));

  EXPECT_THAT([builder_ptr]() { builder_ptr->result(); },
      ThrowsMessage<GroupEmpty>(
          HasSubstr("Device base_id group " + group_id + " is empty")));
}

TEST(BuilderTests, throwsInvalidArgument) {
  DeviceBuilderPtr builder = make_shared<Builder>();

  EXPECT_NO_THROW(builder->setDeviceInfo(
      "base_id", BuildInfo{"device_name", "device description"}));

  auto* builder_ptr = builder.get();

  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addReadable("Nonsense parent ID",
            BuildInfo{"readable_name"},
            DataType::Boolean,
            RETURNS_TRUE);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("No parent group with ID Nonsense parent ID exists. Build "
                    "parent group first")));

  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addReadable(
            BuildInfo{"readable_name"}, DataType::None, nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("Data Type can not be None or Unknown")));

  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addReadable(
            BuildInfo{"readable_name"}, DataType::Unknown, nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("Data Type can not be None or Unknown")));

  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addReadable(
            BuildInfo{"readable_name"}, DataType::Boolean, nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("ReadCallback can not be nullptr")));

  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addWritable(
            BuildInfo{"writable_name"}, DataType::None, nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("Data Type can not be None or Unknown")));

  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addWritable(
            BuildInfo{"writable_name"}, DataType::Unknown, nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("Data Type can not be None or Unknown")));

  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addWritable(
            BuildInfo{"writable_name"}, DataType::Boolean, nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("WriteCallback can not be nullptr")));

  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addObservable(
            BuildInfo{"observable_name"}, DataType::None, nullptr, nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("Data Type can not be None or Unknown")));

  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addObservable(
            BuildInfo{"observable_name"}, DataType::Unknown, nullptr, nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("Data Type can not be None or Unknown")));

  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addObservable(
            BuildInfo{"observable_name"}, DataType::Boolean, nullptr, nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("ReadCallback can not be nullptr")));

  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addObservable(BuildInfo{"observable_name"},
            DataType::Boolean,
            RETURNS_TRUE,
            nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("IsObservingCallback can not be nullptr")));

  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addCallable(BuildInfo{"executable_name"}, nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("ExecuteCallback can not be nullptr")));

  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addCallable(BuildInfo{"callable_name"},
            DataType::None,
            nullptr,
            nullptr,
            nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("Result Type can not be None or Unknown")));

  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addCallable(BuildInfo{"callable_name"},
            DataType::Unknown,
            nullptr,
            nullptr,
            nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("Result Type can not be None or Unknown")));

  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addCallable(BuildInfo{"callable_name"},
            DataType::Boolean,
            nullptr,
            nullptr,
            nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("ExecuteCallback can not be nullptr")));

  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addCallable(BuildInfo{"callable_name"},
            DataType::Boolean,
            EXECUTES_NOTHING,
            nullptr,
            nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("AsyncExecuteCallback can not be nullptr")));
  // NOLINTBEGIN(modernize-use-nullptr)
  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addCallable(BuildInfo{"callable_name"},
            DataType::Boolean,
            EXECUTES_NOTHING,
            CALLS_NOTHING,
            nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("CancelCallback can not be nullptr")));
}

TEST(BuilderTests, returnsCorrectID) {
  DeviceBuilderPtr builder = make_shared<Builder>();

  EXPECT_NO_THROW(builder->setDeviceInfo(
      "base_id", BuildInfo{"device_name", "device description"}));

  EXPECT_EQ(builder->addGroup(BuildInfo{"group_name"}), "base_id:0");

  EXPECT_EQ(builder->addReadable(
                BuildInfo{"readable_name"}, DataType::Boolean, RETURNS_TRUE),
      "base_id:1");

  EXPECT_EQ(builder->addWritable(
                BuildInfo{"writable_name"}, DataType::Boolean, WRITES_NOTHING),
      "base_id:2");

  EXPECT_EQ(builder
                ->addObservable(BuildInfo{"observable_name"},
                    DataType::Boolean,
                    RETURNS_TRUE,
                    ENABLES_OBSERVATION)
                .first,
      "base_id:3");

  EXPECT_EQ(
      builder->addCallable(BuildInfo{"executable_name"}, EXECUTES_NOTHING),
      "base_id:4");

  EXPECT_EQ(builder->addCallable(BuildInfo{"callable_name"},
                DataType::Boolean,
                EXECUTES_NOTHING,
                CALLS_NOTHING,
                CANCELS_NOTHING),
      "base_id:5");

  // Subgroup tests
  EXPECT_EQ(builder->addGroup("base_id:0", BuildInfo{"sub_group_name"}),
      "base_id:0.0");

  EXPECT_EQ(builder->addReadable("base_id:0.0",
                BuildInfo{"readable_name"},
                DataType::Boolean,
                RETURNS_TRUE),
      "base_id:0.0.0");

  EXPECT_EQ(builder->addWritable("base_id:0.0",
                BuildInfo{"writable_name"},
                DataType::Boolean,
                WRITES_NOTHING),
      "base_id:0.0.1");

  EXPECT_EQ(builder
                ->addObservable("base_id:0.0",
                    BuildInfo{"observable_name"},
                    DataType::Boolean,
                    RETURNS_TRUE,
                    ENABLES_OBSERVATION)
                .first,
      "base_id:0.0.2");

  EXPECT_EQ(builder->addCallable(
                "base_id:0.0", BuildInfo{"executable_name"}, EXECUTES_NOTHING),
      "base_id:0.0.3");

  EXPECT_EQ(builder->addCallable("base_id:0.0",
                BuildInfo{"callable_name"},
                DataType::Boolean,
                EXECUTES_NOTHING,
                CALLS_NOTHING,
                CANCELS_NOTHING),
      "base_id:0.0.4");
  // NOLINTEND(modernize-use-nullptr)
  EXPECT_NO_THROW(builder->result());
}

} // namespace Information_Model_Manager::testing