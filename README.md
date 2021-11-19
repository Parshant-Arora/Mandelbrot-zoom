# Mandelbrot-zoom

My CS293 course project. Implementation of Mandelbrot Zoom using SFML graphics library, and efficient use of Data Structures

Author - Parshant Arora (200050099) 

Project - Mandelbrot Zoom	 

Implementation language - C++ 

Graphics Package - SFML

Github Repo - https://github.com/Parshant-Arora/Mandelbrot-zoom (private currently)

Lines ~ 900-1000

Demo - https://drive.google.com/drive/folders/1aMzds918GLNpYz6T-9Y-6Un82xxLwG_H?usp=sharing

===================Compile Command==============================

g++ -c $@

g++ $@ -o ./a.out -lsfml-graphics -lsfml-window -lsfml-system

./a.out

(@ = file name)


======================Details===================================

1. Mandelbrot fractal is an infinitely repeating pattern, with a very simple underlying maths. 
2. Mandelbrot Sets are defined by points all points z such that f(z) = z^2 +c , f(f(z)), f(f(f(z)))..all are finite(with c = 0). 
3. We do M number of iterations on a point z and calculate the t as max number of iterations before crossing mode 2, and then using 2 colouring schemes, assign a color to a pixel.
4.Mandelbrot zoom produce some interesting and colourful patterns.
5. Data Structures used BST and Heap
6. Entropy calculation of 100 random tiles.



=======================LOG======================================

Version 1.1 - Implemented Basic Mandelbrot Drawing in simplecpp

Version 1.2 - Improvised the code with proper classes and functions

Version 1.3 - Switched to SFML library and implemented Zoom 

Version 1.4 - Added Automatic Zoom

Version 1.5 - Added Buttons and final touch 

====================!======================!====================
