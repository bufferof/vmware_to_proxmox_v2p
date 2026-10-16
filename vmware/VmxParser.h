#ifndef VMXPARSER_H
#define VMXPARSER_H

#include <vector>
#include <string>

enum class FirmwareType
{
    BIOS,
    EFI,
    UNKNOWN
};

struct CPUConfig
{
    uint32_t numvcpus;
    uint32_t coresPerSocket;
    uint32_t coresPerNode;
    uint32_t numSMT;
    bool hotadd;
};

struct MemoryConfig
{
    uint64_t memsize;
};

struct DiskConfig
{
    std::string controller;
    std::string device;
    std::string deviceType;
    std::string fileName;
    std::string mode;
    std::string controllerType;
    bool present;
};

struct CDRomConfig
{
    std::string controller;
    std::string device;
    std::string deviceType;
    std::string fileName;
    bool present;
    bool startConnected;
    bool autodetect;
};

struct NetworkConfig
{
    std::string device;
    std::string virtualDev;
    std::string connectionType;
    std::string addressType;
    uint16_t pciSlotNumber;
    bool present;
};

struct PciBridgeConfig
{
    std::string name;
    std::string virtualDev;
    uint32_t functions;
    uint32_t pciSlotNumber;
    bool present;
};

struct DisplayConfig
{
    uint64_t vramSize;
    uint64_t graphicsMemoryKB;
    bool guestBackedPrimaryAware;
};

struct UsbConfig
{
    bool present;
};

struct VmConfig
{
    std::string displayname;
    std::string guestOS;

    FirmwareType firmware = FirmwareType::UNKNOWN;

    CPUConfig cpu{};
    MemoryConfig memory{};
    DisplayConfig display{};
    UsbConfig usb{};

    std::vector<DiskConfig> disks;
    std::vector<CDRomConfig> cdroms;
    std::vector<NetworkConfig> networks;
    std::vector<PciBridgeConfig> pciBridges;
};

void make_vmconfig(std::string vmx_filepath);

#endif