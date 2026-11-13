#include "utils.h"

#include <Windows.h>
#include <string_view>
#include <cstdint>
#include <stdexcept>
#include <system_error>

static std::vector<std::string_view> Split(
    std::string_view str,
    std::string_view delimiter
) {
    std::vector<std::string_view> result;

    if (delimiter.empty())
        return { str };

    size_t start = 0;
    size_t end;

    while ((end = str.find(delimiter, start)) != std::string_view::npos) {
        result.emplace_back(str.substr(start, end - start));
        start = end + delimiter.size();
    }

    result.emplace_back(str.substr(start));

    return result;
}

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

std::unordered_map<std::string, std::string> makeXmlToHashMap(std::string fileContent)
{
    std::unordered_map<std::string, std::string> convertedResult;

    std::istringstream stream(fileContent);
    std::string line;

    while (std::getline(stream, line))
    {
        auto splittedText = Split(line, " = ");

        std::string value(splittedText[1]);
        value.erase(
            std::remove(value.begin(), value.end(), '"'),
            value.end()
        );

        convertedResult.emplace(splittedText[0], value);
    }

    return convertedResult;
}


static bool EndsWith(const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size() &&
        str.compare(str.size() - suffix.size(),
            suffix.size(), suffix) == 0;
}

static bool StartsWith(const std::string& str, const std::string& prefix) {
    return str.size() >= prefix.size() &&
        str.compare(0, prefix.size(), prefix) == 0;
}

std::string removeAll(std::string str, const std::string& target) {
    if (target.empty()) return str;

    size_t pos = 0;
    while ((pos = str.find(target, pos)) != std::string::npos) {
        str.erase(pos, target.length());
    }

    return str;
}