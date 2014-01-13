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
#ifndef VOXEL_ITERATOR_HPP
#define VOXEL_ITERATOR_HPP

#include <eigen3/Eigen/Core>


/**
 * An iterator for a 3D grid of voxels.
 *
 * The iterator traverses all voxels along a specified direction starting from
 * a given position.
 */
class ForwardVoxelIterator {
public:
    /**
     * Constructs a default voxel iterator.
     *
     * Voxels are assumed to be of unit size, and the iterator is initially
     * positioned at the origin headed in the <1, 1, 1> direction.
     */
    ForwardVoxelIterator();

    /**
     * Constructs a voxel iterator.
     *
     * @param size  the size of each voxel
     * @param pos  the initial position
     * @param dir  the direction in which to iterate
     */
    ForwardVoxelIterator(const Eigen::Vector3d &size,
                         const Eigen::Vector3d &pos,
                         const Eigen::Vector3d &dir);

    ForwardVoxelIterator(const ForwardVoxelIterator &) = default;
    ForwardVoxelIterator(ForwardVoxelIterator &&) = default;
    ForwardVoxelIterator & operator=(const ForwardVoxelIterator &) = default;

    // Post-increment
    ForwardVoxelIterator operator++();

    // Dereferencing
    Eigen::Vector3i operator*();
    const Eigen::Vector3i & operator*() const;

    /// @return the current t value (distance to initial point)
    double t() const { return currentT; }

private:
    /// The size of a voxel
    const Eigen::Vector3d size;

    /// The direction in which we will travel
    const Eigen::Vector3d dir;

    /// The integral steps in each direction when we iterate (either 1 or -1)
    const Eigen::Vector3i step;

    /// The t value which moves us from one voxel to the next
    const Eigen::Vector3d tDelta;

    /// The t value which will get us to the next voxel
    Eigen::Vector3d tNext;

    /// The integer indices for the current voxel
    Eigen::Vector3i voxel;

    /// The t value representing the current point
    double currentT;
};


#endif // VOXEL_ITERATOR_HPP
