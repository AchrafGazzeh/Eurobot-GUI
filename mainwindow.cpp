#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    board = new QSerialPort;
    boardport="";
    port_available=false;

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(robotUpdate()));
    timer->start(1);


    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
                if(serialPortInfo.vendorIdentifier() == 9025){
                    if(serialPortInfo.productIdentifier() == 66){
                        qInfo() << " Port found";
                        boardport = serialPortInfo.portName();
                        port_available = true;
                    }
                }
            }
        }

    if(port_available){
           // open and configure the serialport
           board->setPortName(boardport);
           board->open(QSerialPort::ReadOnly);
           board->setBaudRate(QSerialPort::Baud115200);
           board->setDataBits(QSerialPort::Data8);
           board->setParity(QSerialPort::NoParity);
           board->setStopBits(QSerialPort::OneStop);
           board->setFlowControl(QSerialPort::NoFlowControl);
           qInfo() << " Port Opened!";
       }else{
           // give error message if not available
           QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
       }


    Position(500,500);
    Rotate(0);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::robotUpdate()
{


    if(board->canReadLine() ) {
        serialData = board->readLine();
        serialData = serialData.trimmed();

           if(serialData.length()>0 ){
            // Check if data is rotation
            if(serialData[0]=='r'){


                if(serialData.length()==3)
                {Rotate( serialData.mid(1,serialData.length()-4).toInt() );}
                else
                {
                    Rotate( serialData.mid(1,serialData.length()-1).toInt() );}
            }
        // Check if data is forward
        else if(serialData[0]=='f'){

                    QStringList position = serialData.mid(1).split(",");
                    Position( position[1].toDouble() , position[0].toDouble() );
                }}

    }



}

void MainWindow::Rotate(int angle)
{
    qInfo() << "Rotating: " << angle << "";

    int angleToTurn=angle-globalAngle;

    QPixmap pixmap(ui->robotFrame->pixmap() );
    QTransform tr;
    tr.rotate(angleToTurn);
    pixmap = pixmap.transformed(tr);
    ui->robotFrame->setPixmap(pixmap);
    ui->thetaValue->setText(QString::number(angle));
    globalAngle=angle;


}

void MainWindow::Position(double X,double Y)
{


    double outputX=0.0;
    double outputY=0.0;
    // We will map the (X,Y) coordinates from the real map range to our label map size
    //output = output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start)
    outputX = -40.0 + ( 1000.0 / 3000.0) * (X) ;
    outputY = 440.0 + ((-20.0 - (440.0)) / (2000.0 )) * (Y ) ;

    ui->xValue->setText(QString::number(X));
    ui->yValue->setText(QString::number(Y));
    ui->robotFrame->setGeometry(QRect(round(outputX),round(outputY),80,40));
}

