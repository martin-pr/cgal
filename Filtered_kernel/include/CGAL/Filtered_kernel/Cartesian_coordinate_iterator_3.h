// Copyright (c) 2006  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 3 of the License,
// or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
// SPDX-License-Identifier: LGPL-3.0+
//
//
// Author(s)     : Andreas Fabri, Sylvain Pion

#ifndef CGAL_CARTESIAN_COORDINATE_ITERATOR_3_H
#define CGAL_CARTESIAN_COORDINATE_ITERATOR_3_H

#include <cstddef>
#include <iterator>
#include <boost/variant.hpp>

namespace CGAL {

// This class should go away.
// It is now only used by the Filtered_kernel.
// It allows to iterate over the coordinates of both a Point_3 and a Vector_3,
// using a boost::variant, as the iterator types are the same at the kernel level.

template <class K>
class Cartesian_coordinate_iterator_3
{
  typedef typename K::Point_3 P;
  typedef typename K::Vector_3 V;
  boost::variant<const P*, const V*> var;
  int index;
  typedef Cartesian_coordinate_iterator_3<K> Self;

public:

  typedef typename K::FT FT;

  typedef std::random_access_iterator_tag iterator_category;
  typedef FT                              value_type;
  typedef int                             difference_type;
  typedef const value_type&               reference;
  typedef const value_type*               pointer;

  Cartesian_coordinate_iterator_3()
    : var((const P*) nullptr), index(0) {}

  Cartesian_coordinate_iterator_3(const P *const p, int _index = 0)
    : var(p), index(_index) {}

  Cartesian_coordinate_iterator_3(const V *const v, int _index = 0)
    : var(v), index(_index) {}

  const FT
  operator*() const {
    if (const P* const* p = boost::get<const P*>(&var))
      return (*p)->cartesian(index);
    const V* const* v = boost::get<const V*>(&var);
    CGAL_assertion(v != 0);
    return (*v)->cartesian(index);
  }

  Self&  operator++() {
    index++;
    return *this;
  }

  Self&
  operator--() {
    index--;
    return *this;
  }

  Self
  operator++(int) {
    Self tmp(*this);
    ++(*this);
    return tmp;
  }

  Self
  operator--(int) {
    Self tmp(*this);
    --(*this);
    return tmp;
  }

  Self&
  operator+=(difference_type i) {
    index+=i;
    return *this;
  }

  Self&
  operator-=(difference_type i) {
    index -= i;
    return *this;
  }

  Self
  operator+(difference_type i) const {
    Self tmp=*this;
    return tmp += i;
  }

  Self operator-(difference_type i) const {
    Self tmp=*this;
    return tmp -= i;
  }

  difference_type
  operator-(const Self& x) const {
    CGAL_kernel_assertion(var == x.var);
    return index - x.index;
  }

  reference operator[](difference_type i) const {
    return *(*this + i);
  }

  bool operator==(const Self& x) const {
    return (var == x.var) && (index == x.index) ;
  }

  bool operator!=(const Self& x) const {
    return ! (*this==x);
  }

  bool operator<(const Self& x) const
  {
    return (x - *this) > 0;
  }

};

} //namespace CGAL

#endif // CGAL_CARTESIAN_COORDINATE_ITERATOR_3_H
