#include "Backend.h"
#include <QDebug>
#include <optional>
#include <utils/utils.h>
#include <vmware/VmxParser.h>



Backend::Backend(QObject* parent)
    : QObject(parent)
{
}

void Backend::startMigration()
{
    qDebug() << "Migration started!";
}

void Backend::selectFile()
{
    
    std::optional<std::wstring> path = SelectFolder();

    if (!path.has_value())
        return;

    QString selectedPath = QString::fromStdWString(path.value());

    if (m_vmFolder == selectedPath)
        return;

    m_vmFolder = selectedPath;
    emit vmFolderChanged();

    auto targetFiles = findFiles(path.value(), L".vmx"); //이거 임시로 찾은 것들 중 첫번째 파일만 처리하게 함. 나중에 여러 vmx 한번에 변환 해버리는 기능 추가할 때 수정

    if (targetFiles.empty()) {
        qDebug() << "There are no Files";
        return;
    }

    std::wstring targetFile = std::move(targetFiles[0]);

    std::string vmxFileContent = readFile(targetFile);
    if(vmxFileContent == "") {
        qDebug() << "File Content Not Found~";
        return;
    }

    std::unordered_map<std::string, std::string> vmxInformations = makeXmlToHashMap(vmxFileContent);

    VmConfig vmConfigStructed = make_vmconfig(vmxInformations);
}


void Backend::selectSshKey()
{
    std::optional<std::wstring> path = SelectFile({
        { L"SSH Private Keys (*.pem;*.ppk;*.key)", L"*.pem;*.ppk;*.key" },
        { L"All Files (*.*)", L"*.*" }
    });

    if (!path.has_value())
        return;

    QString selectedPath = QString::fromStdWString(path.value());

    if (m_sshKeyPath == selectedPath)
        return;

    m_sshKeyPath = selectedPath;
    emit sshKeyPathChanged();
}