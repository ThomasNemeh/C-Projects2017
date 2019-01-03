#ifndef ITEM_H
#define ITEM_H
#include <math.h>
#include <string>
#include <iostream>
using std::cout;
using std::ostream;
using std::endl;
using namespace std;

// TODO: your code goes here
class Item {
protected:
    double latitude;
    double longitude;
    string identifier;
    int timeAvailable;


public:
    Item(double lat, double lon, string ID, int time)
        : latitude(lat), longitude(lon), identifier(ID), timeAvailable(time) {
    }

    double getLongitude() const{
    	return longitude;
    }

    double getLatitude() const{
    	return latitude;
    }

    string getIdentifier() const{
    	return identifier;
    }

    int getTimeAvailable() const{
    	return timeAvailable;
    }

    double distanceTo(Item otherItem) {
    	cout << "Hi";
    	double pi = 3.141592653589793;
    	double lat1 = latitude * (pi/180);
    	double long1 = longitude * (pi/180);
    	double long2 = otherItem.getLongitude() * (pi/180);
    	double lat2 = otherItem.getLatitude() * (pi/180);
    	double R = 6373000;

    	double dlon = long2 - long1;
    	double dlat = lat2 - lat1;
    	double a = pow((sin(dlat/2)), 2) + cos(lat1) * cos(lat2) * pow((sin(dlon/2)), 2);
    	double c = 2 * atan2( sqrt(a), sqrt(1-a) );
    	double distance = R * c;

    	return distance;
    }

};

ostream & operator<<(ostream & o,
                     const Item & item) {
    o << "{" << item.getLatitude() << ", " << item.getLongitude() << ", \"" << item.getIdentifier() << "\", " << item.getTimeAvailable() << "}";
    return o;
}


// don't write any code below this line

#endif





