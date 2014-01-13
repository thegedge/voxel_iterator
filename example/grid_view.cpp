//----------------------------------------------------------------------------
// Copyright (c) 2014 Jason Gedge
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//----------------------------------------------------------------------------
#include "grid_view.hpp"
#include "../voxel_iterator.hpp"

#include <cmath>
#include <QtCore/QDebug>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>


template <typename T>
int sign(const T &a) {
    return (T{0} < a) - (a < T{0});
}

void trace(QPainter &p, const Line &line, Projection proj) {
    Eigen::Vector3d dir = (line.second - line.first).normalized();
    ForwardVoxelIterator iter(Eigen::Vector3d::Ones(), line.first, dir);

    // Draw filled rectangles for every voxel we iterate over
    const double maxT = (line.first - line.second).norm();
    for(; iter.t() + 1e-5 < maxT; ++iter) {
        Eigen::Vector3i voxel = *iter;
        switch(proj) {
        case Projection::XY:
            p.fillRect(QRectF(voxel.x(), voxel.y(), 1.0, 1.0), Qt::green);
            break;
        case Projection::XZ:
            p.fillRect(QRectF(voxel.x(), voxel.z(), 1.0, 1.0), Qt::green);
            break;
        case Projection::YZ:
            p.fillRect(QRectF(voxel.y(), voxel.z(), 1.0, 1.0), Qt::green);
            break;
        }
    }
}

GridView::GridView(QWidget *parent)
    : QWidget(parent)
{}

void GridView::mouseMoveEvent(QMouseEvent *evt) {
    evt->accept();
}

void GridView::paintEvent(QPaintEvent *evt) {
    QPainter p(this);

    const double num = maxX_ - minX_ + 1;
    const double szx = width() / num;
    const double szy = height() / num;

    // Background
    p.fillRect(rect(), Qt::white);

    // Voxel tracing
    p.scale(szx, szy);
    trace(p, line_, projection_);
    p.resetTransform();

    // Vertical grid lines
    {
        p.setPen(Qt::gray);
        for(double x = szx; x < width(); x += szx)
           p.drawLine(QLineF(x, 0, x, height()));
    }

    // Horizontal grid lines
    {
        p.setPen(Qt::gray);
        for(double y = szy; y < height(); y += szy)
            p.drawLine(QLineF(0, y, width(), y));
    }

    // Projected line
    p.setPen(Qt::red);
    switch(projection_) {
    case Projection::XY:
        p.drawLine(QLineF(szx*line_.first.x(), szy*line_.first.y(),
                          szx*line_.second.x(), szy*line_.second.y()));
        break;
    case Projection::XZ:
        p.drawLine(QLineF(szx*line_.first.x(), szy*line_.first.z(),
                          szx*line_.second.x(), szy*line_.second.z()));
        break;
    case Projection::YZ:
        p.drawLine(QLineF(szx*line_.first.y(), szy*line_.first.z(),
                          szx*line_.second.y(), szy*line_.second.z()));
        break;
    }

    // Draw a border
    p.setPen(Qt::black);
    p.drawRect(rect().adjusted(-1, -1, -1, -1));

    evt->accept();
}
