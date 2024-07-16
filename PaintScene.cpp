#include "PaintScene.h"

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{

}

PaintScene::~PaintScene()
{

}

void PaintScene::Clear()
{
    this->QGraphicsScene::clear();
    m_square = 0;
    m_points.clear();
}

void PaintScene::Unity()
{
    // exceprion
    if (m_points.empty() || m_points.size() < 2)
    {
        return;
    }

    // get a points
    QVector<QPointF> hull = Jarvis();

    // paint it on scene
    PaintConvexHull(hull);

    this->m_square = FindSquare(hull);
}

// векторное произведение
int PaintScene::VectorMul(QPointF a, QPointF b)
{
    return a.x() * b.y() - b.x() * a.y();
}

void PaintScene::PaintConvexHull(QVector<QPointF> &hull)
{
    forn(i, hull.size() - 1)
    {
        addLine(hull[i].x(),
                hull[i].y(),
                hull[i+1].x(),
                hull[i+1].y(),
                QPen(Qt::black));
    }
    addLine(hull[hull.size() - 1].x(),
            hull[hull.size() - 1].y(),
            hull[0].x(),
            hull[0].y(),
            QPen(Qt::black));
}

qreal PaintScene::FindSquare(QVector<QPointF> &hull)
{
    qreal S{0};
    if (hull.size() < 3)
    {
        return S;
    }

    int n { static_cast<int>(hull.size()) };
    forn(i, n)
    {
        S += static_cast<qreal>(VectorMul(hull[i], hull[(i + 1) % n]));
    }

    return abs(S)/2;
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    constexpr qreal SIZE {4};
    QPointF point = event->scenePos();
    addEllipse(point.x() - SIZE / 2,
               point.y() - SIZE / 2,
               SIZE,
               SIZE,
               QPen(Qt::black),
               QBrush(Qt::black));

    m_points.append(point);
    emit signalAddNewPoint(point);
}

QVector<QPointF> PaintScene::Jarvis()
{
    // find the topmost left point
    QPointF head = m_points[0];
    for(auto &val : m_points)
    {
        if (val.x() < head.x() || (val.x() == head.x() && val.y() < head.y()))
        {
            head = val;
        }
    }

    QVector<QPointF> hull {head}; // result vector
    QPointF p0 = head; // the reference point from which the rightmost point is considered
    do{
        QPointF rightmost;

        if (p0 == m_points[0])
        {
            rightmost = m_points[1];
        }
        else
        {
            rightmost = m_points[0];
        }

        // find the rightmost point, relative to current p0
        for(auto &val : m_points)
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
