#include "wdggraph.h"
#include "ui_wdggraph.h"

//#include <QDate>

wdgGraph::wdgGraph(QWidget *parent,
                   int width,  ///< width of simulated display [px]
                   int height, ///< height of simulated display [px]
                   int mul):   ///< multiplier for screensize on Qt screen
    QWidget(parent),
    ui(new Ui::wdgGraph),
    m_widthScreen(width * mul),
    m_heightScreen(height * mul),
    m_widthDisplay(width),
    m_heightDisplay(height),
    m_mult(mul)
{
  ui->setupUi(this);
  m_canvas = QImage(m_widthScreen,m_heightScreen,QImage::Format_RGB32);
  clear();
}

void wdgGraph::clear() {
  QColor col(getColorFrom565(0xffff));
  m_canvas.fill(col);
}

wdgGraph::~wdgGraph()
{
  delete ui;
}


void wdgGraph::paintEvent (QPaintEvent *e) {
  QPainter painter(this);
  painter.drawPixmap(0,0,QPixmap::fromImage(m_canvas));
}




void wdgGraph::setPixel(int x, int y, QRgb color) {
  int xs = x * m_mult;
  int ys = y * m_mult;
  if((xs > m_widthScreen) || (ys > m_heightScreen))
    return;
  m_drawColor = color;
  for (int i = xs; i < xs + m_mult ; i++)
    for (int j = ys; j < ys + m_mult ; j++)
      m_canvas.setPixel(i, j, color);
}


QRgb getColorFrom565(uint16_t color) {
  QRgb qCol = 0;
  qCol |= (color & 0x001F) << 3;
  qCol |= (color & 0x07E0) << 5;
  qCol |= (color & 0xF100) << 8;
  return qCol;
}
