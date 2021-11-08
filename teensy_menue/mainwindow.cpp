#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Adafruit_Simu.h"
#include "fnt8x11.h"
#include <QKeyEvent>
#include "objhndlglib.h"
#include "simulation/cRtc.h"
#include "cWheels.h"

extern struct stTxtList Texts[];
extern MainWindow* pw;
extern ILI9341_t3 tft;
extern cWheels wheels;

const volatile tChunkTab memChunks[] =
{
  {8, 2220},
  {16, 2220},
  {32, 2220},
  {64, 2220},
  {128, 2210},
  {256, 2210},
  {512, 2210},
  {1024, 2210},
};

const volatile int TabSize = sizeof (memChunks) / sizeof (memChunks[0]);

//Adafruit_Simu simuDisplay(1,2,3);
//stStatus devStatus;          ///< status of the device
//stParams devPars;            ///< parameters of the device
//cMenue menue(320,240, &simuDisplay);
//cRtc rtc;
//cParEnum f1MainItems(0);
//cParEnum f4MainItems(0);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    pw = this;
    Txt::setResource(&Texts[0]);
    ui->setupUi(this);
    ui->cbLog->addItem("0");
    ui->cbLog->addItem("1");
    ui->cbLog->addItem("2");
    ui->cbLog->addItem("3");
    ui->cbLog->addItem("4");
/*    simuDisplay.setParent(ui->wdgDisplay);
    simuDisplay.setRotation(1);
    simuDisplay.setFont(fnt8x11); */
    tft.setParent(ui->wdgDisplay);
    tft.setRotation(1);
    tft.setFont(fnt8x11);

    ui->tbLog->setPlainText("start\n");
    menue.init();
    ui->chkDoubleSize->setChecked(true);
//    startTimer(300);
    startTimer(100);
   repaint();
   m_initialized = true;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
     {
       case Qt::Key_U:
       case Qt::Key_PageUp:
        on_btn_up_clicked();
        break;
       case Qt::Key_D:
       case Qt::Key_PageDown:
         on_btn_down_clicked();
         break;
       case Qt::Key_Return:
         menue.handleKey(enKey::KEY_OK);
         break;
    }
    repaint();
}


void MainWindow::on_btn_ok_clicked()
{
  wheels.getBounce().createEdge();
    repaint();
}

void MainWindow::on_btn_down_clicked()
{

  wheels.getEncoder().incrementPos();
  repaint();
}

void MainWindow::on_btn_up_clicked()
{
  wheels.getEncoder().decrementPos();
  repaint();
}

void MainWindow::on_btn_f1_clicked()
{
  //  menue.handleKey(enKey::F1);
    repaint();
}

void MainWindow::on_btn_f2_clicked()
{
  // menue.handleKey(enKey::F2);
   repaint();
}

void MainWindow::on_btn_f4_clicked()
{
    //menue.handleKey(enKey::F4);
    repaint();

}

void MainWindow::on_btn_f3_clicked()
{
   // menue.handleKey(enKey::F3);
    repaint();
}

extern void loop();

void MainWindow::timerEvent(QTimerEvent *event)
{
    loop();
    //menue.handleKey(enKey::TICK);
    repaint();
}



void MainWindow::on_chkDoubleSize_clicked()
{
  if (ui->chkDoubleSize->isChecked()) {
     ui->wdgDisplay->setFixedHeight(480);
     ui->wdgDisplay->setFixedWidth(640);
     ui->wdgDisplay->setMultiplier(2);
  } else {
    ui->wdgDisplay->setFixedHeight(240);
    ui->wdgDisplay->setFixedWidth(320);
    ui->wdgDisplay->setMultiplier(1);
  }
  menue.refreshAll();
  repaint();
}


void MainWindow::log(const char* txt, int level)
{
  if(m_initialized)
  {
//    int selLevel = ui->cbLog->currentData().toString().toInt();
    int selLevel = ui->cbLog->currentIndex();
    if(selLevel == 0)
      return;
    if(level >= selLevel) {
      ui->tbLog->moveCursor (QTextCursor::End);
      ui->tbLog->insertPlainText (txt);
    }
  }
}

void MainWindow::on_btnClear_clicked()
{
    ui->tbLog->setPlainText("");
}

