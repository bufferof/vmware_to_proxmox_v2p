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

VmConfig make_vmconfig(std::unordered_map<std::string, std::string> vmxHashed)
{
	VmConfig config;

	config.displayName = vmxHashed["displayname"];
	config.guestOS = vmxHashed["guestos"];
    config.firmware = ParseFirmware(vmxHashed);

	return config;
}