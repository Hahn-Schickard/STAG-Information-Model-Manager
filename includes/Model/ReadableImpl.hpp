#ifndef __MODEL_READABLE_IMPLEMENTATION_HPP_
#define __MODEL_READABLE_IMPLEMENTATION_HPP_

#include "Information_Model/Readable.hpp"

#include <functional>
#include <memory>

namespace Information_Model_Manager {
struct ReadableImpl : public Information_Model::Readable {
  using ReadCallback = std::function<Information_Model::DataVariant()>;

  ReadableImpl(Information_Model::DataType type, const ReadCallback& read_cb);

  Information_Model::DataType dataType() const final;

  Information_Model::DataVariant read() const final;

private:
  Information_Model::DataType type_ = Information_Model::DataType::Unknown;
  ReadCallback read_;
};

using ReadableImplPtr = std::shared_ptr<ReadableImpl>;
} // namespace Information_Model_Manager

#endif //__MODEL_READABLE_IMPLEMENTATION_HPP_