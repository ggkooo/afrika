# Afrika Browser

A minimal and lightweight web browser focused on speed, simplicity, and privacy. Educational and experimental project based on C++/Qt.

## Main features
- Minimal interface with basic navigation controls
- Simple settings storage
- Uses Qt (Widgets + WebEngine/MVC)

## How to build

**Requirements:**
- C++ compiler (g++ or clang) with C++11/C++14 support
- CMake 3.5+
- Qt5 or Qt6 development libraries (including moc)

On Debian/Ubuntu:

```bash
sudo apt update
sudo apt install -y build-essential cmake git qt5-default qtbase5-dev qtwebengine5-dev
```

To build:

```bash
mkdir build && cd build
cmake ..
make
```

The executable will be generated in the `build/` folder.
