# Integrate Grove - RGB LED Matrix w/Driver with MangoH and Grove IoT Exapansion Card

This project demonstrates how to integrate Grove - RGB LED Matrix w/Driver with MangoH and Grove IoT Exapansion Card.


## Prerequisites

* A mangOH Red board.
* A Grove IoT Expansion card.
* Grove - RGB LED Matrix w/Driver: See detail information on wiki page: http://wiki.seeedstudio.com/Grove-RGB_LED_Matrix_w-Driver/

Grove - RGB LED Matrix w/Driver
------------------
8x8 RGB LED Matrix is awesome for simple image display, 64 pixel leds and 255 colors for each pixel means almost infinite possibilities  

Legato Application
------------------
There are 3 legato applications:
* ```ledmatrixService```: provides api for pushing data like number, string, image to Grove - Red LED Matrix.
* ```ledmatrixDatahub```: push data to datahub.
* ```ledmatrixDisplay```: register for notification of value updates, create observation (filter) for Grove - RGB LED Matrix w/Driver.

## Setup
1. Insert Grove IoT Expansion card into Mangoh Red
1. Jump 5V Pin on Grove IoT Card
1. Grove - RGB LED Matrix w/Driver with I2C connector on Grove card



## How To Run

1. Build the ledmatrixService app by running ```mkapp -t wp85 ledmatrixService.adef``` in datahubLedMatrix directory.
1. Run ```instapp ledmatrixService.wp85.update 192.168.2.2``` to install the app.
1. Build the ledmatrixDatahub app by running ```mkapp -t wp85 ledmatrixDatahub.adef``` in datahubLedMatrix directory.
1. Run ```instapp ledmatrixDatahub.wp85.update 192.168.2.2``` to install the app.
1. Build the ledmatrixDisplay app by running ```mkapp -t wp85 ledmatrixDisplay.adef``` in datahubLedMatrix directory.
1. Run ```instapp ledmatrixDisplay.wp85.update 192.168.2.2``` to install the app.
