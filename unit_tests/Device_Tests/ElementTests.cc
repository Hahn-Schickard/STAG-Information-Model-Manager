#include "CallableImpl.hpp"
#include "ElementImpl.hpp"
#include "GroupImpl.hpp"
#include "ObservableImpl.hpp"
#include "ReadableImpl.hpp"
#include "WritableImpl.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <optional>
#include <stdexcept>

namespace Information_Model_Manager::testing {
using namespace std;
using namespace ::testing;
using namespace Information_Model;

TEST(ElementUtilTests, toStringThrows) {
  string result{};
  // we deliberately want to test how out of range casts are handled
  // NOLINTNEXTLINE(clang-analyzer-optin.core.EnumCastOutOfRange,readability-magic-numbers)
  EXPECT_THAT([&result]() { result = toString(static_cast<ElementType>(230)); },
      ThrowsMessage<logic_error>(
          HasSubstr("Could not decode ElementType enum value")));

  EXPECT_TRUE(result.empty());
}

struct ElementTestParam {
  string id;
  string name;
  string description;
  ElementType element_type;
  DataType data_type;
  ElementFunction function;

  // NOLINTNEXTLINE(readability-identifier-naming)
  friend void PrintTo(const ElementTestParam& param, std::ostream* os) {
    *os << "(id: " << param.id << ", name:" << param.name
        << ", description:" << param.description
        << ", element_type:" << toString(param.element_type)
        << ", data_type:" << toString(param.data_type) << ")";
  }
};

struct ElementTests : public TestWithParam<ElementTestParam> {
  ElementTests() {
    expected = GetParam();
    tested = make_shared<ElementImpl>(expected.id,
        BuildInfo{expected.name, expected.description},
        expected.function);
  }

  ElementTestParam expected;
  shared_ptr<ElementImpl> tested;
};

TEST_P(ElementTests, canGetType) {
  EXPECT_EQ(tested->type(), expected.element_type);
}

TEST_P(ElementTests, canGetFunction) {
  EXPECT_EQ(tested->function(), expected.function);
}

INSTANTIATE_TEST_SUITE_P(ElementTestsValues,
    ElementTests,
    Values( // clang-format off
        ElementTestParam{
            "readable_bool",
            "readable_element",
            "description of a readable element",
            ElementType::Readable,
            DataType::Boolean,
            make_shared<ReadableImpl>(
                DataType::Boolean, 
                [](){ return true;}
            )
        },
        ElementTestParam{
            "writable_string",
            "writable_element",
            "description of a writable element",
            ElementType::Writable,
            DataType::String,
            make_shared<WritableImpl>(
                DataType::String, 
                [](const DataVariant&){}
            )
        },
        ElementTestParam{
            "observable_double",
            "observable_element",
            "description of a observable element",
            ElementType::Observable,
            DataType::Double,
            make_shared<ObservableImpl>(
                DataType::Double, 
                [](){ return 20.2;},// NOLINT(readability-magic-numbers)
                [](bool){}
            )
        },
        ElementTestParam{
            "callable_opaque",
            "callable_element",
            "description of a callable element",
            ElementType::Callable,
            DataType::Opaque,
            make_shared<CallableImpl>(
                DataType::Opaque, 
                ParameterTypes{}, 
                [](const Parameters&){},
                [](const Parameters&){
                    promise<DataVariant> result;
                    auto result_future = ResultFuture(
                        make_shared<uintmax_t>(0), 
                        result.get_future()
                    );
                    result.set_exception(
                        make_exception_ptr(
                            runtime_error("Test exception")
                        )
                    );
                    return result_future;
                }, 
                [](uintmax_t){}
            )
        },
        ElementTestParam{
            "group",
            "group_element",
            "description of a group element",
            ElementType::Group,
            DataType::None,
            make_shared<GroupImpl>(
                "group:0"
            )
        }
    ), // clang-format on
    [](const TestParamInfo<ElementTests::ParamType>& info) {
      return info.param.id;
    });

} // namespace Information_Model_Manager::testing