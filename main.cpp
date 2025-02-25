#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// Define the StateClimate class to store climate data for a state
class StateClimate {
    private:
        int fips;   // Federal Information Processing Standards code
        int year;   // Year of the data
        double temp; // Temperature in Fahrenheit
        double tempc; // Temperature in Celsius
    
    public:
        // Constructor to initialize the StateClimate object
        StateClimate(int f, int y, double t, double tc);
    
        // Getters to access private members
        int getFips() const;
        int getYear() const;
        double getTemp() const;
        double getTempC() const;
    
        // Setters to modify private members
        void setFips(int f);
        void setYear(int y);
        void setTemp(double t);
        void setTempC(double tc);
    
        // Display function to print the climate data
        void display() const;
};

// Constructor implementation
StateClimate::StateClimate(int f, int y, double t, double tc) : fips(f), year(y), temp(t), tempc(tc) {}

// Getter implementations
int StateClimate::getFips() const { return fips; }
int StateClimate::getYear() const { return year; }
double StateClimate::getTemp() const { return temp; }
double StateClimate::getTempC() const { return tempc; }

// Setter implementations
void StateClimate::setFips(int f) { fips = f; }
void StateClimate::setYear(int y) { year = y; }
void StateClimate::setTemp(double t) { temp = t; }
void StateClimate::setTempC(double tc) { tempc = tc; }

// Display function implementation
void StateClimate::display() const {
    cout << "FIPS: " << fips << ", Year: " << year << ", Temp: " << temp << ", TempC: " << tempc << endl;
}

// Function to compare StateClimate objects by FIPS number
bool compareByFips(const StateClimate &a, const StateClimate &b) {
    return a.getFips() < b.getFips();
}

// Function to find all entries with the given FIPS number
vector<StateClimate> findAllByFips(const vector<StateClimate> &climateData, int fips) {
    vector<StateClimate> results;
    for (const auto &entry : climateData) {
        if (entry.getFips() == fips) {
            results.push_back(entry);
        }
    }
    return results;
}

int main() {
    vector<StateClimate> climateData; // Vector to store climate data
    ifstream file("climdiv_state_year.csv"); // Open the CSV file
    
    // Check if the file was opened successfully
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    getline(file, line); // Skip header line

    // Read data from the file line by line
    while (getline(file, line)) {
        stringstream ss(line);
        int fips, year;
        double temp, tempc;
        char comma;

        // Parse the line and extract data
        ss >> fips >> comma >> year >> comma >> temp >> comma >> tempc;
        climateData.emplace_back(fips, year, temp, tempc); // Add data to the vector
    }

    file.close(); // Close the file

    // Sort the climateData vector by FIPS number
    sort(climateData.begin(), climateData.end(), compareByFips);

    // Prompt the user to enter a FIPS number
    int userFips;
    cout << "Enter the FIPS number of the state: ";
    cin >> userFips;

    // Find all entries with the given FIPS number
    vector<StateClimate> results = findAllByFips(climateData, userFips);

    // Display the results
    if (!results.empty()) {
        for (const auto &entry : results) {
            entry.display();
        }
    } else {
        cout << "State with FIPS number " << userFips << " not found." << endl;
    }

    return 0;
}