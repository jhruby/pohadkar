#pragma once

template <class T, size_t Len>
T *begin(T val[Len])
{
   return val;
}

template <class T, size_t Len>
T *end(T val[Len])
{
   return val +  Len;
}

template <class T, size_t Len>
auto size(T val[Len]) -> size_t
{
   return Len;
}

