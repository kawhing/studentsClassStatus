#ifndef MODEL_H
#define MODEL_H
#pragma once
#include "mainwindow.h"

class Model
{
public:
    Model(const QString modelFile);
    Model();
    bool isFile(const QString suffix, const QString file);
    void runPy();
    void editpicture(bool flag, QString file);
    bool runOver();
    void editPythonPath(QString pythonPath);
private:
    bool isPt, isPicture, isRunOver;
    QString modelFile, pictureFile, pythonPath;
};

#endif // MODEL_H
