#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <QVector>
#include <QPoint>

class ConvexHull
{
private:
    QVector<QPoint> m_Hull;
    qreal m_Square;

    // векторное произведение
    int VectorMul(QPoint a, QPoint b);
    // находит точку ближайшую к (0, 0)
    QPoint FindMinPoint(const QVector<QPoint>&);
    qreal CalculateArea();
    QVector<QPoint> Jarvis(const QVector<QPoint>&);
    // QVector<QPoint> Graham(const QVector<QPoint>&);

public:
    ConvexHull(const QVector<QPoint>&);

    qreal GetSquare()
    {
        return m_Square;
    }

    QVector<QPoint> &GetHullPoints()
    {
        return m_Hull;
    }
};

#endif // CONVEXHULL_H
