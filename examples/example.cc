#include <iostream>

#include "data_view/data_view.h"

int main() {
  const char buf[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  size_t buf_len = sizeof(buf);
  data_view::ConstDataView data_view(buf, buf_len);

  uint16_t v;
  data_view.Read(0, &v, true);
  std::cout << v << std::endl;  // 256
  data_view.Read(0, &v, false);
  std::cout << v << std::endl;  // 1

  return 0;
}