#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>

#include "loadcsv.h"
#include "pdfexporter.h"
#include "csvchart.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();

    void on_plotButton_clicked();

    void on_exportButton_clicked();

private:
    Ui::MainWindow *ui;
    loadcsv csvloader;
    QChartView *chartView;
    pdfexporter exporter;
    csvchart chartcsv;
};

#endif // MAINWINDOW_H
