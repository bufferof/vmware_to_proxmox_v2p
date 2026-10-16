#include "utils.h"

#include <Windows.h>
#include <string>

std::string WStringToString(const std::wstring& wstr)
{
    if (wstr.empty())
        return {};

    int size = WideCharToMultiByte(
        CP_UTF8, 0,
        wstr.data(), static_cast<int>(wstr.size()),
        nullptr, 0, nullptr, nullptr
    );

    if (size == 0)
        return {};

    std::string result(size, '\0');

    WideCharToMultiByte(
        CP_UTF8, 0,
        wstr.data(), static_cast<int>(wstr.size()),
        result.data(), size, nullptr, nullptr
    );

    return result;
}