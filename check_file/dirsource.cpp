#include "dirsource.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

classicCheck::classicCheck(QDir f_dir,QDir s_dir) :
 first_dir(f_dir),sec_dir(s_dir)
{
    first_path= first_dir.path();
    sec_path= sec_dir.path();

}

classicCheck::classicCheck(QString f_path,QString s_path) :
 first_path(f_path),sec_path(s_path)
{
    if(normal_directory(first_path) && normal_directory(first_path))
        qDebug()<<"folder is found";
    else
    {
        first_path=QDir::currentPath();
        sec_path=QDir::currentPath();
    }

    first_dir.setPath(first_path);
    sec_dir.setPath(sec_path);

}

classicCheck::classicCheck(const classicCheck *copy)
{
    first_dir= copy->first_dir;
    sec_dir= copy->sec_dir;
    first_path= copy->first_path;
    sec_path= copy->sec_path;
}

QStringList classicCheck::get_files(QDir self_dir)
{
    self_dir.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot); //ковыряем только файлы
    return self_dir.entryList();
}

QByteArray classicCheck::open_file(QDir self_dir, QString f_name)
{
    QByteArray self_ba;
    self_dir.setCurrent(self_dir.path());//работаем с выбраной директорией
    QFile file1(f_name);
    file1.open(QIODevice::ReadOnly);//открываем файл на чтение
    if(file1.isOpen())
    {
        self_ba=file1.readAll();//если успешно ковырнули файл- читаем в QByteArray
        file1.close();//закрываем файл за ненадобностью
    }
    else
       self_ba=NULL;//Если что-то пошло не так и файл не открылся

    return self_ba;
}


QStringList classicCheck::duplicate_files()
{
    QStringList list_equ_f;
    QStringList first_list=get_files(first_dir);
    for(QString f_name : first_list)
    {
        QByteArray first_ba=open_file(first_dir,f_name);
        if(first_ba.isNull())
            continue;
        QStringList sec_list=get_files(sec_dir);
        for(QString f_sec : sec_list)
        {
            QByteArray sec_ba=open_file(sec_dir,f_sec);
            if(sec_ba.isNull() || first_ba.size()!=sec_ba.size())
                continue;

            if(first_ba == sec_ba)
                list_equ_f<<(f_name+" - "+f_sec);   
        }
    }
    qDebug()<<list_equ_f;
    return list_equ_f;
}

void classicCheck::set_all_dir(const QDir _dir1, const QDir _dir2)
{
    first_dir=_dir1;
    sec_dir=_dir2;
    first_path=_dir1.path();
    sec_path=_dir2.path();

}

void classicCheck::set_all_path(const QString _path1, const QString _path2)
{
    if(normal_directory(_path1) && normal_directory(_path2))
    {
        first_path=_path1;
        sec_path=_path2;
    }
    else
    {
        qDebug()<<"folder not found";
        first_path=QDir::currentPath();
        sec_path=QDir::currentPath();
    }

    first_dir.setPath(first_path);
    sec_dir.setPath(sec_path);

}

void classicCheck::operator=(const classicCheck &copy)
{
    first_dir= copy.first_dir;
    sec_dir= copy.sec_dir;
    first_path= copy.first_path;
    sec_path= copy.sec_path;
}

bool classicCheck::normal_directory(QString _path)
{
    QDir _dir(_path);
    if( _dir.exists() )
        return true;

    return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

summCheck * summCheck::p_inst = 0;
summCheckDestroy summCheck::destroyer;

summCheckDestroy::~summCheckDestroy() {
    delete p_inst;
}
void summCheckDestroy::initialize( summCheck* p ) {
    p_inst = p;
}
bool summCheck::normal_directory(QString _path)
{
    QDir _dir(_path);
    if( _dir.exists() )
        return true;

    return false;
}

QByteArray summCheck::open_file(QDir self_dir, QString f_name)
{
    QByteArray self_summ=NULL;
    QCryptographicHash hash(QCryptographicHash::Md5);
    self_dir.setCurrent(self_dir.path());//работаем с выбраной директорией
    QFile file1(f_name);
    file1.open(QIODevice::ReadOnly);//открываем файл на чтение
    if(file1.isOpen())
    {
        if(hash.addData(&file1))
            self_summ= hash.result();
        file1.close();//закрываем файл за ненадобностью
    }

    return self_summ;
}

QStringList summCheck::get_files(QDir self_dir)
{
    self_dir.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot); //ковыряем только файлы
    return self_dir.entryList();
}

summCheck& summCheck::getInstance() {//создание и обращение к указателю класса, работаем через него
    if(!p_inst){
        p_inst = new summCheck();
        destroyer.initialize( p_inst);
    }
    return *p_inst;
}

void summCheck::set_all_dir(const QDir _dir1, const QDir _dir2)
{
    first_dir=_dir1;
    sec_dir=_dir2;
    first_path=_dir1.path();
    sec_path=_dir2.path();
    filling_map();
}

void summCheck::set_all_path(const QString _path1, const QString _path2)
{
    if(normal_directory(_path1) && normal_directory(_path2))
    {
        first_path=_path1;
        sec_path=_path2;
    }
    else
    {
        qDebug()<<"folder not found";
        first_path=QDir::currentPath();
        sec_path=QDir::currentPath();
    }

    first_dir.setPath(first_path);
    sec_dir.setPath(sec_path);
    filling_map();
}

void summCheck::filling_map()//заполняем наш QMap
{
    files_first_dir.clear();
    QStringList _list=get_files(first_dir);
    for(QString f_name : _list)
    {
        QByteArray self_summ=open_file(first_dir,f_name);
        if(!self_summ.isNull())
            files_first_dir.insert(self_summ,f_name);
    }
}

QStringList summCheck::duplicate_files()//из второй директории считаем суммы и кидаем в QMap, который выдает нам совпавшие файлы
{
    QStringList list_equ_f;
    QStringList sec_list=get_files(sec_dir);
    for(QString f_sec : sec_list)
    {
        QByteArray sec_ba=open_file(sec_dir,f_sec);
        for(QString f_name : files_first_dir.values(sec_ba))
            list_equ_f<<f_name+" - "+f_sec;
    }

    qDebug()<<list_equ_f;
    return list_equ_f;
}

