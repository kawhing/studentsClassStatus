#pragma once
#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/model.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pythonDirLineEdit->setText("/home/kawhing/miniconda3/envs/yolov/bin/python");
    connects();
}
bool MainWindow::isPicture(const QString pictureFile){
    QFile file(pictureFile);
    if (!file.open(QIODevice::ReadOnly))
            return false;
    // 读取文件头部字节
    QByteArray header = file.read(8);
    file.close();

    // JPEG: FF D8 FF
    if(header.startsWith(QByteArray::fromHex("FFD8FF")))
           return true;

       // PNG: 89 50 4E 47 0D 0A 1A 0A
       if (header.startsWith(QByteArray::fromHex("89504E470D0A1A0A")))
           return true;

       // GIF: 47 49 46 38
       if (header.startsWith(QByteArray::fromHex("474946")))
           return true;

       // BMP: 42 4D
       if (header.startsWith(QByteArray::fromHex("424D")))
           return true;

       return false;
}
void MainWindow::display(){
    Model model;
    const QString resultPicture = "result.jpg";
    if(model.isFile("jpg", resultPicture)){
        QPixmap resultJPG = (resultPicture);
        ui->pictureResultLabel->setPixmap(resultJPG);
    }
}
void MainWindow::connects(){
    connect(ui->homePushButton, &QPushButton::clicked, [=](){
       ui->stackedWidget->setCurrentWidget(ui->homePage);
    });

    connect(ui->picturePushButton, &QPushButton::clicked, [=](){
       ui->stackedWidget->setCurrentWidget(ui->picturePage);
    });
    connect(ui->broswerPushButton, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->picturePage);

        const QString fileName = QFileDialog::getOpenFileName(
            this,
            "选择文件",
            QDir::homePath(),
            "图像文件 (*.png *.jpg)"
        );

        if (fileName.isEmpty()) {
            QMessageBox::warning(this, "打开失败", "未选择任何文件！");
            return;
        }

        qDebug() << "选中文件:" << fileName;

        // 显示路径到 QListWidget
        ui->fileDirLineEdit->setText(fileName);
    });
    connect(ui->pictureDeducatePushButton, &QPushButton::clicked, [=](){
        Model model(ui->modelDirLineEdit->text());
        model.editPythonPath(ui->pythonDirLineEdit->text());
        if(model.isFile("png", ui->fileDirLineEdit->text()) || model.isFile("jpg", ui->fileDirLineEdit->text())){
            model.editpicture(true, ui->fileDirLineEdit->text());
            model.runPy();
            if(model.runOver()){
                this->display();
            }
        }

    });

    connect(ui->cameraPushButton, &QPushButton::clicked, [=](){
       ui->stackedWidget->setCurrentWidget(ui->cameraPage);
    });
    connect(ui->settingsPushButton, &QPushButton::clicked, [=](){
       ui->stackedWidget->setCurrentWidget(ui->settingsPage);
    });
    connect(ui->pythonBroswerPushButton, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentWidget(ui->picturePage);
        const QString fileName = QFileDialog::getOpenFileName(
            this,
            "选择文件",
            QDir::homePath(),
            "python解释器 (python)"
            );
        if (fileName.isEmpty()) {
            QMessageBox::warning(this, "打开失败", "未选择任何文件！");
            return;
        }
        qDebug() << "选中文件:" << fileName;
        // 显示路径到 QListWidget
        ui->pythonDirLineEdit->setText(fileName);
    });
    connect(ui->modelBroswerPushButton, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->settingsPage);

        const QString fileName = QFileDialog::getOpenFileName(
            this,
            "选择文件",
            QDir::homePath(),
            "模型文件 (*.pt)"
        );

        if (fileName.isEmpty()) {
            QMessageBox::warning(this, "打开失败", "未选择任何文件！");
            return;
        }

        qDebug() << "选中文件:" << fileName;

        // 显示路径到 QListWidget
        ui->modelDirLineEdit->setText(fileName);

    });
}
MainWindow::~MainWindow()
{
    delete ui;
}
