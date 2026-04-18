// COMSC-210 | Lab  30| Tianyi Cao 
// Include necessary headers for file handling, data structures, etc.
#include <iostream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <fstream>
#include <sstream>

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
    }

    // Function 1: Load initial data from external file
    void loadData(const string& filename){
        // Open an external file to read initial data about departments and populate the map
        // If file does not open, print an error and exit
        
        // Read data from file and populate map
            // For each line, extract department and student data
            // Insert student into the appropriate list in the array for their department
        
        // Close the file
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
    // Parameters: map of departments, number of intervals (Handled by class members)
    void runSimulation() {
        displayEnvironment("Hour 0 (Registration Opens)");

        // Begin a time-based simulation for registration changes
            // For 72 time intervals
                // Iterate through each department in the map
                    // For each department, simulate changes
                        // Randomly decide if a student is to be added or removed from each category (enrolled, waitlisted, dropped)
                            // If adding, generate or select a new student name to add to the list
                            // If removing, select a random student from the list to remove
                        
                        // Print the changes for this interval, e.g., "Added {student} to {category} in {department}"
                        
                // Simulate more complex registration changes
                // random events impacting the registration
                // system crashes, prerequisite overrides, mass drops
                
                // Wait or pause briefly to simulate the passage of time between intervals
        
        // --- WIREFRAME MOCKUP CODE BELOW ---
        cout << "Simulation started for " << totalTimePeriods << " hours of add/drop period...\n" << endl;
        for (int i = 1; i <= totalTimePeriods; i++) {
            if (i == 12) {
                // Mocking: select a random student from the list to remove (Enrolled -> Dropped)
                string student = deptMap["Computer Science"][0].front();
                deptMap["Computer Science"][0].pop_front();
                deptMap["Computer Science"][2].push_back(student);
                cout << "  -> Removed " << student << " from Enrolled in Computer Science" << endl;
            }
            if (i == 13) {
                 // Mocking: select a new student name to add to the list (Waitlist -> Enrolled)
                string waitlistedStudent = deptMap["Computer Science"][1].front();
                deptMap["Computer Science"][1].pop_front();
                deptMap["Computer Science"][0].push_back(waitlistedStudent);
                cout << "  -> Added " << waitlistedStudent << " to Enrolled in Computer Science" << endl;
            }
        }

        displayEnvironment("Hour " + to_string(totalTimePeriods) + " (Registration Closes)");
    }
};
   

// Define main function
int main() {
    RegistrationSimulation sim(72);
    
    sim.loadData("students_data.txt");
    sim.runSimulation();

    // End of main function
    return 0;
}
