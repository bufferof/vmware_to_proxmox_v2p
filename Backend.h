#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>

class Backend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString vmFolder READ vmFolder NOTIFY vmFolderChanged)
    Q_PROPERTY(QString sshKeyPath READ sshKeyPath NOTIFY sshKeyPathChanged)

public:
    explicit Backend(QObject* parent = nullptr);

    QString vmFolder() const { return m_vmFolder; }
    QString sshKeyPath() const { return m_sshKeyPath; }

signals:
    void vmFolderChanged();
    void sshKeyPathChanged();

private:
    QString m_vmFolder;
    QString m_sshKeyPath;

public slots:
    void startMigration();
    void selectFile();
    void selectSshKey();
};

#endif