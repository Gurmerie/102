#include "pdfexporter.h"
#include <QObject>
#include <QPainter>
#include <QFileInfo>
#include <QPrinter>
#include <QMessageBox>
#include <QSizeF>
#include <QtGlobal>
#include <iostream>
#include <QApplication>

pdfexporter::pdfexporter(QObject *parent) : QObject(parent) {}

bool pdfexporter::exportWidgetToPDF(QWidget *widget, const QString &filePath, qreal marginMM) {
    if (!widget || filePath.isEmpty()) {
        return false;
    }

    std::cout << "Initializing printer" << std::endl;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageMargins(QMarginsF(marginMM, marginMM, marginMM, marginMM), QPageLayout::Millimeter);

    if (!printer.isValid()) {
        return false;
    }
    std::cout << "Initializing painter" << std::endl;

    QPainter painter(&printer);
    if (!painter.isActive()) {
        return false;
    }
    // QSizeF pageSize = printer.pageRect(QPrinter::Millimeter).size();
    // QSizeF widgetSize = widget->size();
    // qreal xScale = pageSize.width() / qreal(widgetSize.width());
    // qreal yScale = pageSize.height() / qreal(widgetSize.height());
    // qreal scale = qMin(xScale, yScale);
    painter.scale(10, 10);

    std::cout << "Rendering widget" << std::endl;

    qApp->processEvents();
    widget->render(&painter);
    painter.end();

    QFileInfo fi(filePath);
    return fi.exists() && fi.size() > 0;
}












