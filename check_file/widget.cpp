#include "widget.h"
#include "ui_widget.h"
#include "dirsource.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(openFolder()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(openFolder()));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_3_clicked()
{
    ui->listWidget->clear();
    classicCheck check(ui->FirstDir->text(),ui->LastDir->text());
    ui->listWidget->addItems(check.duplicate_files());
}

void Widget::on_pushButton_4_clicked()
{
    ui->listWidget->clear();
    summCheck::getInstance().set_all_path(ui->FirstDir->text(),ui->LastDir->text());
    ui->listWidget->addItems(summCheck::getInstance().duplicate_files());
}

void Widget::openFolder()
{
    QString dir = QFileDialog::getExistingDirectory(this,
                               QString::fromUtf8("Открыть папку"),
                               QDir::currentPath(),
                               QFileDialog::ShowDirsOnly
                               | QFileDialog::DontResolveSymlinks);

    if(ui->pushButton==QObject::sender())
        ui->FirstDir->setText(dir);
    else
        ui->LastDir->setText(dir);

}
