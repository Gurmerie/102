#ifndef PDFEXPORTER_H
#define PDFEXPORTER_H

#include <QObject>
#include <QWidget>
#include <QString>

class pdfexporter : public QObject
{
    Q_OBJECT
public:
    explicit pdfexporter(QObject *parent = nullptr);
    bool exportWidgetToPDF(QWidget *widget, const QString &filePath, qreal marginMM = 15.0);
};

#endif // PDFEXPORTER_H
