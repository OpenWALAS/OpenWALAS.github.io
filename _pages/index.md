---
layout: defaults/page
permalink: index.html
narrow: true
title: Welcome to OpenWALAS
---

{% include baidu-analysis.html %}

<head>
  <meta name="baidu-site-verification" content="Ivf7ppggHc" />
  <title>My title</title>
</head>
One new version is released in **January 20th, 2022**.

{% include busuanzi_statistics.html %}

## What is it?

![main-UI](picture\main-UI.png)

![multi-model](picture\multi-model.png)

{% include components/intro.md %}

OpenWALAS program suit  contains the functions of automatic meshing of ship hulls, cut-off hull mesh, straight beam modal analysis, characteristic calculation of transverse section, as well as 3D model display and 2D curve drawing. The software suit contains the GUI program OpenWALAS and five non-GUI core programs: OpenWALAS_PRE, OpenWALAS_FSCM, OpenWALAS_TDGF, OpenWALAS _IORM and OpenWALAS _TIME_RESP.

![main-UI](picture\frame diagram.png)

- OpenWALAS_PRE program for pre-processing, is mainly used to calculate the mode of wetted floating structures from dry modal informtions, in which the structural FEM model is 3D FEM model or beam model.
- 3D calculation and analysis function in time domain: OpenWALAS_TDGF (time domain green's function method, called 'TDGF') and OpenWALAS_IORM（Inner and outer regions matching of Rankine source, called 'IORM') are the core program. The hydrodynamic coefficients are mainly calculated, including impulse response function of radiation forces, impulse response function of diffraction exciting forces, impulse response function of incident exciting forces, impulse response function of sectional wave loads, etc.
- 3D calculation and analysis function in frequency domain: OpenWALAS_FSCM（forward speed correction method in frequency domain, called 'FSCM')  is based on the forward speed correction assumption (i.e., low speed and high frequency)  boundary element method and Morison's equation in three-dimensional frequency domain,  to assess the influence of forward  speed. The hydrodynamic coefficients (such as incident wave exciting force, diffraction wave exciting force, added mass and added damping), motions and wave loads, hydroelastic modal responses, wetted-surface pressures, wave height distributions of surrounding fluid fields, and second-order forces are mainly calculated. It also has the function of eliminating irregular frequency by adding a rigid cover on the inner free surface using the extended integral equation. There are three methods (near-field pressure integral method, middle-field control-surface method and far-field momentum method) are proposed to calculate the second-order forces, including rigid modes and elastic modes.
- OpenWALAS_TIME_RESP is a calculating program of elastic modal responses and wave loads in time domain, which includes the functions of nonlinear incident force, hydrostatic restoring force, slamming force, Morison's equation, as well as indirect time-domain method.

## How to use it

This web site supplies the [*executable programs* ](https://github.com/OpenWALAS/OpenWALAS.github.io/releases) and [*documentations*](https://github.com/OpenWALAS/OpenWALAS.github.io/tree/master/doc) of OpenWALAS and also provides [examples](https://github.com/OpenWALAS/OpenWALAS.github.io/tree/master/example) of how you can use it.

### - Two ways for running

- First way: run OpenWALAS wit GUI to input parameters, calculate and post-process, as well as everything else.

- Second way: command line

  - (a) 3D frequency-domain module: OpenWALAS_PRE -> OpenWALAS_FSCM.
  - (b)  3D indirect time-domain module: OpenWALAS_PRE -> OpenWALAS_FSCM -> OpenWALAS_TIME_RESP.
  - (c)  3D direct time-domain module: OpenWALAS_PRE -> OpenWALAS_TDGF or OpenWALAS_IORM -> OpenWALAS_ TIME_RESP.

### - Installation

- Designed for Linux, Windows and macOS operation system.
- -***Windows***: double click  ['OpenWALAS' ](https://github.com/OpenWALAS/OpenWALAS.github.io/releases/download/V1.0.0/OpenWALAS1.0_X64_64BITS.exe) directly  to install the software.
- -***Linux***: double click '[OpenWALAS](https://github.com/OpenWALAS/OpenWALAS.github.io/releases/download/V1.0.0/OpenWALAS1.0_X64_64BITS.deb)' directly to install the software or compile from the source files.
- -***macOS***: double click 'OpenWALAS' directly to install the software.
- *The other versions of the executive programs* [*click here* ](https://github.com/OpenWALAS/OpenWALAS.github.io/releases).

### - Documentation

[The documentations](doc/OpenWALAS V1.0 User Manual.pdf ) cover the basic information of installing and using them.

### - Examples

Here's some [examples](https://github.com/OpenWALAS/OpenWALAS.github.io/tree/master/example) .

## Licensing & Copyright

OpenWALAS is distributed under the terms of the [GNU General Public License](http://www.gnu.org/licenses/gpl.html) (GPL).

- Some answers to common questions about the license:

  -  *If I write an application which uses OpenWALAS, am I forced to distribute that application?*
     No. The license gives you the option to distribute your application if you want to. You do not have to exercise this option in the license.
  -  *If I wanted to distribute an application which uses OpenWALAS, what license would I need to use?*
     The GNU General Public License (GPL).

- The bottom line for commercial users:

  - *OpenWALAS can be used internally ('in-house') without restriction, but only redistributed in other software that is under the GNU GPL*.

The author always respects the intellectual property rights and labor achievements, and supports the behavior of sharing software and related documents. Any organization and individual can freely share the program and related documentation within a limited scope, but the following principles should be followed.

- (a) The projects encourage relevant researchers and authors to carry out joint-research, utilize this program, and further improve the program, so as to contribute to the technology development of global ship and ocean engineering;
- (b) Copyrights of the software and documentation belongs to the original author;
- (c) This program shall not be used for any commercial purpose without the permission of the original author, otherwise it will be deemed as infringement;
- (d) The source and the original author must be cited, if the software and the contents of this document are reprinted;
- (e) For those who do not abide by this statement or illegally use this software and the contents of this document, the rights are reserved according to law.

作者一贯尊重知识产权和劳动成果，并支持分享软件和相关文档的行为，在有限范围内可自由分享本程序和相关文档，但需遵循以下原则：

- *1、鼓励相关科研人员与作者开展联合研究，发挥本程序作用，并进一步完善程序，为全球船舶与海洋工程技术发展做贡献;*
- *2、程序和文档的版权归原作者所有；*
- *3、未经原作者允许不得将本程序用于**任何商业目的**，否则将视为侵权；*
- *4、转载或者引用本程序和本文内容请**注明来源及原作者**；*
- *5、对于不遵守此声明或者其他违法使用本程序和本文内容者，本人依法保留追究权等.*

## Release History

- **OpenWALAS-1.0** was released in January 2022.

## References


- [1] Wu, Y.S., 1984, Hydroelasticity of floating bodies. Ph.D., Thesis, Brunel University, U.K. 
- [2] Yang P, Gu XK, Tian C, Cheng XM, Ding J. 2014. [Numerical Study of 3D Pulsating Source Green Function of Finite Water Depth](doc/Numerical Study of 3D Pulsating Source Green Function of Finite Water Depth.pdf), Proceedings of the 33th International Conference on Ocean, Offshore and Arctic Engineering (OMAE), San Francisco, California, USA, June.
- [3] Yang, P., 2016. [3D Nonlinear Hydro-elastic Response Study of Ships in Time Domain (Doctoral thesis)](doc/3D Nonlinear Hydro-elastic Response Study of Ships in Time Domain-Ph.D thesis.pdf). China Ship Scientific Research Center, Wuxi, China. (In Chinese).
- [4] Yang P, Ye MX, Li JC, et al. 2018. [Mathematical derivation of simplified calculation of symmetrical green function](doc/Mathematical derivation of simplified calculation of symmetrical green function.pdf). Chinese Journal of Ship Research, 13 (Supp 1): 22-28.
- [5] Yang P，Kou GY，Zhu XK, et al. 2019. [Numerical calculation method for wave loads of floating structures in shallow water](doc/Numerical calculation method for wave loads of floating structures in shallow water.pdf). Chinese Journal of Ship Research, 14(1): 19-26.
- [6] Yang P, Li JR, Gu XK, Wu DW. 2019. [Application of the 3D time-domain Green's function for finite water depth in hydroelastic mechanics](Application of the 3D time-domain Green's function for fnite water depth-OE.pdf). Ocean Engineering, 189. 
- [7] Yang P, Li JR, Wu DW, Zhang W. 2020. [Irregular Frequency Elimination of Three-Dimensional Hydroelasticity in Frequency Domain](doc/Irregular frequency elimination of three-dimensional hydroelasticity in frequency domain -Peng Yang.pdf). Ocean Engineering, 196.

<hr />

