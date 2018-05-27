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



private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
