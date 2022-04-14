#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <math.h>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    double Start_SC_Mass, Gas_Flow_Speed, Fly_Time, Start_Orbit_Height,
    Start_Orbit_Inclination,Finally_Orbit_Height,Finally_Orbit_Inclination, Engine_Specific_Mass,
    Electro_Specific_Mass, SSS_Realitive_Mass, Realitive_Construct_Mass, Gravitation_Param, EFFICIENCY;



    Start_SC_Mass=ui->lineEdit_2->text().toDouble();
    Gas_Flow_Speed=ui->lineEdit_3->text().toDouble();
    Fly_Time=ui->lineEdit_4->text().toDouble()*86400;
    Start_Orbit_Height=ui->lineEdit_5->text().toDouble();
    Start_Orbit_Inclination=ui->lineEdit_6->text().toDouble();
    Finally_Orbit_Height=ui->lineEdit_7->text().toDouble();
    Finally_Orbit_Inclination=ui->lineEdit_25->text().toDouble();
    Engine_Specific_Mass=ui->lineEdit_8->text().toDouble();
    Electro_Specific_Mass=ui->lineEdit_9->text().toDouble();
    SSS_Realitive_Mass=ui->lineEdit_11->text().toDouble();
    Realitive_Construct_Mass=ui->lineEdit_12->text().toDouble();
    Gravitation_Param=ui->lineEdit_13->text().toDouble()*1000;
    EFFICIENCY=ui->lineEdit_14->text().toDouble();


    double Start_Orbit_Radius = (6371 + Start_Orbit_Height)*1000;
    double Finnaly_Orbit_Radius = (6371 + Finally_Orbit_Height)*1000;
    double Initial_Speed = sqrt(Gravitation_Param/Start_Orbit_Radius);
    double Delta_velocity = Initial_Speed*sqrt(1-2*sqrt(Start_Orbit_Radius/Finnaly_Orbit_Radius)*cos((M_PI/2)*(Finally_Orbit_Inclination-Start_Orbit_Inclination))+(Start_Orbit_Radius/Finnaly_Orbit_Radius));
    double Gas_Mass = Start_SC_Mass*(1-exp((-Delta_velocity)/Gas_Flow_Speed));
    double Engines_Thrust = (Gas_Flow_Speed*Gas_Mass)/(Fly_Time);
    double Engines_Power = (Engines_Thrust*Gas_Flow_Speed)/(2*EFFICIENCY);
    double Construct_Mass = Realitive_Construct_Mass * Start_SC_Mass;
    double Engines_Mass = Engine_Specific_Mass * Engines_Thrust;
    double Electro_Mass = Electro_Specific_Mass * Engines_Power;
    double SSS_Mass = SSS_Realitive_Mass * Gas_Mass;
    double Payload_Mass =Start_SC_Mass - Gas_Mass - Construct_Mass - SSS_Mass - Engines_Mass - Electro_Mass;

    ui->lineEdit_26->setText(QString::number(Electro_Mass));
    ui->lineEdit_24->setText(QString::number(Payload_Mass));
    ui->lineEdit_23->setText(QString::number(SSS_Mass));
    ui->lineEdit_22->setText(QString::number(Engines_Mass));
    ui->lineEdit_21->setText(QString::number(Construct_Mass));
    ui->lineEdit_20->setText(QString::number(Engines_Power/1000));
    ui->lineEdit_19->setText(QString::number(Engines_Thrust/9.81));
    ui->lineEdit_18->setText(QString::number(Gas_Mass));
    ui->lineEdit_16->setText(QString::number(Delta_velocity/1000));
    ui->lineEdit_15->setText(QString::number(Initial_Speed/1000));

}

void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox::about(this, "О программе", "Самарский Университетет\n Кафедра космического машиностроения\n Разработчик: Хайруллин И.И.\n https://github.com/razbiralochka");
}

