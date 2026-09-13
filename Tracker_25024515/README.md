# Rainfall Tracker - COS3711 Assignment

## What This Is

So basically this is a rainfall tracking application that I built using C++ and Qt. You can add rainfall records, store them, search through them, and also export everything to XML. There's also backup and restore functionality which was pretty useful while testing.

## What You Need

- Qt 5 (make sure it's installed properly)
- Qt Creator (for development)
- A C++ compiler that works with Qt 5 (should come with Qt Creator)

## How The Project Is Organized

```
RainfallTracker/
|
|-- RainfallTracker.pro
|-- main.cpp
|
|-- Q1/
|   |-- rainrecord.h
|   |-- rainrecord.cpp
|
|-- Q2/
|   |-- rainxml.h
|   |-- rainxml.cpp
|
|-- Q3/
|   |-- stationthread.h
|   |-- stationthread.cpp
|   |-- mytablewidgetmemento.h
|   |-- mytablewidgetmemento.cpp
|
|-- Client/
    |-- client.h
    |-- client.cpp
```

Each folder basically handles a different part of the assignment requirements.

## Getting It To Run

1. Open Qt Creator
2. Go to File → Open File or Project
3. Open the RainfallTracker.pro file
4. Choose a Qt 5 kit (should prompt you)
5. If it asks, run qmake
6. Build it (Build menu or Ctrl+B)
7. Run it

Should be straightforward. If you get errors, make sure your Qt 5 compiler is properly set up in the kits settings.

## Actually Using The App

**Adding Records:**
1. Type in a station code (e.g. AagA100)
2. Pick a date
3. Enter how much rainfall (in mm)
4. Click "Add Record"
5. It shows up in the table

**Creating XML:**
Just click the "Generate XML" button after you've added some records. It displays the XML with all your data - station code, date, rainfall amount, etc.

**Searching:**
1. Enter the station code you want to find in the search box
2. Click "Search in Thread"
3. It runs the search in a separate thread (so the UI doesn't freeze) and shows the results

**Backup/Restore:**
- Click "Backup Table" to save the current state
- Make some changes
- Click "Restore Table" if you want to go back to how it was

Pretty useful when testing different scenarios.

## Test Data I Used

If you want to try it out with some sample data:

```
Station: AagA100, Date: 01/01/2023, Rainfall: 10mm
Station: BcdB123, Date: 02/01/2023, Rainfall: 5mm
Station: AagA100, Date: 03/01/2023, Rainfall: 25mm
```

## Station Codes

They need to follow a specific format (like AagA100). Make sure you follow whatever format was specified in the assignment requirements or it won't accept it.

## Important Notes

- The .pro file is essential - that's how Qt Creator knows how to build everything
- All the actual code is in the .cpp and .h files
- You don't need to include build folders or the .exe file when submitting (obviously)
- Qt Creator generates a bunch of user-specific files - ignore those for submission too

## What Each Part Does

- **Q1**: Handles the rainfall record structure
- **Q2**: Deals with XML generation and parsing
- **Q3**: Threading stuff for the search function, plus the memento pattern for backup/restore
- **Client**: The main UI and application logic

---

Pretty straightforward project once you get Qt set up. Let me know if you run into any issues.
