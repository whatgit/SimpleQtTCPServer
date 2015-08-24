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

  connect(client, SIGNAL(readyRead()),
    this, SLOT(startRead()));
}

void TCPServer::startRead()
{
  char buffer[1024] = {0};
  client->read(buffer, client->bytesAvailable());
  cout << buffer << endl;
  //client->close();
}
