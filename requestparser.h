#ifndef REQUESTPARSER_H
#define REQUESTPARSER_H

#include <QObject>
#include <QTcpSocket>
#include "qhttp.h"
class RequestParser : public QObject
{
	Q_OBJECT
	int m_socketDescriptor;
	bool m_headersDone;
	QByteArray m_buffer;
	QHttpRequestHeader m_header;
	double m_responseHttpVersion;

public:
	explicit RequestParser( QObject *parent = 0);

signals:
	void write(QByteArray);
	void close();
	void httpGet(QHttpRequestHeader);
	void httpPut(QHttpRequestHeader header, QByteArray content);
	void httpPost(QHttpRequestHeader header, QByteArray content);
	void httpDelete(QHttpRequestHeader);\

public slots:
	void read(QByteArray data);
	void serveIndex();
	void serveFile(QString filename);
	void httpResponse(QHttpResponseHeader header, QByteArray content);
	void httpResponseHead(QHttpResponseHeader header);
	void httpResponseContent(QByteArray content);
	void httpResponseClose();


};

#endif // REQUESTPARSER_H
