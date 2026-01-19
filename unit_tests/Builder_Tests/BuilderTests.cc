#include "CallableImpl.hpp"
#include "DeviceImpl.hpp"
#include "ElementImpl.hpp"
#include "ObservableImpl.hpp"
#include "ReadableImpl.hpp"
#include "WritableImpl.hpp"

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

TEST(BuilderTests, throwsDeviceInfoNotSet) {
  auto builder = make_shared<Builder>();
  auto returns_true = []() { return true; };
  auto writes_nothing = [](const DataVariant&) {};
  auto enables_observation = [](bool) {};
  auto executes_nothing = [](const Parameters&) {};
  auto calls_nothing = [](const Parameters&) {
    promise<DataVariant> promised_result;
    auto result_future =
        ResultFuture(make_shared<uintmax_t>(0), promised_result.get_future());
    promised_result.set_exception(
        make_exception_ptr(runtime_error("Test exception")));
    return result_future;
  };
  auto cancels_nothing = [](uintmax_t) {};

  EXPECT_THROW(builder->addGroup(BuildInfo{"group_name"}), DeviceInfoNotSet);

  EXPECT_THROW(builder->addGroup("group_id", BuildInfo{}), DeviceInfoNotSet);

  EXPECT_THROW(builder->addReadable(
                   BuildInfo{"readable_name"}, DataType::Boolean, returns_true),
      DeviceInfoNotSet);

  EXPECT_THROW(builder->addReadable(
                   "group_id", BuildInfo{}, DataType::Boolean, returns_true),
      DeviceInfoNotSet);

  EXPECT_THROW(
      builder->addWritable(
          BuildInfo{}, DataType::Boolean, writes_nothing, returns_true),
      DeviceInfoNotSet);

  EXPECT_THROW(builder->addWritable("group_id",
                   BuildInfo{},
                   DataType::Boolean,
                   writes_nothing,
                   returns_true),
      DeviceInfoNotSet);

  EXPECT_THROW(
      builder->addObservable(
          BuildInfo{}, DataType::Boolean, returns_true, enables_observation),
      DeviceInfoNotSet);

  EXPECT_THROW(builder->addObservable("group_id",
                   BuildInfo{},
                   DataType::Boolean,
                   returns_true,
                   enables_observation),
      DeviceInfoNotSet);

  EXPECT_THROW(builder->addCallable(BuildInfo{},
                   DataType::Boolean,
                   executes_nothing,
                   calls_nothing,
                   cancels_nothing,
                   ParameterTypes{}),
      DeviceInfoNotSet);

  EXPECT_THROW(builder->addCallable("group_id",
                   BuildInfo{},
                   DataType::Boolean,
                   executes_nothing,
                   calls_nothing,
                   cancels_nothing,
                   ParameterTypes{}),
      DeviceInfoNotSet);

  EXPECT_THROW(
      builder->addCallable(BuildInfo{}, executes_nothing, ParameterTypes{}),
      DeviceInfoNotSet);

  EXPECT_THROW(builder->addCallable(
                   "group_id", BuildInfo{}, executes_nothing, ParameterTypes{}),
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
        builder_ptr->addObservable(
            BuildInfo{"observable_name"},
            DataType::Boolean,
            []() { return true; },
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
        builder_ptr->addCallable(
            BuildInfo{"callable_name"},
            DataType::Boolean,
            [](const Parameters&) {},
            nullptr,
            nullptr);
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("AsyncExecuteCallback can not be nullptr")));
  // NOLINTBEGIN(modernize-use-nullptr)
  EXPECT_THAT(
      [builder_ptr]() {
        builder_ptr->addCallable(
            BuildInfo{"callable_name"},
            DataType::Boolean,
            [](const Parameters&) {},
            [](const Parameters&) {
              promise<DataVariant> promise;
              promise.set_exception(
                  make_exception_ptr(CallCanceled(0, "Mock Builder Test")));
              // we need to set it as 0, not nullptr
              return ResultFuture(0, promise.get_future());
            },
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

  EXPECT_EQ(
      builder->addReadable(
          BuildInfo{"readable_name"}, DataType::Boolean, []() { return true; }),
      "base_id:1");

  EXPECT_EQ(builder->addWritable(BuildInfo{"writable_name"},
                DataType::Boolean,
                [](const DataVariant&) {}),
      "base_id:2");

  EXPECT_EQ(builder
                ->addObservable(
                    BuildInfo{"observable_name"},
                    DataType::Boolean,
                    []() { return true; },
                    [](bool) {})
                .first,
      "base_id:3");

  EXPECT_EQ(builder->addCallable(
                BuildInfo{"executable_name"}, [](const Parameters&) {}),
      "base_id:4");

  EXPECT_EQ(builder->addCallable(
                BuildInfo{"callable_name"},
                DataType::Boolean,
                [](const Parameters&) {},
                [](const Parameters&) {
                  promise<DataVariant> promise;
                  promise.set_exception(
                      make_exception_ptr(CallCanceled(0, "Mock Builder Test")));
                  return ResultFuture(0, promise.get_future());
                },
                [](uintmax_t) {}),
      "base_id:5");

  // Subgroup tests
  EXPECT_EQ(builder->addGroup("base_id:0", BuildInfo{"sub_group_name"}),
      "base_id:0.0");

  EXPECT_EQ(builder->addReadable("base_id:0.0",
                BuildInfo{"readable_name"},
                DataType::Boolean,
                []() { return true; }),
      "base_id:0.0.0");

  EXPECT_EQ(builder->addWritable("base_id:0.0",
                BuildInfo{"writable_name"},
                DataType::Boolean,
                [](const DataVariant&) {}),
      "base_id:0.0.1");

  EXPECT_EQ(builder
                ->addObservable(
                    "base_id:0.0",
                    BuildInfo{"observable_name"},
                    DataType::Boolean,
                    []() { return true; },
                    [](bool) {})
                .first,
      "base_id:0.0.2");

  EXPECT_EQ(builder->addCallable("base_id:0.0",
                BuildInfo{"executable_name"},
                [](const Parameters&) {}),
      "base_id:0.0.3");

  EXPECT_EQ(builder->addCallable(
                "base_id:0.0",
                BuildInfo{"callable_name"},
                DataType::Boolean,
                [](const Parameters&) {},
                [](const Parameters&) {
                  promise<DataVariant> promise;
                  promise.set_exception(
                      make_exception_ptr(CallCanceled(0, "Mock Builder Test")));
                  return ResultFuture(0, promise.get_future());
                },
                [](uintmax_t) {}),
      "base_id:0.0.4");
  // NOLINTEND(modernize-use-nullptr)
  EXPECT_NO_THROW(builder->result());
}

} // namespace Information_Model_Manager::testing