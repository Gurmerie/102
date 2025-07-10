#ifndef CSVCHART_H
#define CSVCHART_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QLineSeries>
#include <QtCharts>
#include <QChart>

class csvchart : public QObject
{
    Q_OBJECT
public:
    explicit csvchart(QObject *parent = nullptr);
    QChart *plotChart(const QStringList &header, const QVector<QStringList> &rows, int colX, int colY) const;
};

#endif // CSVCHART_H
