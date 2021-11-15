#include <iostream>
#include <math.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>

using namespace std;
using namespace sf;

#define WINDOW_X 250
#define WINDOW_Y 250


//Colouring Schemes
void HSVtoRGB(float H, float S,float V, int *a){
    float s = S/100;
    float v = V/100;
    float C = s*v;
    float X = C*(1-abs(fmod(H/60.0, 2)-1));
    float m = v-C;
    float r,g,b;
    if(H >= 0 && H < 60){
        r = C,g = X,b = 0;
    }
    else if(H >= 60 && H < 120){
        r = X,g = C,b = 0;
    }
    else if(H >= 120 && H < 180){
        r = 0,g = C,b = X;
    }
    else if(H >= 180 && H < 240){
        r = 0,g = X,b = C;
    }
    else if(H >= 240 && H < 300){
        r = X,g = 0,b = C;
    }
    else{
        r = C,g = 0,b = X;
    }
    int R = (r+m)*255;
    int G = (g+m)*255;
    int B = (b+m)*255;
    a[0] = R;
    a[1] = G;
    a[2] = B;
}

void get_rgb_smooth(int n, int iterations, int * a) {
	// map n on the 0..1 interval
    double t = (double)n/(double)iterations;
    // Use smooth polynomials for r, g, b
    int r = (int)(9*(1-t)*t*t*t*255);
    int g = (int)(15*(1-t)*(1-t)*t*t*255);
    int b =  (int)(8.5*(1-t)*(1-t)*(1-t)*t*255);
    a[0]=r;a[1]=g;a[2]=b;
}


class Mandelbrot{
private:    
    double w,h; //width, height of window
    int iterations ; //max iterations we check
    double orig_x,orig_y; //origin co-ordinates
    double show_xl,show_xr,show_yl,show_yr; //range of x , y on window
    int pixel_size; 
    int zf; //zoom factor
    int color_scheme; //0 for colourful, 1 for blue-black
    sf::RenderWindow window;
    Texture texture;
    sf::Sprite sprite;
    Image image;
public:
    Mandelbrot(double,double,int);
    void draw();
    void Start();
    int colour(double,double);
    void zoom();
};

Mandelbrot::Mandelbrot(double w,double h,int scheme){
    this->w = w;
    this->h = h;
    show_xr = 2;  //starting range [-2,2]*[-2,2]
    show_xl = -2;
    show_yr = 2;
    show_yl = -2;
    orig_x = w/2;
    orig_y = h/2;
    pixel_size = 1; //keep it 1
    iterations = 80;
    zf = 2;
    window.create(sf::VideoMode(w, h), "SFML works!");
    image.create(w, h);
    color_scheme = scheme;
}

void Mandelbrot::draw(){
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    double x = show_xl + event.mouseButton.x/w * (show_xr-show_xl);
                    double y = show_yl + event.mouseButton.y/h * (show_yr-show_yl);
                    double temp_xr = show_xr,temp_xl = show_xl,temp_yr = show_yr,temp_yl = show_yl;
                    show_xr= x + (temp_xr-temp_xl)/(2*zf); //update the variables
                    show_xl= x - (temp_xr-temp_xl)/(2*zf);
                    show_yr= y + (temp_yr-temp_yl)/(2*zf);
                    show_yl= y - (temp_yr-temp_yl)/(2*zf);
                    // std::cout<<show_xr<<" "<<show_xl<<show_yr<<" "<<show_yl<<endl;
                }
            }
        }
        window.clear();

        int n = w*1.0/pixel_size,m = h*1.0/pixel_size;

        for (int i = -n/2; i <=n/2; i++)
        {
            for (int j = -m/2; j <= m/2; j++)
            {   
                
                double pos_x = 0.5*(show_xr+show_xl) + i*1.0/n * (show_xr-show_xl),pos_y = 0.5*(show_yr+show_yl) + j*1.0/m * (show_yr-show_yl);
                // std::cout<<pos_x<<" "<<pos_y<<" "<<orig_x<<" "<<orig_y<<"\n";
                int a[3] = {0,0,0};
                switch (color_scheme)
                {
                case 0:
                    HSVtoRGB(colour(pos_x,pos_y)*255.0/iterations,255,255*bool(colour(pos_x,pos_y)>0),a);
                    break;
                case 1:
                     get_rgb_smooth(colour(pos_x,pos_y),iterations,a);
                default:
                    break;
                }
                // if(color_scheme==0)HSVtoRGB(colour(pos_x,pos_y)*255.0/iterations,255,255*bool(colour(pos_x,pos_y)>0),a);
                // if(color_scheme==1) get_rgb_smooth(colour(pos_x,pos_y),iterations,a);
                int rd = a[0],gr=a[1],bl=a[2];
                // std::cout<<"setting "<<orig_x+i*pixel_size<<" "<<orig_y+j*pixel_size<<endl;;
                image.setPixel(orig_x+i*pixel_size,orig_y+j*pixel_size,sf::Color(rd,gr,bl));
                // std::cout<<"set\n";
            }
        }
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        window.draw(sprite);
        window.display();
    }
}

int Mandelbrot::colour(double a,double b){ //return iterations, used to determine colour
    double x0 = a;
    double y0 = b;
    double x = 0,y = 0;
    int i = iterations;
    while(i--){
        if (x*x+y*y>4)return iterations-i;
        double new_x = x*x - y*y;
        double new_y = 2*x*y;
        x = new_x+x0;y = new_y+y0;
    }
    return iterations;
}

