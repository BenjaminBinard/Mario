#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include<QPushButton>

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
private:
    QWidget * widget_general;
    QGraphicsView * myview;
};

#endif // MAINWINDOW_H
