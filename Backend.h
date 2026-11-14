#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <optional>
#include <vmware/VmxParser.h>

class Backend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString vmFolder READ vmFolder NOTIFY vmFolderChanged)
    Q_PROPERTY(QString sshKeyPath READ sshKeyPath NOTIFY sshKeyPathChanged)
    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameInfoChanged)
    Q_PROPERTY(QString vmSpec READ vmSpec NOTIFY vmSpecInfoChanged)
public:
    explicit Backend(QObject* parent = nullptr);

    QString vmFolder() const { return m_vmFolder; }
    QString sshKeyPath() const { return m_sshKeyPath; }
    QString displayName() const { return m_displayName; }
    QString vmSpec() const { return m_vmSpec; }

signals:
    void vmFolderChanged();
    void sshKeyPathChanged();
    void displayNameInfoChanged();
    void vmSpecInfoChanged();

private:
    QString m_vmFolder;
    QString m_sshKeyPath;
    QString m_displayName;
    QString m_vmSpec;
    std::optional<VmConfig> vmxConfig;

public slots:
    void startMigration();
    void selectFile();
    void selectSshKey();
};

#endif