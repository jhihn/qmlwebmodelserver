#include <QCoreApplication>
#include "threadedtcpserver.h"
#include <QThread>
#include <QThreadPool>
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	ThreadedTcpServer server;
#ifdef USETHREADPOOL
	int idealThreadCount = QThread::idealThreadCount();
	QThreadPool::globalInstance()->setMaxThreadCount(idealThreadCount+5);
	qDebug() << Q_FUNC_INFO << "idealThreadcount modified. from/to:" << idealThreadCount << QThreadPool::globalInstance()->maxThreadCount();
#endif
	return a.exec();
}
