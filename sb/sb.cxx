#include <cstdio>
#include <vector>
#include <list>
#include <string>
#include "Utils.h"
#include <array>

int main()
{
  std::vector<int> a {4, 5, 6};
  double b[] = {7, 8, 9};
  std::list<std::string> c {"a", "b", "c"};
  std::array<float,3> d = {9.9, 9.8, 9.7};
  for (auto tup : mAIDA::zip(a, b, c, a, d))
    {
      int x, w;
      double y, k;
      std::string z;
      boost::tie(x, y, z, w, k) = tup;
      printf("%d %g %s %d %f\n", x, y, z.c_str(), w, k);
    }
}
