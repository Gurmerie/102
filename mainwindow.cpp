#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QFileDialog>
#include "loadcsv.h"
#include <QMessageBox>
#include "pdfexporter.h"
#include "csvchart.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , chartView(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open CSV File"), "C:/Users/stj.egurmericliler/testingFiles", tr("CSV File (*.csv);;All File (*)"));

    if (fileName.isEmpty()) {
        std::cerr << "--> No file selected." << std::endl;
        return;
    }

    bool ok = csvloader.loadFile(fileName);
    if (!ok) {
        std::cerr << "--> Could not load file." << std::endl;
        return;
    }

    QStringList headers = csvloader.headers();
    if (!ok || headers.isEmpty()) {
        QMessageBox::warning(this, tr("Load CSV"), tr("Failed to read header from:\n%1").arg(fileName));
        return;
    }

    ui->comboBox1->clear();
    ui->comboBox1->addItems(headers);
    ui->comboBox2->clear();
    ui->comboBox2->addItems(headers);
}

void MainWindow::on_plotButton_clicked()
{
    int colX = ui->comboBox1->currentIndex();
    int colY = ui->comboBox2->currentIndex();

    if (colX < 0 || colY < 0) {
        QMessageBox::warning(this, tr("Plot"), tr("Please select both X and Y columns."));
        return;
    }

    QVector<QStringList> rows = csvloader.rows();
    if (rows.isEmpty()) {
        std::cerr << "--> Could not load rows." << std::endl;
        return;
    }

    QStringList headers = csvloader.headers();
    if (headers.isEmpty()) {
        std::cerr << "--> Could not load headers." << std::endl;
        return;
    }

    QChart *chart = new QChart;
    chart = chartcsv.plotChart(headers, rows, colX, colY);

    if (!chart) {
        QMessageBox::warning(this, tr("Chart"), tr("Could not plot chart."));
        return;
    }

    if (chartView) {
        chartView->setChart(chart);
    } else {
        chartView = new QChartView(chart, this);
        ui->verticalLayout->addWidget(chartView);
    }
}

void MainWindow::on_exportButton_clicked()
{
    if (!chartView) {
        QMessageBox::warning(this, tr("Export"), tr("There is no chart to export."));
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF."), "C:/Users/stj.egurmericliler/testingFiles", tr("PDF File (*.pdf)"));

    if (fileName.isEmpty()) {
        return;
    }

    std::cout << "Exporting" << std::endl;
    bool ok = exporter.exportWidgetToPDF(chartView, fileName, 15.0);
    std::cout << "Exported" << std::endl;
    if (!ok) {
        QMessageBox::warning(this, tr("Export"), tr("Couldn't export chart to PDF."));
    } else {
        QMessageBox::information(this, tr("Export"), tr("Exported chart to PDF."));
    }
}

