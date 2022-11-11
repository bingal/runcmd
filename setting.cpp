#include "setting.h"
#include "ui_setting.h"
#include <QFileDialog>
#include <QSettings>
#include <QApplication>
#include <QFile>
#include <QMessageBox>

Setting::Setting(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Setting)
{
    ui->setupUi(this);

    QString configPath = QCoreApplication::applicationDirPath()+"/config.ini";
    QFile configFile = QFile(configPath);
    if(configFile.exists()){
        QSettings setIni=QSettings(configPath, QSettings::IniFormat);
        setIni.beginGroup("CONFIG");
        if(setIni.contains("cmd")){
            ui->cmd->setText(setIni.value("cmd").toString());
        }
        if(setIni.contains("args")){
            ui->args->setText(setIni.value("args").toString());
        }
        if(setIni.contains("path")){
            ui->path->setText(setIni.value("path").toString());
        }
        setIni.endGroup();
    }
}

Setting::~Setting()
{
    delete ui;
}

void Setting::on_openBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("打开可执行文件"),
                                                    "",
                                                    tr("可执行文件(*.exe *.bat)"));
    if(!fileName.isEmpty()){
        ui->cmd->setText(fileName);
    }
}


void Setting::on_saveBtn_clicked()
{
    QString cmd = ui->cmd->text();
    if(cmd.isEmpty()){
        QMessageBox::information(this, tr("出错了"),tr("请选择执行命令"));
        return;
    }
    QFile cmdFile(cmd);
    if(!cmdFile.exists()){
        QMessageBox::information(this, tr("出错了"),tr("您输入的命令文件不存在"));
        return;
    }
    QSettings setIni=QSettings(QCoreApplication::applicationDirPath()+"/config.ini", QSettings::IniFormat);
    setIni.beginGroup("CONFIG");
    setIni.setValue("cmd", cmd);
    setIni.setValue("args", ui->args->text());
    setIni.setValue("path", ui->path->text());
    setIni.endGroup();
    QMessageBox::information(this, tr("保持成功"),tr("配置文件保持成功，点确定关闭本窗口"));
    close();
}


void Setting::on_argsBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("打开参数文件"),
                                                    "",
                                                    tr("所有类型(*.*)"));
    if(!fileName.isEmpty()){
        ui->args->setText(fileName);
    }
}


void Setting::on_pathBtn_clicked()
{
    QString exePath = QFileDialog::getExistingDirectory(this);
    if(!exePath.isEmpty()){
        ui->path->setText(exePath);
    }
}

