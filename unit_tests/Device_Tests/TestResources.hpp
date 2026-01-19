#include <Information_Model/DataVariant.hpp>
#include <Variant_Visitor/Visitor.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Information_Model_Manager::testing {
inline Information_Model::DataVariant otherThan(
    const Information_Model::DataVariant& input) {
  return Variant_Visitor::match(
      input, // NOLINTBEGIN(readability-magic-numbers)
      [](bool) -> Information_Model::DataVariant {
        return std::vector<uint8_t>{0x00, 0x01, 0xAB};
      },
      [](intmax_t) -> Information_Model::DataVariant {
        return Information_Model::Timestamp{2025, 9, 10, 13, 01, 24, 32};
      },
      [](uintmax_t) -> Information_Model::DataVariant {
        return std::string("A new value");
      },
      [](double) -> Information_Model::DataVariant {
        return uintmax_t{9789121};
      },
      [](Information_Model::Timestamp) -> Information_Model::DataVariant {
        return intmax_t{-698872};
      },
      [](const std::vector<uint8_t>&) -> Information_Model::DataVariant {
        return true;
      },
      [](const std::string&) -> Information_Model::DataVariant {
        return 20.3512;
      }); // NOLINTEND(readability-magic-numbers)
}

inline void PrintTo(
    const Information_Model::DataVariant& param, std::ostream* os) {
  *os << toString(param);
}

// NOLINTNEXTLINE(readability-identifier-naming)
MATCHER_P(ExceptionPointee, exception_type, "") {
  try {
    rethrow_exception(arg);
    return false;
  } catch (const std::exception& ex) {
    return typeid(ex) == typeid(exception_type) &&
        ex.what() == exception_type.what();
  }
}

} // namespace Information_Model_Manager::testing