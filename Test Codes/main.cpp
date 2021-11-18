// #include<simplecpp>
// #include<turtle.h>
#define WINDOW_X 250
#define WINDOW_Y 250
#include"Mandelbrot.h"



int main(){
    // initCanvas("Lasso", WINDOW_X,WINDOW_Y);
    
    Mandelbrot m(WINDOW_X,WINDOW_Y);
    // m.draw();
    m.Start();
    wait(-1);

}