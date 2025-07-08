#include "loadcsv.h"
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <iostream>

loadcsv::loadcsv(QObject *parent) : QObject(parent) {}

bool loadcsv::loadFile(const QString &filePath) {
    m_headers.clear();
    m_rows.clear();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "--> Could not open file." << std::endl;
        return false;
    }

    QTextStream in(&file);
    if(in.atEnd()) {
        std::cerr << "--> End of file." << std::endl;
        return false;
    }

    QString headerLine = in.readLine();
    m_headers = headerLine.split(',', Qt::KeepEmptyParts);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList row = line.split(',', Qt::KeepEmptyParts);
        m_rows.append(row);
    }

    return true;
}

QStringList loadcsv::headers() const {
    return m_headers;
}

QVector<QStringList> loadcsv::rows() const {
    return m_rows;
}
