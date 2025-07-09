# C++ Discord Bot Template (DPP)

A minimal C++ Discord bot template using the DPP (D++ Discord C++ Library).

## Project Structure

```
cpp-cmake-dpp/
├── bot.cpp                      # Main entry point
├── CMakeLists.txt              # Build configuration
├── include/
│   ├── manager.h               # Bot command manager
│   ├── ICommand.h              # Command interface
│   ├── IUIBuilder.h            # UI building interface
│   ├── file_manager.h          # File operations utility
│   └── commands/
│       ├── cmd_sys.h           # System commands
│       └── cmd_config.h        # Configuration commands
└── source/
    ├── manager.cpp             # Manager implementation
    └── commands/
        ├── cmd_sys.cpp         # System command implementations
        └── cmd_config.cpp      # Configuration command implementations
```

## Features

- Command management system with interface-based design
- Slash command support with options
- Button, select menu, and form interaction handlers
- UI building interface for creating interactive components
- File management system for persistent data storage
- Basic ping command included
- Configuration command with modal forms example
- Modern C++26 standards
- CMake build system

## Setup

1. Install DPP library
2. Set environment variable `DISCORD_BOT_TOKEN` with your bot token
3. Build and run:

```bash
mkdir build && cd build
cmake ..
make
./discord_bot
```

## Adding Commands

1. Create command header in `include/commands/`
2. Implement command in `source/commands/`
3. Add to CMakeLists.txt SOURCES
4. Register in Manager constructor
5. Use IUIBuilder for interactive components
6. Use FileManager for persistent data

## Example Commands

- `/ping` - Basic ping command
- `/config` - Configuration command with modal forms and file storage

## Environment Variables

- `DISCORD_BOT_TOKEN`: Your Discord bot token (required)
