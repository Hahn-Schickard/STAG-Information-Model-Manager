#include "ObservableImpl.hpp"

#include <Event_Model/ListenerFactory.hpp>
#include <Event_Model/Source.hpp>

namespace Information_Model_Manager {
using namespace std;
using namespace Information_Model;
using namespace Event_Model;

struct Connection : public Information_Model::Observer {
  explicit Connection(const ListenerPtr<DataVariant>& listener)
      : listener_(listener) {}

  ~Connection() override = default;

private:
  ListenerPtr<DataVariant> listener_;
};

ObservableImpl::ObservableImpl(DataType type,
    const ReadCallback& read_cb,
    const IsObservingCallback& observed)
    : readable_(make_shared<ReadableImpl>(type, read_cb)), observed_(observed),
      source_(make_shared<Source<DataVariant>>(
          [this]() { observed_(true); }, [this]() { observed_(false); })) {}

DataType ObservableImpl::dataType() const { return readable_->dataType(); }

DataVariant ObservableImpl::read() const { return readable_->read(); }

[[nodiscard]] ObserverPtr ObservableImpl::subscribe(
    const ObservableImpl::ObserveCallback& observe_cb,
    const ObservableImpl::ExceptionHandler& handler) {
  if (!observe_cb) {
    throw invalid_argument("ObserveCallback can not be empty");
  }
  if (!handler) {
    throw invalid_argument("ExceptionHandler can not be empty");
  }

  // use the default normal priority, for DataVariant events
  auto connection = makeListener<DataVariant>(observe_cb, handler, source_);

  return make_shared<Connection>(connection);
}

void ObservableImpl::notify(const DataVariant& value) {
  source_->notify(make_shared<DataVariant>(value));
}

} // namespace Information_Model_Manager