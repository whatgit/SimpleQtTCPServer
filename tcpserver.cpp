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
  if(strcmp("Do you have something to send?",buffer.constData()) == 0)
  {
      data.append(QByteArray::number(0xAB));
      data.prepend(QByteArray::number(0x01));
      cout << "writing;" << data.constData() << endl;
      client->write(data);
  }
    if(++readCount >= 100000){
            data.append("platoon1.7");
            data.append(0.0);
            data.prepend(data.size());
            client->write(data);
    }
  }
}
