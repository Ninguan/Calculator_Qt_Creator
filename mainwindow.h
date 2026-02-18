#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void numclick();
    void dotclick();
    void clear();
    void clearPrev();
    void oper();
    void res();
    void trygsqOper();
    void piclick();

private:
    Ui::MainWindow *ui;
    double val() const;
    void stVal(double a);
    void textDis(const QString &s);
    double appBin(QChar op, double c, double d);
    double RadDz(const QString &name, double f);

    double first_num = 0.0;
    QChar operation = 0;
    bool flag = true;
    double previus_answer = 0.0;
};
#endif // MAINWINDOW_H
