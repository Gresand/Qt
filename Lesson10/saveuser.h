#ifndef SAVEUSER_H
#define SAVEUSER_H

#include <QObject>
#include <QFile>

class saveUser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList model MEMBER listData NOTIFY modelChanged)
    Q_PROPERTY(int oldT MEMBER oldT)
    Q_PROPERTY(int newT MEMBER newT NOTIFY modelChanged)
public:
    explicit saveUser(QObject *parent = nullptr);
    virtual ~saveUser();
    Q_INVOKABLE void loadSave();
    Q_INVOKABLE void save();
public slots:
    void setTask(QString);
signals:
    void modelChanged();
    void initEnd(bool succed);
private:
    QFile* saveFile;
    QString dataLoad;
    QString newData;
    QStringList listData;
    bool flagChange;
    int oldT;
    int newT;
};

#endif // SAVEUSER_H
