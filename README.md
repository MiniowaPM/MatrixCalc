# 🧮 MatrixCalc

**A cross-platform graphical matrix calculator built with C++ and wxWidgets.**

![C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![wxWidgets](https://img.shields.io/badge/GUI-wxWidgets-39A849?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-In_Development-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

## 🚀 About The Project

**MatrixCalc** is a desktop application designed to perform mathematical operations on matrices quickly and intuitively. By leveraging the **wxWidgets** framework, the project aims to provide a native-feeling graphical user interface (GUI) across different operating systems (Windows, macOS, Linux) while keeping the computational backend lightning-fast in C++.

Whether you are a student solving linear algebra problems or a developer needing quick matrix transformations, MatrixCalc provides the essential tools in a clean windowed environment.

*Note: The project is currently undergoing configuration and structural improvements. The core code is available, and build system enhancements are on the roadmap.*

## ✨ Key Features (Planned & Implemented)

### 🧮 Core Matrix Operations
* **Basic Arithmetic:** Matrix Addition, Subtraction, and Multiplication.
* **Scalar Operations:** Multiply or divide a matrix by a scalar value.
* **Advanced Calculations:**
  * Determinant calculation.
  * Matrix Transposition.
  * Matrix Inversion.

### 🖥️ Graphical Interface
* **Dynamic Grids:** Input matrices of custom dimensions using a grid-based UI.
* **Native Look & Feel:** Utilizes wxWidgets to ensure the application looks native on your specific operating system.
* **Error Handling:** Visual alerts for invalid operations (e.g., trying to multiply incompatible matrices or inverting a singular matrix).

## 🏗️ Architecture & Tech Stack

* **Language:** C++ (Standard C++11 or higher)
* **GUI Framework:** [wxWidgets](https://www.wxwidgets.org/) (Version 3.x) - A C++ library that lets developers create applications for Windows, macOS, Linux, and other platforms with a single code base.

## 🔮 Roadmap (Next Steps)

Since the project is in early/restructuring phases, here are the immediate priorities:

* **🛠️ Build System Revamp:** Implement a robust `CMakeLists.txt` for easier cross-platform building and dependency resolution for wxWidgets.
* **🧹 Code Refactoring:** Separate the UI logic (wxWidgets events) strictly from the mathematical matrix processing logic.
* **🖼️ UI Polish & Screenshots:** Finalize the layout sizing and add high-quality screenshots to this README.
* **💾 Save/Load Feature:** Ability to export matrix results to `.txt` or `.csv` files.
