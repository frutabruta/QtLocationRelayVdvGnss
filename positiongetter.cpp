#include "positiongetter.h"

PositionGetter::PositionGetter()
{
    emit signalStringError("Available position sources:"+ QGeoPositionInfoSource::availableSources().join(" "));


    QLocationPermission perm;
    perm.setAccuracy(QLocationPermission::Precise);
    perm.setAvailability(QLocationPermission::WhenInUse);

    switch (qApp->checkPermission(perm)) {
    case Qt::PermissionStatus::Granted:
        setupPositioning();
        break;
    case Qt::PermissionStatus::Undetermined:
        qApp->requestPermission(perm, this, [this](const QPermission &p) {
            if (p.status() == Qt::PermissionStatus::Granted)
                setupPositioning();
            else
                qDebug()<<"Status: location permission denied";
        });
        break;
    case Qt::PermissionStatus::Denied:
        qDebug()<<"Status: location permission denied by OS/policy";
        break;
    }

}




void PositionGetter::setupPositioning()
{
    emit signalStringError("Available position sources:"+ QGeoPositionInfoSource::availableSources().join(" "));

    m_source = QGeoPositionInfoSource::createDefaultSource(this);

    if (!m_source) {
        emit signalStringError("Status: no default position source (winrt plugin likely didn't load with MinGW — check Device Manager for a GPS/NMEA COM port instead)");
        return;
    }

    emit signalStringError(QString("Status: using \"%1\" source").arg(m_source->sourceName()));

    connect(m_source, &QGeoPositionInfoSource::positionUpdated,
            this, &PositionGetter::slotPositionUpdated);
    connect(m_source, &QGeoPositionInfoSource::errorOccurred,
            this, &PositionGetter::slotErrorOccurred);

    m_source->setUpdateInterval(1000);
    m_source->startUpdates();
}


void PositionGetter::slotErrorOccurred(QGeoPositionInfoSource::Error error)
{
    emit signalStringError(QString("Status: positioning error (%1)").arg(int(error)));

}




void PositionGetter::slotPositionUpdated(const QGeoPositionInfo &info)
{
    const QGeoCoordinate c = info.coordinate();
    emit signalStringData(QString("Lat/Lon: %1, %2  (updated %3)")
                              .arg(c.latitude())
                              .arg(c.longitude())
                              .arg(info.timestamp().toString(Qt::ISODate)));
    emit signalPositionUpdate(QPointF(c.longitude(),c.latitude()));

}
