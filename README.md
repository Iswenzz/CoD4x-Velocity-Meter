# CoD4x Velocity Meter

[![Build status](https://ci.appveyor.com/api/projects/status/0890ff8p951r3bbk?svg=true)](https://ci.appveyor.com/project/Iswenzz/cod4x-velocity-meter)
[![codecov](https://codecov.io/gh/Iswenzz/CoD4x-Velocity-Meter/branch/master/graph/badge.svg)](https://codecov.io/gh/Iswenzz/CoD4x-Velocity-Meter)
[![CodeFactor](https://www.codefactor.io/repository/github/iswenzz/cod4x-velocity-meter/badge)](https://www.codefactor.io/repository/github/iswenzz/cod4x-velocity-meter)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

This program calculates the active player's velocity in real time, and displays it to the application window. Velocity is calculated by using the following formula: 

![](https://www.gstatic.com/education/formulas/images_long_sheet/en/distance_formula.svg)

To explain this a bit: The image above is the geometrical formula for distance between 2 points. We store this value in a class property, and update it every 50 milliseconds, therefore giving us Velocity, which is measured in distance per time.

![](https://i.imgur.com/yTMBhpZ.png)

## Features

* Show spectated player's velocity
* Change background color
* Change foreground color
* Transparency
* Always on top option
