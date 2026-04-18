// COMSC-210 | Lab  31| Tianyi Cao 
// Include necessary headers for file handling, data structures, etc.
#include <iostream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

// Initialize a map to store department information, each associated with an array of lists for enrolled, waitlisted, and dropped students
typedef map<string, array<list<string>, 3>> RegistrationMap;

class RegistrationSimulation {
private:
    RegistrationMap deptMap;
    int totalTimePeriods;

public:
    // Constructor to initialize the simulation periods instead of manual setters
    RegistrationSimulation(int periods) {
        totalTimePeriods = periods;
        srand(time(0)); // Seed random number generator for realistic simulation
    }

    // Function 1: Load initial data from external file
    void loadData(const string& filename){
        cout << "Attempting to load data from " << filename << "..." << endl;
        ifstream file(filename);

    // If file does not open, print an error and exit
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << "!" << endl;
        return;
    }
        
        string line, dept, studentId;
        int count = 0;

        while (getline(file, line)) {
            stringstream ss(line);
            if (getline(ss, dept, ',') && getline(ss, studentId)) {
                deptMap[dept][1].push_back(studentId);
                count++;
        }
    }


        // Close the file
        file.close();
        cout << "Successfully loaded " << count << " student records into waitlists.\n" << endl;
    }

    void displayEnvironment(const string& timeStamp) {
        cout << "\n=== Registration State at " << timeStamp << " ===" << endl;
        for (const auto& pair : deptMap) {
            cout << "Department: " << pair.first << endl;
            cout << "  [Enrolled]:   " << pair.second[0].size() << " students" << endl;
            cout << "  [Waitlisted]: " << pair.second[1].size() << " students" << endl;
            cout << "  [Dropped]:    " << pair.second[2].size() << " students" << endl;
        }
        cout << "========================================\n" << endl;
    } 

    // Define a function to simulate registration changes over time
    void runSimulation() {
        displayEnvironment("Hour 0 (Registration Opens)");
        cout << "Simulation started for " << totalTimePeriods << " hours of add/drop period...\n" << endl;

        for (int i = 1; i <= totalTimePeriods; i++) {
            bool changesMade = false;
        // Parameters: map of departments, number of intervals (Handled by class members)
            
            for (auto& pair : deptMap) { 
                if (!pair.second[0].empty() && (rand() % 100 < 10)) { 
                    string student = pair.second[0].front();
                    pair.second[0].pop_front();
                    pair.second[2].push_back(student);
                    changesMade = true;
                }
                
            if (!pair.second[1].empty() && pair.second[0].size() < 10) { 
                    string waitlistedStudent = pair.second[1].front();
                    pair.second[1].pop_front();
                    pair.second[0].push_back(waitlistedStudent);
                    changesMade = true;
                }
                
            }
            
            if (changesMade && (i == 12 || i == 36 || i == 72)) {
                 cout << ">> Activity logged at Hour " << i << "..." << endl;
            }
        }

        displayEnvironment("Hour " + to_string(totalTimePeriods) + " (Registration Closes)");
    }
};
   
    int totalEnrolled=0, totalWaitlisted=0, totalDropped=0;
    for (const auto& pair : deptMap) {
        totalEnrolled += pair.second[0].size();
        totalWaitlisted += pair.second[1].size();
        totalDropped += pair.second[2].size();
    }
    cout << "Total Students Enrolled: " << totalEnrolled << endl;
        cout << "Total Students Waitlisted: " << totalWaitlisted << endl;
        cout << "Total Students Dropped: " << totalDropped << endl;
        cout << ">>> END OF REPORT <<<\n" << endl;


// Define main function
int main() {
    RegistrationSimulation sim(72);
    
    sim.loadData("students_data.txt");
    sim.runSimulation();

    // End of main function
    return 0;
}
