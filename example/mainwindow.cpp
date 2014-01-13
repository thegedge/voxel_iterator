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
#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "grid_view.hpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->xy->setProjection(Projection::XY);
    ui->xz->setProjection(Projection::XZ);
    ui->yz->setProjection(Projection::YZ);
    updateLine();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateLine() {
    Line line{
        {ui->x1->value(), ui->y1->value(), ui->z1->value()},
        {ui->x2->value(), ui->y2->value(), ui->z2->value()},
    };

    ui->xy->setLine(line);
    ui->xz->setLine(line);
    ui->yz->setLine(line);
}
