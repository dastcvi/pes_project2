# pes_project2

This is the repository for my solution to the second project for CU Boulder's
ECEN 5813 Principles of Embedded Software class.

The project involves three parts: a circular buffer implementation with unit
testing, an embedded UART driver, and a user application. The target hardware
is NXP's FRDM-KL25Z development board, which hosts an MKL25Z128VLK4 MCU. The
MCU is based on an ARM Cortex-M0+ running at 48 MHz.

## Directory structure

* linux/ - circular buffer and unit test source code to run on Linux
* frdm/  - embedded KDS IDE software project implementing the full application
