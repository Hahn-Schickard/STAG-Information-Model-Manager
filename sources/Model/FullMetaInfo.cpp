#include "FullMetaInfo.hpp"

namespace Information_Model_Manager {
using namespace std;
using namespace Information_Model;

FullMetaInfo::FullMetaInfo(const string& id, const BuildInfo& meta)
    : id_(id), meta_(meta) {}

string FullMetaInfo::id() const { return id_; }

string FullMetaInfo::name() const { return meta_.name; }

string FullMetaInfo::description() const { return meta_.description; }

} // namespace Information_Model_Manager