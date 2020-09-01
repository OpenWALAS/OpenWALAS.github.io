---
layout: defaults/page
permalink: index.html
narrow: true
title: Welcome to openWALAS
---

## What is it?

![main-UI](picture\main-UI.png)

{% include components/intro.md %}

openWALAS程序包括船体网格自动划分、船体网格切分、直梁模态分析、横剖面特性计算等功能，以及三维模型显示和二维曲线绘制功能。

The software suit contains the GUI program openWALAS and five non-GUI core programs: openWALAS_PRE, openWALAS_FSCM, openWALAS_TDGF, openWALAS _IORM and openWALAS _TIME_RESP.

(1)  openWALAS_PRE为数据预处理程序，主要用于通过干面元及其振型信息来计算湿模型的振型，其中结构有限元模型为3D FEM模型或梁模型。

(2)  三维时域计算分析功能：openWALAS_TDGF（时域格林函数法，‘TDGF’）和openWALAS_IORM（内外场匹配的Rankine源法，‘IORM’）为核心计算程序，主要计算水动力系数，包括辐射势脉冲响应函数、绕射势脉冲响应函数、入射势脉冲响应函数、波浪载荷脉冲响应函数等。

(3)  三维频域计算分析功能：openWALAS_FSCM（三维频域航速修正方法，‘FSCM’），采用三维频域航速修正假设（即低速、高频）计及航速影响，主要计算入射力、绕射力、附加质量和附加阻尼等动力系数、运动和波浪载荷、水弹性模态响应、湿表面压力、周围流场波高分布。并具备在内部自由面添加刚盖消除不规则频率功能（即扩展积分方程）。

(4)  openWALAS_TIME_RESP为时域模态响应计算程序，里面包含了间接时域、非线性入射力、静水恢复力、砰击力、弹性模态时域响应和波浪载荷等计算功能。

## How to use it

This web site is the executable program and documentation for openWALAS and also provides examples of how you can use it.

### - Two ways for running

  （一）  方式一：运行openWALAS界面完成输入参数设置、计算和后处理绘图，在界面中完成一切操作。

  （二）  方式二：手动调用

    (1)  三维频域模块：openWALAS_PRE-> openWALAS_FSCM。
    (2)  三维间接时域模块：openWALAS_PRE-> openWALAS_FSCM -> openWALAS_TIME_RESP。
    (3)  三维直接时域模块：openWALAS_PRE -> openWALAS_TDGF or openWALAS_IORM -> openWALAS_ TIME_RESP。

### - Installation

- Designed for Linux, Windows and macOS operation system.
- -Windows: direct double click ['openWALAS.msi' ](bin/openWALAS2020_X86_64bits.msi) to install the software.
- -Linux: direct double click 'openWALAS.deb' to install the software or compile from the source files.
- -macOS: direct double click 'openWALAS.DWG' to install the software.

### - Documents

[The documentation](doc/openWALAS V1.0 User Manual.pdf ) covers the basics of installing and using it.

### - Examples

Here's some [examples](https://github.com/openWALAS/openWALAS.github.io/tree/master/example) .

## Licensing & Copyright

OpenWALAS is distributed under the terms of the [GNU General Public License](http://www.gnu.org/licenses/gpl.html) (GPL).

I. Some answers to common questions about the license:

> *If I write an application which uses GSL, am I forced to distribute that application?*
> No. The license gives you the option to distribute your application if you want to. You do not have to exercise this option in the license.
>
> *If I wanted to distribute an application which uses GSL, what license would I need to use?*
> The GNU General Public License (GPL).

II. The bottom line for commercial users:

> *GSL can be used internally ("in-house") without restriction, but only redistributed in other software that is under the GNU GPL.*

作者一贯尊重知识产权和劳动成果，并支持分享软件和相关文档的行为，在有限范围内可自由分享本程序和相关文档，但需遵循以下原则：

*1、程序和文档的版权归原作者所有；*

*2、未经原作者允许不得将本程序用于**任何商业目的**，否则将视为侵权；*

*3、转载或者引用本程序和本文内容请**注明来源及原作者**；*

*4、对于不遵守此声明或者其他违法使用本程序和本文内容者，本人依法保留追究权等；*

*5、鼓励相关科研人员与作者开展联合研究，发挥本程序作用，并进一步完善程序。*

## Release History

**openWALAS-1.0** was released in September 2020.

<hr />


