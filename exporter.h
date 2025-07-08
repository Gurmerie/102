#ifndef EXPORTER_H
#define EXPORTER_H

#include <string>

class ExportConfig;

class Exporter {
public:
    virtual ~Exporter() = default;
    virtual void exportDocument(const std::string& filePath, const ExportConfig& config) = 0;
};

#endif // EXPORTER_H
