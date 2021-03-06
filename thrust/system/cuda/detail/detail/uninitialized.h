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

#pragma once

#include <thrust/detail/config.h>
#include <cstddef>
#include <new>

namespace thrust
{
namespace system
{
namespace cuda
{
namespace detail
{
namespace detail
{
namespace uninitialized_detail
{


template<typename T> struct alignment_of_impl;

template<typename T, std::size_t size_diff>
  struct helper
{
  static const std::size_t value = size_diff;
};

template<typename T>
  struct helper<T,0>
{
  static const std::size_t value = alignment_of_impl<T>::value;
};

template<typename T>
  struct alignment_of_impl
{
  struct big { T x; char c; };

  static const std::size_t value = helper<big, sizeof(big) - sizeof(T)>::value;
};


template<typename T>
  struct alignment_of
    : uninitialized_detail::alignment_of_impl<T>
{};


template<std::size_t Align> struct aligned_type;

// __align__ is CUDA-specific, so guard it
#if THRUST_DEVICE_COMPILER == THRUST_DEVICE_COMPILER_NVCC
// implement aligned_type with specialization because MSVC
// requires literals as arguments to declspec(align(n))
template<> struct aligned_type<1>
{
  struct __align__(1) type { };
};

template<> struct aligned_type<2>
{
  struct __align__(2) type { };
};

template<> struct aligned_type<4>
{
  struct __align__(4) type { };
};

template<> struct aligned_type<8>
{
  struct __align__(8) type { };
};

template<> struct aligned_type<16>
{
  struct __align__(16) type { };
};

template<> struct aligned_type<32>
{
  struct __align__(32) type { };
};

template<> struct aligned_type<64>
{
  struct __align__(64) type { };
};

template<> struct aligned_type<128>
{
  struct __align__(128) type { };
};

template<> struct aligned_type<256>
{
  struct __align__(256) type { };
};

template<> struct aligned_type<512>
{
  struct __align__(512) type { };
};

template<> struct aligned_type<1024>
{
  struct __align__(1024) type { };
};

template<> struct aligned_type<2048>
{
  struct __align__(2048) type { };
};

template<> struct aligned_type<4096>
{
  struct __align__(4096) type { };
};

template<> struct aligned_type<8192>
{
  struct __align__(8192) type { };
};
#else
template<std::size_t Align> struct aligned_type
{
  struct type { };
};
#endif // THRUST_DEVICE_COMPILER

template<std::size_t Len, std::size_t Align>
  struct aligned_storage
{
  union type
  {
    unsigned char data[Len];

    typename aligned_type<Align>::type align;
  };
};


} // end uninitialized_detail


template<typename T>
  class uninitialized
{
  private:
    typename uninitialized_detail::aligned_storage<
      sizeof(T),
      uninitialized_detail::alignment_of<T>::value
    >::type storage;

    __device__ __thrust_forceinline__ const T* ptr() const
    {
      return reinterpret_cast<const T*>(storage.data);
    }

    __device__ __thrust_forceinline__ T* ptr()
    {
      return reinterpret_cast<T*>(storage.data);
    }

  public:
    // copy assignment
    __device__ __thrust_forceinline__ uninitialized<T> &operator=(const T &other)
    {
      T& self = *this;
      self = other;
      return *this;
    }

    __device__ __thrust_forceinline__ T& get()
    {
      return *ptr();
    }

    __device__ __thrust_forceinline__ const T& get() const
    {
      return *ptr();
    }

    __device__ __thrust_forceinline__ operator T& ()
    {
      return get();
    }

    __device__ __thrust_forceinline__ operator const T&() const
    {
      return get();
    }

    __thrust_forceinline__ __device__ void construct()
    {
      ::new(ptr()) T();
    }

    template<typename Arg>
    __thrust_forceinline__ __device__ void construct(const Arg &a)
    {
      ::new(ptr()) T(a);
    }

    template<typename Arg1, typename Arg2>
    __thrust_forceinline__ __device__ void construct(const Arg1 &a1, const Arg2 &a2)
    {
      ::new(ptr()) T(a1,a2);
    }

    template<typename Arg1, typename Arg2, typename Arg3>
    __thrust_forceinline__ __device__ void construct(const Arg1 &a1, const Arg2 &a2, const Arg3 &a3)
    {
      ::new(ptr()) T(a1,a2,a3);
    }

    template<typename Arg1, typename Arg2, typename Arg3, typename Arg4>
    __thrust_forceinline__ __device__ void construct(const Arg1 &a1, const Arg2 &a2, const Arg3 &a3, const Arg4 &a4)
    {
      ::new(ptr()) T(a1,a2,a3,a4);
    }

    template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    __thrust_forceinline__ __device__ void construct(const Arg1 &a1, const Arg2 &a2, const Arg3 &a3, const Arg4 &a4, const Arg5 &a5)
    {
      ::new(ptr()) T(a1,a2,a3,a4,a5);
    }

    template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
    __thrust_forceinline__ __device__ void construct(const Arg1 &a1, const Arg2 &a2, const Arg3 &a3, const Arg4 &a4, const Arg5 &a5, const Arg6 &a6)
    {
      ::new(ptr()) T(a1,a2,a3,a4,a5,a6);
    }

    template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
    __thrust_forceinline__ __device__ void construct(const Arg1 &a1, const Arg2 &a2, const Arg3 &a3, const Arg4 &a4, const Arg5 &a5, const Arg6 &a6, const Arg7 &a7)
    {
      ::new(ptr()) T(a1,a2,a3,a4,a5,a6,a7);
    }

    template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
    __thrust_forceinline__ __device__ void construct(const Arg1 &a1, const Arg2 &a2, const Arg3 &a3, const Arg4 &a4, const Arg5 &a5, const Arg6 &a6, const Arg7 &a7, const Arg8 &a8)
    {
      ::new(ptr()) T(a1,a2,a3,a4,a5,a6,a7,a8);
    }

    template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
    __thrust_forceinline__ __device__ void construct(const Arg1 &a1, const Arg2 &a2, const Arg3 &a3, const Arg4 &a4, const Arg5 &a5, const Arg6 &a6, const Arg7 &a7, const Arg8 &a8, const Arg9 &a9)
    {
      ::new(ptr()) T(a1,a2,a3,a4,a5,a6,a7,a8,a9);
    }

    template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
    __thrust_forceinline__ __device__ void construct(const Arg1 &a1, const Arg2 &a2, const Arg3 &a3, const Arg4 &a4, const Arg5 &a5, const Arg6 &a6, const Arg7 &a7, const Arg8 &a8, const Arg9 &a9, const Arg10 &a10)
    {
      ::new(ptr()) T(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);
    }

    __thrust_forceinline__ __device__ void destroy()
    {
      T& self = *this;
      self.~T();
    }
};


template<typename T, std::size_t N>
  class uninitialized_array
{
  public:
    typedef T             value_type; 
    typedef T&            reference;
    typedef const T&      const_reference;
    typedef T*            pointer;
    typedef const T*      const_pointer;
    typedef pointer       iterator;
    typedef const_pointer const_iterator;
    typedef std::size_t   size_type;

    __thrust_forceinline__ __device__ iterator begin()
    {
      return data();
    }

    __thrust_forceinline__ __device__ const_iterator begin() const
    {
      return data();
    }

    __thrust_forceinline__ __device__ iterator end()
    {
      return begin() + size();
    }

    __thrust_forceinline__ __device__ const_iterator end() const
    {
      return begin() + size();
    }

    __thrust_forceinline__ __device__ const_iterator cbegin() const
    {
      return begin();
    }

    __thrust_forceinline__ __device__ const_iterator cend() const
    {
      return end();
    }

    __thrust_forceinline__ __device__ size_type size() const
    {
      return N;
    }

    __thrust_forceinline__ __device__ bool empty() const
    {
      return false;
    }

    __thrust_forceinline__ __device__ T* data()
    {
      return impl.get();
    }

    __thrust_forceinline__ __device__ const T* data() const
    {
      return impl.get();
    }

    // element access
    __thrust_forceinline__ __device__ reference operator[](size_type n)
    {
      return data()[n];
    }

    __thrust_forceinline__ __device__ const_reference operator[](size_type n) const
    {
      return data()[n];
    }

    __thrust_forceinline__ __device__ reference front()
    {
      return *data();
    }

    __thrust_forceinline__ __device__ const_reference front() const
    {
      return *data();
    }

    __thrust_forceinline__ __device__ reference back()
    {
      return data()[size() - size_type(1)];
    }

    __thrust_forceinline__ __device__ const_reference back() const
    {
      return data()[size() - size_type(1)];
    }

  private:
    uninitialized<T[N]> impl;
};


} // end detail
} // end detail
} // end cuda
} // end system
} // end thrust

