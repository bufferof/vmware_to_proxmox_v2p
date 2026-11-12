#include "VmxParser.h"
#include "utils/utils.h"

#include <iostream>
#include <future>

static FirmwareType ParseFirmware(
    const std::unordered_map<std::string, std::string>& config
) {
    auto it = config.find("firmware");

    if (it == config.end())
        return FirmwareType::BIOS;

    if (it->second == "efi")
        return FirmwareType::EFI;

    if (it->second == "bios")
        return FirmwareType::BIOS;

    return FirmwareType::UNKNOWN;
}

static std::vector<std::string> FindDisks(
    const std::unordered_map<std::string, std::string>& vmx
) {
    std::vector<std::string> disks;

    for (const auto& [key, value] : vmx) {
        if ( EndsWith(key,".fileName") &&
          (StartsWith(key,"scsi") || StartsWith(key,"sata") || StartsWith(key,"nvme") || StartsWith(key,"ide")) &&
           EndsWith(key,".vmdk")) {
            disks.push_back(value);
        }
    }

    return disks;
}

VmConfig make_vmconfig(std::unordered_map<std::string, std::string> vmxHashed)
{
	VmConfig config;

    // Default Informations
	config.displayName = vmxHashed["displayname"];
	config.guestOS = vmxHashed["guestos"];
    config.firmware = ParseFirmware(vmxHashed);
    
    // CPU Informations
    config.cpu.numvcpus = convertStringToInteger<uint32_t>(vmxHashed["numvcpus"]);
    config.cpu.coresPerSocket = convertStringToInteger<uint32_t>(vmxHashed["cpuid.coresPerSocket"]);
    if (vmxHashed["vcpu.hotadd"] == "true") config.cpu.hotadd = true;
    
    // Memory Informations
    config.memory.memsize = convertStringToInteger<uint64_t>(vmxHashed["memsize"]);

    // Disk Informations
    std::vector<std::string> disks = FindDisks(vmxHashed);



	return config;
}
