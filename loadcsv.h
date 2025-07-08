#ifndef LOADCSV_H
#define LOADCSV_H

#include <QObject>
#include <QString>
#include <QStringList>

class loadcsv : public QObject
{
    Q_OBJECT
public:
    loadcsv(QObject *parent = nullptr);
    QStringList loadHeader(const QString &filePath, bool *ok = nullptr) const;
};

#endif // LOADCSV_H
