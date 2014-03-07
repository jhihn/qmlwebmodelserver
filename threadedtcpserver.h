#ifndef THREADEDTCPSERVER_H
#define THREADEDTCPSERVER_H

#include <QTcpServer>

class ThreadedTcpServer : public QTcpServer
{
	Q_OBJECT
    QByteArray m_buffer;
	bool m_headersDone;

public:
	explicit ThreadedTcpServer(QObject *parent = 0);
	void incomingConnection(qintptr socketDescriptor);

public slots:
};

#endif // THREADEDTCPSERVER_H
