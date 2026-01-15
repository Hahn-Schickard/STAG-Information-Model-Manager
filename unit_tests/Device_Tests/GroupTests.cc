#include "CallableImpl.hpp"
#include "ElementImpl.hpp"
#include "GroupImpl.hpp"
#include "ObservableImpl.hpp"
#include "ReadableImpl.hpp"
#include "WritableImpl.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Information_Model_Manager::testing {
using namespace std;
using namespace ::testing;
using namespace Information_Model;

struct GroupTests : public testing::Test {
  GroupTests() {
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

    sub_element = make_shared<ElementImpl>(sub_group->generateID(),
        BuildInfo{"Subelement", "just a subelement"},
        readable);
    sub_group->addElement(sub_element);

    auto sub_sub_group_id = sub_group->generateID();
    sub_sub_group = make_shared<GroupImpl>(sub_sub_group_id);
    sub_group->addElement(make_shared<ElementImpl>(sub_sub_group_id,
        BuildInfo{"Subsubgroup", "just a sub-subgroup"},
        sub_sub_group));
    sub_sub_element = make_shared<ElementImpl>(sub_sub_group->generateID(),
        BuildInfo{"Subsubelement", "just a sub-subelement"},
        readable);
    sub_sub_group->addElement(sub_sub_element);
  }

  string base_id = "based_id:0";
  GroupImplPtr tested = make_shared<GroupImpl>(base_id);
  string sub_group_id;
  ElementPtr sub_element;
  GroupImplPtr sub_sub_group;
  ElementPtr sub_sub_element;
  unordered_map<string, ElementImplPtr> built;
};

TEST_F(GroupTests, addElementThrows) {
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
        tested->addElement(make_shared<ElementImpl>("based_id:1",
            BuildInfo{"a", "b"},
            make_shared<ReadableImpl>(
                DataType::Opaque, []() { return true; })));
      },
      ThrowsMessage<invalid_argument>(
          HasSubstr("Given element is not part of this group")))
      << print_element_ids();

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
        tested->addElement(make_shared<ElementImpl>(base_id + ".0",
            BuildInfo{"a", "b"},
            make_shared<ReadableImpl>(
                DataType::Opaque, []() { return true; })));
      },
      ThrowsMessage<logic_error>(HasSubstr(
          "Element with id " + base_id + ".0 is already in this group")))
      << print_element_ids();
}

TEST_F(GroupTests, throwsElementNotFound) {
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

  string ex_msg3 =
      "Element with reference id " + sub_sub_element->id() + "0 was not found";
  EXPECT_THAT([&]() { tested->element(sub_sub_element->id() + "0"); },
      ThrowsMessage<ElementNotFound>(HasSubstr(ex_msg3)));
}

TEST_F(GroupTests, throwsIDPointsThisGroup) {
  EXPECT_THAT([&]() { tested->element(base_id); },
      ThrowsMessage<IDPointsThisGroup>(HasSubstr(
          "Reference ID " + base_id + " points to this group element")));
}

TEST_F(GroupTests, isCorrectSize) { EXPECT_EQ(tested->size(), built.size()); }

TEST_F(GroupTests, canGetElementById) {
  for (const auto& [id, element] : built) {
    auto tested_element = tested->element(id);

    EXPECT_EQ(tested_element->id(), element->id());
    EXPECT_EQ(tested_element->name(), element->name());
    EXPECT_EQ(tested_element->description(), element->description());
    EXPECT_EQ(tested_element->type(), element->type());
  }

  auto tested_sub_element = tested->element(sub_element->id());
  EXPECT_EQ(tested_sub_element->id(), sub_element->id());
  EXPECT_EQ(tested_sub_element->name(), sub_element->name());
  EXPECT_EQ(tested_sub_element->description(), sub_element->description());
  EXPECT_EQ(tested_sub_element->type(), sub_element->type());

  auto tested_sub_sub_element = tested->element(sub_sub_element->id());
  EXPECT_EQ(tested_sub_sub_element->id(), sub_sub_element->id());
  EXPECT_EQ(tested_sub_sub_element->name(), sub_sub_element->name());
  EXPECT_EQ(
      tested_sub_sub_element->description(), sub_sub_element->description());
  EXPECT_EQ(tested_sub_sub_element->type(), sub_sub_element->type());
}

TEST_F(GroupTests, canGetAsMap) {
  unordered_map<string, ElementPtr> built_as_base;
  for (const auto& [id, element] : built) {
    auto correct_id = id.substr(base_id.size());
    if (correct_id.front() == '.') {
      correct_id.erase(0, 1);
    }
    if (correct_id.back() == '.') {
      correct_id.pop_back();
    }
    built_as_base.try_emplace(correct_id, element);
  }

  EXPECT_THAT(tested->asMap(), ContainerEq(built_as_base));
}

TEST_F(GroupTests, canGetAsVector) {
  vector<ElementPtr> built_as_vector;
  built_as_vector.reserve(built.size());
  for (const auto& [_, element] : built) {
    built_as_vector.push_back(element);
  }
  auto predicate = [](const ElementPtr& lhs, const ElementPtr& rhs) {
    return lhs->id() < rhs->id();
  };
  sort(built_as_vector.begin(), built_as_vector.end(), predicate);

  auto tested_vector = tested->asVector();
  EXPECT_THAT(tested_vector, ContainerEq(built_as_vector));
}

TEST_F(GroupTests, canVisitEach) {
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