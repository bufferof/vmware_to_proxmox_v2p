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
    vmxConfig = make_vmconfig(vmxInformations); // VMX 파일 내용 -> vmConfig 구조체로 저장
    if (!vmxConfig.has_value()) {
        qDebug() << "vmx Parsing Failed~";
        return;
    }
    
    if (!vmxConfig.has_value()) {
        qWarning() << "VMX config is empty";
        return;
    }

    const VmConfig& config = *vmxConfig;

    // 1. 문자열 변환
    QString displayName = QString::fromUtf8(
        config.displayName.data(),
        static_cast<qsizetype>(config.displayName.size())
    );

    // 2. VM 사양 문자열 생성
    QString vmSpec = QStringLiteral("%1 vCPU     •     %2 GB RAM     •     %3 disks")
        .arg(config.cpu.numvcpus)
        .arg(config.memory.memsize / 1024)
        .arg(static_cast<qulonglong>(config.disks.size()));

    // 3. 멤버 변수에 저장
    m_displayName = std::move(displayName);
    m_vmSpec = std::move(vmSpec);

    // 4. QML 업데이트
    emit displayNameInfoChanged();
    emit vmSpecInfoChanged();
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