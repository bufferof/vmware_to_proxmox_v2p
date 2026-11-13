#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <optional>
#include <shobjidl.h>
#include <initializer_list>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <charconv>

std::wstring SelectFolder();
std::string WStringToString(const std::wstring& wstr);
std::wstring SelectFile(std::initializer_list<COMDLG_FILTERSPEC> filters);
std::vector<std::wstring> findFiles(const std::wstring& folder, const std::wstring& extension);
std::string readFile(std::wstring filePath);
std::unordered_map<std::string, std::string> makeXmlToHashMap(std::string fileContent);
static bool EndsWith(const std::string& str, const std::string& suffix);
static bool StartsWith(const std::string& str, const std::string& prefix);
std::string removeAll(std::string str, const std::string& target);
static std::vector<std::string_view> Split(
    std::string_view str,
    std::string_view delimiter
);

template<typename T>
static T convertStringToInteger(const std::string& target)
{
    T value = 0;

    auto [ptr, ec] = std::from_chars(
        target.data(),
        target.data() + target.size(),
        value
    );

    if (ec != std::errc{} || ptr != target.data() + target.size()) {
        throw std::invalid_argument("Invalid integer value");
    }

    return value;
}
#endif