#ifndef __WRITABLE_METRIC_IMPLEMENTATION_HPP
#define __WRITABLE_METRIC_IMPLEMENTATION_HPP

#include "ReadableMetricImpl.hpp"
#include "WritableMetric.hpp"

#include <functional>

namespace Model_Factory {
  template<class T>
  class WritableMetricImpl
      : public ReadableMetricImpl<T>
      , public Information_Model::WritableMetric<T> {
   public:
    WritableMetricImpl(const std::string& ref_id,
        const std::string& name,
        const std::string& desc,
        std::function<Information_Model::DataWrapper<T>()> read_cb,
        std::function<void(Information_Model::DataWrapper<T>)> write_cb)
        : ReadableMetricImpl<T>(ref_id, name, desc, read_cb)
        , write_cb_(write_cb) {}

    void setMetricValue(Information_Model::DataWrapper<T> value) {
      write_cb_(value);
    }

   private:
    std::function<void(Information_Model::DataWrapper<T>)> write_cb_;
  };
}   // namespace Model_Factory

#endif   //__WRITABLE_METRIC_IMPLEMENTATION_HPP