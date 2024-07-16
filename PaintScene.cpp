#include "PaintScene.h"
#include "convexhull.h"

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

PaintScene::PaintScene(QObject *parent)
    : QGraphicsScene(parent)
{

}

PaintScene::~PaintScene()
{

}

void PaintScene::Clear()
{
    this->QGraphicsScene::clear();
    m_DotsOnScene.clear();
}

void PaintScene::MakeHull()
{
    if (m_DotsOnScene.empty() || m_DotsOnScene.size() < 2)
    {
        return;
    }

    // get a points of convex hull
    ConvexHull hull(m_DotsOnScene);

    // paint it on scene
    PaintConvexHull(hull.GetHullPoints());

    // send to main window the area of hull
    emit getSquare(hull.GetSquare());
}

void PaintScene::PaintConvexHull(const QVector<QPoint> &hull)
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

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    constexpr qreal SIZE {4};
    QPoint point = event->scenePos().toPoint();
    addEllipse(point.x() - SIZE / 2,
               point.y() - SIZE / 2,
               SIZE,
               SIZE,
               QPen(Qt::black),
               QBrush(Qt::black));

    m_DotsOnScene.append(point);
    emit signalAddNewPoint(point);
}
