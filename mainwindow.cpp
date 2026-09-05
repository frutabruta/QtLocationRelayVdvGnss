#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Log what plugins are actually available on this build/device


    connect(&positionGetter,&PositionGetter::signalStringData,this,&MainWindow::slotDataUpdated );
    connect(&positionGetter,&PositionGetter::signalStringError,this,&MainWindow::slotError);

    positionGetter.setupPositioning();


}

void MainWindow::setupPositioning()
{

}



void MainWindow::slotDataUpdated(QString data)
{
    ui->label_data->setText(data);
}

void MainWindow::slotError(QString error)
{
    ui->label_error->setText(error);
}