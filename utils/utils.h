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
#include <type_traits>

std::wstring SelectFolder();
std::string WStringToString(const std::wstring& wstr);
std::wstring SelectFile(std::initializer_list<COMDLG_FILTERSPEC> filters);
std::vector<std::wstring> findFiles(const std::wstring& folder, const std::wstring& extension);
std::string readFile(std::wstring filePath);
std::unordered_map<std::string, std::string> makeXmlToHashMap(std::string fileContent);
bool EndsWith(const std::string& str, const std::string& suffix);
bool StartsWith(const std::string& str, const std::string& prefix);
std::string removeAll(std::string str, const std::string& target);
std::vector<std::string_view> Split(
    std::string_view str,
    std::string_view delimiter
);


template<typename T>
T convertStringToInteger(std::string_view target)
{
    static_assert(std::is_integral_v<T>, "T must be an integer type");

    // 앞뒤 공백 및 개행 제거
    constexpr std::string_view whitespace = " \t\r\n";

    const auto first = target.find_first_not_of(whitespace);

    if (first == std::string_view::npos)
        throw std::invalid_argument("Empty integer value");

    const auto last = target.find_last_not_of(whitespace);

    target = target.substr(first, last - first + 1);

    T value = 0;

    auto [ptr, ec] = std::from_chars(
        target.data(),
        target.data() + target.size(),
        value
    );

    if (ec != std::errc{} || ptr != target.data() + target.size())
        throw std::invalid_argument("Invalid integer value");

    return value;
}
#endif