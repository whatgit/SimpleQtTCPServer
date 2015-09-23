#include "traciwrapper.h"
using namespace std;

TraCIWrapper::TraCIWrapper()
{
}

void TraCIWrapper::createTraCISetSpeed(QDataStream *data, QString vehId, double newSpeed)
{
    quint8 command1 = CMD_SET_VEHICLE_VARIABLE;
    quint8 command2 = VAR_SPEED;
    quint8 var_type_double = TYPE_DOUBLE;
    quint8 temp;

    *data << command1 << command2 << quint8(vehId.size());
    for(int i = 0; i < vehId.size(); i++)
    {
        temp = vehId.at(i).toLatin1();
        *data << temp;
    }
    *data << var_type_double << newSpeed;
}

void TraCIWrapper::processTraCIMessage(QDataStream *in)
{
    quint8 temp;
    quint8 length;
    quint8 command;
    *in >> length;
    *in >> command;
    if(command == VTI_VEHICLE_INSERT)
    {
        quint32 nameLength;
        QString name;
        *in >> nameLength;
        for(quint8 i = 0; i < nameLength; i++)
        {
            *in >> temp;
            name += temp;
        }
        //cout << "insert : " << QString::number(nameLength).toStdString() << endl;
        cout << "insert : " << name.toStdString() << endl;
    }

}
