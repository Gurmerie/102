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
    std::cout << "Initializing printer format" << std::endl;
    printer.setOutputFormat(QPrinter::PdfFormat);
    std::cout << "Initializing printer output" << std::endl;
    printer.setOutputFileName(filePath);
    std::cout << "Initializing printer margins" << std::endl;
    printer.setPageMargins(QMarginsF(marginMM, marginMM, marginMM, marginMM), QPageLayout::Millimeter);

    if (!printer.isValid()) {
        return false;
    }
    std::cout << "Initializing painter" << std::endl;
    QPainter painter(&printer);
    if (!painter.isActive()) {
        return false;
    }
    std::cout << "Initializing painter pageSize" << std::endl;
    QSizeF pageSize = printer.pageRect(QPrinter::Millimeter).size();
    std::cout << "Initializing painter widgetSize" << std::endl;
    QSizeF widgetSize = widget->size();
    std::cout << "Initializing painter scale" << std::endl;
    qreal xScale = pageSize.width() / qreal(widgetSize.width());
    qreal yScale = pageSize.height() / qreal(widgetSize.height());
    qreal scale = qMin(xScale, yScale);
    std::cout << "Setting painter scale" << std::endl;
    painter.scale(10, 10);
    std::cout << "Rendering widget" << std::endl;
    qApp->processEvents();
    widget->render(&painter);
    std::cout << "Quitting painter" << std::endl;
    painter.end();
    std::cout << "Retrieving file info" << std::endl;
    QFileInfo fi(filePath);
    return fi.exists() && fi.size() > 0;
}












