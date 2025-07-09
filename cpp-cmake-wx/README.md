# wxWidgets CMake Template

A minimal C++26/C23 wxWidgets application template with modern CMake.

## Features

- **Modern C++ Standards**: C++26 and C23 support
- **wxWidgets 3.3.0**: Latest wxWidgets with automatic fallback to FetchContent
- **Modern CMake**: Clean, minimal CMake configuration
- **Cross-platform**: Works on Windows, macOS, and Linux
- **Basic GUI**: Simple main frame with menu bar and status bar

## Building

### Prerequisites

- CMake 3.30 or higher
- C++26 compatible compiler (GCC 13+, Clang 16+, MSVC 2022+)
- wxWidgets 3.3.0+ (optional - will be downloaded automatically if not found)

### Build Steps

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Running

```bash
./wxapp  # Linux/macOS
wxapp.exe  # Windows
```

## Project Structure

```
├── CMakeLists.txt       # Build configuration
├── app.cpp             # Application entry point
├── include/            # Header files
│   └── mainframe.h     # Main window header
└── source/             # Source files
    └── mainframe.cpp   # Main window implementation
```

## Customization

1. **Change project name**: Edit `project(wxapp ...)` in `CMakeLists.txt`
2. **Add new source files**: Place `.cpp` files in `source/` directory
3. **Add new headers**: Place `.h` files in `include/` directory
4. **Modify UI**: Edit `MainFrame` class in `include/mainframe.h` and `source/mainframe.cpp`

## License

This template is provided as-is for educational and development purposes.
