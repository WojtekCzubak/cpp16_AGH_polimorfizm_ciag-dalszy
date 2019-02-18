#include <iostream>
#include <vector>

using namespace std;

class Mobile
{
public:
    virtual void goTo(int x, int y) = 0;
    virtual ~Mobile() {}
};

class Flyable : virtual public Mobile
{
public:
    virtual void flyTo(int x, int y) = 0;
    virtual ~Flyable() {}
};

class Sailable : virtual public Mobile // to ma funkcje sailTo ale tez i goTo bo roszszerza Mobile
{
public:
    virtual void sailTo(int x, int y) = 0;
    virtual ~Sailable() {}
};

class Vehicle : virtual public Mobile // to taki bardziej typ znacznikowy bo to taka wydmuszka

{
public:
    virtual ~Vehicle() {}
};
// od tej pory zaczynaja sie klasy konkretne
class Car : public Vehicle // car implementuje interface vehicle
{
public:
    void goTo(int x, int y) override { cout << "Car::goTo" << endl; }
    virtual ~Car() {}
};

class Person : public Mobile //taka osoba moze sie przesuwac - implementuje interface mobile
{
public:
    void goTo(int x, int y) override { cout << "Person::goTo" << endl; }
    virtual ~Person() override {}
private:
    string fstName_;
    //...
};

class Ship : public Vehicle, public Sailable //ten statek to jest pojazd, ktory tworzymy z pojazdu i czegos plywajacego, tak sobie to komponujemy :)
{
public:
    void goTo(int x, int y) override { cout << "Ship::goTo" << endl; }
    void sailTo(int x, int y) override { cout << "Ship::sailTo" << endl;  }
    virtual ~Ship() override {}
};

class Spacecraft : public Vehicle, public Flyable //podobniej jak wyzej bo statek kosmiczny jest latajacym pojazdem
{
public:
    void goTo(int x, int y) override { cout << "Spacecraft::goTo" << endl; }
    void flyTo(int x, int y) override { cout << "Spacecraft::flyTo" << endl; }
    virtual ~Spacecraft() override {}
};

class Seaplane : public Vehicle, public Flyable, public Sailable //hydroplan to mamy 3 cechy w jednym taki kombajn :)
{
public:
    void goTo(int x, int y) override { cout << "Seaplane::goTo" << endl; }
    void flyTo(int x, int y) override { cout << "Seaplane::flyTo" << endl; }
    void sailTo(int x, int y) override { cout << "Seaplane::sailTo" << endl;  }
    virtual ~Seaplane() override {}
};

void moveAllTo(int x, int y, vector<Mobile*> mobiles) { //fcja do przesuwania wszystkiego na ekranie. Polimorficzna jest struktura vektor ktora gromadzi wskazniki do mobile.
    //fcja powinna otrzymywac tyle danych ile jest jej potrzebnych. Rzutujemy wszystkie cechy na bycie mobilnym
    //zostaje wiec kolekcja wszystkiego na bycie mobilnym
    for (auto m : mobiles) { m->goTo(x, y); } //nowa petla for dla c++11.
}

void flyAllTo(int x, int y, vector<Flyable*> flyables) {
    for (auto f : flyables) { f->flyTo(x, y); }
}

void sailAllTo(int x, int y, vector<Sailable*> sailables) {
    for (auto s : sailables) { s->sailTo(x, y); }
}

// ponizej rozmiar rosnie az do 16 bo pojawil sie pole wirtualne.
// dzieje sie tak po kompilator dodaje wskaznik do tablicy fcji wirtualnych
//kazda klasa ma dodatkowe pole ktore powieksza rozmiar
class C1
{
        int x;
};

class C2
{
    virtual void f1 () {}
    int x;
};
// te klay powyzej i ich odwolanie w main sa dodane dla zwizualizowania "Vtbl" - tablice funkcji wirtualnych

void demo1()
{
    cout << "demo1()" << endl;
    vector<Mobile*> mobiles { //vektor ktorego elementami sa wskazniki do czegos co jest mobilne. zmienna mobiles jest zmienna typu wlasnie takiego vector...
        new Car{},
        new Person {},
        new Ship {},
        new Spacecraft {},
        new Seaplane {}
    };

    cout << "moveAllTo(1,2, mobiles):" << endl;
    moveAllTo(1, 2, mobiles);
    cout << endl;

    vector<Flyable*> flyables {
        new Spacecraft {},
        new Seaplane {}
    };

    cout << "flyAllTo(1,2, flyables):" << endl;
    flyAllTo(1,2, flyables);
    cout << endl;

    vector<Sailable*> sailables {
        new Ship {},
        new Seaplane {}
    };

    cout << "sailAllTo(1,2, flyables):" << endl;
    sailAllTo(1,2, sailables);
}

int main()
{
    C1 c1{};
    cout << "sizeof (C1) = " << sizeof (C1) << endl;
    cout << "sizeof (c1) = " << sizeof (c1) << endl;

    C2 c2{};
    cout << "sizeof (C2) = " << sizeof (C2) << endl;
    cout << "sizeof (c2) = " << sizeof (c2) << endl;

    demo1();
    return 0;
}
