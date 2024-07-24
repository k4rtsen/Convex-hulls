#include "Paint.h"
#include "ui_Paint.h"

Paint::Paint(QMainWindow *parent)
    : QMainWindow(parent)
    , m_pUI(new Ui::Paint)
{
    m_pUI->setupUi(this);
    m_pScene = new PaintScene();
    m_pUI->graphicsView->setScene(m_pScene);
    connect(m_pScene, &PaintScene::signalAddNewPoint, this, &Paint::GetNewPoint);
    connect(m_pScene, &PaintScene::getSquare, this, &Paint::GetSquare);

    m_pTimer = new QTimer();
    connect(m_pTimer, &QTimer::timeout, this, &Paint::SlotTimer);
    m_pTimer->start(100);
}

Paint::~Paint()
{
    delete m_pTimer;
    delete m_pScene;
    delete m_pUI;
}

void Paint::SlotTimer()
{
    m_pTimer->stop();
    m_pScene->setSceneRect(0,0, m_pUI->graphicsView->width(), m_pUI->graphicsView->height());
}

void Paint::ResizeEvent(QResizeEvent *event)
{
    m_pTimer->start(100);
    QWidget::resizeEvent(event);
}

void Paint::GetSquare(qreal square)
{
    m_pUI->l_square->setText(QString::number(square) + "px");
}

void Paint::GetNewPoint(QPoint point)
{
    QString str = "(x: " + QString::number(point.x()) + ", y: " + QString::number(point.y()) + ")";
    m_pUI->textEdit->append(str);
}

void Paint::on_bAsm_clicked()
{
    m_pScene->MakeHull();
    update();
}

void Paint::on_bClear_clicked()
{
    m_pScene->Clear();
    m_pUI->l_square->setText("0");
    m_pUI->textEdit->clear();
    update();
}

void Paint::on_bAddPoint_clicked()
{
    if (m_pUI->x_coordinate->text().isEmpty() || m_pUI->y_coordinate->text().isEmpty())
    {
        return;
    }
    int x = m_pUI->x_coordinate->text().toInt();
    int y = m_pUI->y_coordinate->text().toInt();
    m_pScene->AddNewPoint(QPoint{x, y});
}

