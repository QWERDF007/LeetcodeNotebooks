# Leetcode 题解

| :tiger:                            | :cat:                      | :dog:               | :dragon:                     |
| ---------------------------------- | -------------------------- | ------------------- | ---------------------------- |
| [数组](doc/array.md)               | [字符串](doc/str.md)       | [数学](doc/math.md) | [二叉树](doc/binary_tree.md) |
| [位运算](doc/bitwise_operation.md) | [链表](doc/linked_list.md) |                     |                              |

## build


- Windows:

  build

  ```shell
  build.bat --build --config Release --parallel
  ```

  cmake & build

  ```shell
  build.bat --build --config Release --parallel --update --cmake_extra_defines gtest_force_shared_crt=ON
  ```

  build & test

  ```shell
  build.bat --build --config Release --parallel --test
  ```

  cmake & build & test

  ```shell
  build.bat --build --config Release --parallel --update --cmake_extra_defines gtest_force_shared_crt=ON --test
  ```

- Linux:

  build
  
  ```shell
  ./build.sh --build --config Release --parallel
  ```

  cmake & build
  
  ```shell
  ./build.sh --build --config Release --parallel --update
  ```
  
  build & test
  
  ```shell
  ./build.sh --build --config Release --parallel --test
  ```
  
  cmake & build & test
  
  ```shell
  ./build.sh --build --config Release --parallel --update --test
  ```

