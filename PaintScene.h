#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QVector>
#include <cmath>

class PaintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();
    void Clear();
    void Unity();
    qreal GetSquare() const
    {
        return m_square;
    }

private:
    QVector<QPointF> m_points;
    qreal m_square{0};

private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    int VectorMul(QPointF a, QPointF b);
    void PaintConvexHull(QVector<QPointF>&);
    qreal FindSquare(QVector<QPointF>&);

    // QPoint &findMin(QVector<QPoint>&);
    QVector<QPointF> Jarvis();
    // QVector<QPoint> graham();

signals:
    void signalAddNewPoint(QPointF point);
};

#endif // PAINTSCENE_H
