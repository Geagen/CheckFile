#ifndef APPLOGIC_H
#define APPLOGIC_H

#include <QObject>
#include "dirsource.h"

class AppLogic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList model MEMBER resultList NOTIFY modelChanged)
public:
    explicit AppLogic(QObject *parent = nullptr);

    QStringList resultList;
    Q_INVOKABLE QStringList get_list(){return resultList;}

public slots:
    void findeEqfileM1(QString _path1,QString _path2);
    void findeEqfileM2(QString _path1,QString _path2);

signals:
    void modelChanged();
private:

};

#endif // APPLOGIC_H
