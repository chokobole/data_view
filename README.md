# DataView

`DataView` is similar to javascript [DataView](https://developer.mozilla.org/ko/docs/Web/JavaScript/Reference/Global_Objects/DataView). It can read or write by from `uint8` to `double`.

## Contents
- [DataView](#dataview)
  - [Contents](#contents)
  - [How to use](#how-to-use)
  - [Examples](#examples)
  - [Usages](#usages)
    - [DataView](#dataview-1)
    - [Read](#read)
    - [Write](#write)

## How to use

To use `data_view`, add the followings to your `WORKSPACE` file.

```python
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "data_view",
    sha256 = "<sha256>",
    strip_prefix = "data_view-<commit>",
    urls = [
        "https://github.com/chokobole/data_view/archive/<commit>.tar.gz",
    ],
)
```

Then, in your `BUILD` files, import and use the rules.

```python
load("@data_view//bazel:data_view_cc.bzl", "data_view_copts")

cc_library(
    name = "...",
    copts = data_view_copts(),
    deps = [
      "@data_view",
    ]
)
```

## Examples

Build example.

```bash
bazel run //examples:example
```

```c++
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
```

## Usages

### DataView

If you want to just read bytes, then use `ConstDataView`. If you want to modify bytes, then use `DataView`.

### Read

Signature of `Read` is like below.

```c++
// Returns true if succeeded to read. (offset + sizeof(T) <= |length_|)
template <typename T>
bool Read(size_t offset, T* value, bool little_endian) const;
```

* `offset`: byte offset to read from.
* `value`
* `little_endian`: If set true, read as little endian, Otherwise read as big endian.

For example,

```c++
data_view::ConstDataView data_view;
uint16_t v;
data_view.Read(0, &v, true);
```

### Write

Signature of `Write` is like below.

```c++
// Returns true if succeeded to write. (offset + sizeof(T) <= |length_|)
template <typename T>
bool Write(size_t offset, T value, bool little_endian);
```

* `offset`: byte offset to write to.
* `value`
* `little_endian`: If set true, write as little endian, Otherwise write as big endian.

For example,

```c++
char buf[16] = {0,};
size_t buf_len = sizeof(buf);
data_view::DataView data_view(buf, buf_len);
data_view.Write(0, 127, true);
```