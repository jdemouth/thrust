/*
 *  Copyright 2008-2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


/*! \file replace.inl
 *  \brief Inline file for replace.h.
 */

#include <thrust/detail/config.h>
#include <thrust/replace.h>
#include <thrust/iterator/iterator_traits.h>
#include <thrust/system/detail/generic/select_system.h>
#include <thrust/system/detail/generic/replace.h>
#include <thrust/system/detail/adl/replace.h>

namespace thrust
{

template<typename InputIterator, typename OutputIterator, typename Predicate, typename T>
  OutputIterator replace_copy_if(InputIterator first, InputIterator last,
                                 OutputIterator result,
                                 Predicate pred,
                                 const T &new_value)
{
  using thrust::system::detail::generic::select_system;
  using thrust::system::detail::generic::replace_copy_if;

  typedef typename thrust::iterator_system<InputIterator>::type  system1;
  typedef typename thrust::iterator_system<OutputIterator>::type system2;

  return replace_copy_if(select_system(system1(),system2()), first, last, result, pred, new_value);
} // end replace_copy_if()

template<typename InputIterator1, typename InputIterator2, typename OutputIterator, typename Predicate, typename T>
  OutputIterator replace_copy_if(InputIterator1 first, InputIterator1 last,
                                 InputIterator2 stencil,
                                 OutputIterator result,
                                 Predicate pred,
                                 const T &new_value)
{
  using thrust::system::detail::generic::select_system;
  using thrust::system::detail::generic::replace_copy_if;

  typedef typename thrust::iterator_system<InputIterator1>::type system1;
  typedef typename thrust::iterator_system<InputIterator2>::type system2;
  typedef typename thrust::iterator_system<OutputIterator>::type system3;

  return replace_copy_if(select_system(system1(),system2(),system3()), first, last, stencil, result, pred, new_value);
} // end replace_copy_if()


template<typename InputIterator, typename OutputIterator, typename T>
  OutputIterator replace_copy(InputIterator first, InputIterator last,
                              OutputIterator result,
                              const T &old_value,
                              const T &new_value)
{
  using thrust::system::detail::generic::select_system;
  using thrust::system::detail::generic::replace_copy;

  typedef typename thrust::iterator_system<InputIterator>::type  system1;
  typedef typename thrust::iterator_system<OutputIterator>::type system2;

  return replace_copy(select_system(system1(),system2()), first, last, result, old_value, new_value);
} // end replace_copy()

template<typename ForwardIterator, typename Predicate, typename T>
  void replace_if(ForwardIterator first, ForwardIterator last,
                  Predicate pred,
                  const T &new_value)
{
  using thrust::system::detail::generic::select_system;
  using thrust::system::detail::generic::replace_if;

  typedef typename thrust::iterator_system<ForwardIterator>::type system;

  return replace_if(select_system(system()), first, last, pred, new_value);
} // end replace_if()

template<typename ForwardIterator, typename InputIterator, typename Predicate, typename T>
  void replace_if(ForwardIterator first, ForwardIterator last,
                  InputIterator stencil,
                  Predicate pred,
                  const T &new_value)
{
  using thrust::system::detail::generic::select_system;
  using thrust::system::detail::generic::replace_if;

  typedef typename thrust::iterator_system<ForwardIterator>::type system1;
  typedef typename thrust::iterator_system<InputIterator>::type   system2;

  return replace_if(select_system(system1(),system2()), first, last, stencil, pred, new_value);
} // end replace_if()

template<typename ForwardIterator, typename T>
  void replace(ForwardIterator first, ForwardIterator last,
               const T &old_value,
               const T &new_value)
{
  using thrust::system::detail::generic::select_system;
  using thrust::system::detail::generic::replace;

  typedef typename thrust::iterator_system<ForwardIterator>::type system;

  return replace(select_system(system()), first, last, old_value, new_value);
} // end replace()

} // end namespace thrust

