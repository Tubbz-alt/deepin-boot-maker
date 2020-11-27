#ifndef QTBASEINSTALLER_H
#define QTBASEINSTALLER_H

#include "../util/sevenzip.h"
#include "bmhandler.h"

#include <QObject>

enum ProgressStatus
{
    CHECKSPACE,
    CHECKINTEGRITY,
    FORMATUSB,
    INSTALLBOOTLOADER,
    GETINSTALLDIR,
    EXTRACTISO,
    SYNCIO,
    EJECTDISK,
    FINISHED
};

class QtBaseInstaller : public QObject
{
    Q_OBJECT
public:
    explicit QtBaseInstaller(QObject *parent = nullptr);

public:
    void setformat(bool);
    void setPartionName(const QString&);
    void setImage(const QString&);
    void beginInstall();
    void checkError();

protected:
    virtual bool umountPartion() = 0;
    virtual bool umountDisk() = 0;
    virtual QString getMountPoint();
    virtual bool ejectDisk();

private:
    bool hasEnoughSpace();
    bool checkISOIntegrity();
    bool formatUsb();
    bool installBootload();
    bool extractISO();
    bool syncIO();
    bool configSyslinux();

signals:
    void progressfinished(ProgressStatus status, BMHandler::ErrorType error);
    void reportProgress(int current, const QString &title, const QString &description);
    void reportextractProgress(int, int, const QString &);

public slots:

public:
    SevenZip m_sevenZipCheck;

protected:
    bool m_bFormat;
    QString m_strPartionName;
    QString m_strImage;
    ProgressStatus m_progressStatus;
    BMHandler::ErrorType m_progressError;
};

#endif // QTBASEINSTALLER_H