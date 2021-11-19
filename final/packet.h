// #ifndef PACKET_H
// #define PACKET_H

class Packet{
    public:
    double xl,yl,xr,yr;
    double entropy;
    Packet(double,double,double,double,double);
    Packet(){};
};

Packet::Packet(double xl,double yl,double xr,double yr,double entropy){
    this->xl = xl;
    this->xr = xr;
    this->yl = yl;
    this->yr = yr;
    this->entropy = entropy;
}

// #endif