#ifndef POSITIONGETTER_H
#define POSITIONGETTER_H

#include <QObject>
#include <QLocationPermission>
#include <QCoreApplication>
#include <QGeoPositionInfoSource>

class PositionGetter : public QObject
{
    Q_OBJECT
public:
    PositionGetter();

    QGeoPositionInfoSource *m_source = nullptr;
    void setupPositioning();
public slots:

private slots:
    void slotPositionUpdated(const QGeoPositionInfo &info);
    void slotErrorOccurred(QGeoPositionInfoSource::Error error);

signals:
    void signalStringData(QString message);
    void signalStringError(QString message);
};

#endif // POSITIONGETTER_H
