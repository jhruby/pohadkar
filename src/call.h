#pragma once

template <class F, class... T>
auto for_every(F && fun, T&... devices)
{
   bool z[] = { (fun(devices), true)... };
   (void)z;
}