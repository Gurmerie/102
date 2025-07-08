#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loadcsv.h"

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

    void on_pushButton_2_clicked();

    void on_frame_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_activated(int index);

    void on_comboBox_2_activated(int index);

private:
    Ui::MainWindow *ui;
    loadcsv csvloader;
};
#endif // MAINWINDOW_H
