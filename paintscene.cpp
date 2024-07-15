#include "paintscene.h"

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{

}

paintScene::~paintScene()
{

}

void paintScene::clear()
{
    this->QGraphicsScene::clear();
    square = 0;
    points.clear();
}

void paintScene::unity()
{
    // exceprion
    if (points.empty() || points.size() < 2)
        return;

    // get a points
    QVector<QPointF> hull = jarvis();

    // paint it on scene
    paintConvexHull(hull);

    this->square = findSquare(hull);
}

// векторное произведение
int paintScene::vector_mul(QPointF a, QPointF b)
{
    return a.x() * b.y() - b.x() * a.y();
}

void paintScene::paintConvexHull(QVector<QPointF> &hull)
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

qreal paintScene::findSquare(QVector<QPointF> &hull)
{
    qreal S{0};
    if (hull.size() < 3)
        return S;

    int n { static_cast<int>(hull.size()) };
    forn(i, n)
    {
        S += static_cast<qreal>(vector_mul(hull[i], hull[(i + 1) % n]));
    }

    return abs(S)/2;
}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    constexpr qreal SIZE {4};
    QPointF point = event->scenePos();
    addEllipse(point.x() - SIZE / 2,
               point.y() - SIZE / 2,
               SIZE,
               SIZE,
               QPen(Qt::black),
               QBrush(Qt::black));

    points.append(point);
    emit signal_addNewPoint(point);
}

QVector<QPointF> paintScene::jarvis()
{
    // find the topmost left point
    QPointF head = points[0];
    for(auto &val : points)
    {
        if (val.x() < head.x() || (val.x() == head.x() && val.y() < head.y()))
            head = val;
    }

    QVector<QPointF> hull {head}; // result vector
    QPointF p0 = head; // the reference point from which the rightmost point is considered
    do{
        QPointF rightmost;

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
            int vm = vector_mul( (val - p0), (rightmost - p0));
            if (vm > 0)
                rightmost = val;
        }

        p0 = rightmost;
        hull.append(rightmost);
    }
    while(p0 != head);

    hull.pop_back();

    return hull;
}
