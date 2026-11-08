#include "utils.h"

#include <fstream>
#include <windows.h>
#include <string>
#include <filesystem>
#include <iterator>

namespace fs = std::filesystem;

std::wstring SelectFolder() {
    std::wstring path;

    IFileDialog* dialog = nullptr;

    if (SUCCEEDED(CoCreateInstance(
        CLSID_FileOpenDialog,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&dialog)
    ))) {
        DWORD options;
        if (SUCCEEDED(dialog->GetOptions(&options))) {
            dialog->SetOptions(options | FOS_PICKFOLDERS);
        }

        if (SUCCEEDED(dialog->Show(nullptr))) {
            IShellItem* item = nullptr;

            if (SUCCEEDED(dialog->GetResult(&item))) {
                PWSTR folderPath = nullptr;

                if (SUCCEEDED(item->GetDisplayName(
                    SIGDN_FILESYSPATH, &folderPath
                ))) {
                    path = folderPath;
                    CoTaskMemFree(folderPath);
                }

                item->Release();
            }
        }

        dialog->Release();
    }

    return path;
}


std::wstring SelectFile(
    std::initializer_list<COMDLG_FILTERSPEC> filters
) {
    std::wstring path;
    IFileDialog* dialog = nullptr;

    if (SUCCEEDED(CoCreateInstance(
        CLSID_FileOpenDialog,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&dialog)
    ))) {
        DWORD options;
        if (SUCCEEDED(dialog->GetOptions(&options))) {
            dialog->SetOptions(options | FOS_FILEMUSTEXIST);
        }

        dialog->SetFileTypes(
            static_cast<UINT>(filters.size()),
            filters.begin()
        );

        if (SUCCEEDED(dialog->Show(nullptr))) {
            IShellItem* item = nullptr;

            if (SUCCEEDED(dialog->GetResult(&item))) {
                PWSTR filePath = nullptr;

                if (SUCCEEDED(item->GetDisplayName(
                    SIGDN_FILESYSPATH, &filePath
                ))) {
                    path = filePath;
                    CoTaskMemFree(filePath);
                }

                item->Release();
            }
        }

        dialog->Release();
    }

    return path;
}


std::vector<std::wstring> findFiles(const std::wstring& folder, const std::wstring& extension)
{
    std::vector<std::wstring> files;

    for (const auto& it : fs::directory_iterator(folder)) {
        if (it.is_regular_file() && it.path().extension() == extension) {
            files.push_back(it.path().wstring());
        }
    }

    return files;
}

std::string readFile(std::wstring filePath)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) return "";

    return std::string (
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );
}