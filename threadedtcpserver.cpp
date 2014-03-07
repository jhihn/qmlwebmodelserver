#include "threadedtcpserver.h"
#include <QTcpSocket>
#include <QDir>
#include <QCryptographicHash>
#include <QDateTime>
#include "qhttp.h"
#include "serverthread.h"
#include <QThreadPool>

ThreadedTcpServer::ThreadedTcpServer(QObject *parent) :
    QTcpServer(parent)
{
	if (listen(QHostAddress::AnyIPv4, 5555))
		qDebug() << Q_FUNC_INFO << "listening on port" << serverPort();
	else
		qDebug() << Q_FUNC_INFO << "listening failed";
}

void ThreadedTcpServer::incomingConnection(qintptr socketDescriptor)
{
	qDebug() << Q_FUNC_INFO << "Client connected";
	ServerThread *thread = new ServerThread(socketDescriptor);

	QThreadPool::globalInstance()->start(thread);

	//connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	//thread->start();

}
