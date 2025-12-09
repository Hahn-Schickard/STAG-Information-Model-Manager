#ifndef __MODEL_OBSERVABLE_IMPLEMENTATION_HPP_
#define __MODEL_OBSERVABLE_IMPLEMENTATION_HPP_

#include "ReadableImpl.hpp"

#include "Event_Model/SourceInterface.hpp"
#include "Information_Model/Observable.hpp"

#include <functional>
#include <memory>

namespace Information_Model_Manager {

struct ObservableImpl : public Information_Model::Observable {
  using ReadCallback = ReadableImpl::ReadCallback;
  using NotifyCallback =
      std::function<void(const Information_Model::DataVariant&)>;
  using IsObservingCallback = std::function<void(bool)>;

  ObservableImpl(Information_Model::DataType type,
      const ReadCallback& read_cb,
      const IsObservingCallback& observed);

  Information_Model::DataType dataType() const final;

  Information_Model::DataVariant read() const final;

  [[nodiscard]] Information_Model::ObserverPtr subscribe(
      const Information_Model::Observable::ObserveCallback& observe_cb,
      const Information_Model::Observable::ExceptionHandler& handler) final;

  void notify(const Information_Model::DataVariant& value);

private:
  ReadableImplPtr readable_;
  IsObservingCallback observed_;
  Event_Model::SourceInterfacePtr<Information_Model::DataVariant> source_;
};
} // namespace Information_Model_Manager

#endif //__MODEL_OBSERVABLE_IMPLEMENTATION_HPP_