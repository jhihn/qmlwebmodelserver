#include "modelmapper.h"
#include <QDir>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QtDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStringListModel>

#include "mimetypemapper.h"

ModelMapper::ModelMapper(QObject *parent) :
	QObject(parent)
{
	m_watcher.addPath(QDir::currentPath());
	qDebug() << Q_FUNC_INFO << "watching" << QDir::currentPath();
	QDir dir;
	QStringList entryFilter;
	entryFilter << "*.json";
	QStringList entries = dir.entryList(entryFilter, QDir::Files);
	foreach (const QString entry, entries){
		if (addModel(entry)) {
			m_watcher.addPath(entry);
			qDebug() << Q_FUNC_INFO << "watching" << entry;
		}
	}
	connect(&m_watcher, SIGNAL(directoryChanged(QString)), this, SLOT(updateModelConfig(QString)));
	connect(&m_watcher, SIGNAL(fileChanged(QString)), this, SLOT(updateModelConfig(QString)));

}


void ModelMapper::updateModelConfig(QString path)
{
	QFileInfo dirFI(path);
	if (dirFI.isDir())
	{
		QDir dir(path);
		QStringList entryFilter;
		entryFilter << "*.json";
		QStringList entries = dir.entryList(entryFilter, QDir::Files);
		foreach(const QString entry, entries)
		{
			if (!m_modelFileMap.values().contains(entry))
			{
				if (addModel(entry)) m_watcher.addPath(entry);
			}
		}
	} else {
		if (!QFile::exists(path) || modelId(path) != QString())
		{
			removeModel(modelId(path)); // file removed or changed.
		}
	}

}

QString ModelMapper::modelFile(QString id)
{
	if (m_modelFileMap.contains(id))
		return m_modelFileMap[id];
	else
		return QString();
}

void ModelMapper::removeModel(QString id)
{
	m_modelInfo.remove(id);
	m_modelFileMap.remove(id);
}

QString ModelMapper::modelId(QString path)
{
	foreach (const QString modelName, m_modelFileMap.keys())
	{
		if (m_modelFileMap[modelName] == path)
		{
			return modelName;
		}
	}
	return QString();
}

bool ModelMapper::addModel(QString path)
{
	QString id;

	QFile config(path);
	if (config.open(QIODevice::ReadOnly))
	{
		QByteArray text = config.readAll();
		config.close();
		QJsonParseError err;
		QJsonDocument doc = QJsonDocument::fromJson(text, &err);
		if (err.error == QJsonParseError::NoError)
		{
			QJsonObject obj =  doc.object();
			QVariantMap vm = obj.toVariantMap();
			//qDebug() << Q_FUNC_INFO << vm;
			id =  vm["id"].toString();
			m_modelInfo[id] = vm;
			m_modelFileMap[id] = path;
			return true;
		} else {
			qDebug() << Q_FUNC_INFO << err.errorString();
		}
	} else{
		qDebug() << Q_FUNC_INFO << "could not open" << path;
	}

	return false;
}

void ModelMapper::getModel(QHttpRequestHeader header)
{
	QStringList parts = header.path().split("/");
	QByteArray content;
	QHttpResponseHeader response;
	if (parts.length() == 2 && parts[1] == "")
	{
		content.append("<HTML><BODY><UL>");
		foreach (const QString id, m_modelInfo.keys())
		{
			content.append("<LI><A HREF=\"/" + id.toUtf8() + "\">" + id.toUtf8() +"</A></LI>");
		}
		content.append("</UL></BODY><HTML>");
		QHttpResponseHeader header;
		header.setStatusLine(200, "OK", 1, 0);
		header.setContentLength(content.length());
		emit httpResponse(header, content);
	} else if (parts.length() == 2 ) {
		QString name, queryString;
		QMap<QString,QString> queryParams;
		int questionMark = parts[1].indexOf("?");
		if (questionMark == -1)
			name = parts[1];
		else {
			name = parts[1].left(questionMark);
			queryString = parts[1].mid(questionMark+1);
			QStringList paramList = queryString.split("&");
			foreach (const QString param, paramList)
			{
				QStringList pair =  param.split("=");
				if (pair.length() == 2)
				{
					queryParams[pair[0]] = pair[1];
				}
			}
		}

		if (m_modelInfo.contains(name))
		{
			QVariantMap map = m_modelInfo[name];
			QSqlDatabase db;
			QString clas = map["class"].toString();
			QString connectionName;
			if (clas.startsWith("QSql"))
			{
				if (map.contains("database"))
				{
					QVariantMap database = m_modelInfo[name]["database"].toMap();
					QString driver, name, host, username, password, connectOptions;
					int port = -1;
					if (database.contains("driver"))
						driver = database["driver"].toString();
					if (database.contains("name"))
						name = database["name"].toString();
					if (database.contains("host"))
						host = database["host"].toString();
					if (database.contains("username"))
						username = database["username"].toString();
					if (database.contains("password"))
						password = database["password"].toString();
					if (database.contains("connectionoptions"))
						connectOptions = database["connectionoptions"].toString();
					if (database.contains("port"))
						port = database["port"].toInt();
					connectionName = QString("%1:%2:%3:%4:%5:%6").arg(driver).arg(host).arg(port).arg(name).arg(username).arg(connectOptions);

					if (!QSqlDatabase::connectionNames().contains(connectionName))
						db = QSqlDatabase::addDatabase(driver, connectionName);
					else
						db = QSqlDatabase::database(connectionName);

					if (!name.isEmpty()) db.setDatabaseName(name);
					if (!host.isEmpty()) db.setHostName(host);
					if (!username.isEmpty()) db.setUserName(username);
					if (!password.isEmpty()) db.setPassword(password);
					if (!connectOptions.isEmpty()) db.setConnectOptions(connectOptions);
					if (port != -1) db.setPort(port);

					if (!db.open())
					{
						qDebug() << Q_FUNC_INFO << "failed to open database" << connectionName << ":" << db.lastError().databaseText();
					} else {
						qDebug() << Q_FUNC_INFO << "opened database" << name;
					}

				}
			}
			if (clas.length())
			{
				QVariantMap modelInfo = m_modelInfo[name][clas].toMap();
				if (clas == "QSqlTableModel" && db.isOpen())
				{
					QSqlTableModel model(this, db);
					if (modelInfo.contains("table")) model.setTable(modelInfo["table"].toString());
					if (modelInfo.contains("filter")) model.setFilter(modelInfo["filter"].toString());
					if (modelInfo.contains("sort"))
					{
						int column = 0, order = 0;
						if (modelInfo["sort"].toMap().contains("column"))
							column =  modelInfo["sort"].toMap()["column"].toInt();
						if (modelInfo["sort"].toMap().contains("order"))
							order =  modelInfo["sort"].toMap()["order"].toInt();
						model.setSort(column,(Qt::SortOrder)  order);
					}
					if (!model.select())
						qDebug() << Q_FUNC_INFO << "table select failed" << model.tableName();
					qDebug() << Q_FUNC_INFO << model.rowCount() << model.columnCount();
					outputModel(&model);

				} else if (clas == "QSqlQueryModel" && db.isOpen()) {
					QSqlQueryModel model;
					if (modelInfo.contains("query"))
					{
						QSqlQuery query(db);
						if (!query.prepare(modelInfo["query"].toString()))
							qDebug() << Q_FUNC_INFO << "failed to prepare query";

						QMap<QString,QString> modelBounds;


						foreach(const QString key, queryParams)
						{
							if (   key != "modelRowStart"
								&& key != "modelRowEnd"
								&& key != "modelColStart"
								&& key != "modelColEnd"
							)
								query.bindValue(key, queryParams[key]);
							else
								modelBounds[key] = queryParams[key];

						}
						query.exec();
						//qDebug() << Q_FUNC_INFO << query.boundValues();
						model.setQuery(query);
						qDebug() << model.query().executedQuery();
						if (model.lastError().isValid())
							qDebug() << Q_FUNC_INFO << model.lastError();

						outputModel(&model, modelBounds);
					}

				} else if (clas == "QStringListModel") {
					QStringListModel model;
					QStringList list;
					if (modelInfo.contains("source"))
					{
						QString listFile = modelInfo["source"].toString();
						QFile f(listFile);
						QTextStream stream(&f);
						QString string;
						if (f.open(QIODevice::ReadOnly))
						{
							while (!stream.atEnd())
							{
								stream  >> string;
								list << string;
							}
						}
					} else if (modelInfo.contains("list")) {
						list = modelInfo["list"].toStringList();
					}
					model.setStringList(list);
					outputModel(&model);
				}

			} else{
				qDebug() << Q_FUNC_INFO << "failed to create model" << name << clas;
				QByteArray content = "<HTML><BODY>Failed to create model.</BODY></HTML>";
				response.setStatusLine(200, "OK", 1,0);
				response.setContentLength(content.length());
				emit httpResponse(response, content);
			}
		} else{
			qDebug() << Q_FUNC_INFO << "model not found:" << name;
			QHttpResponseHeader response;
			if (QFile::exists("files/"+header.path()))
			{
				QFile f("files/"+header.path());
				int dot = header.path().lastIndexOf(".");
				QString ext = "";
				if (dot != -1)
					ext = header.path().mid(dot);
				if (f.open(QIODevice::ReadOnly))
				{
					response.setStatusLine(200, "OK", 1,1);
					MimeTypeMapper mimeMap;
					response.setContentType(mimeMap[ext.toUtf8()]);
					response.setContentLength(f.size());
					emit httpResponseHead(response);
					while (!f.atEnd())
					{
						emit httpResponseContent(f.read(1024*512));
					}
					emit httpResponseClose();
				}
			} else {
				QByteArray content = "<HTML><BODY>Model not found and file not found</BODY></HTML>";
				response.setStatusLine(404, "OK", 1,0);
				response.setContentLength(content.length());
				emit httpResponse(response, content);
			}
		}
	} else {
		QHttpResponseHeader response;
		QByteArray content = "<HTML><BODY>Invalid model request (too much path)</BODY></HTML>";
		response.setStatusLine(200, "OK", 1,0);
		response.setContentLength(content.length());
		emit httpResponse(response, content);
	}


}


void ModelMapper::postModel(QHttpRequestHeader header, QByteArray content)
{
	Q_UNUSED(header)
	Q_UNUSED(content)
}

void ModelMapper::outputModel(QAbstractItemModel *model)
{
	QMap<QString,QString> modelBounds;
	outputModel(model, modelBounds);
}

void ModelMapper::outputModel(QAbstractItemModel *model, QMap<QString, QString>modelBounds)
{
	qDebug() << Q_FUNC_INFO << "model bounds" << model->rowCount() << model->columnCount();
	int modelRowStart = modelBounds.contains("modelRowStart") ? modelBounds["modelRowStart"].toInt() : 0;
	int modelRowEnd  = modelBounds.contains("modelRowEnd") ? modelBounds["modelRowEnd"].toInt() : model->rowCount();
	int modelColStart = modelBounds.contains("modelColStart") ? modelBounds["modelColStart"].toInt() : 0;
	int modelColEnd = modelBounds.contains("modelColEnd") ? modelBounds["modelColEnd"].toInt() : model->columnCount();

	QHttpResponseHeader header;
	header.setStatusLine(200, "OK", 1,1);
	header.setContentType("application/json");
	header.setValue("Transfer-Encoding", "chunked");
	emit httpResponseHead(header);
	emit httpResponseContent("A\r\n{\"model\":{\r\n");
	for (int row = modelRowStart; row < modelRowEnd; row++)
	{\
		QStringList valueList;
		for (int col = modelColStart; col < modelColEnd; col++)
		{
			valueList << model->data(model->index(row, col)).toString();
		}
		QString rowText = QString("\"(%1,%2)\": [\"%3\"]%4").arg(row).arg(modelColStart)
			.arg(valueList.join("\",\""))
			.arg(row == modelRowEnd-1 ? "": ",");
		emit httpResponseContent(QString("%1\r\n").arg(rowText.length(), 0, 16).toUtf8());
		emit httpResponseContent(rowText.toUtf8());
		emit httpResponseContent("\r\n");
	}
	emit httpResponseContent("2\r\n}}\r\n");
	emit httpResponseContent("0\r\n\r\n");
	emit httpResponseClose();
}
