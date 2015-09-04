#include "tcpserver.h"
#include <iostream>
using namespace std;

TCPServer::TCPServer(QObject* parent): QObject(parent)
{
  connect(&server, SIGNAL(newConnection()),
    this, SLOT(acceptConnection()));
  readCount = 0;
  server.listen(QHostAddress::Any, 8888);
}

TCPServer::~TCPServer()
{
  client->close();
  server.close();
}

void TCPServer::acceptConnection()
{
  client = server.nextPendingConnection();
  cout << "someone has connected" << endl;
  connect(client, SIGNAL(readyRead()),
    this, SLOT(startRead()));
}

void TCPServer::startRead()
{
  QByteArray data;
  if(client->state() == QTcpSocket::ConnectedState)
  {
  QByteArray buffer(client->bytesAvailable(),0);
  buffer = client->readAll();
  cout << "I received:" << buffer.constData() << endl;
  if(buffer.contains("Do you have something to send?"))
  {
      /*
      char msg[15];
          msg[0] = 0; //first four char-values give size of complete message
          msg[1] = 0;
          msg[2] = 0;
          msg[3] = 15;
          msg[4] = 11; // size of the message without first four char-values
          msg[5] = CMD_GET_SIM_VARIABLE; // Command Type
          msg[6] = 1; // next 8 char-values give target time value
          msg[7] = 0;
          msg[8] = 11;
          msg[9] = 12;
          msg[10] = 10;
          msg[11] = 1;
          msg[12] = 10;
          msg[13] = 99;
          msg[14] = POSITION_2D; // Type of data given back (car positions)
          */
      // Try to send change lane command
      char msg[29];
          msg[0] = 0; //first four char-values give size of complete message
          msg[1] = 0;
          msg[2] = 0;
          msg[3] = 29;
          msg[4] = 25; // size of the message without first four char-values
          msg[5] = CMD_SET_VEHICLE_VARIABLE; // Command Type
          msg[6] = CMD_CHANGELANE; // next 8 char-values give target time value
          msg[7] = 'p';
          msg[8] = 'l';
          msg[9] = 'a';
          msg[10] = 't';
          msg[11] = 'o';
          msg[12] = 'o';
          msg[13] = 'n';
          msg[14] = '1';
          msg[15] = '.';
          msg[16] = '4';
          msg[17] = TYPE_COMPOUND;
          //integer 2
          msg[18] = 0;
          msg[19] = 0;
          msg[20] = 0;
          msg[21] = 2;
          //
          msg[22] = TYPE_BYTE;
          msg[23] = 2;
          msg[24] = TYPE_INTEGER;
          //1000ms
          msg[25] = 0;
          msg[26] = 0;
          msg[27] = 0x03;
          msg[28] = 0xe8;
          //

      string message = quint32(15) + quint8(11) + "hellohello";
      quint32 datasize = 0x000f;


      cout<< "I'm writing : " << msg << endl;
      client->write(msg,29);
      //client->write(message.c_str(),15);
  }
    if(++readCount >= 100000){
            data.append("platoon1.7");
            data.append(0.0);
            data.prepend(data.size());
            client->write(data);
    }
  }
}
