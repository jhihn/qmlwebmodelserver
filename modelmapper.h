#ifndef MODELMAPPER_H
#define MODELMAPPER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QAbstractItemModel>
#include <QJsonObject>

#include "qhttp.h"

class ModelMapper : public QObject
{
	Q_OBJECT
	QFileSystemWatcher m_watcher;
	QMap <QString, QVariantMap> m_modelInfo;
	QMap <QString, QString> m_modelFileMap;

	void outputModel(QAbstractItemModel *model);
	void outputModel(QAbstractItemModel *model, QMap<QString, QString>modelBounds);

public:
	explicit ModelMapper(QObject *parent = 0);

signals:
	void httpResponse(QHttpResponseHeader header, QByteArray content);
	void httpResponseHead(QHttpResponseHeader header);
	void httpResponseContent(QByteArray content);
	void httpResponseClose();

public slots:
	void updateModelConfig(QString path);
	bool addModel(QString path);
	QString modelFile(QString id);
	QString modelId(QString path);
	void removeModel(QString id);

	void getModel(QHttpRequestHeader);
	void postModel(QHttpRequestHeader, QByteArray content);

};

#endif // MODELMAPPER_H
