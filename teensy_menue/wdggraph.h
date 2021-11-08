#ifndef WDGGRAPH_H
#define WDGGRAPH_H

#include <QWidget>
#include <QPainter>

#define GRAPH_CNT   3


namespace Ui {
class wdgGraph;
}



struct stData {
  double x;
  double y;
};

typedef std::vector<stData> vData;

QRgb getColorFrom565(uint16_t color);

class wdgGraph : public QWidget
{
    Q_OBJECT

public:
    explicit wdgGraph(QWidget *parent = 0, int width = 320, int height = 240, int mul = 2);
    ~wdgGraph();
    void drawLine(int x1, int y1, int x2, int y2);
    void setPixel(int x, int y, QRgb color = 0);
    void paintEvent (QPaintEvent *e);
    void draw(int i);
    void refresh() { repaint();}
    void clear();
    void setMultiplier(int m) { m_mult = m; }


private:
    void initGraph();

    Ui::wdgGraph *ui;
    QImage m_canvas;


    double m_xMin = 0, m_yMin = 0;
    double m_xMax = 100, m_yMax = 100;  ///< range

    int m_widthScreen;    ///< width on the QT screen
    int m_heightScreen;   ///< height on the QT screen
    int m_widthDisplay;   ///< width of the simulated display
    int m_heightDisplay;  ///< height on the simulated display
    int m_mult;
    QRgb m_drawColor = 0;
};

#endif // WDGGRAPH_H
