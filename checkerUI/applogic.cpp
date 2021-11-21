#include "applogic.h"

AppLogic::AppLogic(QObject *parent) : QObject(parent)
{

}

void AppLogic::findeEqfileM1(QString _path1, QString _path2)
{
    classicCheck new_check(_path1,_path2);
    resultList= new_check.duplicate_files();
    modelChanged();

}

void AppLogic::findeEqfileM2(QString _path1, QString _path2)
{
    summCheck::getInstance().set_all_path(_path1,_path2);
    resultList=  summCheck::getInstance().duplicate_files();
     modelChanged();
}
