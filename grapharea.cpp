#include "grapharea.h"
#include "ui_grapharea.h"

GraphArea::GraphArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphArea)
{
    ui->setupUi(this);
}

GraphArea::~GraphArea()
{
    delete ui;
}

void GraphArea::drawGraph(std::vector<double>& x, std::vector<double>& y)
{
    this->x.push_front(x);
    this->y.push_front(y);
    if (this->x.size() > 4) {
        this->x.pop_back();
        this->y.pop_back();
    }
    update();
}

void GraphArea::paintEvent(QPaintEvent *) {
    QPainter brush(this);
    QPen pen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    brush.setPen(pen);

    // iterates through the deque of lines and graphs them
    if (x.size() > 0) {
        for (int j = 0; j < x.size(); ++j)
            for (unsigned long i = 0; i < x.at(j).size() - 1; ++i) {
                QLineF line(x.at(j).at(i), y.at(j).at(i), x.at(j).at(i+1), y.at(j).at(i+1));
                brush.drawLine(line);
            }
    }
}

void GraphArea::reset() {
    this->x.clear();
    this->y.clear();
    update();
}
