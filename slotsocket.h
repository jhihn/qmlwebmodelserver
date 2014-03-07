#ifndef SLOTSOCKET_H
#define SLOTSOCKET_H

#include <QTcpSocket>

class SlotSocket : public QTcpSocket
{
	Q_OBJECT
public:
	explicit SlotSocket(QObject *parent = 0);

signals:
	void read(QByteArray data);

public slots:
	void write(QByteArray data);
	void close();
	void readReady();
};

#endif // SLOTSOCKET_H
