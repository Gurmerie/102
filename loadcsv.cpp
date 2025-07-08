#include "loadcsv.h"
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <iostream>

loadcsv::loadcsv(QObject *parent) : QObject(parent) {}

QStringList loadcsv::loadHeader(const QString &filePath, bool *ok) const {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "--> Could not open file." << std::endl;
        if (ok) {
            *ok = false;
        }
        return {};
    }
    QTextStream in(&file);
    if (in.atEnd()) {
        std::cerr << "--> End of file." << std::endl;
        if (ok) {
            *ok = false;
        }
        return {};
    }
    QString headerLine = in.readLine();
    file.close();

    if (ok) {
        *ok = true;
    }
    std::cout << "--> Retrieved headers." << std::endl;
    return headerLine.split(',', Qt::SkipEmptyParts);
}
