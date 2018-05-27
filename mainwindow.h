#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSpinBox>
#include <QGridLayout>
#include <QMainWindow>
#include <QLabel>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:


    unsigned int threads;
    unsigned int markerSize;
    unsigned int iterations;
    
    QWidget *widget;
    QGridLayout mainLayout;
    QSpinBox QnumberOfThreads;
    QSpinBox QnumberOfIterations;
    QSpinBox QmarkerSize;

    QLabel threadsLabel;
    QLabel iterationsLabel;
    QLabel markerSizeLabel;


    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initializeWidgets();

public slots:

    void setThreads(int);
    void setMarkerSize(int);
    void setIterations(int);




private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
