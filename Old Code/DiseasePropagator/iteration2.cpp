#include <string> 
#include <cmath> 
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Person {
	protected:
		string identifier;
        float chance = 0.95;
        int infectTime, state, day = 1;
        //bool isInfected, sucept;

    public: 
        Person(string name) {
            identifier = name;
            state = 0;
            infectTime = 0;
        }

        Person(string name, bool susceptible, bool infected, int timeTillHealthy) {
            identifier = name;
            infectTime = timeTillHealthy;
            if(susceptible && !infected) {
                state = 0;
            }
            else if(susceptible && infected) {
                state = 1;
            }
            else if(!susceptible && !infected) {
                state = -2;
            }
	    }

        Person(string name, string status, int timeTillHealthy) {
            identifier = name;
            infectTime = timeTillHealthy;
            transform(status.begin(), status.end(), status.begin(), ::tolower);
            if(status == "suceptible") {
                state = 0;
            }
            else if(status == "recovered") {
                state = -1;
            }
            else if(status == "inocculated") {
                state = -2;
            }
            else if(status == "sick") {
                state = 1;
            }
            else {
                throw "failed to set status!!!";
            }
        }

        bool isSusceptible() {
            return ((state == 0) || (state == 1));
        }

        bool isInfected() {
            return (state == 1);
        }

        string name() {
            return identifier;
        }


        string status_string() {
            string s = ("On day " + std::to_string(day) + ", " + identifier + ": ");
	        if(isInfected() && infectTime > 0) 
		       	s += ("Infected for " + std::to_string(infectTime) + " more days.");
	        else if (isSusceptible())
		    	s += ("Is Suceptible but not infected.");
            if (!isSusceptible()) 
		    	s += ("Is not Suceptible!");
        }

        void status() {
            string s = status_string();
            cout << s << endl;
        }
        
        void infect(int numDays) {
            state = 1;
            infectTime = numDays + 1;
            update();
        }
        
        void infectChance(float c) {
            if(isSusceptible()) {
                if(c == -1) {
                c = chance;
                }
                srand(time(NULL));
                if (rand() / RAND_MAX >= .95) {
                    infect(5);
                }
            }
        }

        void update() {
            day++;
            if (isInfected() && infectTime > 0) {
                infectTime--;
                if (infectTime == 0) {
                    state = -1;
                }
            } else {}
            status();
        }
        
        void propogate(int n) {
            if (n == -1) {
                while (isSusceptible()) {
                    update();
                }
            } 
            else {
                int i = 0;
                while (isSusceptible() || i > n) {
                    update();
                    i++;
                }
            }
        }
};

class People {
    protected:
    vector<Person> pop;
    string popIdent;
    bool popSusceptible, popInfected;
    int DEFAULT_SIZE = 100;

    void generate(int num) {
        for(int i = 0; i < num; i++)
        {
            Person p(std::to_string(i));
            pop.push_back(p);
        }
    }

    void generateInfect(int num) {
        for(int i = 0; i < num; i++)
        {
            Person p(std::to_string(i), true, true, 5);
            pop.push_back(p);
        }
    }

    public:
    People(string popName) {
        popIdent = popName;
        generate(DEFAULT_SIZE);
    }

    People(string popName, int size) {
        popIdent = popName;
        generate(size);
    }

    int getSize() {
        return pop.size();
    }

    void update() {
        popSusceptible = false;
        for(int i = 0; i < pop.size(); i++) {
            Person p = pop.at(i);
            p.update();
            if(p.isSusceptible()) {
                popSusceptible = true;
            }
            if(p.isInfected()) {
                popInfected = true;
            }
        }
    }

    void propogate(int n) {
        if (n == -1) {
            while (popSusceptible) {
                update();
            }
        } 
        else {
            int i = 0;
            while (popSusceptible || i > n) {
                update();
                i++;
            }
        }
    }

    bool isInfected() {
        bool infected = false;
        for(int i = 0; i < pop.size(); i++) {
            if((pop.at(i)).isInfected()) {
                infected = true;
            }
        }
        popInfected = infected;
        return infected;
    }

    void generateInfected(int numDays) {
        
    }
};

int main() {
    Person p1("Joe");
    /*p1.status();
    p1.infect(5);
    p1.update();
    p1.propogate(-1);*/
    
    return 0;
}
