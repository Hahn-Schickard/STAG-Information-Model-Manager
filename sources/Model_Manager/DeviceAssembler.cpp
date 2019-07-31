#include "DeviceAssembler.hpp"

DeviceAssembler::DeviceAssembler(const std::string NAME, const std::string REF_ID,
                                 const std::string DESC)
    : Model_Factory::DeviceBuilder(NAME, REF_ID, DESC)
{
}