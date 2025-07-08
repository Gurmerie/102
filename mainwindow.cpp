#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QFileDialog>
#include "loadcsv.h"
#include <QMessageBox>

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
    if (series->count() == 0) {
        QMessageBox::information(this, tr("Plot"), tr("No numeric data found in the selected columns"));
        delete series;
        return;
    }
    QChart *chart = new QChart;

    chart->addSeries(series);
    chart->createDefaultAxes();
    // QValueAxis *axisX = qobject_cast<QValueAxis *>(chart->axisX());
    // QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axisY());
    // axisX->setRange(2000, 2003);
    // axisY->setRange(100, 1000);
    chart->setTitle(QString("%1 vs %2").arg(ui->comboBox1->currentText()).arg(ui->comboBox2->currentText()));
    if (chartView) {
        chartView->setChart(chart);
    } else {
        chartView = new QChartView(chart, this);
        ui->verticalLayout->addWidget(chartView);
    }
}


void MainWindow::on_comboBox1_activated(int index)
{

}

