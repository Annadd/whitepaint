#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void drawPoint(const QPoint& ptBegin, const QPoint& ptEnd);
    void initCache();

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
    Ui::MainWindow *ui;
    QPoint lastCursorPos;
    QPainter* painter;
    bool isLeftMousePressed;
    QPixmap* image;
};

#endif // MAINWINDOW_H
