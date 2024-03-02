#include "../include/Vehicle.hpp"

void Vehicle::setCost_for_each_line (int cost)
{
    cost_for_each_line = cost;
}
void Vehicle::setCost_for_each_line_Traffic (int cost)
{
    cost_for_each_line_Traffic = cost;
}
void Vehicle::setMinute_per_km (int min)
{
    minute_per_km = min;
}
void Vehicle::setMinute_per_km_Traffic(int min)
{
    minute_per_km_Traffic = min;
}
void Vehicle::setMinute_gettingOn_gettingOff (int min)
{
    minute_gettingOn_gettingOff = min;
}
void Vehicle::setMinute_gettingOn_gettingOff_Traffic (int min)
{
    minute_gettingOn_gettingOff_Traffic = min;
}
int Vehicle::getCost_for_each_line ()
{
    return cost_for_each_line;
}
int Vehicle::getCost_for_each_line_Traffic ()
{
    return cost_for_each_line_Traffic;
}
int Vehicle::getMinute_per_km ()
{
    return minute_per_km;
}
int Vehicle::getMinute_per_km_Traffic ()
{
    return minute_per_km_Traffic;
}
int Vehicle::getMinute_gettingOn_gettingOff ()
{
    return minute_gettingOn_gettingOff;
}
int Vehicle::getMinute_gettingOn_gettingOff_Traffic ()
{
    return minute_gettingOn_gettingOff_Traffic;
}

Bus::Bus(int cost,int cost_traffic,int min_per_km,int min_per_km_traffic , int min_get_inoff,int min_get_inoff_traffic)
{
    setCost_for_each_line(cost);
    setCost_for_each_line_Traffic(cost_traffic);
    setMinute_per_km(min_per_km);
    setMinute_per_km_Traffic(min_per_km_traffic);
    setMinute_gettingOn_gettingOff(min_get_inoff);
    setMinute_gettingOn_gettingOff_Traffic(min_get_inoff_traffic);
}
Taxi::Taxi(int cost,int cost_traffic,int min_per_km,int min_per_km_traffic , int min_get_inoff,int min_get_inoff_traffic)
{
    setCost_for_each_line(cost);
    setCost_for_each_line_Traffic(cost_traffic);
    setMinute_per_km(min_per_km);
    setMinute_per_km_Traffic(min_per_km_traffic);
    setMinute_gettingOn_gettingOff(min_get_inoff);
    setMinute_gettingOn_gettingOff_Traffic(min_get_inoff_traffic);
}
Subway::Subway(int cost,int cost_traffic,int min_per_km,int min_per_km_traffic , int min_get_inoff,int min_get_inoff_traffic)
{
    setCost_for_each_line(cost);
    setCost_for_each_line_Traffic(cost_traffic);
    setMinute_per_km(min_per_km);
    setMinute_per_km_Traffic(min_per_km_traffic);
    setMinute_gettingOn_gettingOff(min_get_inoff);
    setMinute_gettingOn_gettingOff_Traffic(min_get_inoff_traffic);
}
Taxi::Taxi()
{
    setCost_for_each_line(6000);
    setCost_for_each_line_Traffic(9000);
    setMinute_per_km(2);
    setMinute_per_km_Traffic(4);
    setMinute_gettingOn_gettingOff(5);
    setMinute_gettingOn_gettingOff_Traffic(10);
}
Bus::Bus()
{
    setCost_for_each_line(2250);
    setCost_for_each_line_Traffic(2250);
    setMinute_per_km(4);
    setMinute_per_km_Traffic(8);
    setMinute_gettingOn_gettingOff(15);
    setMinute_gettingOn_gettingOff_Traffic(30);
}
Subway::Subway()
{
    setCost_for_each_line(3267);
    setCost_for_each_line_Traffic(3267);
    setMinute_per_km(1);
    setMinute_per_km_Traffic(1);
    setMinute_gettingOn_gettingOff(8);
    setMinute_gettingOn_gettingOff_Traffic(24);
}