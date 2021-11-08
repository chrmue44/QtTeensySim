#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wdggraph.h"
#include "simulation/Adafruit_Simu.h"
#include "cmenue.h"

namespace Ui {
class MainWindow;
}

extern cMenue menue;
extern Adafruit_Simu simuDisplay;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void log(const char* text, int level);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *);

private slots:
    void on_btn_ok_clicked();

    void on_btn_down_clicked();

    void on_btn_up_clicked();

    void on_btn_f1_clicked();

    void on_btn_f2_clicked();

    void on_btn_f4_clicked();

    void on_btn_f3_clicked();
    void timerEvent(QTimerEvent *event);

    void on_chkDoubleSize_clicked();

    void on_btnClear_clicked();

private:
    Ui::MainWindow *ui;
    bool m_initialized = false;
};

#endif // MAINWINDOW_H
