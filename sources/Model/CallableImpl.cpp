#include "CallableImpl.hpp"

#include <chrono>

namespace Information_Model_Manager {
using namespace std;
using namespace Information_Model;

CallableImpl::CallableImpl(
    const ParameterTypes& supported, const ExecuteCallback& execute_cb)
    : CallableImpl(DataType::None, supported, execute_cb, nullptr, nullptr) {}

CallableImpl::CallableImpl(DataType result_type,
    const ParameterTypes& supported,
    const ExecuteCallback& execute_cb,
    const AsyncExecuteCallback& call_cb,
    const CancelCallback& cancel_cb)
    : result_type_(result_type), supported_params_(supported),
      execute_(execute_cb), call_(call_cb), cancel_(cancel_cb) {}

void CallableImpl::execute(const Parameters& parameters) const {
  checkParameters(parameters, supported_params_);

  execute_(parameters);
}

void CallableImpl::canReturn() const {
  if (result_type_ == DataType::None) {
    throw ResultReturningNotSupported();
  }
}

DataVariant CallableImpl::call(uintmax_t timeout) const {
  auto params = makeDefaultParams(supported_params_);
  return call(params, timeout);
}

DataVariant CallableImpl::call(
    const Parameters& parameters, uintmax_t timeout) const {
  canReturn();
  if (!call_) {
    throw ResultReturningNotSupported();
  }
  checkParameters(parameters, supported_params_);

  auto result_future = call_(parameters);
  if (result_future.waitFor(chrono::milliseconds(timeout)) ==
      future_status::ready) {
    return result_future.get();
  } else {
    throw CallTimedout("metric");
  }
}

[[nodiscard]] ResultFuture CallableImpl::asyncCall(
    const Parameters& parameters) const {
  canReturn();
  if (!call_) {
    throw ResultReturningNotSupported();
  }
  checkParameters(parameters, supported_params_);

  return call_(parameters);
}

void CallableImpl::cancelAsyncCall(uintmax_t call_id) const {
  canReturn();
  if (!cancel_) {
    throw ResultReturningNotSupported();
  }

  cancel_(call_id);
}

DataType CallableImpl::resultType() const { return result_type_; }

ParameterTypes CallableImpl::parameterTypes() const {
  return supported_params_;
}

} // namespace Information_Model_Manager