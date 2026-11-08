#ifndef VMXPARSER_H
#define VMXPARSER_H

#include <vector>
#include <string>
#include <unordered_map>

enum class FirmwareType
{
    BIOS,
    EFI,
    UNKNOWN
};

struct CPUConfig
{
    uint32_t numvcpus = 1;
    uint32_t coresPerSocket = 1;
    bool hotadd = false;
};

struct MemoryConfig
{
    uint64_t memsize = 0;  // MB
};

struct DiskConfig
{
    std::string controller;
    std::string device;
    std::string fileName;
    bool present = false;
};

struct CDRomConfig
{
    std::string controller;
    std::string device;
    std::string fileName;
    bool present = false;
};

struct NetworkConfig
{
    std::string device;
    std::string virtualDev;
    std::string connectionType;
    bool present = false;
};

struct VmConfig
{
    std::string displayName;
    std::string guestOS;

    FirmwareType firmware = FirmwareType::UNKNOWN;

    CPUConfig cpu{};
    MemoryConfig memory{};

    std::vector<DiskConfig> disks;
    std::vector<CDRomConfig> cdroms;
    std::vector<NetworkConfig> networks;
};

VmConfig make_vmconfig(std::unordered_map<std::string, std::string> vmxHashed);

#endif