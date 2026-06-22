# Micro-Projet-JIN4526



Authors: Javier David Caniz Meng \& Raphael Lefevre

## boucle de Gameplay

1) Event du jour -> choix d'action
2) nourrir ?
3) améliorer ?
4) produire food ?
5) produire materials ?
6) produire manpower ?
7) attack ?
8) recap

## Current prototype

The game now opens an SFML window called `Resource Kingdom`.

Controls:

- `F`: produce food with available peasants
- `M`: produce materials with available peasants
- `P`: recruit one peasant for 20 food
- `S`: recruit one soldier for 15 food and 15 materials
- `A`: attack the enemy castle with available soldiers
- `Space`: feed everyone
- `N`: go to the next day
- `Escape`: quit

On Windows, if `cmake` is not in your PATH, build from a terminal with:

```bat
call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat" -arch=x64
"C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" --build out\build\x64-Debug
```

