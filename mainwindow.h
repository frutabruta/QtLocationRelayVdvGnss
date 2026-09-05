#pragma once

#include <QMainWindow>
#include <QGeoPositionInfoSource>
#include <QLabel>

#include "positiongetter.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:


    void slotDataUpdated(QString data);
    void slotError(QString error);
private:
     Ui::MainWindow *ui;
    void setupPositioning();

     PositionGetter positionGetter;



};