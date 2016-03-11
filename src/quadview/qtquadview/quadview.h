#ifndef QUADVIEW_H
#define QUADVIEW_H

#include <QMainWindow>

namespace Ui {
class QuadView;
}

class QuadView : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuadView(QWidget *parent = 0);
    ~QuadView();

private slots:
    void on_pushButton_clicked();

private:
    Ui::QuadView *ui;
    double flightTime;
};

#endif // QUADVIEW_H
