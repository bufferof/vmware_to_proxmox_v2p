#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString vmFolder READ vmFolder NOTIFY vmFolderChanged)
public:
    QString vmFolder() const { return m_vmFolder; }
    explicit Backend(QObject* parent = nullptr);

signals:
    void vmFolderChanged();

private:
    QString m_vmFolder;

public slots:
    void startMigration();
    void selectFile();
};


#endif