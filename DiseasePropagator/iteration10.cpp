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

        int getStatus() {
            return state;
        }

        int getDay() {
            return day;
        }

        string status_string() {
            string s = ("On day " + std::to_string(day) + ", " + identifier + ": ");
	        if(isInfected() && infectTime > 0) 
		       	s += ("Infected for " + std::to_string(infectTime) + " more days.");
	        else if(isSusceptible())
		    	s += ("Is suceptible but not infected.");
            if(!isSusceptible()) 
		    	s += ("Is not suceptible!");
            return s;
        }

        void status() {
            string s = status_string();
            cout << s << endl;
        }
        
        void infect(int numDays) {
            state = 1;
            infectTime = numDays + 1;
            cout << update() << endl;
        }
        
        void infectChance(float c, int numDays) {
            if(isSusceptible()) {
                if(c == -1) {
                    c = chance;
                }
                srand(time(NULL));
                if (rand() / RAND_MAX >= .95) {
                    infect(numDays);
                }
            }
        }

        string update() {
            day++;
            if (isInfected() && infectTime > 0) {
                infectTime--;
                if (infectTime == 0) {
                    state = -1;
                }
            } else {}
            return status_string();
        }
        
        void propogate(int n) {
            if (n == -1) {
                while (isSusceptible()) {
                    cout << update() << endl;
                }
            } 
            else {
                int i = 0;
                while (isSusceptible() || i > n) {
                    cout << update() << endl;
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

    void generateInocculated(int num) {
        for(int i = 0; i < num; i++)
        {
            Person p(std::to_string(i), false, false, 5);
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

    People(string popName, int numSucept, int numInfected, int numInnoculated) {
        popIdent = popName;
        generate(numSucept);
        generateInfect(numInfected);
        generateInocculated(numInnoculated);
    }

    int getSize() {
        return pop.size();
    }

    void update() {
        popSusceptible = false;
        for(int i = 0; i < pop.size(); i++) {
            Person p = pop.at(i);
            interact(p);
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
                status();
            }
        } 
        else {
            int i = 0;
            while (popSusceptible || i > n) {
                update();
                status();
                i++;
            }
        }
    }

    string status_string() {
        string s = popIdent + " on Day " + std::to_string(pop.back().getDay()) + ": ";
        
        for(int i = 0; i < pop.size(); i++)
        {
            s += std::to_string((pop.at(i)).getStatus()) + "\t";
        }
        return s;
    }

    void status() {
        string s = status_string();
        cout << s << endl;
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

    Person randPerson() {
        return pop.at((1.0 * rand()/RAND_MAX) * pop.size());
    }

    void interact(Person p) {
        if(p.isInfected()) {
            (randPerson()).infectChance(-1, 5);
        }
    }
};









int main() {
    /*Person p1("Joe");
    p1.status();
    p1.infect(5);
    p1.update();
    p1.propogate(-1);*/

    People peeps("town", 10, 10, 5);
    peeps.status();
    peeps.update();
    peeps.status();
    
    return 0;
}
