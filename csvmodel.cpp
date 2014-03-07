#include <QFile>
#include "csvmodel.h"

CsvModel::CsvModel(QObject *parent) :
	QAbstractItemModel(parent)
{


}

Qt::ItemFlags CsvModel::flags(const QModelIndex & index) const
{
	return Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable;
}
QVariant CsvModel::data(const QModelIndex &index, int role) const
{
	return m_data[index.row()][index.column()];
}
QVariant CsvModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	return m_dataHeaders[section];
}
int CsvModel::rowCount()
{
	return m_data.keys().count();
}

int CsvModel::columnCount()
{
	return m_dataHeaders.count();
}

bool CsvModel::setFile(QString filename, bool hasHeaders, QChar sep)
{
	QFile f(filename);
	if (f.open(QIODevice::ReadOnly))
	{
		if (hasHeaders)
		{
			QByteArray ba = f.readLine();
			ba = ba.trimmed();
			for (int i=0; i<ba.length(); i++)
			{
				m_headers = parseLine(ba);
			}
		}
		return true;
	}
	return false;
}

QList<QStringList> parseData(QByteArray line, char sep)
{
	QList<QStringList> out2;
	QStringList out;
	QByteArray myLine = line.trimmed();
	QString val;
	char q = 0;
	while (i < myLine.length())
	{
		if (myLine[i] == '"')
		{
			if (q)
			{
				if (i+1 < len(myLine) && myLine[i+1] == '"')
				{
					val += '"';
					i+=1;
				} else {
					q=0;
				}
			} else {
				q='"';
			}

		} else {
			if (myLine[i] == sep)
			{
				out.append(val);
				val ='';
				while (myLine[i+1] == ' ')
					i += 1;
			} else {
				if (q==0)
				{
					if (myLine[i] == '\n')
					{
						out.append(val);
						out2.append(out);
						out.clear();
						val='';
					} else {
						val += myLine[i];
					}
				} else {
					val += myLine[i];
				}
			}
		}
		i+=1;
	}
	if (val.length())
		out.append(val);
	if (out.size())
		out2.append(out);

	return out2;
}
