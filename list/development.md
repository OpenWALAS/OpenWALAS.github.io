---
title: Develop about OpenWALAS
permalink: list/development.html
narrow: true
show_profile: true
layout: defaults/page
---

{% include baidu-analysis.html %}

## How to develop?

You can download the [source files](https://github.com/OpenWALAS/OpenWALAS.github.io/tree/master/src) simply. If you want, you could modify the codes. Furthermore, compile and run them freely.

## Compiling environments

  - Suggested programming platforms
    - [Eclipse](https://www.eclipse.org/downloads/) +  [GCC](http://gcc.gnu.org/) for the non-GUI of OpenWALAS.
    - [Qt Creator](https://www.qt.io/product/development-tools) for the GUI of OpenWALAS.
  - GCC (or  [MinGW](http://www.mingw.org/) on Windows) or the other C/C++ compilers
  - Dependent libraries of OpenWALAS: [gsl](http://www.gnu.org/software/gsl/), [Qt](https://www.qt.io/), [Qwt](Qwt), [openCV](https://opencv.org/)
    - non-GUI codes only depend on gsl.
    - GUI program depends on gsl, Qt, Qwt, openCV.
  - Support openMP (parallels on thread level)
    - Compiling option '-fopenmp'

## Develop forms

- The communication group will be established in the later stage.

- In the present stage, the developers could email (pycssrc@qq.com) to the project group.

- The project team is very welcome to exchange views.

## Enjoy it!

<!--//添加评论系统 gitalk-->
{% include gitalk.html %}