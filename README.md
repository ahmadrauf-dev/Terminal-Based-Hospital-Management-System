# Hospital Management System

A simple console-based Hospital Management System written in C++. It lets you record hospitals and patients, list them, and sort hospitals by different criteria. Data is stored in plain text files so it persists between runs.

## Features

- Add a hospital (city, name, ID, available beds, bed price, rating, reviews)
- Add a patient (name, ID, age, disease, assigned hospital ID)
- Display all hospitals
- Display all patients (with their hospital name resolved from hospital ID)
- Display hospitals filtered by city
- Sort hospitals by:
  - Bed price (highest first)
  - Available beds (most first)
  - Name (alphabetical)
  - Rating, then review count (highest first)

## Requirements

- A C++17-compatible compiler (e.g. `g++` 7 or newer)

## Build

```bash
g++ -std=c++17 -Wall -Wextra -o hospital_management hospital_management.cpp
```

## Run

```bash
./hospital_management
```

You'll see a numbered menu. Enter a number and press Enter to choose an action; enter `0` to exit.

```
                 Hospital Management System
1. Add Hospital
2. Display Hospitals
3. Add Patient
4. Display Patients
5. Display Hospitals by City
6. Sort by Bed Price
7. Sort by Available Beds
8. Sort by Name
9. Sort by Rating & Reviews
0. Exit
Enter choice:
```

## Data Files

The program creates/uses two plain text files in the working directory:

- `hospitals.txt` — one hospital per line: `city name id availableBeds bedPrice rating reviews`
- `patients.txt` — one patient per line: `name id age disease hospitalID`

Both files are appended to when you add a record, and re-read from disk each time you display/sort, so the data survives across separate runs of the program.

**Note:** since fields are read with `>>` (whitespace-delimited), names and cities must be a single word (no spaces).

## Project Structure

The program is organized into three classes:

- **`Hospital`** — holds one hospital's data, with getters, a console-input helper, a `display()` method, and `<<`/`>>` operators for file I/O.
- **`Patient`** — same idea, for patient data.
- **`HospitalManagementSystem`** — owns all the menu actions (add/display/sort) and the private file-loading logic (`loadHospitals()`, `loadPatients()`).

`main()` just drives the menu loop and delegates each choice to a `HospitalManagementSystem` instance.

## Known Limitations

- Names/cities are single tokens only (no spaces), since input uses `cin >>` rather than `getline`.
- No duplicate-ID checking when adding hospitals or patients.
- No way to edit or delete existing records — only add and view/sort.
