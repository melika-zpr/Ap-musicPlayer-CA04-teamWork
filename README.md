# Terminal Music Player

A lightweight, high-performance, and interactive console-based music player built in C++. This project features a custom Terminal User Interface (TUI) that provides a smooth, visually appealing experience for managing and listening to your music library directly from the command line.

## 🚀 Key Features

* **Interactive TUI:** A responsive command-line interface using ANSI escape sequences for clean, professional layout and coloring.
* **Playlist Management:** View, navigate, and switch between different playlists effortlessly.
* **Playback Control:** Robust controls including Play, Pause, Resume, Stop, Next, Previous, and Seek (Forward/Backward).
* **Smart Playback Modes:** Supports multiple playback behaviors:
    * `No Repeat`
    * `Repeat One`
    * `Repeat All`
    * `Shuffle`
* **Modularity:** Clean object-oriented design separating the UI rendering logic from the core playback engine.

## 🛠 Prerequisites

To build and run this project, you will need:
* **Compiler:** A C++17 compatible compiler (e.g., `g++` or `clang++`).
* **Build Tool:** `make`.
* **OS:** Designed for Unix-like systems (Linux, macOS) due to terminal-specific commands (`clear`, ANSI codes).

## 📥 Building and Running

1. **Clone the repository:**
   ```bash
   git clone <your-repository-url>
   cd <project-folder-name>