#include <string> 
#include <cmath> 
#include <iostream>
#include <vector>
using namespace std;

class Person {
	private:
		string identifier;
        float chance = 0.95;
        int infectTime, day = 1;
        bool isInfected, isSusceptible;

    public: 
        Person(string name) {
            identifier = name;
            isSusceptible = true;
            isInfected = false;
            infectTime = 0;
        }

        Person(string name, bool susceptible, bool infected, int timeTillHealthy) {
            identifier = name;
            isSusceptible = susceptible;
            isInfected = infected;
            infectTime = timeTillHealthy;
	    }

        string status_string() {
            string s = ("On day " + std::to_string(day) + ", " + identifier + ": ");
	        if(isInfected && infectTime > 0) 
		       	s += ("Infected for " + std::to_string(infectTime) + " more days.");
	        else if (isSusceptible)
		    	s += ("Is Suceptible but not infected.");
            if (!isSusceptible)
		    	s += ("Is not Suceptible!");
			return s;
        }

        void status() {
            string s = status_string();
            cout << s << endl;
        }
        
        void infect(int numDays) {
            isInfected = true;
            infectTime = numDays + 1;
            update();
        }
        
        void infectChance(float c) {
            if(c == -1) {
                c = chance;
            }
            srand(time(NULL));
            if (rand() / RAND_MAX >= .95) {
                infect(5);
            }
        }

        void update() {
            day++;
            if (isInfected && infectTime > 0) {
                infectTime--;
                if (infectTime == 0) {
                    isInfected = false;
                    isSusceptible = false;
                }
            } else {}
            status();
        }
        
        void propogate(int n) {
            if (n == -1) {
                while (isSusceptible) {
                    update();
                }
            } 
            else {
                int i = 0;
                while (isSusceptible || i > n) {
                    update();
                    i++;
                }
            }
        }

};

int main() {
    Person p1("Joe");
    p1.status();
    p1.infect(5);
    p1.update();
    p1.propogate(-1);
    
    return 0;
}
