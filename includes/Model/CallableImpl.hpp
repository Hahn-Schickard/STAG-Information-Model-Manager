#ifndef __MODEL_CALLABLE_IMPLEMENTATION_HPP_
#define __MODEL_CALLABLE_IMPLEMENTATION_HPP_

#include "Information_Model/Callable.hpp"

#include <functional>
#include <memory>

namespace Information_Model_Manager {
struct CallableImpl : public Information_Model::Callable {
  using ExecuteCallback =
      std::function<void(const Information_Model::Parameters&)>;
  using AsyncExecuteCallback = std::function<Information_Model::ResultFuture(
      const Information_Model::Parameters&)>;
  using CancelCallback = std::function<void(uintmax_t)>;

  CallableImpl(const Information_Model::ParameterTypes& supported,
      const ExecuteCallback& execute_cb);

  CallableImpl(Information_Model::DataType result_type,
      const Information_Model::ParameterTypes& supported,
      const ExecuteCallback& execute_cb,
      const AsyncExecuteCallback& call_cb,
      const CancelCallback& cancel_cb);

  ~CallableImpl() override = default;

  void execute(const Information_Model::Parameters& parameters) const final;

  Information_Model::DataVariant call(uintmax_t timeout) const final;

  Information_Model::DataVariant call(
      const Information_Model::Parameters& parameters,
      uintmax_t timeout) const final;

  [[nodiscard]] Information_Model::ResultFuture asyncCall(
      const Information_Model::Parameters& parameters) const final;

  void cancelAsyncCall(uintmax_t call_id) const final;

  Information_Model::DataType resultType() const final;

  Information_Model::ParameterTypes parameterTypes() const final;

private:
  void canReturn() const;

  Information_Model::DataType result_type_ = Information_Model::DataType::None;
  Information_Model::ParameterTypes supported_params_;
  ExecuteCallback execute_;
  AsyncExecuteCallback call_;
  CancelCallback cancel_;
};
} // namespace Information_Model_Manager

#endif //__MODEL_CALLABLE_IMPLEMENTATION_HPP_