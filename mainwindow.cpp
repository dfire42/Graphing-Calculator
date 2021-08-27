#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_DrawButton_clicked()
{
    Interpreter *i = new Interpreter(ui->EnterEquation->text().toStdString());
    if (i->getParsedEquation() != nullptr) {
        // adds a new line and stores it
        ui->EquationList->addItem(ui->EnterEquation->text());
        ui->EquationList->setCurrentIndex(ui->EquationList->count() - 1);
    }
    delete i;
}

void MainWindow::on_EquationList_currentIndexChanged(const QString &arg1)
{
    if (ui->EquationList->count() > 0) {
        // generate points and graph
        Interpreter III(arg1.toStdString());
        HandleVars *coords = III.getParsedEquation();
        std::vector<double> x, y;

        // since (0,0) is at the top left corner, the following trick while making
        // the vector of points will move (0,0) to (235, 150)
        // this trick will also flip the y axis so that the slop is correct
        double input = -250;
        while (input < 500) {
            x.push_back((input + 235));
            y.push_back((150 - coords->getPoint(std::to_string(input))));
            input += .1;
        }
        ui->graph->drawGraph(x, y);     // adds new line to deque in graph area
    } else
        ui->graph->reset();     // if there are no stored equations, clear the graph
}

void MainWindow::on_DeleteLine_clicked()
{
    ui->EquationList->removeItem(ui->EquationList->currentIndex());
}

void MainWindow::on_EnterEquation_returnPressed()
{
    on_DrawButton_clicked();
}
