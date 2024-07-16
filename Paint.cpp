#include "Paint.h"
#include "ui_Paint.h"

Paint::Paint(QMainWindow *parent)
    : QMainWindow(parent)
    , m_pUI(new Ui::Paint)
{
    m_pUI->setupUi(this);
    m_pScene = new PaintScene();
    m_pUI->graphicsView->setScene(m_pScene);
    connect(m_pScene, &PaintScene::signalAddNewPoint, this, &Paint::SlotAddNewPoint);

    m_pTimer = new QTimer();
    connect(m_pTimer, &QTimer::timeout, this, &Paint::slotTimer);
    m_pTimer->start(100);
}

Paint::~Paint()
{
    delete m_pTimer;
    delete m_pScene;
    delete m_pUI;
}

void Paint::slotTimer()
{
    m_pTimer->stop();
    m_pScene->setSceneRect(0,0, m_pUI->graphicsView->width(), m_pUI->graphicsView->height());
}

void Paint::resizeEvent(QResizeEvent *event)
{
    m_pTimer->start(100);
    QWidget::resizeEvent(event);
}

void Paint::SlotAddNewPoint(QPointF point)
{
    QString str = "(x: " + QString::number(point.x()) + ", y: " + QString::number(point.y()) + ")";
    m_pUI->textEdit->append(str);
}

void Paint::on_pushButton_clicked()
{
    m_pScene->clear();
    m_pUI->l_square->setText("0");
    m_pUI->textEdit->clear();
    update();
}


void Paint::on_pushButton_2_clicked()
{
    m_pScene->Unity();
    m_pUI->l_square->setText(QString::number(m_pScene->GetSquare()) + "px");
    update();
}
