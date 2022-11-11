#ifndef SETTING_H
#define SETTING_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Setting; }
QT_END_NAMESPACE

class Setting : public QWidget
{
    Q_OBJECT

public:
    Setting(QWidget *parent = nullptr);
    ~Setting();

private slots:
    void on_openBtn_clicked();

    void on_saveBtn_clicked();

    void on_argsBtn_clicked();

    void on_pathBtn_clicked();

private:
    Ui::Setting *ui;
};
#endif // SETTING_H
