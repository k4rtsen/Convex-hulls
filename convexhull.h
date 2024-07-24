#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <QVector>
#include <QPoint>
#include <iostream>
using namespace std;

class ConvexHull
{
private:
    QVector<QPoint> m_Hull;
    qreal m_Square;

    // векторное произведение
    int VectorMul(QPoint a, QPoint b);
    // находит точку ближайшую к (0, 0)
    QPoint FindMinPoint(const QVector<QPoint>&, int *minIndex = nullptr);
    qreal CalculateArea(const QVector<QPoint>&);
    QVector<QPoint> Jarvis(const QVector<QPoint>&);
    QVector<QPoint> Graham(QVector<QPoint>);

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

//for debug
ostream &operator<<(ostream &os, const QPoint point);
template<typename Obj>
void printVector(const QVector<Obj>&);

#endif // CONVEXHULL_H
