#ifndef DIRSOURCE_H
#define DIRSOURCE_H
#include <QDir>
#include <QFile>
#include <QCryptographicHash>
#include <QDebug>

class classicCheck//Решение в лоб перебором и сравнением файлов 1 директории с другим
{
    //простая реализация
public:
    classicCheck(){first_dir=QDir::current();sec_dir=QDir::current();first_path=QDir::currentPath();sec_path=QDir::currentPath();}//дефолтный конструктор все переменные суются в директорию запуска программы
    ~classicCheck(){}//пустой деструктор т.к. нет необходимости самому дистить хранящиеся данные
    classicCheck(QDir f_dir,QDir s_dir);//конструктор для передачи 2х экземпляров класса QDir
    classicCheck(QString f_path,QString s_path);//конструктор для передачи 2х экземпляров класса QString
    classicCheck(const classicCheck *copy);//конструктор копирования(в данном случае не обязателен т.к. копии не будут создаваться)

    //-----блок сеттеров и геттеров на случай "важных переговоров"
    void set_all_dir(const QDir _dir1, const QDir _dir2);
    void set_all_path(const QString _path1,const QString _path2);
    void set_first_path(const QString _path){if(normal_directory(_path)) first_path=_path;}
    void set_second_path(const QString _path){if(normal_directory(_path)) sec_path=_path;}
    void set_first_dir( const QDir _dir){first_dir=_dir;}
    void set_second_dir(const QDir _dir){sec_dir=_dir;}
    const QString get_first_path(){return first_path;}
    const QString get_second_path(){return sec_path;}
    const QDir get_first_dir(){return first_dir;}
    const QDir get_second_dir(){return sec_dir;}

    QStringList duplicate_files();//основная функция поиска дубликата

    void operator=(const classicCheck &copy);

private:
     QDir first_dir;//первая директория
     QDir sec_dir;//вторая директория
     QString first_path;//путь к первой директории
     QString sec_path;//путь к второй директории

     bool normal_directory(QString _path);//для проверки корректности введенных строчно директорий
     QByteArray open_file(QDir self_dir, QString f_name);//возвращаем массив с данными файла
     QStringList get_files(QDir self_dir);// возвращаем список файлов директории
};

//-----------------------------------------------------------------
// Реализация номер 2. Идея составить QMap где ключом будет "контрольная сумма" файла, значением поставлено название файла
// сам класс реализован под синглтон для разнообразия решения(при использовании в реальном многопоточно приложении может иметь свои плюсы)

class summCheck;

class summCheckDestroy  //что бы синглтон "умер сам" при завершении работы программы
{
  private:
    summCheck* p_inst;
  public:
    ~summCheckDestroy();
    void initialize( summCheck* p );//связка указателя синглтона с созданным экземплярос в "чистильщике"
};

class summCheck
{
  private:
    static summCheck* p_inst;
    static summCheckDestroy destroyer;

    QDir first_dir;//первая директория
    QDir sec_dir;//вторая директория
    QString first_path;//путь к первой директории
    QString sec_path;//путь к второй директории
    QMap<QByteArray,QString> files_first_dir;
    bool normal_directory(QString _path);//для проверки корректности введенных строчно директорий

  protected:
    summCheck(){first_dir=QDir::current();sec_dir=QDir::current();first_path=QDir::currentPath();sec_path=QDir::currentPath();}
    summCheck( const summCheck& ) = delete;             //для данной реалищзации нужно исключить конструктор копирования и оператор присвоения
    summCheck& operator=( summCheck& ) = delete;
   ~summCheck() { }
    QByteArray open_file(QDir self_dir, QString f_name);//возвращаем массив с данными файла
    QStringList get_files(QDir self_dir);// возвращаем список файлов директории

    friend class summCheckDestroy;
  public:
    static summCheck& getInstance();
    //-----блок сеттеров и геттеров
    void set_all_dir(const QDir _dir1, const QDir _dir2);
    void set_all_path(const QString _path1,const QString _path2);
    void set_first_path(const QString _path){if(normal_directory(_path)) first_path=_path;first_dir.setPath(_path);filling_map();}
    void set_second_path(const QString _path){if(normal_directory(_path)) sec_path=_path;sec_dir.setPath(_path);}
    void set_first_dir( const QDir _dir){first_dir=_dir;first_path=_dir.path();filling_map();}
    void set_second_dir(const QDir _dir){sec_dir=_dir;sec_path=_dir.path();}
    const QString get_first_path(){return first_path;}
    const QString get_second_path(){return sec_path;}
    const QDir get_first_dir(){return first_dir;}
    const QDir get_second_dir(){return sec_dir;}

    void filling_map();
     QStringList duplicate_files();//основная функция поиска дубликата
};


#endif // DIRSOURCE_H
