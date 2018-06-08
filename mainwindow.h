#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSpinBox>
#include <QGridLayout>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QPixmap>
#include <opencv2/core.hpp>
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
    QString filePath;

    QWidget *widget;
    QGridLayout mainLayout;

    QPushButton FileSelect;
    QPushButton Start;
    QPushButton SaveImage;
    QSpinBox QnumberOfThreads;
    QSpinBox QnumberOfIterations;
    QSpinBox QmarkerSize;

    QLabel threadsLabel;
    QLabel iterationsLabel;
    QLabel markerSizeLabel;

    cv::Mat mat;
    QImage image;
    QPixmap pixMap;

    QGraphicsScene scene;
    QGraphicsView view;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initializeWidgets();
    void setFilePath(QString);

public slots:

    void setThreads(int);
    void setMarkerSize(int);
    void setIterations(int);
    void SelectFile();
    void remakeImage();
    void saveImage();


private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
