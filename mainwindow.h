#pragma once

#include <QMainWindow>
#include <QGeoPositionInfoSource>
#include <QLabel>
#include <QPointF>

#include "positiongetter.h"
#include "UdpSender/udpsender.h"

#include "MapaVykresleni/gnsswebsocketdragmap.h"


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


    GnssWebsocketDragMap mapPlot;

private slots:

    void slotDataUpdatedString(QString data);
    void slotError(QString error);
    void slotDataUpdate(QPointF coordinates);
    void slotSourceChanged(int index);
    void slotDataUpdateRealPosition(QPointF coordinates);
    void slotMapPositionReceived(double latitude, double longitude, bool centerMap);

    void on_pushButton_dragMap_clicked();

    void on_checkBox_dragMapRelay_stateChanged(int arg1);
    void on_checkBox_realPositionRelay_stateChanged(int arg1);

};