#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QSplitter>
#include <QListWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QProcess>
#include <QImage>
#include <QPixmap>
#include <QFileInfo>

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
    void connects();
    ~MainWindow();

private slots:


private:
    bool isPicture(const QString pictureFile);
    bool isPictureUsing = false;
    bool isCameraUsing = false;
    void pictureDeducate(QString *pictureFile);
    void videoDeducate();
    void display();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
