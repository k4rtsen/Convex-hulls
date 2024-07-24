#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include <QMainWindow>
#include <QTimer>
#include <QResizeEvent>

#include <PaintScene.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Paint;
}
QT_END_NAMESPACE

class Paint : public QMainWindow
{
    Q_OBJECT

public:
    explicit Paint(QMainWindow *parent = 0);
    ~Paint();

private:
    Ui::Paint *m_pUI;
    QTimer *m_pTimer;
    PaintScene *m_pScene;

private:
    void ResizeEvent(QResizeEvent * event);

public slots:
    void GetNewPoint(QPoint);
    void GetSquare(qreal);

private slots:
    void SlotTimer();
    void on_bAsm_clicked();
    void on_bClear_clicked();
    void on_bAddPoint_clicked();
};

#endif // PAINT_H
