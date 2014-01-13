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
#ifndef GRID_VIEW_HPP
#define GRID_VIEW_HPP

#include <utility>
#include <eigen3/Eigen/Core>
#include <QtWidgets/QWidget>


typedef std::pair<Eigen::Vector3d, Eigen::Vector3d> Line;

enum class Projection {
    XY,
    XZ,
    YZ
};

/**
 * A class to view a 2D projection of a 3D line.
 */
class GridView : public QWidget {
    Q_OBJECT

public:
    explicit GridView(QWidget *parent = 0);

public:
    void setMinX(int v) { minX_ = v; repaint(); }
    void setMaxX(int v) { maxX_ = v; repaint(); }
    void setMinY(int v) { minY_ = v; repaint(); }
    void setMaxY(int v) { maxY_ = v; repaint(); }
    void setProjection(Projection v) { projection_ = v; repaint(); }
    void setLine(Line v) { line_ = v; repaint(); }

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    int minX_{0};
    int maxX_{20};
    int minY_{0};
    int maxY_{20};
    Projection projection_{Projection::XY};
    Line line_{{0, 0, 0}, {0, 0, 0}};
};

#endif // GRID_VIEW_HPP
