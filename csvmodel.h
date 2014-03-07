#ifndef CSVMODEL_H
#define CSVMODEL_H

#include <QAbstractItemModel>

class CsvModel : public QAbstractItemModel
{
	Q_OBJECT
	QMap<QString,QMap<QString,QString> > m_data;
	QMap<int,QString> m_dataHeaders;
public:
	explicit CsvModel(QObject *parent = 0);


	Qt::ItemFlags flags(const QModelIndex & index) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	int rowCount();
	int columnCount();

signals:

public slots:
	bool setFile(QString filename, bool hasHeaders = true, QChar sep = ',');
};

#endif // CSVMODEL_H
