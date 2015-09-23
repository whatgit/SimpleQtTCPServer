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
  //cout << "someone has connected" << endl;
  connect(client, SIGNAL(readyRead()),
    this, SLOT(startRead()));
}

void TCPServer::startRead()
{
  if(client->state() == QTcpSocket::ConnectedState) //If it's connected
  {
  QByteArray buffer(client->bytesAvailable(),0);
  buffer = client->readAll();
  QDataStream in(buffer);
  wrapper.processTraCIMessage(&in);
  cout << "I received:" << buffer.constData() << endl;

  if(buffer.contains("Do you have something to send?"))
  {
      QByteArray testOut;
      QDataStream out(&testOut,QIODevice::ReadWrite);

      qint32 size = 0;
      quint8 cmd_size = 0;
      out << size << cmd_size;

      wrapper.createTraCISetSpeed(&out, "dummy.0", 0.00);

      out.device()->seek(4);
      cmd_size = testOut.size()-4;
      out << cmd_size;
      out.device()->seek(0);
      size = testOut.size();
      out << size;
      out.device()->seek(0);

      cout<< "I'm writing : " << testOut.constData() << endl;
      client->write(testOut.constData(),testOut.size());
    }
  }
}

