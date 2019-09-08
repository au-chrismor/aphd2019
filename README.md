# Active Pedestrian Hazard Detection (APHD) for InnovateFPGA 2019

The code in this repository forms part of our submission to the Terasic / Intel InnovateFPGA 2019 design contest.

## Synopsis

APHD is an appliance intended to alert the driver of a vehicle to the risk of pedestrian collision.  It does so through the use of multiple cameras, image recognition and learning processes.  In addition, an Intel Cyclone V FPGA device is used to accelerate processing.

## Requirements

To build this project, you will need the following components:

* Ubuntu 16.04.1 LTS or Centos 7.6.  Note that if you are using Ubuntu, the kernel version MUST NOT EXCEED 4.8

* Intel OpenCL Runtime 18.1

* Intel OpenVINO tools with FPGA Support 2019.1.094

* Terasic Cyclone 5 BSP 17.1

* gcc Compiler compatible with C++ 11

## Building the code

1.  It is best to start on a clean installation.  Most of our development and testing was carried out with Centos

2.  Follow the Terasic setup instructions, paying special attention to the versions listed.  In essence the sequence is:

2.1  Install OpenCL Runtime

2.2  Install OpenVINO

2.3  Install the Terasic BSP

2.4  Update gcc 

2.5  Compile and test the Terasic samples.  If these don't load, stop and fix any problems first!

2.6  Run "make: from the "src" directory to build the application

## Hardware setup

The application should work with cameras supported by the V4L interfaces, so most USB webcams will work.  We tested common Microsoft and Logitech cameras.  If the camera is recognised correctly it should work.

