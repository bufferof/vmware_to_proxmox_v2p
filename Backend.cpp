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