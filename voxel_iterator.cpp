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
#include "voxel_iterator.hpp"


/**
 * Gets the sign of a value.
 *
 * @param a  the value to retrieve the sign from
 *
 * @return 1 if \c a is negative, -1 if \c a is positive, and 0 otherwise.
 */
template <typename T>
int sign(const T &a) {
    return (T{0} < a) - (a < T{0});
}

ForwardVoxelIterator::ForwardVoxelIterator() {
    ForwardVoxelIterator(Eigen::Vector3d::Ones(), Eigen::Vector3d::Zero(),
                         Eigen::Vector3d::Ones());
}

ForwardVoxelIterator::ForwardVoxelIterator(const Eigen::Vector3d &size,
                                           const Eigen::Vector3d &pos,
                                           const Eigen::Vector3d &direction)
    : size(size)
    , dir(direction.normalized())
    , step(sign(dir.x()), sign(dir.y()), sign(dir.z()))
    , tDelta(size.x() / std::fabs(dir.x()),
             size.y() / std::fabs(dir.y()),
             size.z() / std::fabs(dir.z()))
    , voxel(pos.x() / size.x(), pos.y() / size.y(), pos.z() / size.z())
    , currentT(0.0)
{
    tNext.x() = std::fmod(pos.x(), size.x());
    tNext.y() = std::fmod(pos.y(), size.y());
    tNext.z() = std::fmod(pos.z(), size.z());

    if(step.x() == 1) tNext.x() = size.x() - tNext.x();
    if(step.y() == 1) tNext.y() = size.y() - tNext.y();
    if(step.z() == 1) tNext.z() = size.z() - tNext.z();

    tNext.x() /= std::fabs(dir.x());
    tNext.y() /= std::fabs(dir.y());
    tNext.z() /= std::fabs(dir.z());
}

ForwardVoxelIterator ForwardVoxelIterator::operator++() {
    if(tNext.x() < tNext.y()) {
        if(tNext.x() < tNext.z()) {
            currentT = tNext.x();
            voxel.x() += step.x();
            tNext.x() += tDelta.x();
        } else {
            currentT = tNext.z();
            voxel.z() += step.z();
            tNext.z() += tDelta.z();
        }
    } else if(tNext.y() < tNext.z()) {
        currentT = tNext.y();
        voxel.y() += step.y();
        tNext.y() += tDelta.y();
    } else {
        currentT = tNext.z();
        voxel.z() += step.z();
        tNext.z() += tDelta.z();
    }

    return *this;
}

Eigen::Vector3i ForwardVoxelIterator::operator*() {
    return voxel;
}

const Eigen::Vector3i & ForwardVoxelIterator::operator*() const {
    return voxel;
}
