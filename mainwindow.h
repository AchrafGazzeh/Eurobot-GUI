#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRect>
#include <QDebug>
#include <qtserialport/QSerialPort>
#include <qtserialport/QSerialPortInfo>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void robotUpdate();
private:
    Ui::MainWindow *ui;
    QSerialPort *board;
    QString serialData;

    int globalAngle=0;
    QString boardport;
    bool port_available;
    QTimer *timer;


    void Rotate(int angle);
    void Position(double X, double Y);
};
#endif // MAINWINDOW_H
