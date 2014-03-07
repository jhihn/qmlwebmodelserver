#ifndef MIMETYPEMAPPER_H
#define MIMETYPEMAPPER_H

#include <QMap>
#include <QByteArray>

class MimeTypeMapper : public QMap<const char*, const char*>
{
public:
	explicit MimeTypeMapper();

	const QByteArray operator[](const QByteArray key) const;
};

#endif // MIMETYPEMAPPER_H
