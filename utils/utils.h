#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <optional>
#include <shobjidl.h>
#include <initializer_list>

std::string readTxtFile(const std::string& path);
std::wstring SelectFolder();
std::string WStringToString(const std::wstring& wstr);
std::wstring SelectFile(std::initializer_list<COMDLG_FILTERSPEC> filters);

#endif