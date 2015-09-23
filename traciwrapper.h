#ifndef TRACIWRAPPER_H
#define TRACIWRAPPER_H
#include <QtNetwork>
#include <QObject>
#include <iostream>
#include "TraCIConstants.h"
#include "VTIConstants.h"

class TraCIWrapper
{
public:
    TraCIWrapper();
    void createTraCISetSpeed(QDataStream *data, QString vehId, double newSpeed);
    void processTraCIMessage(QDataStream *in);
};

#endif // TRACIWRAPPER_H
