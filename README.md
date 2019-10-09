COMP 477 Assignment 1
--------------------------
General Comments:
--------------------------
Many abstractions of OpenGL methods have been designed to make working with them easier. For
example, there is an Object class that contains a Shader class which contains methods to pass in uniforms
to shader programs. Both programs have some commands to modify the objects that are specifically set to be
affected by these commands. This can be toggled by making the objects static or dynamic by using the appropriate
method in the object class. The commands are as follows:

W = Move camera in negative Z direction
S = Move camera in positive Z direction
A = Move camera in negative X direction
D = Move camera in positive X direction
O = Scale the object up by a factor of 10%
P = Scale the object down by a factor of 10%
Left-Arrow = Rotate the camera counterclockwise around the up vector
Right-Arrow = Rotate the camera clockwise around the up vector
Up-Arrow = Rotate the camera counterclockwise around the right vector
Down-Arrow = Rotate the camera clockwise around the right vector
B = Rotate the objects around the x-axis in counterclockwise fashion
N = Rotate the objects around the y-axis in counterclockwise fashion
E = Rotate the objects around the z-axis in counterclockwise fashion
J = Translate the objects along the negative x-axis
L = Translate the objects along the positive x-axis
I = Translate the objects along the positive y-axis
K = Translate the objects along the negative y-axis
Page Up = Translate the objects along the positive z-axis
Page Down = Translate the objects along the negative z-axis

IMPORTANT NOTE: Upon execution of either program, view the objects by pressing the s key at least once to set the camera properly.


Problem 1: 
--------------------------
The executable file can be found in the cmake-build-debug folder and is called COMP_477_A1.exe . The main
method is found in the problem_1.cpp file. Upon execution, the user will be asked to enter the part of the exercise to
execute. By selecting 'a' for example, part a of the problem will be executed. If another part is desired for execution,
the program must be run again in order to select another part of the problem to execute.

Problem 2: 
--------------------------
The executable file can be found in the cmake-build-debug folder and is called COMP_477_A2.exe . The main
method is found in the problem_2.cpp file. Upon execution, the user will be asked to enter the part of the exercise to
execute. By selecting 'a' for example, part a of the problem will be executed. If another part is desired for execution,
the program must be run again in order to select another part of the problem to execute. The points that define the path
and the interpolation can be found in the main method (and modified if desired).
