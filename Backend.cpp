#include "Backend.h"
#include <QDebug>
#include <optional>
#include <utils/utils.h>



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