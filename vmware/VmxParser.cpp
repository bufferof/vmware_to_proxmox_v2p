#include "VmxParser.h"
#include "utils/utils.h"

#include <iostream>
#include <future>
#include <utility>
#include <regex>

std::regex pattern(R"(^ethernet([0-9]+)\.present$)"); // 이더넷 찾을 때 쓰는 regex


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

static std::pair<std::vector<std::pair<std::string, std::string>>, std::vector<std::pair<std::string, std::string>>>  FindDisks(
    const std::unordered_map<std::string, std::string>& config
) {
    std::vector<std::pair<std::string,std::string>> disks;
    std::vector<std::pair<std::string, std::string>> cdROMs;

    for (const auto& [key, value] : config) {
        if ( EndsWith(key,".fileName") &&
          (StartsWith(key,"scsi") || StartsWith(key,"sata") || StartsWith(key,"nvme") || StartsWith(key,"ide"))) {
            if (EndsWith(key, ".vmdk")) {
                disks.push_back(std::make_pair(removeAll(key, ".fileName"), value));
            }
            else if (EndsWith(key, ".iso")) {
                cdROMs.push_back(std::make_pair(removeAll(key, ".fileName"), value));
            }
            
        }
    }

    return {disks, cdROMs};
}

static std::vector<std::string> FindNetworkInterfaces(
  const std::unordered_map<std::string, std::string> &config  
) {
    std::vector<std::string> ethernets;

    for (const auto& [key, value] : config) {
        std::smatch match;
        if (std::regex_match(key, match, pattern)) {
            ethernets.push_back(std::string(Split(key, ".")[0]));
        }
    }

    return ethernets;
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

    // Disk Informations && CDRom Informations 
    auto [disks,cdroms] = FindDisks(vmxHashed);

    for (auto &it : disks) {
        DiskConfig disk;
        disk.controller = Split(it.first, ":")[0];
        disk.device = vmxHashed[it.first + ".deviceType"];
        disk.fileName = it.second;

        if (vmxHashed[it.first + ".present"] == "TRUE") {
            disk.present = true;
        }

        config.disks.push_back(disk);
    }

    for (auto& it : cdroms) {
        CDRomConfig cdrom;
        cdrom.controller = Split(it.first, ":")[0];
        cdrom.device = vmxHashed[it.first + ".deviceType"];
        cdrom.fileName = it.second;

        if (vmxHashed[it.first + ".present"] == "TRUE") {
            cdrom.present = true;
        }

        config.cdroms.push_back(cdrom);
    }

    // Network Interface Informations
    std::vector<std::string> ethernets = FindNetworkInterfaces(vmxHashed);

    for (auto& it : ethernets) {
        NetworkConfig network;
        network.device = it;
        network.virtualDev = vmxHashed[it + ".virtualDev"];
        network.connectionType = vmxHashed[it + ".connectionType"];
        
        if (vmxHashed[it + ".present"] == "TRUE") {
            network.present = true;
        }

        config.networks.push_back(network);
    }

	return config;
}
