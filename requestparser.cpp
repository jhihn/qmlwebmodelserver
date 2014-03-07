#include "requestparser.h"
#include <QFile>

RequestParser::RequestParser(QObject *parent) :
	QObject(parent)
{
}

void RequestParser::read(QByteArray data)
{
	m_buffer = m_buffer + data;
	int eoh = m_buffer.indexOf("\r\n\r\n");
	if (eoh > 0 && m_headersDone == false)
	{
		if (m_headersDone == false)
		{
			QHttpRequestHeader header(QString(m_buffer.left(eoh+4)));
			m_header = header;
			m_headersDone = true;

		}
	}

	if (m_headersDone)
	{
		QString method = m_header.method();
		QString path = m_header.path();
		if (method == "GET")
		{
			qDebug() << "Http: GET" << path;
			emit httpGet(m_header);
			m_buffer = "";
			m_headersDone = false;
		} else if (method == "POST" || method == "PUT") {

			if ((uint) m_buffer.length() == m_header.contentLength() - (uint)(eoh+4))
			{
				qDebug() << "Http: POST" << path;
				if (method == "POST")
					emit httpPost(m_header, m_buffer.mid(eoh+4, m_header.contentLength()));
				else
					emit httpPut(m_header, m_buffer.mid(eoh+4, m_header.contentLength()));
				m_buffer = "";
				m_headersDone = false;

			} // if we have all post data
		} else if (method == "DELETE") {
			emit httpDelete(m_header);
			m_buffer = "";
			m_headersDone = false;
		}

	} // headers done == true

}

void RequestParser::serveIndex()
{
	QHttpResponseHeader header;
	header.setStatusLine(200, "OK", 1,1);
	QByteArray buffer = "<HTML><BODY>Index</BODY></HTML>";

	header.setContentLength(buffer.length());
	header.setContentType("text/html");
	emit write(header.toString().toUtf8());
	emit write(buffer);
	exit(0);
}

void RequestParser::serveFile(QString filename)
{
	QFile file(filename);
	QHttpResponseHeader header;
	if (file.open(QIODevice::ReadOnly))
	{
		header.setStatusLine(200, "OK", 1,0);
		QByteArray data = file.readAll();
		header.setContentLength(data.length());
		emit write(header.toString().toUtf8());
		emit write("\r\n");
		emit write(data);
		emit close();

	} else {
		header.setStatusLine(404, "NOT FOUND", 1,0);
		emit write(header.toString().toUtf8());
		emit close();
	}
}


void RequestParser::httpResponse(QHttpResponseHeader header, QByteArray content)
{
	m_responseHttpVersion = header.majorVersion() + header.minorVersion() / 10.0;
	emit write(header.toString().toUtf8());
	emit write(content);
}

void RequestParser::httpResponseHead(QHttpResponseHeader header)
{
	m_responseHttpVersion = header.majorVersion() + header.minorVersion() / 10.0;
	emit write(header.toString().toUtf8());
}

void RequestParser::httpResponseContent(QByteArray content)
{
	 emit write(content);
}

void RequestParser::httpResponseClose()
{
	if (m_responseHttpVersion < 1.1 )
		emit close();
}


