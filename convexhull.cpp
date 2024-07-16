#include "convexhull.h"

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

ConvexHull::ConvexHull(const QVector<QPoint> &points)
    : m_Square(0)
{
    m_Hull = Jarvis(points);
    m_Square = CalculateArea();
}

int ConvexHull::VectorMul(QPoint a, QPoint b)
{
    return a.x() * b.y() - b.x() * a.y();
}

QPoint ConvexHull::FindMinPoint(const QVector<QPoint> &points)
{
    QPoint head = points[0];
    for(auto &val : points)
    {
        if (val.x() < head.x() || (val.x() == head.x() && val.y() < head.y()))
        {
            head = val;
        }
    }
    return head;
}

qreal ConvexHull::CalculateArea()
{
    qreal S{0};
    if (m_Hull.empty())
    {
        return S;
    }

    int n { static_cast<int>(m_Hull.size()) };
    forn(i, n)
    {
        S += static_cast<qreal>(VectorMul(m_Hull[i], m_Hull[(i + 1) % n]));
    }

    return abs(S)/2;
}

QVector<QPoint> ConvexHull::Jarvis(const QVector<QPoint> &points)
{
    // find the topmost left point
    QPoint head = FindMinPoint(points);

    QVector<QPoint> hull {head}; // result vector
    QPoint p0 = head; // the reference point from which the rightmost point is considered
    do{
        QPoint rightmost;

        if (p0 == points[0])
        {
            rightmost = points[1];
        }
        else
        {
            rightmost = points[0];
        }

        // find the rightmost point, relative to current p0
        for(auto &val : points)
        {
            int vm = VectorMul( (val - p0), (rightmost - p0));
            if (vm > 0)
            {
                rightmost = val;
            }
        }

        p0 = rightmost;
        hull.append(rightmost);
    }
    while(p0 != head);

    hull.pop_back();

    return hull;
}

