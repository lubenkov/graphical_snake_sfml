# graphical-snake-sfml

A graphical Snake game written in C++14 with SFML 2.5.1. It has a menu, five color themes, score tracking, and an optional self-collision rule.

![C++](https://img.shields.io/badge/C%2B%2B-14-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-2.5.1-8CC445?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Windows-0078D6?style=flat-square&logo=windows&logoColor=white)
![License: MIT](https://img.shields.io/badge/License-MIT-green.svg?style=flat-square)

## About

The snake moves around the field, eats apples, and grows. The field wraps at the edges. Self-collision can be enabled in the settings, and the best score is stored in `Score.txt`.

This project is a small exercise in SFML rendering, event handling, and game-state logic.

## How the code is organised

| File / directory | Responsibility |
| :-- | :-- |
| `main.cpp` | Entry point, game loop, input, rendering, menu, settings, and game objects |
| `ColorDesign.h` | Five color palettes |
| `resources/` | Fonts and game resources |
| `Score.txt` | Initial and saved high score |
| `snake.sln` / `snake4.vcxproj` | Visual Studio solution and project |

## Controls

| Key / input | Action |
| :-- | :-- |
| `W`, `A`, `S`, `D` | Move up / left / down / right |
| `Space` | Start from the main menu |
| Left mouse button | Use the menu and settings |
| `Esc` | Close the game |

## Build and run

1. Install Visual Studio 2019 or 2022 with the **Desktop development with C++** workload and the **v141** build tools.
2. Set up **SFML 2.5.1 for Visual C++ 15 (2017), x64**. The SFML headers are in `extlibs/include`; the project expects the matching libraries in `extlibs/lib/x64` and DLLs in `extlibs/bin/x64`.
3. Open `snake.sln`.
4. Select **Release Dynamic | x64**, then build and run with `F5`.

> The repository contains SFML headers but not the compiled SFML libraries or runtime DLLs. A matching SFML 2.5.1 package is required to build and run the game.

## Dependency

- [SFML 2.5.1](https://www.sfml-dev.org/download/sfml/2.5.1/) — Simple and Fast Multimedia Library.

## License

MIT — see [LICENSE](LICENSE).

<details>
<summary><b>🇷🇺 По-русски</b></summary>

<br>

Графическая «Змейка» на C++ и SFML 2.5.1. Управление WASD, пять цветовых тем, настройка столкновения с хвостом и сохранение рекорда. Для сборки нужны Visual Studio и соответствующие библиотеки SFML.
</details>
