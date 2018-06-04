#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <utility>
#include <iostream>
#include <QSpinBox>
#include <QFileDialog>
#include <QMessageBox>
#include <img_generator.hpp>
#include <vector>
#include <future>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    scene(this),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete widget;
    delete ui;
}

void MainWindow::setThreads(int threads)
{
    this->threads = threads;
}

void MainWindow::setIterations(int iterations)
{
    this->iterations = iterations;
}

void MainWindow::setMarkerSize(int markerSize)
{
    this->markerSize = markerSize;
}

void MainWindow::setFilePath(QString path)
{
    this->filePath = path;
}

void MainWindow::SelectFile()
{
    this->filePath = QFileDialog::getOpenFileName(nullptr, "Open", "");
    image.load(filePath);
    pixMap = QPixmap::fromImage(image);
    pixMap = pixMap.scaledToHeight(view.height(), Qt::SmoothTransformation);
    scene.addPixmap(pixMap);
    view.fitInView(scene.sceneRect(),Qt::KeepAspectRatio);
    view.setScene(&scene);
}


void MainWindow::remakeImage()
{
        Mat src;
        src = imread(filePath.toStdString(),CV_LOAD_IMAGE_COLOR);
        Mat output(src.rows, src.cols, CV_8UC3, Scalar(255,255,255));

        RNG rng(0xFFFFFFF);
        std::vector<std::future<void>> futures;
        for(int i = 0 ; i < threads; i++)
        {
            futures.emplace_back( std::async(std::launch::async, generate, src, output, iterations/threads, markerSize, i*src.cols/threads, (i+1)*src.cols/threads, std::reference_wrapper<RNG>(rng)));
        }

        for( auto &f : futures )
            f.get();

        image = QImage((uchar*)output.data, output.cols, output.rows, output.step, QImage::Format_RGB888);

        pixMap = QPixmap::fromImage(image);
        pixMap = pixMap.scaledToHeight(view.height(), Qt::SmoothTransformation);
        scene.addPixmap(pixMap);
        view.fitInView(scene.sceneRect(),Qt::KeepAspectRatio);
        view.setScene(&scene);


}

void MainWindow::initializeWidgets()
{
    threads = 0;
    iterations = 0;
    markerSize = 0;

    QnumberOfIterations.setKeyboardTracking(true);
    QnumberOfThreads.setKeyboardTracking(true);
    QmarkerSize.setKeyboardTracking(true);

    QnumberOfIterations.setMaximum(200000000);
    QnumberOfThreads.setMaximum(256);
    QmarkerSize.setMaximum(200);

    QObject::connect(&QnumberOfThreads, SIGNAL(valueChanged(int)), this, SLOT(setThreads(int)));
    QObject::connect(&QnumberOfIterations, SIGNAL(valueChanged(int)), this, SLOT(setIterations(int)));
    QObject::connect(&QmarkerSize, SIGNAL(valueChanged(int)), this, SLOT(setMarkerSize(int)));
    QObject::connect(&FileSelect, SIGNAL(clicked(bool)), this, SLOT(SelectFile()));
    QObject::connect(&Start, SIGNAL(clicked(bool)), this, SLOT(remakeImage()));
    threadsLabel.setText(QString("Number of threads :"));
    iterationsLabel.setText(QString("Number of Iterations :"));
    markerSizeLabel.setText(QString("Circle size :"));

    Start.setText(QString("Start!"));
    FileSelect.setText(QString("Select file"));

    widget = new QWidget;
    mainLayout.addWidget(&threadsLabel,0,0);
    mainLayout.addWidget(&QnumberOfThreads,0,1);
    mainLayout.addWidget(&iterationsLabel,1,0);
    mainLayout.addWidget(&QnumberOfIterations,1,1);
    mainLayout.addWidget(&markerSizeLabel,2,0);
    mainLayout.addWidget(&QmarkerSize,2,1);
    mainLayout.addWidget(&FileSelect, 3, 0);
    mainLayout.addWidget(&Start, 3, 1);
    mainLayout.addWidget(&view, 0, 2, 4, 1);
    
    widget->setLayout(&mainLayout);
    this->setCentralWidget(widget);
}
