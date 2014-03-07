#include "slotsocket.h"
#include <QtDebug>

SlotSocket::SlotSocket(QObject *parent) :
	QTcpSocket(parent)
{
	connect(this, SIGNAL(readyRead()), this, SLOT(readReady()));
}

void SlotSocket::readReady()
{
	QByteArray ba = readAll();
	//qDebug() << Q_FUNC_INFO << ba;
	emit read(ba);
}

void SlotSocket::write(QByteArray data)
{
	QTcpSocket::write(data);
}

void SlotSocket::close()
{
	QTcpSocket::disconnectFromHost();
}
