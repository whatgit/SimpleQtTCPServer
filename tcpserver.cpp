#include "tcpserver.h"
#include <iostream>
using namespace std;

TCPServer::TCPServer(QObject* parent): QObject(parent)
{
  connect(&server, SIGNAL(newConnection()),
    this, SLOT(acceptConnection()));

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
  if(client->state() == QTcpSocket::ConnectedState)
  {
  QByteArray buffer(client->bytesAvailable(),0);
  buffer = client->readAll();
  cout << "I received:" << buffer.constData() << endl;
  }
}
