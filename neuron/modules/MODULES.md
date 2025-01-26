# Modules

Neuron is split into several modules which are generally built together to get the full engine.
Generally, each is built as a shared library, allowing for smaller overall updates.

## Core
This module contains general purpose code and utilities.
Also exports the following libraries (which can't be easily built as shared libraries):
- [GLM](https://github.com/g-truc/glm)
- [Dear ImGUI](https://github.com/ocornut/imgui)
- [Stb](https://github.com/nothings/stb)

**Dependencies:** _None_

## Log
This module provides easy logging setup and management with a light wrapper over top of [spdlog](https://github.com/gabime/spdlog)

**Dependencies:**
- spdlog
- _core_

## OS
This module provides platform specific and os specific things (window creation, common low level socket api, etc...)

**Dependencies:**
- **Common:**
  - _core_
  - _log_
- **Windows Only:**
  - kernel32.dll
  - user32.dll
  - shcore.dll
  - ws2_32.dll
  - comdlg32.dll
  - dwmapi.dll
- **TODO:** Dependencies on other systems

## Application
This module provides a framework and utilities for setting up an application.

**Dependencies:**
- _core_
- _log_
- _os_

