#include "utils.h"

#include <fstream>
#include <sstream>
#include <windows.h>
#include <shobjidl.h>
#include <iostream>
#include <string>

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

std::string readTxtFile(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open()) return "";

	std::stringstream buffer;
	buffer << file.rdbuf();

	return buffer.str();
}

