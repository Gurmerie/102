#ifndef CSVCHART_H
#define CSVCHART_H

#include "exportLib_global.h"

#include <QObject>
#include <QString>
#include <QStringList>
#include <QLineSeries>
#include <QtCharts>
#include <QChart>

class EXPORTLIB_EXPORT csvchart : public QObject
{
    Q_OBJECT
public:
    explicit csvchart(QObject *parent = nullptr);
    QChart *plotChart(const QStringList &header, const QVector<QStringList> &rows, int colX, int colY) const; //plots a chart with given x and y
    QChart *addCurve(QChart *chart, const QStringList &headers, const QVector<QStringList> &rows, int colX, int colY) const;
};

#endif // CSVCHART_H
