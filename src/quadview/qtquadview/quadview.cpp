#include "quadview.h"
#include "ui_quadview.h"

QuadView::QuadView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuadView)
{
    ui->setupUi(this);
}

QuadView::~QuadView()
{
    delete ui;
}

void QuadView::on_pushButton_clicked()
{
    ui->statusBar->showMessage(QString("Connected"));
    ui->pushButton->setText(QString("Disconnect"));
}
