#ifndef __READABLE_METRIC_IMPLEMENTATION_HPP_
#define __READABLE_METRIC_IMPLEMENTATION_HPP_

#include "ReadableMetric.hpp"

#include <functional>

namespace Model_Factory {

  template<class T>
  class ReadableMetricImpl : public Information_Model::ReadableMetric<T> {
   public:
    ReadableMetricImpl(const std::string& ref_id,
        const std::string& name,
        const std::string& desc,
        std::function<Information_Model::DataWrapper<T>()> read_cb)
        : Information_Model::ReadableMetric<T>(ref_id, name, desc)
        , read_cb_(read_cb) {}

    Information_Model::DataWrapper<T> getMetricValue() {
      return read_cb_();
    }

   private:
    std::function<Information_Model::DataWrapper<T>()> read_cb_;
  };
}   // namespace Model_Factory

#endif   //__READABLE_METRIC_IMPLEMENTATION_HPP_