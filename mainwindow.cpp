#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>
#include "loadcsv.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open CSV File"), QString(), tr("CSV File (*.csv);;All File (*)"));

    if (fileName.isEmpty()) {
        std::cerr << "--> No file selected." << std::endl;
        return;
    }

    bool ok = false;
    QStringList headers = csvloader.loadHeader(fileName, &ok);
    if (!ok || headers.isEmpty()) {
        QMessageBox::warning(this, tr("Load CSV"), tr("Failed to read header from:\n%1").arg(fileName));
        return;
    }

    ui->comboBox1->clear();
    ui->comboBox1->addItems(headers);
    ui->comboBox2->clear();
    ui->comboBox2->addItems(headers);

}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_pushButton_3_clicked()
{

}

void MainWindow::on_frame_customContextMenuRequested(const QPoint &pos)
{

}

void MainWindow::on_pushButton_4_clicked()
{

}


void MainWindow::on_comboBox_activated(int index)
{

}


void MainWindow::on_comboBox_2_activated(int index)
{

}

