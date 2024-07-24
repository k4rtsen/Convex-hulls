#include "convexhull.h"

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

template<typename Obj>
void printVector(const QVector<Obj>& vector)
{
    for(auto &val : vector)
    {
        cout << val << endl;
    }
}

ostream &operator<<(ostream &os, const QPoint point)
{
    return os << point.x() << ", " << point.y();
}

ConvexHull::ConvexHull(const QVector<QPoint> &points)
    : m_Square{0}
{
    // частный случай: если все точки лежат на одной прямой
    // m_Hull = Jarvis(points);
    m_Hull = Graham(points);
    m_Square = CalculateArea(m_Hull);
}

int ConvexHull::VectorMul(QPoint a, QPoint b)
{
    return a.x() * b.y() - b.x() * a.y();
}

QPoint ConvexHull::FindMinPoint(const QVector<QPoint> &points, int *minIndex)
{
    QPoint head = points[0];
    int count{0};
    for(auto &val : points)
    {
        if (val.x() < head.x() || (val.x() == head.x() && val.y() < head.y()))
        {
            head = val;
            if (minIndex != nullptr)
            {
                *minIndex = count;
            }
        }
        count++;
    }
    return head;
}

qreal ConvexHull::CalculateArea(const QVector<QPoint> &points)
{
    qreal S{0};
    if (points.empty())
    {
        return S;
    }

    int n { static_cast<int>(points.size()) };
    forn(i, n)
    {
        S += static_cast<qreal>(VectorMul(points[i], points[(i + 1) % n]));
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

QVector<QPoint> ConvexHull::Graham(QVector<QPoint> points)
{
    int minIndex;
    QPoint head = FindMinPoint(points, &minIndex);

    if (minIndex > 0 && minIndex < points.size())
    {
        swap(points[0], points[minIndex]);
    }

    // сортировка по полярному углу относительно нулевой точки
    sort(points.begin(), points.end(), [&](QPoint a, QPoint b){
        return VectorMul((a - head), b - head) < 0;
    });

    printVector(points);

    QVector<QPoint> hull;
    for(auto &val : points)
    {
        while(hull.size() >= 1)
        {
            QPoint newVector = val - hull.back();

            int preLast {0};
            if (hull.size() > 1)
            {
                preLast = hull.size() - 2;
            }
            QPoint lastVector = hull.back() - hull[preLast];

            if (VectorMul(newVector, lastVector) < 0)
            {
                hull.pop_back();
            }
            else
            {
                break;
            }
        }
        hull.push_back(val);
    }

    return hull;
}
