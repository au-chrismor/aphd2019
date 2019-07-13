# Preparing the OpenCL / OpenVINO environment

## Introduction

This project relies on the Intel OpenVINO toolkit, and the setup on Linux (especially when using FPGA support) is not trivial.  This document summarises the various installation instructions and steps I took to make it all work.

The reference for these instructions are located at https://github.com/intel/intel-graphics-compiler/blob/master/documentation/build_ubuntu.md I did my build on CentOS 7 in spite of the name of the instructions.

My development machine is actually quite low-spec because I am trying to replicate what a production model of the detector would run on.  It is a 3.1GHz Celeron G4900 with 4GB RAM.  While it does work well with the final code, the build process is rather painful.  Just be patient.

## Pre-Requisites

Maybe this is obvious, or maybe it's not but Intel's OpenCL drivers which are required to support OpenVINO only support Intel Processors (with the exception of the ARM CPU on a Raspberry Pi), so you need an Intel CPU with embedded graphics.  This means most modern Intel CPU's are OK; especially the current G and J Series Celeron, Gen 6+ Core, and a lot of Xeon processors.

If you have an AMD processor, you are in all likelihood on your own.  Sorry

The build requirements are not well aligned, you will need *both* versions 2 and 3 of cmake

*Warning* This process updates your build tools to support gcc 7, because I could not get things to compile with the stock gcc 4.  If this is going to be a problem for you, plan ahead now.

The steps to install the pre-requisites are:

$ sudo yum install -y epel-release centos-release-scl

$ sudo yum install -y cmake cmake3 git devtoolset-7-gcc-c++ patch bison flex

## Get the code

You need to create a build workspace to bring together all the bits.

$ mkdir opencl_env

$ cd opencl_env

$ git clone -b release_80 https://github.com/llvm-mirror/llvm llvm_source

$ git clone -b release_80 https://github.com/llvm-mirror/clang llvm_source/tools/clang

$ git clone -b ocl-open-80 https://github.com/intel/opencl-clang llvm_source/projects/opencl-clang

$ git clone -b llvm_release_80 https://github.com/KhronosGroup/SPIRV-LLVM-Translator llvm_source/projects/llvm-spirv

$ git clone https://github.com/intel/llvm-patches llvm_patches

$ git clone https://github.com/intel/intel-graphics-compiler igc

$ git clone git@github.com:intel/gmmlib.git gmmlib

$ mkdir build

At the end of this, you should have a layout which looks like:

opencl_env
    | - igc
    | - llvm_patches
    | - llvm_source
         | - projects
                | - clang
                | - llvm-spirv
                | - opencl-clang

## Build GMMLib

We need this first so that OpenCL works:

$ mkdir gmmlib/build

$ cd gmmlib/build

$ cmake -DCMAKE_BUILD_TYPE= Release -DARCH= 64 ..

$ make -j`nproc`

$ sudo make install

## Build IGC (Intel Graphics Compiler)

#### Remember: if something breaks, remove the build directory and re-create it before running cmake again.

$ cd {build_root}/build

$ scl enable devtoolset-7 bash

$ cmake3 -DIGC_OPTION__FORCE_SYSTEM_LLVM=FALSE ../igc/IGC

Now build it with:

make -j`nproc`

## Install everything

It's probably taken quite a while to get to this point, so here goes:

$ sudo make install

## Verifying these steps

One thing I really hate is to follow a walk-through only to discover that there are typos or things which just plain don't work.

As a result, I take the following steps with instruction guides like these:

1.  Document each step
2.  Review and simply.  Remove duplicates, unnecessary components, etc
3.  Step-by-step repeat on a new system or VM
4.  Fix any problems, and repeat from step 3
5.  Bask in the satisfaction of instructions which actually work.

