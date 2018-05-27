#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <utility>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete widget;
    delete ui;
}

void MainWindow::initializeWidgets()
{
    threadsLabel.setText(QString("Number of threads :"));
    iterationsLabel.setText(QString("Number of Iterations :"));
    markerSizeLabel.setText(QString("Circle size :"));
    widget = new QWidget;
    mainLayout.addWidget(&threadsLabel,0,0);
    mainLayout.addWidget(&QnumberOfThreads,0,1);
    mainLayout.addWidget(&iterationsLabel,1,0);
    mainLayout.addWidget(&QnumberOfIterations,1,1);
    mainLayout.addWidget(&markerSizeLabel,2,0);
    mainLayout.addWidget(&QmarkerSize,2,1);

    
    widget->setLayout(&mainLayout);
    this->setCentralWidget(widget);
}
