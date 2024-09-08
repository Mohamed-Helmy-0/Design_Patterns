#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <typeinfo>

using namespace std;


class Vehicle
{
    int id;
public:
    virtual void move() = 0;
    virtual ~Vehicle(){};
    void setId(int id) 
    {
        this->id = id;
    }
    int getId() 
    {
        return id;
    }
};

class Car : public Vehicle
{
    
    void move() override {
        cout<<" Id="<<getId()<<endl;
        cout<<"Car is Moving"<<endl;
    }
};
class Bike : public Vehicle
{
    void move() override {
        cout<<" Id="<<getId()<<endl;
        cout<<"Bike is Moving"<<endl;
    }
};
class Truck : public Vehicle
{
    void move() override {
        cout<<" Id="<<getId()<<endl;
        cout<<"Truck is Moving"<<endl;
    }
};



class VehicleFactory
{
protected:
    vector<string> readFromFile(const std::string& filePath) 
    {
        vector<string> lines;
        std::ifstream file(filePath);  // Open the file
        if (!file.is_open()) {
            std::cerr << "Failed to open the file: " << filePath << std::endl;
            return lines;
        }

        std::string line;
        while (std::getline(file, line)) {  // Read the file line by line
        lines.push_back(line);  // Print each line to the console
        }

        file.close();  // Close the file
        return lines;
    }

public:
    virtual ~VehicleFactory(){};
    virtual Vehicle* CreateVehicle() =0;
    void move()
    {
        Vehicle * vecPointer= CreateVehicle();
        vecPointer->move();
        delete vecPointer;
    }
    // Vehicle* CreateVehicle(string type)
    // {
    //     if(type == "Car")
    //         return new Car();
    //     else if(type == "Bike")
    //         return new Bike();
    //     else if(type == "Truck")
    //         return new Truck();  
    //     else
    //         return NULL;  // Return NULL if type not found.
    // }
};
class CarFactory : public VehicleFactory
{
    Vehicle* CreateVehicle() override
    {
        vector<string> lines=readFromFile("ids.txt");
        for(auto &line : lines)
        {
            if(line.find("carId")!= string::npos)
            {
                
                int NumberLength = (line.find(";")-line.find("="))-1 ;
                istringstream iss(  line.substr(line.find("=")+1,
                                                NumberLength)
                                                );
                int id;
                iss >> id;
                Car * car = new Car();
                car->setId(id);
                return car;
            }
        }
        return NULL;  // Return NULL if type not found.
    }
};

class BikeFactory : public VehicleFactory
{
    Vehicle* CreateVehicle() override
    {
             vector<string> lines=readFromFile("ids.txt");
        for(auto &line : lines)
        {
            if(line.find("bikeId")!= string::npos)
            {
                
                int NumberLength = (line.find(";")-line.find("="))-1 ;
                istringstream iss(  line.substr(line.find("=")+1,
                                                NumberLength)
                                                );
                int id;
                iss >> id;
                Bike * bike = new Bike();
                bike->setId(id);
                return bike;
            }
        }
        return NULL;  // Return NULL if type not found.
    }
};
int main()
{
    cout<< "Start Code Main." << endl;



    // Vehicle* car = new Car();
    // car->move();
    // Vehicle* bike = new Bike();
    // bike->move();
    // delete car;
    // delete bike;

    // cout<<"Please write vehicle type: ";
    // string type;
    // cin >> type;
    // VehicleFactory factory;
    // Vehicle* vec=factory.CreateVehicle(type);
    // if(vec!= NULL)
    //     vec->move();
    // else    
    //     cout << "Vehicle type not found." << endl;


    VehicleFactory *factory;
    factory = new BikeFactory();
    factory->move();

    cout << "End Code Main." << endl;
    return 0;
}