#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "qcustomplot.h" // the header file of QCustomPlot. Don't forget to add it to your project, if you use an IDE, so it gets compiled.

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setupDemo(int demoIndex);
    void setupQuadraticDemo(QCustomPlot *customPlot);
    void setupItemDemo(QCustomPlot *customPlot);

    void setupPlayground(QCustomPlot *customPlot);
    float deg2rad(float);

private slots:
    void on_pushButton_clicked();

    void realtimeDataSlot();
    void bracketDataSlot();
    void screenShot();
    void allScreenShots();

    void on_horizontalSlider_sliderMoved(int position);

    //void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QCustomPlot *customPlot ;
    QString demoName;
    QTimer dataTimer;
    QCPItemTracer *itemDemoPhaseTracer;
    QCPItemTracer *itemDemoPhaseTracer1;
    QCPItemTracer *itemDemoPhaseTracer2;
    int currentDemoIndex;
    int i=0;
    QCPItemTracer *phaseTracer1;
    float totaldist;
    float totaltouch;
};

#endif // MAINWINDOW_H
