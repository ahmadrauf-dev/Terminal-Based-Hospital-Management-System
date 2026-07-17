#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const string HOSP_FILE = "hospitals.txt";
const string PAT_FILE  = "patients.txt";


class Hospital {
private:
    string city;
    string name;
    int id;
    int availableBeds;
    float bedPrice;
    float rating;
    int reviews;

public:
    Hospital() : id(0), availableBeds(0), bedPrice(0.0f), rating(0.0f), reviews(0) {}

    Hospital(string city, string name, int id, int availableBeds,
              float bedPrice, float rating, int reviews)
        : city(move(city)), name(move(name)), id(id),
          availableBeds(availableBeds), bedPrice(bedPrice),
          rating(rating), reviews(reviews) {}

    // Getters
    const string& getCity() const { return city; }
    const string& getName() const { return name; }
    int getId() const { return id; }
    int getAvailableBeds() const { return availableBeds; }
    float getBedPrice() const { return bedPrice; }
    float getRating() const { return rating; }
    int getReviews() const { return reviews; }

    
    void inputFromUser() {
        cout << "City: "; cin >> city;
        cout << "Hospital Name: "; cin >> name;
        cout << "Hospital ID: "; cin >> id;
        cout << "Available Beds: "; cin >> availableBeds;
        cout << "Bed Price: "; cin >> bedPrice;
        cout << "Rating (0-5): "; cin >> rating;
        cout << "Reviews: "; cin >> reviews;
    }

    void display() const {
        cout << city << " | " << name << " | ID:" << id
                   << " | Beds:" << availableBeds
                   << " | Price:" << bedPrice
                   << " | Rating:" << rating
                   << " | Reviews:" << reviews << "\n";
    }


    friend ostream& operator<<(ostream& out, const Hospital& h) {
        out << h.city << ' ' << h.name << ' ' << h.id << ' '
            << h.availableBeds << ' ' << h.bedPrice << ' '
            << h.rating << ' ' << h.reviews;
        return out;
    }

    friend istream& operator>>(istream& in, Hospital& h) {
        in >> h.city >> h.name >> h.id >> h.availableBeds
           >> h.bedPrice >> h.rating >> h.reviews;
        return in;
    }
};

// should add a little description section about patients like what type is he suffering etc
// TODO add des
class Patient {
private:
    string name;
    int id;
    int age;
    string disease;
    int hospitalID;

public:
    Patient() : id(0), age(0), hospitalID(0) {}

    Patient(string name, int id, int age, string disease, int hospitalID)
        : name(move(name)), id(id), age(age),
          disease(move(disease)), hospitalID(hospitalID) {}

    const string& getName() const { return name; }
    int getId() const { return id; }
    int getAge() const { return age; }
    const string& getDisease() const { return disease; }
    int getHospitalID() const { return hospitalID; }

    void inputFromUser() {
        cout << "Patient Name: "; cin >> name;
        cout << "Patient ID: "; cin >> id;
        cout << "Age: "; cin >> age;
        cout << "Disease: "; cin >> disease;
        cout << "Hospital ID: "; cin >> hospitalID;
    }

    friend ostream& operator<<(ostream& out, const Patient& p) {
        out << p.name << ' ' << p.id << ' ' << p.age << ' '
            << p.disease << ' ' << p.hospitalID;
        return out;
    }

    friend istream& operator>>(istream& in, Patient& p) {
        in >> p.name >> p.id >> p.age >> p.disease >> p.hospitalID;
        return in;
    }
};


class HospitalManagementSystem {
public:
    void addHospital() {
        Hospital h;
        h.inputFromUser();

        ofstream fp(HOSP_FILE, ios::app);
        if (!fp) {
            cout << "File error.\n";
            return;
        }
        fp << h << '\n';
        cout << "Hospital added.\n";
    }
// arrange these alphabatically...
// #TODO
    void displayHospitals() {
        vector<Hospital> hospitals = loadHospitals();
        if (hospitals.empty()) {
            cout << "No hospital data.\n";
            return;
        }
        displayHospitalList(hospitals);
    }

    void displayHospitalsByCity() {
        vector<Hospital> hospitals = loadHospitals();
        if (hospitals.empty()) {
            cout << "No hospital data.\n";
            return;
        }

        string city;
        cout << "Enter city: ";
        cin >> city;

        bool found = false;
        for (const auto& h : hospitals) {
            if (h.getCity() == city) {
                cout << h.getName() << " (ID:" << h.getId() << ")\n";
                found = true;
            }
        }

        if (!found)
            cout << "No hospitals found in this city.\n";
    }

    void sortByBedPrice() {
        vector<Hospital> hospitals = loadHospitals();
        sort(hospitals.begin(), hospitals.end(),
                  [](const Hospital& a, const Hospital& b) {
                      return a.getBedPrice() > b.getBedPrice();
                  });
        displayHospitalList(hospitals);
    }

    void sortByBeds() {
        vector<Hospital> hospitals = loadHospitals();
        sort(hospitals.begin(), hospitals.end(),
                  [](const Hospital& a, const Hospital& b) {
                      return a.getAvailableBeds() > b.getAvailableBeds();
                  });
        displayHospitalList(hospitals);
    }

    void sortByName() {
        vector<Hospital> hospitals = loadHospitals();
        sort(hospitals.begin(), hospitals.end(),
                  [](const Hospital& a, const Hospital& b) {
                      return a.getName() < b.getName();
                  });
        displayHospitalList(hospitals);
    }

    void sortByRatingReviews() {
        vector<Hospital> hospitals = loadHospitals();
        sort(hospitals.begin(), hospitals.end(),
                  [](const Hospital& a, const Hospital& b) {
                      if (a.getRating() != b.getRating())
                          return a.getRating() > b.getRating();
                      return a.getReviews() > b.getReviews();
                  });
        displayHospitalList(hospitals);
    }

    void addPatient() {
        Patient p;
        p.inputFromUser();

        ofstream fp(PAT_FILE, ios::app);
        if (!fp) {
            cout << "File error.\n";
            return;
        }
        fp << p << '\n';
        cout << "Patient added.\n";
    }

    void displayPatients() {
        vector<Patient> patients = loadPatients();
        vector<Hospital> hospitals = loadHospitals();

        if (patients.empty()) {
            cout << "No patient records.\n";
            return;
        }

        for (const auto& p : patients) {
            string hospName = "Unknown";

            for (const auto& h : hospitals) {
                if (p.getHospitalID() == h.getId()) {
                    hospName = h.getName();
                    break;
                }
            }

            cout << p.getName() << " | ID:" << p.getId()
                       << " | Age:" << p.getAge()
                       << " | Disease:" << p.getDisease()
                       << " | Hospital:" << hospName << "\n";
        }
    }

private:
    vector<Hospital> loadHospitals() {
        vector<Hospital> hospitals;
        ifstream fp(HOSP_FILE);
        if (!fp) return hospitals;

        Hospital h;
        while (fp >> h)
            hospitals.push_back(h);

        return hospitals;
    }

    vector<Patient> loadPatients() {
        vector<Patient> patients;
        ifstream fp(PAT_FILE);
        if (!fp) return patients;

        Patient p;
        while (fp >> p)
            patients.push_back(p);

        return patients;
    }

    void displayHospitalList(const vector<Hospital>& hospitals) {
        for (const auto& h : hospitals)
            h.display();
    }
};

int main() {
    HospitalManagementSystem system;
    int choice;

    do {
        cout << "\n\t\t Hospital Management System \t\t\n";
        cout << "1. Add Hospital\n";
        cout << "2. Display Hospitals\n";
        cout << "3. Add Patient\n";
        cout << "4. Display Patients\n";
        cout << "5. Display Hospitals by City\n";
        cout << "6. Sort by Bed Price\n";
        cout << "7. Sort by Available Beds\n";
        cout << "8. Sort by Name\n";
        cout << "9. Sort by Rating & Reviews\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
           
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            continue;
        }

        switch (choice) {
            case 1: system.addHospital(); break;
            case 2: system.displayHospitals(); break;
            case 3: system.addPatient(); break;
            case 4: system.displayPatients(); break;
            case 5: system.displayHospitalsByCity(); break;
            case 6: system.sortByBedPrice(); break;
            case 7: system.sortByBeds(); break;
            case 8: system.sortByName(); break;
            case 9: system.sortByRatingReviews(); break;
            case 0: cout << "Program exited.\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
