# Multimedia System on MCB1768

## Abstract
This project utilizes the NXP MCB1768 development board, which features an ARM Cortex-M3 processor, to implement a multimedia system. The system integrates an 8-LED display, an LCD screen, an MP3 player (volume controlled by a potentiometer), and an interactive user interface with three main functionalities: an MP3 audio player, a Mario-style game, and a photo gallery. The project emphasizes embedded systems programming, real-time task handling, and user experience design.

---

## Overview

### Features
- **Main Menu**:
  - Provides a user-friendly interface to select among three functionalities using the joystick.
- **MP3 Player**:
  - Plays audio via USB Audio Class.
  - Volume control through an onboard potentiometer.
  - Interrupt-driven and USB-enabled for efficient audio streaming.
- **Mario-Style Game**:
  - A side-scrolling obstacle game.
  - Features player character movement (left, right, jump) and collision detection.
  - Includes multiple levels with increasing difficulty.
- **Photo Gallery**:
  - Displays preloaded images on the LCD screen.
  - Allows navigation between images using joystick controls.

---

### Hardware Components
- **MCB1768 Board**:
  - ARM Cortex-M3 microcontroller.
  - 8 LEDs for status indication.
  - LCD display for graphical output.
  - Integrated joystick for user input.
  - Onboard potentiometer for analog input.

---

### Software Architecture

#### Core Modules
- **Main Controller (`main.c`)**:
  - Manages menu navigation and high-level task switching between modules.
- **Game Logic (`game_logic.c`)**:
  - Implements gameplay mechanics, character control, and obstacle interaction.
- **Audio Module (`usbdmain.c`)**:
  - Manages MP3 playback using USB Audio Class specifications.
  - Incorporates potentiometer-based volume control.
- **Photo Viewer (`photo_viewer.c`)**:
  - Handles image rendering and navigation.

#### Middleware and APIs
- **CMSIS-RTOS**: Provides a real-time operating system foundation.
- **GLCD Library**: Manages LCD operations, including text rendering and graphical displays.
- **USB Stack**: Supports audio data streaming and USB communication.
- **Joystick Input (`KBD.h`)**: Processes joystick interactions.

---

## Technologies and Methodologies

### Technologies
- **ARM Cortex-M3 Microcontroller**:
  - At the core of the MCB1768 board, providing efficient and low-power computation.
- **Real-Time Operating System (RTOS)**:
  - Enables multitasking and priority-based scheduling.
- **USB Audio Class**:
  - Used for MP3 player functionality.
- **Graphics LCD (GLCD)**:
  - Provides graphical rendering for the game and photo viewer.
- **Analog-to-Digital Conversion (ADC)**:
  - Used for potentiometer-based volume control.

### Methodologies
- **Interrupt-Driven Programming**:
  - Ensures responsiveness to joystick inputs and real-time audio processing.
- **State Machine Design**:
  - Used in the game logic to manage states like running, retrying, or exiting the game.
- **Modular Programming**:
  - Separation of concerns into distinct modules for easier maintainability and scalability.
- **Polling and Debouncing**:
  - Handles joystick input for smooth navigation and gameplay.

---

## Summary
The Multimedia System on MCB1768 demonstrates the capabilities of embedded systems in handling interactive multimedia tasks. With a modular design and efficient use of hardware resources, the project showcases integration across user interface design, audio processing, and graphical rendering. The system provides a cohesive and engaging user experience, highlighting real-world applications of embedded programming and system-level design.
