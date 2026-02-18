#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QtWidgets>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser->setReadOnly(true);
    ui->textBrowser->setAlignment(Qt::AlignRight);
    ui->textBrowser->setPlainText("0");
    connect(ui->num0, &QPushButton::clicked, this, &MainWindow::numclick);
    connect(ui->num1, &QPushButton::clicked, this, &MainWindow::numclick);
    connect(ui->num2, &QPushButton::clicked, this, &MainWindow::numclick);
    connect(ui->num3, &QPushButton::clicked, this, &MainWindow::numclick);
    connect(ui->num4, &QPushButton::clicked, this, &MainWindow::numclick);
    connect(ui->num5, &QPushButton::clicked, this, &MainWindow::numclick);
    connect(ui->num6, &QPushButton::clicked, this, &MainWindow::numclick);
    connect(ui->num7, &QPushButton::clicked, this, &MainWindow::numclick);
    connect(ui->num8, &QPushButton::clicked, this, &MainWindow::numclick);
    connect(ui->num9, &QPushButton::clicked, this, &MainWindow::numclick);
    connect(ui->point, &QPushButton::clicked, this, &MainWindow::dotclick);
    connect(ui->num_plus, &QPushButton::clicked, this, &MainWindow::oper);
    connect(ui->num_minus, &QPushButton::clicked, this, &MainWindow::oper);
    connect(ui->num_dz, &QPushButton::clicked, this, &MainWindow::oper);
    connect(ui->num_mnoz, &QPushButton::clicked, this, &MainWindow::oper);
    connect(ui->num_cancsel, &QPushButton::clicked, this, &MainWindow::clear);
    connect(ui->num_delete, &QPushButton::clicked, this, &MainWindow::clearPrev);
    connect(ui->num_cos, &QPushButton::clicked, this, &MainWindow::trygsqOper);
    connect(ui->num_sin, &QPushButton::clicked, this, &MainWindow::trygsqOper);
    connect(ui->num_tg, &QPushButton::clicked, this, &MainWindow::trygsqOper);
    connect(ui->num_ctg, &QPushButton::clicked, this, &MainWindow::trygsqOper);
    connect(ui->num_pi, &QPushButton::clicked, this, &MainWindow::piclick);
    connect(ui->num_sqrt, &QPushButton::clicked, this, &MainWindow::trygsqOper);
    connect(ui->num_rown, &QPushButton::clicked, this, &MainWindow::res);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::val() const{
    QString str = ui->textBrowser->toPlainText().trimmed();
    if((str == "Error") or (str.isEmpty())){
        return 0.0;
    }
    return str.replace(',','.').toDouble();
}
void MainWindow::stVal(double r){
    ui->textBrowser->setPlainText(QString::number(r, 'g', 10));
}

void MainWindow::textDis(const QString &strr){
    ui->textBrowser->setPlainText(strr);
}

void MainWindow::numclick(){
    auto *button = qobject_cast<QPushButton*>(sender());
    if (!button){
        return;
    }
    QString check = ui->textBrowser->toPlainText();
    if ((flag) or (check=="0")){
        ui->textBrowser->setPlainText(button->text());
        flag = false;
    }
    else{
        ui->textBrowser->setPlainText(check + button->text());
    }
}

void MainWindow::dotclick(){
    if(flag){
        textDis("0.");
        flag = false;
        return;
    }
    QString check = ui->textBrowser->toPlainText();
    if((!check.contains('.'))and(!check.contains(','))){
        ui->textBrowser->setPlainText(check + '.');
    }
}

void MainWindow::clear(){
    first_num = 0.0;
    operation = 0;
    flag = true;
    stVal(0.0);
}

void MainWindow::clearPrev(){
    stVal(0.0);
    flag = true;
}

double MainWindow::appBin(QChar p, double x, double y){
    switch (p.unicode()){
    case '+' : return x+y;
    case '-' : return x-y;
    case '*' : return x*y;
    case '/' : if(y==0) throw runtime_error("delenie_na_0"); return x/y;
    default: return y;
    }
}

void MainWindow::oper(){
    ui->label->setText("");
    auto *button = qobject_cast<QPushButton*>(sender());
    if (!button){
        return;
    }
    double x = val();
    if(operation == 0){
        first_num = x;
    }
    else{
        try{
            first_num = appBin(operation, first_num, x);
            stVal(first_num);
        }
        catch(...){
            textDis("Error");
            first_num = 0.0;
            operation = 0;
        }
    }
    operation = button->text().at(0);
    flag = true;
    ui->textBrowser->setPlainText("0");
    ui->label->setText(button->text());
}

void MainWindow::res(){
    try{
        double a = val();
        double result = appBin(operation, first_num, a);
        stVal(result);
        previus_answer = result;
        operation = 0;
        flag = true;
    }
    catch(...){
        textDis("Erro");
        operation = 0;
        flag = true;
    }
}

double MainWindow::RadDz(const QString &name, double a){
    if(name=="cos"){
        return cos(a);
    }
    if(name=="sin"){
        return sin(a);
    }
    if(name=="tg"){
        return tan(a);
    }
    if(name=="ctg"){
        return 1/tan(a);
    }
    if((name=="√") or (name == "sqrt")){
        if(a<0) throw runtime_error("pierwiastek od ujemnego");
        return sqrt(a);
    }
    return a;
}

void MainWindow::trygsqOper(){
    auto *button = qobject_cast<QPushButton*>(sender());
    if (!button){
        return;
    }
    try{
        double a = RadDz(button->text().toLower(), val());
        stVal(a);
        previus_answer = a;
        flag = true;
    }
    catch(...){
        textDis("Error");
        flag = true;
    }
    ui->label->setText(button->text());
}

void MainWindow::piclick(){
    stVal(M_PI);
    flag = false;
}

