#pragma once

#include <QMainWindow>
#include <QGeoPositionInfoSource>
#include <QLabel>
#include <QPointF>

#include "positiongetter.h"
#include "UdpSender/udpsender.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);


private:
    Ui::MainWindow *ui;

    UdpSender client;

    void setupPositioning();

    PositionGetter positionGetter;

    void sendCoordinates(QPointF coordinates, qint16 port);

private slots:

    void slotDataUpdatedString(QString data);
    void slotError(QString error);
    void slotDataUpdate(QPointF coordinates);
    void slotSourceChanged(int index);

};