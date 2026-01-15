#include "CallableImpl.hpp"
#include "DeviceImpl.hpp"
#include "ElementImpl.hpp"
#include "ObservableImpl.hpp"
#include "ReadableImpl.hpp"
#include "WritableImpl.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Information_Model_Manager::testing {
using namespace std;
using namespace ::testing;
using namespace Information_Model;

struct DeviceTests : public testing::Test {
  DeviceTests() {
    auto readable =
        make_shared<ReadableImpl>(DataType::Boolean, []() { return true; });
    auto readable_id = tested->generateID();
    auto readable_element = make_shared<ElementImpl>(
        readable_id, BuildInfo{"readable", "just a readable"}, readable);
    tested->addElement(readable_element);
    built.try_emplace(readable_id, readable_element);

    auto writable =
        make_shared<WritableImpl>(DataType::Double, [](const DataVariant&) {});
    auto writable_id = tested->generateID();
    auto writable_element = make_shared<ElementImpl>(writable_id,
        BuildInfo{"Writeable", "just a write only writable"},
        writable);
    tested->addElement(writable_element);
    built.try_emplace(writable_id, writable_element);

    auto observable = make_shared<ObservableImpl>(
        DataType::String, []() { return true; }, [](bool) {});
    auto observable_id = tested->generateID();
    auto observable_element = make_shared<ElementImpl>(observable_id,
        BuildInfo{"Observable", "just an observable"},
        observable);
    tested->addElement(observable_element);
    built.try_emplace(observable_id, observable_element);

    auto callable =
        make_shared<CallableImpl>(ParameterTypes{}, [](const Parameters&) {});
    auto callable_id = tested->generateID();
    auto callable_element = make_shared<ElementImpl>(
        callable_id, BuildInfo{"Callable", "just a callable"}, callable);
    tested->addElement(callable_element);
    built.try_emplace(callable_id, callable_element);

    sub_group_id = tested->generateID();
    auto sub_group = make_shared<GroupImpl>(sub_group_id);
    auto sub_group_element = make_shared<ElementImpl>(
        sub_group_id, BuildInfo{"Subgroup", "just a subgroup"}, sub_group);
    tested->addElement(sub_group_element);
    built.try_emplace(sub_group_id, sub_group_element);
  }

  string base_id = "based_id";
  DeviceImplPtr tested = make_shared<DeviceImpl>(
      base_id, BuildInfo{"test_device", "test device description"});
  string sub_group_id;
  string sub_readable_id;
  unordered_map<string, ElementImplPtr> built;
};

TEST_F(DeviceTests, returnsId) { EXPECT_EQ(tested->id(), base_id); }

TEST_F(DeviceTests, returnsName) { EXPECT_EQ(tested->name(), "test_device"); }

TEST_F(DeviceTests, returnsDescription) {
  EXPECT_EQ(tested->description(), "test device description");
}

TEST_F(DeviceTests, addElementThrows) {
  auto print_element_ids = [this]() {
    string result = "This device contains: \n";
    tested->visit([&result](const ElementPtr& element) {
      result += element->id() + "\n";
    });
    return result;
  };

  EXPECT_THAT([&]() { tested->addElement(nullptr); },
      ThrowsMessage<invalid_argument>(HasSubstr("Given element is empty")));

  EXPECT_THAT(
      [&]() {
        tested->addElement(make_shared<ElementImpl>("another_id:0",
            BuildInfo{"a", "b"},
            make_shared<ReadableImpl>(
                DataType::Opaque, []() { return true; })));
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("Given element is not part of this group")))
      << print_element_ids();
  ;

  EXPECT_THAT(
      [&]() {
        tested->addElement(make_shared<ElementImpl>(base_id,
            BuildInfo{"a", "b"},
            make_shared<ReadableImpl>(
                DataType::Opaque, []() { return true; })));
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("Given element has the same ID as this group")))
      << print_element_ids();

  EXPECT_THAT(
      [&]() {
        tested->addElement(make_shared<ElementImpl>(base_id + ":0",
            BuildInfo{"a", "b"},
            make_shared<ReadableImpl>(
                DataType::Opaque, []() { return true; })));
      },
      ThrowsMessage<logic_error>(HasSubstr(
          "Element with id " + base_id + ":0 is already in this group")))
      << print_element_ids();
}

TEST_F(DeviceTests, throwsElementNotFound) {
  EXPECT_THAT([&]() { tested->element("bad_ref"); },
      ThrowsMessage<ElementNotFound>(
          HasSubstr("Element with reference id bad_ref was not found")));

  string ex_msg1 =
      "Element with reference id " + sub_group_id + ".2 was not found";
  EXPECT_THAT([&]() { tested->element(sub_group_id + ".2"); },
      ThrowsMessage<ElementNotFound>(HasSubstr(ex_msg1)));

  string ex_msg2 =
      "Element with reference id " + sub_group_id + "0 was not found";
  EXPECT_THAT([&]() { tested->element(sub_group_id + "0"); },
      ThrowsMessage<ElementNotFound>(HasSubstr(ex_msg2)));
}

TEST_F(DeviceTests, throwsIDPointsThisGroup) {
  EXPECT_THAT([&]() { tested->element(base_id); },
      ThrowsMessage<IDPointsThisGroup>(HasSubstr(
          "Reference ID " + base_id + " points to this group element")));
}

TEST_F(DeviceTests, isCorrectSize) { EXPECT_EQ(tested->size(), built.size()); }

TEST_F(DeviceTests, canGetElementById) {
  for (const auto& [id, element] : built) {
    auto tested_element = tested->element(id);

    EXPECT_EQ(tested_element->id(), element->id());
    EXPECT_EQ(tested_element->name(), element->name());
    EXPECT_EQ(tested_element->description(), element->description());
    EXPECT_EQ(tested_element->type(), element->type());
  }
}

TEST_F(DeviceTests, canVisitEach) {
  auto visitor = [&](const ElementPtr& tested_element) {
    auto it = built.find(tested_element->id());
    if (it != built.end()) {
      auto element = it->second;
      EXPECT_EQ(tested_element->id(), element->id());
      EXPECT_EQ(tested_element->name(), element->name());
      EXPECT_EQ(tested_element->description(), element->description());
      EXPECT_EQ(tested_element->type(), element->type());
    } else {
      FAIL() << "Element " << tested_element->id()
             << " was not built but exists in group" << endl;
    }
  };

  EXPECT_NO_THROW(tested->visit(visitor));
}

} // namespace Information_Model_Manager::testing