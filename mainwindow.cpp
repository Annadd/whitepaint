#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QPoint>
#include <QDebug>
#include <QPainter>
#include <QSize>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),isLeftMousePressed(false), image(nullptr),painter(nullptr)
{
    ui->setupUi(this);
    setCursor(Qt::CrossCursor);
    setMouseTracking(true);
    image = new QPixmap(QSize(width(),height()));
    painter = new QPainter(image);
    initCache();
}

MainWindow::~MainWindow()
{
    delete painter;
    delete ui;
}

void MainWindow::initCache()
{
    painter->setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter->fillRect(0, 0, image->width(), image->height(), Qt::white);
    update();
}

void MainWindow::drawPoint(const QPoint& ptBegin, const QPoint& ptEnd)
{
    painter->drawLine(ptBegin, ptEnd);
    lastCursorPos = ptEnd;
    update();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter p(this);

    QPen pen = QPen();
    pen.setWidth(3);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::red);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    p.setPen(pen);
    p.drawPixmap(0, 0, image->width(), image->height(), *image);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        lastCursorPos = event->pos();
        isLeftMousePressed = true;
    }
    QWidget::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        if(isLeftMousePressed){
            drawPoint(lastCursorPos, event->pos());
        }
        isLeftMousePressed = false;
    }
    QWidget::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if(event->buttons() & Qt::LeftButton){
        if(isLeftMousePressed){
            drawPoint(lastCursorPos, event->pos());
        }
    }
    QWidget::mouseMoveEvent(event);
}
