# Preparing the OpenCL / OpenVINO environment

## Introduction

This project relies on the Intel OpenVINO toolkit, and the setup on Linux (especially when using FPGA support) is not trivial.  This document summarises the various installation instructions and steps I took to make it all work.

My development machine is actually quite low-spec because I am trying to replicate what a production model of the detector would run on.  It is a 3.1GHz Celeron G4900 with 4GB RAM.  While it does work well with the final code, the build process is rather painful.  Just be patient.

## Pre-Requisites

Maybe this is obvious, or maybe it's not but Intel's OpenCL drivers which are required to support OpenVINO only support Intel Processors (with the exception of the ARM CPU on a Raspberry Pi), so you need an Intel CPU with embedded graphics.  This means most modern Intel CPU's are OK; especially the current G and J Series Celeron, Gen 6+ Core, and a lot of Xeon processors.

If you have an AMD processor, you are in all likelihood on your own.  Sorry

The build requirements are not well aligned, you will need *both* versions 2 and 3 of cmake

*Warning* This process updates your build tools to support gcc 7, because I could not get things to compile with the stock gcc 4.  If this is going to be a problem for you, plan ahead now.

The steps to install the pre-requisites are:

$ sudo yum install -y epel-release centos-release-scl 

$ sudo yum install -y cmake cmake3 git devtoolset-7-gcc-c++ patch bison flex ninja-build

## Install the Intel components

Follow the Terasic installation guide, but in summary:

1.  Install the openCL runtime to /opt/intel/opencl
2.  Install the OpenVINO toolkit to /opt/intel/2019R1
3.  Install the Quartus Programmer to /opt/altera

You will get a warning that the Intel GPU OpenCL driver is not installed.  Until recently you pretty much had to build it, but in /opt/intel/2019R1/openvino/install_dependencies is a script called "install_NEO_OCL_driver.sh".  This will take care of that problem for you.

## Install the Terasic components

1.  Install the Terasic BSP and flash the FPGA board
2.  Install and build the samples
