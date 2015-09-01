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
      quint32 datasize = 0x0002;
      quint32 data1 = 0x0fff;
      quint32 data2 = 0x0015;
      QString str;
      QByteArray block;
      QDataStream sendStream(&block, QIODevice::ReadWrite);
      sendStream << quint32(0) << data1 << data2;

      sendStream.device()->seek(0);
      sendStream << (quint32)(block.size()-sizeof(quint32));

      cout<< "I'm writing : " << msg << endl;
      client->write(msg,15);
      //client->write(block,block.size());
  }
    if(++readCount >= 100000){
            data.append("platoon1.7");
            data.append(0.0);
            data.prepend(data.size());
            client->write(data);
    }
  }
}
