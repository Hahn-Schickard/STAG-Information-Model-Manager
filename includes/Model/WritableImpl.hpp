#ifndef __MODEL_WRITABLE_IMPLEMENTATION_HPP_
#define __MODEL_WRITABLE_IMPLEMENTATION_HPP_

#include "ReadableImpl.hpp"

#include "Information_Model/Writable.hpp"

#include <functional>
#include <memory>

namespace Information_Model_Manager {
struct WritableImpl : public Information_Model::Writable {
  using ReadCallback = ReadableImpl::ReadCallback;
  using WriteCallback =
      std::function<void(const Information_Model::DataVariant&)>;

  WritableImpl(Information_Model::DataType type, const WriteCallback& write_cb);

  WritableImpl(Information_Model::DataType type,
      const ReadCallback& read_cb,
      const WriteCallback& write_cb);

  ~WritableImpl() override = default;

  Information_Model::DataType dataType() const final;

  Information_Model::DataVariant read() const final;

  bool isWriteOnly() const final;

  void write(const Information_Model::DataVariant& value) const final;

private:
  Information_Model::DataType type_ = Information_Model::DataType::Unknown;
  ReadCallback read_;
  WriteCallback write_;
};

using WritableImplPtr = std::shared_ptr<WritableImpl>;
} // namespace Information_Model_Manager

#endif //__MODEL_WRITABLE_IMPLEMENTATION_HPP_