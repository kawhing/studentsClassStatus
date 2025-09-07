#pragma once
#include "model.h"

Model::Model(const QString modelFile) {
    const QString extension = "pt";
    if(isFile(extension, modelFile)){
        this->modelFile = modelFile;
        this->isPt = true;
    }
}
Model::Model(){

}
bool Model::isFile(const QString suffix, const QString file){
    QFileInfo fileInfo(file);
    QString extension = fileInfo.suffix().toLower();
    return (suffix == extension);
}
void Model::editPythonPath(QString pythonPath){
    this->pythonPath = pythonPath;
}
void Model::runPy(){
    if(this->isPt && this->isPicture){
        QProcess modelProcess;
        // 连接信号来获取输出
        QObject::connect(&modelProcess, &QProcess::readyReadStandardOutput, [&]() {
            QByteArray output = modelProcess.readAllStandardOutput();
            qDebug() << "Python输出:" << output;
        });
        QObject::connect(&modelProcess, &QProcess::readyReadStandardError, [&]() {
            QByteArray error = modelProcess.readAllStandardError();
            qDebug() << "Python错误:" << error;
        });
        // 启动进程
        modelProcess.start(pythonPath, QStringList() << "/home/kawhing/Repository/class/main.py" << this->modelFile << this->pictureFile);
        // 等待进程完成（设置更长超时时间，如60秒）
        if (modelProcess.waitForFinished(60000)) {
            const QString result = "result.jpg";
            if(QFile::exists(result)){
                this->isRunOver = true;
                qDebug() << "推理完成，结果文件已生成";
            } else {
                qDebug() << "推理完成，但结果文件未找到";
            }
        } else {
            qDebug() << "进程执行超时或失败";
            modelProcess.terminate(); // 终止进程
            if (!modelProcess.waitForFinished(5000)) {
                modelProcess.kill(); // 强制杀死进程
            }
        }
        qDebug() << "退出代码:" << modelProcess.exitCode();
        qDebug() << "标准错误:" << modelProcess.readAllStandardError();
    }
}
bool Model::runOver(){
    return this->isRunOver;
}
void Model::editpicture(bool flag, QString file){
    this->isPicture = flag;
    this->pictureFile = file;
}
