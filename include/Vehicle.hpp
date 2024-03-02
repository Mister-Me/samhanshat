#ifndef VEHICLE_HPP
#define VEHICLE_HPP

class Vehicle
{
public:
    void setCost_for_each_line (int);
    void setCost_for_each_line_Traffic (int);
    void setMinute_per_km (int);
    void setMinute_per_km_Traffic (int);
    void setMinute_gettingOn_gettingOff (int);
    void setMinute_gettingOn_gettingOff_Traffic (int);
    int getCost_for_each_line ();
    int getCost_for_each_line_Traffic ();
    int getMinute_per_km ();
    int getMinute_per_km_Traffic ();
    int getMinute_gettingOn_gettingOff ();
    int getMinute_gettingOn_gettingOff_Traffic ();
private:
    int cost_for_each_line;
    int minute_per_km;
    int minute_gettingOn_gettingOff;
    int cost_for_each_line_Traffic;
    int minute_per_km_Traffic;
    int minute_gettingOn_gettingOff_Traffic;
};
class Bus : public Vehicle
{
private:
public:
    Bus();
    Bus(int,int,int,int,int,int);
};
class Taxi : public Vehicle
{
private:
  
public:
    Taxi();
    Taxi(int,int,int,int,int,int);
};

class Subway : public Vehicle
{
private:
  
public:
    Subway();
    Subway(int,int,int,int,int,int);
};


#endif