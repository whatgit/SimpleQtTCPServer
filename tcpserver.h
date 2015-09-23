#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include "TraCIConstants.h"
#include "traciwrapper.h"

class TCPServer : public QObject
{
  Q_OBJECT
  public:
    TCPServer(QObject * parent = 0);
    ~TCPServer();
    void sendPacket(const char* data);
  public slots:
    void acceptConnection();
    void startRead();
  private:
    QTcpServer server;
    QTcpSocket* client;
    int readCount;
    TraCIWrapper wrapper;
};

#endif // TCPSERVER_H
