/*Here begins file PlanetSim.cc
/USAGE:
/Either pass with no arguments to input initial conditions on command line
/OR
/usage: PlanetSim Dimension centralMass timeStep nOfOrbitingBodies readInFile cycles
/
/Use M = 0 for mass of sun.
/
/input file must take form - delimited by white space
PlanetName1   mass1    x1...xn   v1...vn 
PlanetName2   mass2    x1...xn   v1...vn
*/

using namespace std;

#include "VectorOps.h"
#include "Forces.h"
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstdio>

#define G 0.0000000000667408

//planet with member state.
struct Planet {
    string name;
    double mass;
    vector<double> position;
    vector<double> velocity;
};

double t, DT; //global time
double M = 1.989 * pow(10, 30); //default mass of sun;
int powerDep = -2; // ie r^-2 rule
int D, N; //dimension, number of planets, time step
//instantiate Forces and VectorOps objects
VectorOps vo;
Forces f;

//declarations
void userSet();
void userInit(Planet*);
void update(Planet*);

int main(int argc, char* argv[]) {
    
    int cycles;

    //user is using a file input and arguments
     if (argc > 1){
    //intialise the array of planets
       double mHold;
        sscanf( argv[1], "%d", &D);
        mHold = atof(argv[2]);
        if(mHold!=0) M = mHold;
        DT = atof(argv[3]);
        sscanf( argv[4], "%d", &N);
    }
    
     //User wants to specify dimension, number of planets etc on command line
    else{
        userSet();
    }
    
    //initialise the array of planets, length N
    Planet* planets = new Planet[N];
    
    //initialise planets with the file
    if (argc > 1 ) {
        string name;
        double m, x1, x2, x3, v1, v2, v3;
        vector<double> xVector (D), vVector (D);
        int j = 0;
        
        ifstream infile(argv[5]);
       
        if (D == 2) {
            while (infile >> name >> m >> x1 >> x2 >> v1 >> v2 && j < N){
                planets[j].name = name;
                planets[j].mass = m;
               
                xVector[0] = x1;
                xVector[1] = x2;
               
                vVector[0] = v1;
                vVector[1] = v2;
                
                planets[j].position = xVector;
                planets[j].velocity = vVector;
                
                j++;
            }
        }
        
        if (D == 3) {
            while (infile >> name >> m >> x1 >> x2 >> x3 >> v1 >> v2 >> v3 && j < N){
                planets[j].name = name;
                planets[j].mass = m;
                
                xVector[0] = x1;
                xVector[1] = x2;
                xVector[2] = x3;

                vVector[0] = v1;
                vVector[1] = v2;
                vVector[2] = v3;
                
                planets[j].position = xVector;
                planets[j].velocity = vVector;
                
                j++;
            }
        }
        
        sscanf(argv[6], "%d", &cycles);
    }
    
     //user will initialise the planets on cmd line
    else {
        userInit(planets);
    
        cout << "\n\nEnter the number of cycles required\n";
        cin >> cycles;
    }
    
    //print the headers for the output
    {
        cout << "name\tmass\t";
        for (int j = 0 ; j < D ; j++) {
            cout << "x" << j+1 << "\t";
        }
        for (int j = 0 ; j < D ; j++) {
            cout << "v" << j+1 << "\t";
        }
        cout << "t" << endl;
    }
   
   //print specified amount of cycles
   while (cycles > 0){
       cout << "t = " << t << endl;
       
        //print info for each planet 1 at a time
        for (int i = 0; i < N ; i++){
            cout << planets[i].name << "\t" << planets[i].mass << "\t"; 
            
            //print positions delimited by tab
            for (int j = 0 ; j < D ; j++) {
                cout << planets[i].position[j] << "\t";
            }
            
            //print velocities delimited by tab
            for (int j = 0 ; j < D ; j++) {
                cout << planets[i].velocity[j] << "\t";
            }
            //end line for next planet
            cout << endl; 
        }
        
        //then update
        update(planets);
        cycles--; 
    }
}

//a function to read in the parameters of the problem specified by the user
void userSet(){
    
    double mHold;
     
    //set dimension
    cout << "\nPlease enter the dimension of the problem\nd= ";
    cin >> D; //static, for use by update function.
    
    //set mass of central body
    cout << "\nPlease enter the mass of the body being orbited\n(enter 0 for default of mass of sol)\nM= ";
    cin >> mHold;
    if(mHold!=0) M = mHold;
    
    //set timestep
    cout << "\nPlease enter the time step required as a decimal\n(considering computational time trade-off)\ndt= ";
    cin >> DT;
    
    //set number of planets
    cout << "\nPlease enter the number of masses orbiting the central body\nn= ";
    cin >> N;
}

//a function to intialise the array of Planet structures according to user input
void userInit(Planet* planets){
    
    //declare the placeholders for initialising the objects.
    vector<double> xVector (D), vVector (D);
    double x, v;
    double m;
    
    //initialise the planets' name, mass, x, v 
    for (int j = 0 ; j < N ; j++) {
        
        cout << "\nEnter the name of planet " << j + 1 << ": " ;
        cin >> planets[j].name;
        
        cout << "\nEnter the planet's mass:\nm= " ;
        cin >> m;
        planets[j].mass = m;
        
        //initialise position and velocity
        for (int i = 0 ; i < D ; i++) {
            cout << "\nEnter the planet's x" << i+1 << " component\nx" << i+1 <<"= ";
            cin >> x;
            xVector[i] = x;
        }
        for (int i = 0 ; i < D ; i++) {
            cout << "\nEnter the planet's v" << i+1 << " component\nv" << i+1 <<"= ";
            cin >> v;
            vVector[i] = v;
        }
        planets[j].position = xVector;
        planets[j].velocity = vVector;
    }
}

//a function to update the position and velocity by reference.
void update(Planet* ps) {
    //for each planet
    for (int j = 0 ; j < N ; j++) {
        //increment x by a half of the timestep
        for(int i = 0 ; i < D ; i++) {
            ps[j].position[i] += 0.5*DT*ps[j].velocity[i];
        }
        
        //update global time
        t+= 0.5*DT;
        
        //find the force acting on the body, where A = -GMm
        vector<double> force (D);
        force = f.forceCalculator(ps[j].position, D, (-1)*G*M*ps[j].mass, powerDep);
        
        //increment v by the force and the time 
        for(int i = 0 ; i < D ; i++) {
            ps[j].velocity[i] += DT*force[i]/(ps[j].mass);
        }
        
        //increment x with the new velocity
        for(int i = 0 ; i < D ; i++) {
            ps[j].position[i] += 0.5*DT*ps[j].velocity[i];
        }
        
        //update global time again
        t+= 0.5*DT;
    }
}

