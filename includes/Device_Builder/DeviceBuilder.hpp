#ifndef __MODEL_BUILDER_DEVICE_BUILDER_HPP_
#define __MODEL_BUILDER_DEVICE_BUILDER_HPP_

#include "DeviceImplementation.hpp"
#include "Information_Model/DeviceBuilderInterface.hpp"

#include <optional>

namespace Information_Model_Manager {
struct DeviceBuilder : public Information_Model::DeviceBuilderInterface {
  // import interface overloads
  using DeviceBuilderInterface::addDeviceElementGroup;
  using DeviceBuilderInterface::addFunction;
  using DeviceBuilderInterface::addReadableMetric;
  using DeviceBuilderInterface::addWritableMetric;

  void buildDeviceBase(const std::string& unique_id, const std::string& name,
      const std::string& desc) override;

  std::string addDeviceElementGroup(const std::string& group_ref_id,
      const std::string& name, const std::string& desc) override;

  std::string addReadableMetric(const std::string& group_ref_id,
      const std::string& name, const std::string& desc,
      Information_Model::DataType data_type, Reader read_cb) override;

  std::string addWritableMetric(const std::string& group_ref_id,
      const std::string& name, const std::string& desc,
      Information_Model::DataType data_type, Writer write_cb,
      Reader read_cb) override;

  Information_Model::UniqueDevicePtr getResult() override;

private:
  using DeviceImplementationPtr = std::unique_ptr<DeviceImplementation>;

  DeviceGroupImplementationPtr getGroupImplementation(
      const std::string& ref_id);

  struct Functionality {
    struct Read {
      Read() = default;
      Read(Reader read_cb) : callback(read_cb) {}

      const Reader callback; // NOLINT(readability-identifier-naming)
    };

    struct Write {
      Write() = default;
      Write(Writer write_cb) : callback(write_cb) {}
      Write(Reader read_cb, Writer write_cb)
          : read_part(read_cb), callback(write_cb) {}

      const Read read_part; // NOLINT(readability-identifier-naming)
      const Writer callback; // NOLINT(readability-identifier-naming)
    };

    struct Execute {
      Execute() = default;
      Execute(Information_Model::Function::ParameterTypes supported_parameters)
          : supported_params(supported_parameters) {}
      Execute(Executor execute_cb, Canceler cancel_cb)
          : call(execute_cb), cancel(cancel_cb) {}
      Execute(Executor execute_cb, Canceler cancel_cb,
          Information_Model::Function::ParameterTypes supported_parameters)
          : call(execute_cb), cancel(cancel_cb),
            supported_params(supported_parameters) {}

      const Executor call; // NOLINT(readability-identifier-naming)
      const Canceler cancel; // NOLINT(readability-identifier-naming)
      const Information_Model::Function::ParameterTypes
          supported_params; // NOLINT(readability-identifier-naming)
    };

    using Group = std::monostate;
    using Interface = std::variant<Group, Read, Write, Execute>;

    Functionality()
        : data_type(Information_Model::DataType::NONE), interface(Group()) {}
    Functionality(Information_Model::DataType type)
        : data_type(type), interface(Read()) {}
    Functionality(Information_Model::DataType type, Reader read_cb)
        : data_type(type), interface(Read(read_cb)) {}
    Functionality(Information_Model::DataType type, Writer write_cb)
        : data_type(type), interface(Write(write_cb)) {}
    Functionality(
        Information_Model::DataType type, Reader read_cb, Writer write_cb)
        : data_type(type), interface(Write(read_cb, write_cb)) {}
    Functionality(Information_Model::DataType result_type,
        Information_Model::Function::ParameterTypes supported_params)
        : data_type(result_type), interface(Execute(supported_params)) {}
    Functionality(Information_Model::DataType result_type, Executor execute_cb,
        Canceler cancel_cb)
        : data_type(result_type), interface(Execute(execute_cb, cancel_cb)) {}
    Functionality(Information_Model::DataType result_type, Executor execute_cb,
        Canceler cancel_cb,
        Information_Model::Function::ParameterTypes supported_params)
        : data_type(result_type),
          interface(Execute(execute_cb, cancel_cb, supported_params)) {}

    Information_Model::ElementType type() const {
      if (std::holds_alternative<Read>(interface)) {
        return Information_Model::ElementType::READABLE;
      } else if (std::holds_alternative<Write>(interface)) {
        return Information_Model::ElementType::WRITABLE;
      } else if (std::holds_alternative<Execute>(interface)) {
        return Information_Model::ElementType::FUNCTION;
      } else {
        return Information_Model::ElementType::GROUP;
      }
    }

    Read getRead() const { return std::get<Read>(interface); }
    Write getWrite() const { return std::get<Write>(interface); }
    Execute getExecute() const { return std::get<Execute>(interface); }

    const Information_Model::DataType
        data_type; // NOLINT(readability-identifier-naming)
    const Interface interface; // NOLINT(readability-identifier-naming)
  };

  std::string addDeviceElement(const std::string& group_ref_id,
      const std::string& name, const std::string& desc,
      const Functionality& functionality);

  DeviceImplementationPtr device_;
};
} // namespace Information_Model_Manager

#endif //__MODEL_BUILDER_DEVICE_BUILDER_HPP_