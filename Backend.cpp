#include "Backend.h"
#include <QDebug>
#include <optional>

#include "utils/utils.h"

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
    
    std::optional<std::wstring> path = readFilePath();
    m_vmFolder = WStringToString(path.value());
    emit vmFolderChanged();
}