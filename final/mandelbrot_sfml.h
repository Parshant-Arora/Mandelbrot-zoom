#include <iostream>
#include <math.h>
#include <stdio.h>
#include<bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include"heap.h"
// #include"button.h"

#include"BST.cpp"


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
    int d_x ,d_y; 
    int pixel_size; 
    int zf; //zoom factor
    int color_scheme; //0 for colourful, 1 for blue-black
    vector<vector<int>> color_t;
    sf::RenderWindow main_window;
    sf::RenderWindow window;
    sf::RectangleShape m_button,a_button,save,toggle; //buttons
    sf::Text t_m,t_a,t_save,t_toggle; //texts
    Texture texture;
    sf::Sprite sprite;
    Image image;
public:
    Mandelbrot(double,double,int);
    void draw();
    class Heap* make_heap();
    double Entropy(int,int,int,int);
    void automate();
    void display_static();
    void Start();
    int colour(double,double);
    void zoom();
    void run();
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
    color_t.resize(w, vector<int>(h));
    zf = 2;
   
    main_window.create(sf::VideoMode(500,500,32), "Welcome", sf::Style::Default);
    m_button = sf::RectangleShape(sf::Vector2f(100.f,100.f));
    m_button.setPosition(100,150);
    a_button = sf::RectangleShape(sf::Vector2f(100.f,100.f));
    a_button.setPosition(300,150);
    save = sf::RectangleShape(sf::Vector2f(50.f,50.f));
    save.setPosition(450,50);
    toggle = sf::RectangleShape(sf::Vector2f(50.f,50.f));
    toggle.setPosition(450,200);
    image.create(w, h);
    color_scheme = scheme;
}

void Mandelbrot::run(){
    
    while (main_window.isOpen())
    {   
    sf::Event event;
    while (main_window.pollEvent(event)) 
    {   
        if (event.type == sf::Event::Closed)
        {
            main_window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2i m_mousePosition = sf::Mouse::getPosition(main_window);
            bool mouseInButton_m =    m_mousePosition.x >= m_button.getPosition().x 
                                && m_mousePosition.x <= m_button.getSize().x + m_button.getPosition().x 
                                && m_mousePosition.y >= m_button.getPosition().y 
                                && m_mousePosition.y <= m_button.getSize().y + m_button.getPosition().y ;
            
            switch(event.mouseButton.button)
            {
            case sf::Mouse::Left:
            {
                // std::cout<<m_mousePosition.x<<" "<<m_mousePosition.y<<", button in "<<m_button.getPosition().x<<" "<<m_button.getPosition().y<<"\n";
                if(mouseInButton_m)
                {   
                    // std::cout<<"Clicked\n";
                    window.create(sf::VideoMode(500, 500), "SFML works!");
                    draw();
                }
            }
            break;
            }

            //automatic

            
            bool mouseInButton_a =    m_mousePosition.x >= a_button.getPosition().x 
                                && m_mousePosition.x <= a_button.getSize().x + a_button.getPosition().x 
                                && m_mousePosition.y >= a_button.getPosition().y 
                                && m_mousePosition.y <= a_button.getSize().y + a_button.getPosition().y ;
            
            switch(event.mouseButton.button)
            {
            case sf::Mouse::Left:
            {
                std::cout<<m_mousePosition.x<<" "<<m_mousePosition.y<<", button in "<<a_button.getPosition().x<<" "<<a_button.getPosition().y<<"\n";
                if(mouseInButton_a)
                {   
                    // std::cout<<"Clicked\n";
                    window.create(sf::VideoMode(500, 500), "SFML works!");
                    automate();
                }
            }
            break;
            } 
        }
    }
   
    main_window.clear(sf::Color(0, 255, 255));
    m_button.setFillColor(sf::Color(255,255,102));
    a_button.setFillColor(sf::Color(255,255,102));
    main_window.draw(m_button);
    main_window.draw(a_button);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cout<<"font error\n";
    }
    t_m.setFont(font); // font is a sf::Font
    t_a.setFont(font); // font is a sf::Font

    // set the string to display
    t_m.setString("Manual");
    t_a.setString("Automatic");

    // set the character size
    t_m.setCharacterSize(20); // in pixels, not points!
    t_a.setCharacterSize(20); // in pixels, not points!

    // set the color
    t_m.setFillColor(sf::Color::Red);
    t_a.setFillColor(sf::Color::Red);
    t_m.setPosition(m_button.getPosition().x + 20,m_button.getPosition().y + 40);
    t_a.setPosition(a_button.getPosition().x +  5,a_button.getPosition().y + 40);
    main_window.draw(t_a);
    main_window.draw(t_m);
    // window.clear();
    
    // manual.draw_it(window);
    
    main_window.display();

    }

}

void Mandelbrot::draw(){
    show_xr = 2;  //starting range [-2,2]*[-2,2]
    show_xl = -2;
    show_yr = 2;
    show_yl = -2;


    while (window.isOpen())
    {   
        
        sf::Event event;
        while (window.pollEvent(event)) 
        {   
            if (event.type == sf::Event::Closed) 
                window.close();
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Down){
                    show_yl += 0.5;
                    show_yr += 0.5;
                } 
                if(event.key.code == sf::Keyboard::Up){
                        show_yl -= 0.5;
                        show_yr -= 0.5;
                }
                if(event.key.code == sf::Keyboard::Left){
                        show_xl -= 0.5;
                        show_xr -= 0.5;
                }
                if(event.key.code == sf::Keyboard::Right){
                        show_xl += 0.5;
                        show_xr += 0.5;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {   
                sf::Vector2i m_mousePosition = sf::Mouse::getPosition(window);
                bool mouseInButton_save =    m_mousePosition.x >= save.getPosition().x 
                                && m_mousePosition.x <= save.getSize().x + save.getPosition().x 
                                && m_mousePosition.y >= save.getPosition().y 
                                && m_mousePosition.y <= save.getSize().y + save.getPosition().y ;
                bool mouseInButton_toggle =    m_mousePosition.x >= toggle.getPosition().x 
                                && m_mousePosition.x <= toggle.getSize().x + toggle.getPosition().x 
                                && m_mousePosition.y >= toggle.getPosition().y 
                                && m_mousePosition.y <= toggle.getSize().y + toggle.getPosition().y ;                                
            
                switch(event.mouseButton.button)
                {
                case sf::Mouse::Left:
                {
                    // std::cout<<m_mousePosition.x<<" "<<m_mousePosition.y<<", button in "<<save.getPosition().x<<" "<<save.getPosition().y<<"\n";
                    if(mouseInButton_save)
                    {   
                        image.saveToFile("Image.png");
                        continue;
                    }
                    if(mouseInButton_toggle)
                    {   
                        color_scheme = 1-color_scheme;
                        continue;
                    }
                }
                break;
                } 
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

        for (int i = -n/2; i <n/2; i++)
        {
            for (int j = -m/2; j < m/2; j++)
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
        save.setFillColor(sf::Color(255,255,255));
        toggle.setFillColor(sf::Color(255,255,255));
        sf::Font font;
        if (!font.loadFromFile("arial.ttf"))
        {
            cout<<"font error\n";
        }

        t_save.setFont(font); // font is a sf::Font
        t_toggle.setFont(font); // font is a sf::Font

        // set the string to display
        t_save.setString("Save");
        t_toggle.setString("Toggle");

        // set the character size
        t_save.setCharacterSize(15); // in pixels, not points!
        t_toggle.setCharacterSize(15); // in pixels, not points!

        // set the color
        t_save.setFillColor(sf::Color::Red);
        t_toggle.setFillColor(sf::Color::Red);
        t_save.setPosition(save.getPosition().x + 10,save.getPosition().y + 10);
        t_toggle.setPosition(toggle.getPosition().x +  5,toggle.getPosition().y + 10);
        save.setFillColor(sf::Color(0,255,255));
        toggle.setFillColor(sf::Color(0,255,255));
        window.draw(save);
        window.draw(toggle);
        window.draw(t_toggle);
        window.draw(t_save);
        window.display();
    }
    // image.saveToFile("test.png");
}

char *int2charstar (int v) { //Convert int to char* label
 char *s = new char[sizeof(int)];
 sprintf(s,"%d",v);
 if(s[1]=='\0'){s[1]=s[0];s[0]='0';s[2]='\0';}
 return s;
};

double Mandelbrot::Entropy(int i_0, int j_0, int d_x,int d_y){
    BST *T = new BST();
    for (int i = i_0; i < i_0 + d_x; i++)
    {
        for (int j = j_0; j < j_0 + d_y; j++)
        {
            Node* input = new Node();
		    input->key = int2charstar(color_t[i][j]);//&c;
            
            // cout<<i<<" "<<j<<" "<<input->key<<" btree"<<endl;
		    T->insert(input);
        }
    }
    TraversalType_e order;
    order  = IN_ORDER;
	T->traverse(order,T->root);
    // cout<<T.x_sq_sum<<" "<<T.x_sum<<"\n";
    double var = T->x_sq_sum/(d_x*d_y) - T->x_sum/(d_x*d_y) * T->x_sum/(d_x*d_y);
    // cout<<var<<"\n";
    delete T;
    return var;

}

Heap* Mandelbrot::make_heap(){
    int n = w*1.0/pixel_size,m = h*1.0/pixel_size;
    Heap* H = new Heap();
    srand(time(0));
    for (int trial = 0; trial < 100; trial++)
    {       
        // cout<<"trial = "<<trial<<endl;
        int w_x = w-d_x , w_y = h-d_y;
        int i = rand()%w_x - n/2;
        int j = rand()%w_y - m/2;
        // cout<<i<<" "<<j<<" in the heap"<<endl;
        double pos_x_l = 0.5*(show_xr+show_xl) + i*1.0/n * (show_xr-show_xl),pos_y_l = 0.5*(show_yr+show_yl) + j*1.0/m * (show_yr-show_yl);   
        double pos_x_r = 0.5*(show_xr+show_xl) + (i+d_x)*1.0/n * (show_xr-show_xl),pos_y_r = 0.5*(show_yr+show_yl) + (j+d_y)*1.0/m * (show_yr-show_yl);   
        double entropy = Entropy(i+n/2,j+m/2,d_x,d_y);
        // cout<<entropy<<"\n";
        Packet P(pos_x_l,pos_y_l,pos_x_r,pos_y_r,entropy);
        //heap insertion
        H->insert(P);
    }
    
       
        // }
    // }
    // cout<<"returning from heap\n";
    return H;
}


void Mandelbrot::display_static(){
    int n = w*1.0/pixel_size,m = h*1.0/pixel_size;

        for (int i = -n/2; i <n/2; i++)
        {
            for (int j = -m/2; j < m/2; j++)
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
                color_t[i+n/2][j+m/2] = colour(pos_x,pos_y);
                
                int rd = a[0],gr=a[1],bl=a[2];
                
                image.setPixel(orig_x+i*pixel_size,orig_y+j*pixel_size,sf::Color(rd,gr,bl));
                // std::cout<<"set\n";
            }
        }
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        window.draw(sprite);
        window.display();
        
}


void Mandelbrot::automate(){
   
    show_xr = 2;  //starting range [-2,2]*[-2,2]
    show_xl = -2;
    show_yr = 2;
    show_yl = -2;
    d_x = w/50,d_y = h/50; 
    int no_zooms = 10;
    while(window.isOpen())
    {   
        // cout<<"yes open"<<endl;
        sf::Event event;
        while (window.pollEvent(event)) 
        {   
            // cout<<"event"<<endl;
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(no_zooms>=0){
            window.clear();
            display_static();
            // image.saveToFile("test.png");
            Heap *H = make_heap();
            Packet P = H->delete_min_and_return();
            // cout<<P.entropy<<" "<<P.xl<<" "<<P.xr<<"\n";
            //update x,y
            show_xr = (P.xr + P.xl)/2 + w*(P.xr-P.xl)/(2*2*d_x);
            show_xl = (P.xr + P.xl)/2 - w*(P.xr-P.xl)/(2*2*d_x);
            show_yr = (P.yr + P.yl)/2 + h*(P.yr-P.yl)/(2*2*d_y);
            show_yl = (P.yr + P.yl)/2 - h*(P.yr-P.yl)/(2*2*d_y);
            delete H;
            no_zooms--;
            sf::sleep(sf::milliseconds(500));
        }
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

