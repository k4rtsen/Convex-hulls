#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include <QMainWindow>
#include <QTimer>
#include <QResizeEvent>

#include <paintscene.h>

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
    Ui::Paint *ui;
    QTimer *timer;
    paintScene *scene;

private:
    void resizeEvent(QResizeEvent * event);

public slots:
    void slot_addNewPoint(QPointF);

private slots:
    void slotTimer();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // PAINT_H
