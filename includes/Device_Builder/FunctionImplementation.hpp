#ifndef __MODEL_BUILDER_FUNCTION_IMPLEMENTATION_HPP_
#define __MODEL_BUILDER_FUNCTION_IMPLEMENTATION_HPP_

#include "ElementMetaInfo.hpp"
#include "Information_Model/Function.hpp"

#include <cstdint>
#include <functional>
#include <future>
#include <mutex>
#include <unordered_set>

namespace Information_Model_Manager {
struct FunctionImplementation : public Information_Model::Function,
                                public ElementMetaInfo {
  using ExecutorResult =
      std::pair<uintmax_t, std::future<Information_Model::DataVariant>>;
  using Executor = std::function<ExecutorResult(Function::Parameters)>;
  using Canceler = std::function<void(uintmax_t)>;

  FunctionImplementation(
      const ParameterTypes& parameters, const Executor& executor);
  FunctionImplementation(Information_Model::DataType result_type,
      const ParameterTypes& parameters,
      const Executor& executor,
      const Canceler& canceler);

  void execute(const Parameters& parameters) override;
  Information_Model::DataVariant call(
      const Parameters& parameters, uintmax_t timeout) override;
  ResultFuture asyncCall(const Parameters& parameters) override;
  void cancelAsyncCall(uintmax_t call_id) override;
  void cancelAllAsyncCalls() override;

private:
  void checkParameters(const Parameters& requested_parameters);
  void removeCaller(uintmax_t call_id);
  ResultFuture addCaller(ExecutorResult&& promised_future);

  Executor executor_;
  Canceler canceler_;
  Information_Model::DataType result_type_;
  std::unordered_set<uintmax_t> calls_;
  std::mutex clear_mx_;
};
} // namespace Information_Model_Manager
#endif //__MODEL_BUILDER_FUNCTION_IMPLEMENTATION_HPP_