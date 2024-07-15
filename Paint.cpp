#include "Paint.h"
#include "ui_Paint.h"

Paint::Paint(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::Paint)
{
    ui->setupUi(this);
    scene = new paintScene();
    ui->graphicsView->setScene(scene);
    connect(scene, &paintScene::signal_addNewPoint, this, &Paint::slot_addNewPoint);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Paint::slotTimer);
    timer->start(100);
}

Paint::~Paint()
{
    delete timer;
    delete scene;
    delete ui;
}

void Paint::slotTimer()
{
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width(), ui->graphicsView->height());
}

void Paint::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}

void Paint::slot_addNewPoint(QPointF point)
{
    QString str = "(x: " + QString::number(point.x()) + ", y: " + QString::number(point.y()) + ")";
    ui->textEdit->append(str);
}

void Paint::on_pushButton_clicked()
{
    scene->clear();
    ui->l_square->setText("0");
    ui->textEdit->clear();
    update();
}


void Paint::on_pushButton_2_clicked()
{
    scene->unity();
    ui->l_square->setText(QString::number(scene->getSquare()) + "px");
    update();
}
