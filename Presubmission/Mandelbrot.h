#include<simplecpp>
#define WINDOW_X 250
#define WINDOW_Y 250
// #include "graphics.h"

int initwindow(int width, int height, const char* title="Windows BGI", int left=0, int top=0, bool dbflag=false, closeflag=true);


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
    double w,h;
    int iterations ;
    double orig_x,orig_y;
    double show_x,show_y;
    int pixel_size;
    int color_scheme; //0 for colourful, 1 for blue-black
    public:
    Mandelbrot(double w,double h){
        this->w = w;
        this->h = h;
        orig_x = w/2;
        orig_y = h/2;
        show_x = 2;
        show_y = 2;
        pixel_size = 1;
        iterations = 80;
    }
    void Start(){
        initCanvas("MandelBrot",WINDOW_X,WINDOW_Y);
        int X = WINDOW_X,Y = WINDOW_Y;
        const float bFx=5*X/24,bFy=Y/4, bLx=19*X/24,bLy=Y/4, bWidth=X/4,bHeight=Y/10;
        Rectangle buttonF(bFx,bFy,bWidth,bHeight), buttonL(bLx,bLy,bWidth,bHeight);
        Text tF(bFx,bFy,"Coloured"), tL(bLx,bLy,"Black-Blue");
        while(1){
        int clickPos = getClick();
        int x = clickPos/65536;
        int y = clickPos % 65536;
        if(bFx-bWidth/2<= x && x<= bFx+bWidth/2 && bFy-bHeight/2 <= y && y <= bFy+bHeight/2){
            if(color_scheme!=0){
                color_scheme = 0;
                draw();
            }
            // closeCanvas();
            // initCanvas("MandelBrot- Colored",WINDOW_X,WINDOW_Y);
        }
        if(bLx-bWidth/2<= x && x<= bLx+bWidth/2 && bLy-bHeight/2 <= y && y <= bLy+bHeight/2){
            // color_scheme = 1;
            // // closeCanvas();
            int w = initCanvas("MandelBrot- Blue-Black",WINDOW_X,WINDOW_Y);
            // draw();
             if(color_scheme!=1){
                color_scheme = 1;
                setcurre
                draw();
            }
        }   
    }
}
    void draw(){
        // Turtle t;
        // t.forward(100);
        int n = w*1.0/pixel_size,m = h*1.0/pixel_size;

        for (int i = -n/2; i <=n/2; i++)
        {
            for (int j = -m/2; j <= m/2; j++)
            {   
                // hue = int(255 * m / MAX_ITER);
                // saturation = 255;
                // value = 255 if m < MAX_ITER else 0;
                double pos_x = i*2.0/n * show_x,pos_y = j*2.0/m * show_y;
                Rectangle r(orig_x+i*pixel_size,orig_y+j*pixel_size,pixel_size,pixel_size);
                int a[3] = {0,0,0};
                if(color_scheme==0)HSVtoRGB(colour(pos_x,pos_y)*255.0/iterations,255,255*bool(colour(pos_x,pos_y)>0),a);
                if(color_scheme==1) get_rgb_smooth(colour(pos_x,pos_y),iterations,a);
                int rd = a[0],gr=a[1],bl=a[2];
                r.setColor(COLOR(rd,gr,bl));
                // cout<<colour(i*10,j*10)<<endl;
                r.setFill();
                r.imprint();
            }
        }
        cout<<"here\n";
    }
    int colour(double a,double b){
        double x0 = a;
        double y0 = b;
        // cout<<x0<<" "<<y0<<"\n";
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

    void zoom(){


    }
};
