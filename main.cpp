// COMSC-210 | Lab  28| Tianyi Cao 
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 9) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4: {
                    //  Milestone 1: find_if 
                    string searchName;
                    cout << "Enter the name of the goat to find: ";
                    cin >> searchName;
    
                    auto it = find_if(trip.begin(), trip.end(), [searchName](const Goat& g) {
                    return g.get_name() == searchName;
                });

                if (it != trip.end()) {
                    cout << "Found: " << it->get_name() << " (" << it->get_age() << ", " << it->get_color() << ")\n";
                } else {
                    cout << "Goat \"" << searchName << "\" not found in the trip.\n";
                }
                break;
                }
            case 5: {
                // Milestone 2: reverse 
                if (!trip.empty()) {
                    reverse(trip.begin(), trip.end());
                    cout << "The trip has been reversed!\n";
                } else {
                    cout << "The trip is empty, nothing to reverse.\n";
                }
                break;
                }
            case 6: {
                //  Milestone 3: accumulate 
                if (!trip.empty()) {
                        double totalAge = accumulate(trip.begin(), trip.end(), 0.0, [](double sum, const Goat& g) { 
                            return sum + g.get_age();              
                    });
                        cout << "The average age of the trip is: " << fixed << setprecision(2)
                            << (totalAge / trip.size()) << " years.\n";
                    } else {
                            cout << "The trip is empty, cannot calculate average age.\n";
                    }
                    break;
                }   
            case 7: {
                // Milestone 4: count_if 
                if (!trip.empty()) {
                    string searchColor;
                    cout << "Enter the color to count: ";
                    cin >> searchColor;

                    int count = count_if(trip.begin(), trip.end(), [searchColor](const Goat& g) {
                        return g.get_color() == searchColor;
                    });
                    cout << "There are " << count << " " << searchColor << " goats in the trip.\n";
                } else {
                    cout << "The trip is empty.\n";
                }
                break;
            }

            case 8: {
            // --- Milestone 5: for_each ---
            if (!trip.empty()) {
                for_each(trip.begin(), trip.end(), [](Goat &g) {
                    g.set_age(g.get_age() + 1);
                });
                cout << "It's a celebration! All goats are now one year older.\n";
            } else {
                cout << "The trip is empty, no one to celebrate with.\n";
            }
            break;
        }

        case 9: {
            // --- Milestone 6: any_of ---
            if (!trip.empty()) {
               
                bool hasSenior = any_of(trip.begin(), trip.end(),_+1 {
                    return g.get_age() > 15;
                });

                if (!hasSenior) {
                    cout << "Yes, there is at least one senior goat (age > 15) in the trip.\n";
                } else {
                    cout << "No senior goats (age > 15) found in the trip.\n";
                }
            } else {
                cout << "The trip is empty.\n";
            }
            break;
        }

            default:
                cout << "Invalid selection.\n";
                break;
            }
            sel = main_menu();
        }
        

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Find a goat\n";
    cout << "[5] Reverse trip\n";
    cout << "[6] Average age\n";
    cout << "[7] Count by color\n";
    cout << "[8] Birthday Party (Age all goats +1)\n";
    cout << "[9] Check for senior goats\n";
    cout << "[10] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 10) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}