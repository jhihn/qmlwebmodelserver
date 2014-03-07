#include <QFile>
#include <QEventLoop>
#include "serverthread.h"
#include "modelmapper.h"

ServerThread::ServerThread(qintptr socketDescriptor, QObject *parent) :
#ifdef USETHREADPOOL
	QRunnable()
#else
	QThread(parent)
#endif
  ,m_socketDescriptor(socketDescriptor)
{
	Q_UNUSED(parent)
}

ServerThread::~ServerThread()
{

}

void ServerThread::run()
{
	SlotSocket *socket = new SlotSocket();
	RequestParser *httpParser = new RequestParser();
	ModelMapper *modelMapper = new ModelMapper();
	if (!socket->setSocketDescriptor(m_socketDescriptor))
	{
		qDebug() << Q_FUNC_INFO <<"cannot set setSocketDescriptor";
		return;
	}
	QObject::connect(socket, SIGNAL(read(QByteArray)), httpParser, SLOT(read(QByteArray)));
	QObject::connect(httpParser, SIGNAL(write(QByteArray)), socket, SLOT(write(QByteArray)));
	QObject::connect(httpParser, SIGNAL(httpGet(QHttpRequestHeader)), modelMapper, SLOT(getModel(QHttpRequestHeader)));
	QObject::connect(httpParser, SIGNAL(httpPost(QHttpRequestHeader,QByteArray)), modelMapper, SLOT(postModel(QHttpRequestHeader,QByteArray)));
	QObject::connect(modelMapper, SIGNAL(httpResponse(QHttpResponseHeader,QByteArray)), httpParser, SLOT(httpResponse(QHttpResponseHeader,QByteArray)));
	QObject::connect(modelMapper, SIGNAL(httpResponseHead(QHttpResponseHeader)), httpParser, SLOT(httpResponseHead(QHttpResponseHeader)));
	QObject::connect(modelMapper, SIGNAL(httpResponseContent(QByteArray)), httpParser, SLOT(httpResponseContent(QByteArray)));
	QObject::connect(modelMapper, SIGNAL(httpResponseClose()), httpParser, SLOT(httpResponseClose()));

#ifdef USETHREADPOOL
	QEventLoop loop;
	loop.exec();
#else
	exec();
#endif

	if (socket) socket->deleteLater();
	if (httpParser) httpParser->deleteLater();
	if (modelMapper) modelMapper->deleteLater();
}

