#include <SFML/Graphics.hpp>
#include "mandelbrot_sfml.h"
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

int main()
{
    Mandelbrot m(500,500,1);
    // m.draw();
    m.automate();
    return 0;
}

