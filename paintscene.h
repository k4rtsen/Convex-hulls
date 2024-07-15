#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QVector>
#include <cmath>

class paintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit paintScene(QObject *parent = 0);
    ~paintScene();
    void clear();
    void unity();
    qreal getSquare() const
    {
        return square;
    }

private:
    QVector<QPointF> points;
    qreal square{0};

private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    int vector_mul(QPointF a, QPointF b);
    void paintConvexHull(QVector<QPointF>&);
    qreal findSquare(QVector<QPointF>&);

    // QPoint &findMin(QVector<QPoint>&);
    QVector<QPointF> jarvis();
    // QVector<QPoint> graham();

signals:
    void signal_addNewPoint(QPointF point);
};

#endif // PAINTSCENE_H
