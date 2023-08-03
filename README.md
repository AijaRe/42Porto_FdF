
# FdF

FDF is short for ’fil de fer’ in French which means ’wireframe
model’.\
This project is about creating a simple wireframe model representation of a 3D land-
scape by linking various points (x, y, z) and representing them on the screen in 2D.



## Rendering

Your program has to represent the model in isometric projection.\
The coordinates of the landscape are stored in a .fdf file passed as a parameter to
your program.\
Each number represents a point in space:
- The horizontal position corresponds to its axis.
- The vertical position corresponds to its ordinate.
- The value corresponds to its altitude.
Keep in mind that the goal of this project is not to parse maps! However, this doesn’t
mean that your program should crash when run. It means that we assume the map
contained in the file is properly formatted

## Graphic management

- Your program has to display the image in a window.
- The management of your window must remain smooth (changing to another win-
dow, minimizing, and so forth).
- Pressing ESC must close the window and quit the program in a clean way.
- Clicking on the cross on the window’s frame must close the window and quit the
program in a clean way.
- The use of the images of the MiniLibX is mandatory.

## Materials

MiniLibX Guides
 - [Harm Smits MiniLibX Guide](https://harm-smits.github.io/42docs/libs/minilibx)
 - [PulgaMecanica MiniLibX Guide](https://pulgamecanica.herokuapp.com/posts/7)
 - [Aurelien Brabant MiniLibX Guide](https://aurelienbrabant.fr/blog/pixel-drawing-with-the-minilibx)