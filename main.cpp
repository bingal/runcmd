#include "setting.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QProcess>
#include <QFile>
#include <QMessageBox>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "runcmd_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QString configPath = QCoreApplication::applicationDirPath()+"/config.ini";

    QFile configFile(configPath);
    if(!configFile.exists()){
        Setting w;
        w.show();
        return a.exec();
    }

    QSettings setIni = QSettings(configPath, QSettings::IniFormat);
    setIni.beginGroup("CONFIG");
    QString cmd = "";
    if(setIni.contains("cmd")){
        cmd = setIni.value("cmd").toString();
    }
    if(cmd.isEmpty()){
        Setting w;
        w.show();
        return a.exec();
    }
    QString args = "";
    if(setIni.contains("args")){
        args = setIni.value("args").toString();
    }
    QString path = "";
    if(setIni.contains("path")){
        path = setIni.value("path").toString();
    }
    setIni.endGroup();

    QStringList processArguments;
    if(!args.isEmpty()){
        foreach(QString arg, args.split(" ")){
            processArguments.append(arg);
        }
    }
    QProcess p;
    p.start(cmd, processArguments);
    p.waitForFinished();
}
