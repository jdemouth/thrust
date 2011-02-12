/*
 *  Copyright 2008-2011 NVIDIA Corporation
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

#pragma once

#include <thrust/detail/config.h>
#include <thrust/detail/functional/actor.h>
#include <thrust/detail/functional/argument.h>

namespace thrust
{
namespace detail
{

template<unsigned int i>
struct placeholder
  : thrust::detail::actor<thrust::detail::argument<i> >
{
  __host__ __device__
  inline placeholder(void)
    : thrust::detail::actor<thrust::detail::argument<i> >()
  {}
};

} // end detail
} // end thrust
