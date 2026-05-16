#include <iostream>
#include <string>
using namespace std;

class WeatherEvent {
protected:
    string name;
    double temperature;

public:
    WeatherEvent() {
        name = "Unknown";
        temperature = 0;
    }

    WeatherEvent(string n, double t = 20) {
        name = n;
        temperature = t;
    }

    virtual ~WeatherEvent() {}

    void changeTemperature(double t) {
        temperature = t;
    }

    string getName() {
        return name;
    }

    virtual void simulate() = 0;

    virtual void printInfo() {
        cout << "Weather Event: " << name << endl;
        cout << "Temperature: " << temperature << " C" << endl;
    }
};

class Storm : public WeatherEvent {
protected:
    int windSpeed;
    bool lightning;

public:
    Storm() : WeatherEvent() {
        windSpeed = 50;
        lightning = false;
    }

    Storm(string n, double t, int w, bool l = true)
        : WeatherEvent(n, t) {
        windSpeed = w;
        lightning = l;
    }

    void increaseWind(int value) {
        windSpeed += value;
    }

    void toggleLightning() {
        lightning = !lightning;
    }

    void simulate() override {
        cout << "Storm simulation started..." << endl;
    }

    void printInfo() override {
        WeatherEvent::printInfo();
        cout << "Wind Speed: " << windSpeed << " km/h" << endl;
        cout << "Lightning: " << (lightning ? "Yes" : "No") << endl;
    }
};

class Precipitation : public WeatherEvent {
protected:
    double amount;
    int duration;

public:
    Precipitation() : WeatherEvent() {
        amount = 10;
        duration = 1;
    }

    Precipitation(string n, double t, double a, int d = 1)
        : WeatherEvent(n, t) {
        amount = a;
        duration = d;
    }

    void increaseAmount(double a) {
        amount += a;
    }

    void extendDuration(int d) {
        duration += d;
    }

    void simulate() override {
        cout << "Precipitation simulation..." << endl;
    }

    void printInfo() override {
        WeatherEvent::printInfo();
        cout << "Amount: " << amount << " mm" << endl;
        cout << "Duration: " << duration << " hours" << endl;
    }
};

class Thunderstorm : public Storm {
private:
    int thunderCount;
    int dangerLevel;

public:
    Thunderstorm() : Storm() {
        thunderCount = 5;
        dangerLevel = 3;
    }

    Thunderstorm(string n, double t, int w, bool l,
                 int tc, int dl = 1)
        : Storm(n, t, w, l) {
        thunderCount = tc;
        dangerLevel = dl;
    }

    void strikeThunder() {
        thunderCount++;
    }

    void increaseDanger() {
        dangerLevel++;
    }

    void simulate() override {
        cout << "Thunderstorm simulation..." << endl;
    }

    void printInfo() override {
        Storm::printInfo();
        cout << "Thunder Count: " << thunderCount << endl;
        cout << "Danger Level: " << dangerLevel << endl;
        cout << "------------------------" << endl;
    }
};

class Rain : public Precipitation {
private:
    string rainType;
    bool heavyRain;

public:
    Rain() : Precipitation() {
        rainType = "Normal";
        heavyRain = false;
    }

    Rain(string n, double t, double a, int d,
         string rt, bool hr = false)
        : Precipitation(n, t, a, d) {
        rainType = rt;
        heavyRain = hr;
    }

    void changeRainType(string type) {
        rainType = type;
    }

    void toggleHeavyRain() {
        heavyRain = !heavyRain;
    }

    void simulate() override {
        cout << "Rain simulation..." << endl;
    }

    void printInfo() override {
        Precipitation::printInfo();
        cout << "Rain Type: " << rainType << endl;
        cout << "Heavy Rain: " << (heavyRain ? "Yes" : "No") << endl;
        cout << "------------------------" << endl;
    }
};

class Hurricane : public Storm {
private:
    int category;
    double eyeDiameter;

public:
    Hurricane() : Storm() {
        category = 1;
        eyeDiameter = 20;
    }

    Hurricane(string n, double t, int w, bool l,
               int c, double e = 20)
        : Storm(n, t, w, l) {
        category = c;
        eyeDiameter = e;
    }

    void increaseCategory() {
        category++;
    }

    void expandEye() {
        eyeDiameter += 5;
    }

    void simulate() override {
        cout << "Hurricane simulation..." << endl;
    }

    void printInfo() override {
        Storm::printInfo();
        cout << "Category: " << category << endl;
        cout << "Eye Diameter: " << eyeDiameter << " km" << endl;
        cout << "------------------------" << endl;
    }
};

class Snow : public Precipitation {
private:
    double snowDepth;
    bool blizzard;

public:
    Snow() : Precipitation() {
        snowDepth = 15;
        blizzard = false;
    }

    Snow(string n, double t, double a, int d,
         double sd, bool b = false)
        : Precipitation(n, t, a, d) {
        snowDepth = sd;
        blizzard = b;
    }

    void increaseSnowDepth(double s) {
        snowDepth += s;
    }

    void toggleBlizzard() {
        blizzard = !blizzard;
    }

    void simulate() override {
        cout << "Snow simulation..." << endl;
    }

    void printInfo() override {
        Precipitation::printInfo();
        cout << "Snow Depth: " << snowDepth << " cm" << endl;
        cout << "Blizzard: " << (blizzard ? "Yes" : "No") << endl;
        cout << "------------------------" << endl;
    }
};

int main() {

    WeatherEvent* events[4];

    events[0] = new Thunderstorm(
        "Thunderstorm",
        18,
        120,
        true,
        15,
        5
    );

    events[1] = new Rain(
        "Rain",
        12,
        30,
        4,
        "Heavy Rain",
        true
    );

    events[2] = new Hurricane(
        "Hurricane",
        28,
        250,
        true,
        4,
        45
    );

    events[3] = new Snow(
        "Snow",
        -5,
        12,
        6,
        35,
        true
    );

    dynamic_cast<Thunderstorm*>(events[0])->increaseDanger();
    dynamic_cast<Rain*>(events[1])->toggleHeavyRain();
    dynamic_cast<Hurricane*>(events[2])->increaseCategory();
    dynamic_cast<Snow*>(events[3])->increaseSnowDepth(10);

    for (int i = 0; i < 4; i++) {
        events[i]->printInfo();
        events[i]->simulate();
        cout << endl;
    }

    for (int i = 0; i < 4; i++) {
        delete events[i];
    }

    return 0;
}

