#include "FunctionImplementation.hpp"

#include <chrono>
#include <thread>

using namespace std;
using namespace Information_Model;
using namespace HaSLI;

namespace Information_Model_Manager {
FunctionImplementation::FunctionImplementation(const HaSLI::LoggerPtr& logger,
    const ParameterTypes& parameters,
    const Executor& executor)
    : FunctionImplementation(
          logger, DataType::NONE, parameters, executor, nullptr) {}

FunctionImplementation::FunctionImplementation(const HaSLI::LoggerPtr& logger,
    DataType result_type,
    const ParameterTypes& parameters,
    const Executor& executor,
    const Canceler& canceler)
    : Function(result_type, parameters), logger_(logger), executor_(executor),
      canceler_(canceler) {}

void FunctionImplementation::checkParameters(
    const Parameters& requested_parameters) {
  for (const auto& requested : requested_parameters) {
    auto supported = parameters.at(requested.first);
    if (requested.second.has_value()) {
      auto requested_param_type = toDataType(requested.second.value());
      if (requested_param_type != supported.first) {
        throw invalid_argument(getElementInfo("Function") +
            " requested parameter " + to_string(requested.first) + " " +
            toString(requested_param_type) +
            " does not match supported parameter " + toString(supported.first) +
            " type");
      }
    } else {
      if (!supported.second) {
        throw invalid_argument(getElementInfo("Function") +
            " requested parameter " + to_string(requested.first) +
            " is marked as mandatory, but has no assigned value");
      }
    }
  }
}

void FunctionImplementation::execute(const Parameters& parameters) {
  if (executor_) {
    checkParameters(parameters);
    thread([this, &parameters]() -> void {
      try {
        executor_(parameters);
      } catch (const exception& ex) {
        logger_->error("{} execute call caught an exception: {}",
            getElementInfo("Function"),
            ex.what());
      } catch (...) {
        logger_->critical("{} execute call caught an unknown exception",
            getElementInfo("Function"));
      }
    }).detach();
  } else {
    throw logic_error(getElementInfo("Function") +
        " executed a nonexistent execute function");
  }
}

Function::ResultFuture FunctionImplementation::addCaller(
    ExecutorResult&& promised_future) {
  if (!calls_.insert(promised_future.first).second) {
    canceler_(promised_future.first);
    throw CallerIDExists(promised_future.first,
        getElementInfo("Function") + " executer returned existing caller id");
  } else {
    return Function::ResultFuture(move(promised_future.second),
        promised_future.first,
        bind(&FunctionImplementation::removeCaller, this, placeholders::_1));
  }
}

void FunctionImplementation::removeCaller(uintmax_t call_id) {
  auto clear_lock = lock_guard(clear_mx_);
  try {
    calls_.erase(call_id);
  } catch (...) {
    // remove must never throw
  }
}

DataVariant FunctionImplementation::call(
    const Parameters& parameters, uintmax_t timeout) {
  if (executor_) {
    if (canceler_) {
      checkParameters(parameters);
      if (result_type_ != DataType::NONE) {
        auto execution_call =
            std::async(std::launch::async, [this, &parameters]() {
              auto promised_future = executor_(parameters);
              return addCaller(move(promised_future));
            });
        auto result_future = execution_call.get();
        auto status =
            result_future.wait_for(std::chrono::milliseconds(timeout));
        if (status == std::future_status::ready) {
          removeCaller(result_future.call_id);
          return result_future.get();
        } else {
          throw FunctionCallTimedout(getElementInfo("Function"));
        }
      } else {
        return Function::call();
      }
    } else {
      throw logic_error(getElementInfo("Function") +
          " called the execute function without a valid canceler");
    }
  } else {
    throw logic_error(
        getElementInfo("Function") + " called a nonexistent execute function");
  }
}

Function::ResultFuture FunctionImplementation::asyncCall(
    const Parameters& parameters) {
  if (executor_) {
    if (canceler_) {
      checkParameters(parameters);
      if (result_type_ != DataType::NONE) {
        return addCaller(move(executor_(parameters)));
      } else {
        return Function::asyncCall();
      }
    } else {
      throw logic_error(getElementInfo("Function") +
          " async called the execute function without a valid canceler");
    }
  } else {
    throw logic_error(getElementInfo("Function") +
        " async called a nonexistent execute function");
  }
}

void FunctionImplementation::cancelAsyncCall(uintmax_t call_id) {
  if (canceler_) {
    auto called = calls_.find(call_id);
    if (called != calls_.end()) {
      canceler_(call_id);
      removeCaller(call_id);
    } else {

      throw CallerNotFound(call_id, getElementInfo("Function"));
    }
  } else {
    throw logic_error(getElementInfo("Function") +
        " called a nonexistent cancel call function");
  }
}

void FunctionImplementation::cancelAllAsyncCalls() {
  if (canceler_) {
    auto clear_lock = lock_guard(clear_mx_);
    for (auto call_id : calls_) {
      canceler_(call_id);
    }
    calls_.clear();
  } else {
    throw logic_error(getElementInfo("Function") +
        " called a nonexistent cancel all calls function");
  }
}

} // namespace Information_Model_Manager
