#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QRunnable>

#include <QTcpSocket>
#include "slotsocket.h"
#include "requestparser.h"

#include "qhttp.h"

class ServerThread : public
#ifdef USETHREADPOOL
	QRunnable
#else
	QThread
#endif
{
#ifndef USETHREADPOOL
	Q_OBJECT
#endif
	qintptr m_socketDescriptor;

	~ServerThread();

public:
	explicit ServerThread(qintptr socketDescriptor, QObject *parent = 0);
	void run();

};

#endif // SERVERTHREAD_H
