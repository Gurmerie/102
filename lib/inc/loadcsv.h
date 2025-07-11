#ifndef LOADCSV_H
#define LOADCSV_H

#include "exportLib_global.h"

#include <QObject>
#include <QString>
#include <QStringList>

class EXPORTLIB_EXPORT loadcsv : public QObject
{
    Q_OBJECT
public:
    explicit loadcsv(QObject *parent = nullptr);

    bool loadFile(const QString &filePath);

    QStringList headers() const;

    QVector<QStringList> rows() const;

private :
    QStringList m_headers;
    QVector<QStringList> m_rows;
};

#endif // LOADCSV_H
