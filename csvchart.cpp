#include "csvchart.h"
#include "loadcsv.h"

#include <QChart>
#include <QString>
#include <QVector>
#include <QLineSeries>
#include <iostream>

csvchart::csvchart(QObject *parent) : QObject(parent) {}

QChart* csvchart::plotChart(const QStringList &header, const QVector<QStringList> &rows, int colX, int colY) const {

    QLineSeries *series = new QLineSeries;
    for (const QStringList &row : rows) {
        if (colX >= row.size() || colY >= row.size()) {
            continue;
        }
        bool okX, okY;
        double x = row[colX].toDouble(&okX);
        double y = row[colY].toDouble(&okY);

        if (okX && okY) {
            series->append(x, y);
        }
    }
    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle(QString("%1 vs %2").arg(header.value(colX)).arg(header.value(colY)));

    return chart;
}
