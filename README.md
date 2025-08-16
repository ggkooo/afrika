# Simple Browser 🧭

A minimal, lightweight web browser focused on speed, simplicity, and privacy. This repository contains a small C++/Qt-based browser intended as an educational and experimental project.

Key goals:
- Fast startup and low resource usage ⚡
- Privacy-respecting defaults 🛡️
- Simple, intuitive interface for everyday browsing ✨

Who it's for:
Users who want a no-frills browser that gets out of the way and lets them browse the web quickly without unnecessary features or complexity.

---

## Table of contents
- Features
- Requirements
- Build (Linux) 🐧
- Build (macOS) 🍎
- Run
- Using Qt Creator
- Troubleshooting & tips ❗


## Features
- Minimal UI with basic navigation controls (back, forward, reload)
- Simple settings storage
- Built with Qt (Widgets + WebEngine/MVC)


## Requirements
- C++ compiler (g++ or clang) with C++11/C++14 support
- CMake 3.5+ (recommended newer)
- Qt development libraries (Qt5 or Qt6). The project uses Qt's meta-object compiler (moc).

Suggested packages on Debian/Ubuntu (adjust for your distro):

- For Qt5 (common):

```bash
sudo apt update
sudo apt install -y build-essential cmake git qt5-default qtbase5-dev qtwebengine5-dev
```

- For Qt6 (if you target Qt6):

```bash
sudo apt update
sudo apt install -y build-essential cmake git qt6-base-dev libqt6webengine-dev
```

If you prefer managing Qt with the official installer or the online installer from the Qt website, that is also fine — just ensure the Qt tools and dev headers are available to CMake.


## Build (Linux) 🛠️

1. Open a terminal and go to the project root (where `CMakeLists.txt` is located):

```bash
cd /path/to/web-browser
```

2. Create and enter a build directory (out-of-source build recommended):

```bash
mkdir -p build && cd build
```

3. Configure the project with CMake (Release recommended for performance):

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
```

- If CMake cannot find Qt automatically, you may need to point CMake to your Qt installation. Example (adjust path to your Qt):

```bash
cmake .. -DCMAKE_PREFIX_PATH=/opt/Qt/6.5.0/gcc_64
```

4. Build the project:

```bash
make -j$(nproc)
```

- Or use Ninja if you prefer:

```bash
cmake -G Ninja ..
ninja
```


## Build (macOS) 🍎

1. Install Xcode Command Line Tools (if not already installed):

```bash
xcode-select --install
```

2. Install Homebrew (optional but recommended) and dependencies, or use the official Qt installer. Using Homebrew (Qt6):

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"  # only if you don't have Homebrew
brew update
brew install cmake git qt
```

3. Build (out-of-source recommended):

```bash
cd /path/to/web-browser
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="$(brew --prefix qt)"
make -j$(sysctl -n hw.ncpu)
```

- If you installed Qt with the Qt online installer, point CMake to your Qt kit instead:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/Users/<you>/Qt/<version>/clang_64
```

- With Ninja:

```bash
cmake -G Ninja .. -DCMAKE_PREFIX_PATH="$(brew --prefix qt)"
ninja
```

Notes for macOS:
- If CMake cannot find Qt, set `CMAKE_PREFIX_PATH` to the Qt installation path as shown above.
- Use `make -j$(sysctl -n hw.ncpu)` to parallelize the build on macOS.
- If web pages do not render, ensure you have Qt WebEngine installed for your Qt version (Homebrew's `qt` includes WebEngine for Qt6).


## Run 🚀

After a successful build the binary is usually placed in `build/`. Example:

```bash
./build/SimpleBrowser
```

Replace `SimpleBrowser` with the actual binary name if different. If you run from the build directory, prefix with `./`.


## Using Qt Creator (optional) 🎯

1. Open Qt Creator and select `File → Open File or Project...` then choose `CMakeLists.txt` in the project root.
2. Configure kit (select Qt version and compiler).
3. Build and run from the IDE (Debug/Release as desired).


## Troubleshooting & tips 🔧

- "CMake Error: Could not find a package configuration file provided by "Qt5"/"Qt6":" — install the Qt dev packages or set `CMAKE_PREFIX_PATH` to your Qt install.
- Missing `moc` errors — ensure Qt development tools are installed (moc, uic are provided by Qt dev packages).
- If web pages do not render, the project may require Qt WebEngine or Qt WebKit. Install `qtwebengine` development packages for your Qt version.
- Clean build:

```bash
rm -rf build && mkdir build && cd build
```

- To build with debugging symbols:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)
```


## Contributing
Contributions and fixes are welcome. Open issues or pull requests with clear descriptions.


## License
Add project license information here (e.g., MIT, GPL) — currently not specified.


---

If you want, I can also add platform-specific instructions (macOS/Windows) or presets for common distributions. Want me to include those? 🙂
