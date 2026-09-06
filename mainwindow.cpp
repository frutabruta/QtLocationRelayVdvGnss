#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>
#include <QtSerialPort/QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Log what plugins are actually available on this build/device


    connect(&positionGetter,&PositionGetter::signalStringData,this,&MainWindow::slotDataUpdatedString );
    connect(&positionGetter,&PositionGetter::signalStringError,this,&MainWindow::slotError);

    connect(&positionGetter,&PositionGetter::signalPositionUpdate,this,&MainWindow::slotDataUpdate);

    connect(ui->comboBox_port,
            &QComboBox::currentIndexChanged,
            this,
            &MainWindow::slotSourceChanged);

  //  positionGetter.setupPositioning();



    ui->comboBox_port->addItem("Default Qt source", "__DEFAULT__");

    const QList<QSerialPortInfo> ports =
        QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &port : ports)
    {
        ui->comboBox_port->addItem(
            QString("NMEA: %1 (%2)").arg(port.portName(),port.description()),port.portName());
    }





}

void MainWindow::setupPositioning()
{

}



void MainWindow::slotDataUpdatedString(QString data)
{
    ui->label_data->setText(data);
}


void MainWindow::slotDataUpdate(QPointF coordinates)
{
    sendCoordinates(coordinates,ui->lineEdit_portNumber->text().toUInt());
}


void MainWindow::slotSourceChanged(int index)
{
    QString sourceId = ui->comboBox_port->itemData(index).toString();

    positionGetter.setSource(sourceId);
}



void MainWindow::slotError(QString error)
{
    qDebug()<<"error "<<error;
    ui->plainTextEdit_error->setPlainText(ui->plainTextEdit_error->toPlainText()+"\n"+error);

}


void MainWindow::sendCoordinates(QPointF coordinates, qint16 port)
{
    QString data=QString("<GNSSLocationService.Data>"
                           "    <latitude>"
                           "        <Degree>"
                           "                           <Value>%1</Value>"
                           "        </Degree>"
                           "        <Direction>"
                           "            <Value>N</Value>"
                           "        </Direction>"
                           "    </latitude>"
                           "    <longitude>"
                           "        <Degree>"
                           "            <Value>%2</Value>"
                           "        </Degree>"
                           "        <Direction>"
                           "            <Value>E</Value>"
                           "        </Direction>"
                           "    </longitude>"
                           "    <GNSSType>MixedGNSSTypes</GNSSType>"
                           "</GNSSLocationService.Data>").arg(QString::number(coordinates.y()),QString::number(coordinates.x()));

    client.odesliRaw("127.0.0.1", data,port);
}


