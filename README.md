# Dashboard for Visualizing Robot Navigation in a Map
![image](https://user-images.githubusercontent.com/23439878/204027519-331ad628-b620-46d1-a167-53a642ad86c9.png)

This repository contains the source code for a dashboard developed with Qt using C++ to help better visualize your robot navigating in a known 3x2 map. 

## Dependencies

* Qt
* QSerialPort

## Setup

1. Clone this repository to your local machine.
2. Open the project in Qt and build it.

## Usage

1. Connect your robot to your computer via a serial port.
2. Run the dashboard executable.
3. The dashboard will automatically detect the serial port and begin receiving data from the robot. The robot's position and orientation will be displayed on the dashboard in real-time.

## Files

The important files in this repository are:

* `mainwindow.h`: Contains the declaration of the `MainWindow` class, which represents the main window of the dashboard.
* `ui_mainwindow.h`: Generated by Qt, contains the definition of the `Ui::MainWindow` class, which provides access to the dashboard's user interface elements.
* `mainwindow.cpp`: Contains the implementation of the `MainWindow` class. This is where the serial communication with the robot and the updating of the dashboard are handled.

