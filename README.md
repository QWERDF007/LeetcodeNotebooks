# Leetcode 题解

| :tiger:              | :cat: | :dog: | :dragon: | :snake: |
| -------------------- | ----- | ----- | -------- | ------- |
| [数组](doc/array.md) |       |       |          |         |

## build


- Windows:

  build

  ```shell
  build.bat --build --config Release --parallel --update --cmake_extra_defines gtest_force_shared_crt=ON
  ```

  build & test

  ```shell
  build.bat --build --config Release --parallel --update --cmake_extra_defines gtest_force_shared_crt=ON --test
  ```

- Linux:

  ```shell
  ./build.sh --build --config Release --parallel --update
  ```

  build & test

  ```shell
  ./build.sh --build --config Release --parallel --update --test
  ```

