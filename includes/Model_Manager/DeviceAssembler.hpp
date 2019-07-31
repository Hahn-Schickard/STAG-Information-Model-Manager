#ifndef __DEVICE_ASSEMBLER_HPP
#define __DEVICE_ASSEMBLER_HPP

#include "DeviceBuilder.hpp"

class DeviceAssembler : public Model_Factory::DeviceBuilder
{
public:
    DeviceAssembler(const std::string NAME, const std::string REF_ID,
                    const std::string DESC);
};

#endif //__DEVICE_ASSEMBLER_HPP