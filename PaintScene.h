#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QVector>

class PaintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();
    void Clear();
    void MakeHull();
    void AddNewPoint(QPoint);

private:
    QVector<QPoint> m_DotsOnScene;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void PaintConvexHull(const QVector<QPoint>&);
    void DrawPointOnScene(QPoint point);

signals:
    void signalAddNewPoint(QPoint point);
    void getSquare(qreal);
};


#endif // PAINTSCENE_H
