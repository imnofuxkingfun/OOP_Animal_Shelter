#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <map>
#include <limits>
using namespace std;
//!!Animal Shelter for mammals
/////////////////////////////////
//!!templates
template <class T>
class Pet{
private:
    T adopted;
public:
    Pet(const T& dc) { adopted = dc;}

    void getTitle() const{
        cout<<adopted.getName()<<" the "<<adopted.getSpecies();
    }
    void adoptionMsg() const{
        cout<<"Congratulations! You've adopted ";
        this->getTitle();
        cout<<"!\n";
    }

};

template<typename T>
void changeName(T& pet){
    cout<<"Insert new name:";
    string name;
    cin>>name;
    pet.setName(name);
}

template<typename T>
void checkName(const T& pet, set<string> nameList){
    set<string>::iterator I = nameList.find(pet.getName());
    if(I != nameList.end())
        throw runtime_error("Name already taken\n");

}

bool checkBool(const string& aux)
{
    if (aux == "1" || aux == "true")
        return true;
    else if(aux == "0" || aux == "false")
        return false;
    else throw invalid_argument("Expected: 1, true, 0 or false as value.\n");
}
/////////////////////////////////
//!!classes
class Animal{ //clasa parinte
protected:
    string name;
    int age;
    float weight; //greutatea in kg
public:
    //constructori si destructor
    Animal() = default;
    Animal(const string& name, const int& age, const float& weight):name(name),age(age),weight(weight){}
    Animal(const Animal& a) = default;
    virtual ~Animal()=default;//sa ne asiguram ca se apeleaza

    
    //operatori
    virtual istream& readAnimal(istream& in);
    virtual ostream& showAnimal(ostream& out) const;
    Animal& operator=(const Animal& a);

    friend istream& operator<<(istream& in, Animal& a);
    friend ostream& operator>>(ostream& out, const Animal& a);

    const string& getName() const;

    void setName(const string &name);

    int getAge() const;

};

istream& Animal::readAnimal(istream &in) {
    cout<<"Name:";
    in>>this->name;
    cout<<"Age:";
    float aux2;
    in>>aux2;
    if(in.fail() || aux2 < 0 || int(aux2) != aux2){
        in.clear(); // reset failbit
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw runtime_error("Age should be a positive integer\n");
    }
    this->age = aux2;
    cout<<"Weight:";
    in>>this->weight;
    if(this->weight < 0 || in.fail())
    {   in.clear(); // reset failbit
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//stackoverflow. fac asta ca sa nu imi mai dea loop infinit
        throw runtime_error("Weight should be a positive float\n");
    }
    return in;
}

ostream& Animal::showAnimal(std::ostream &out) const{
    out<<"Name: ";
    out<<this->name;
    out<<"\nAge: ";
    out<<this->age;
    out<<"\nWeight: ";
    out<<this->weight;
    out<<endl;
    return out;
}

Animal& Animal::operator=(const Animal& a){
    if(this != &a)
    {
        this->name = a.name;
        this->age = a.age;
        this->weight = a.weight;
    }
    return *this;
}

istream& operator<<(istream& in, Animal& a)
{
    return a.readAnimal(in);
}

ostream& operator>>(ostream& out, const Animal& a)
{
    return a.showAnimal(out);
}

const string& Animal::getName() const {
    return this->name;
}

void Animal::setName(const string &name) {
    this->name = name;
}

int Animal::getAge() const {
    return this->age;
}

////////////////////////////////////////////

class Mammal:public Animal{
protected:
    string species;
    string breed;
    bool domestic;
public:
    Mammal():Animal(){};
    Mammal(const string &name, const int &age, const float &weight, const string &species, const string &breed,
           const bool& domestic) : Animal(name, age, weight), species(species), breed(breed), domestic(domestic) {}

    Mammal(const Mammal& m) = default;

    ~Mammal() = default;

    virtual istream& readAnimal(istream& in);
    virtual ostream& showAnimal(ostream& out) const;
    Mammal& operator=(const Mammal& m);

    friend istream& operator>>(istream& in, Mammal& m);
    friend ostream& operator<<(ostream& out, const Mammal& m);

    const string& getSpecies() const;

};

istream& Mammal::readAnimal(istream &in) {
    Animal::readAnimal(in);
    cout<<"Species:";
    in>>this->species;
    cout<<"Breed:";
    in>>this->breed;
    cout<<"Domestic? [1 true / 0 false]:"; //throw error aici !!
    string aux;
    in>>aux;
    this->domestic = checkBool(aux);
    cout<<endl;
    return in;
}

ostream& Mammal::showAnimal(ostream &out)const {
    Animal::showAnimal(out);
    out<<"Species: ";
    out<<this->species;
    out<<"\nBreed: ";
    out<<this->breed<<endl;
    out<<"Domestic: ";
    if(this->domestic == true)
        out<<"true";
    else out<<"false";
    out<<endl;
    return out;
}

Mammal& Mammal::operator=(const Mammal &m) {
    if(this!=&m)
    {
        Animal::operator=(m); //upcasting
        this->species = m.species;
        this->breed = m.breed;
    }
    return *this;
}

istream& operator>>(istream& in, Mammal& m)
{
    return m.readAnimal(in);
}

ostream& operator<<(ostream& out, const Mammal& m)
{
    return m.showAnimal(out);
}

const string& Mammal::getSpecies() const {
    return this->species;
}

//////////////////////////////////////////

class Cat:public Mammal{
private:
    bool indoor;
    int meanLevel; //valoare 1-10
    string favSpot;
public:
    Cat():Mammal(){};
    Cat(const string &name, const int &age, const float &weight, const string &species, const string &breed,
        const bool& domestic, const bool& indoor, int meanLevel, const string &favSpot) :
            Mammal(name, age, weight, species, breed,domestic),
            indoor(indoor), meanLevel(meanLevel), favSpot(favSpot) {}
    Cat(const Cat& c) = default;
    ~Cat() = default;

    //operatori
    istream& readAnimal(istream& in);
    ostream& showAnimal(ostream& out) const;
    Cat& operator=(const Cat& c);

    friend istream& operator>>(istream& in, Cat& c);
    friend ostream& operator<<(ostream& out, const Cat& c);
};

istream& Cat::readAnimal(istream &in) {
    Animal::readAnimal(in); //upcasting
    this->species = "cat";
    cout<<"Breed:";
    in>>this->breed;
    cout<<"Domestic? [1 true / 0 false]:"; //throw error aici !!
    string aux;
    in>>aux;
    this->domestic = checkBool(aux);
    cout<<"Indoor? [1 true / 0 false]:";
    in>>aux;
    this->indoor = checkBool(aux);
    cout<<"Mean Level [0-10]:";
    float aux2;
    in>>aux2;
    if(aux2 < 0 || aux2 > 10 || int(aux2) != aux2 || in.fail()) {
        in.clear(); // reset failbit
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw runtime_error("Expected an integer ranging 0-10.\n");
    }
    this->meanLevel = aux2;
    cout<<"Favorite Spot:";
    in>>this->favSpot;
    cout<<endl;
    return in;
}

ostream& Cat::showAnimal(ostream &out) const {
    Mammal::showAnimal(out);
    out<<"Indoor: ";
    if(this->indoor == true)
        out<<"true";
    else out<<"false";
    out<<"\nMean Level: "<< this->meanLevel;
    out<<"\nFavorite Spot: "<<this->favSpot;
    return out;
}

Cat& Cat::operator=(const Cat& c)
{
    if(this!=&c) //upcasting
    {
        Mammal::operator=(c);
        this->indoor = c.indoor;
        this->meanLevel = c.meanLevel;
        this->favSpot = c.favSpot;
    }
    return *this;
}

istream& operator>>(istream& in, Cat& c){
    return c.readAnimal(in);
}

ostream& operator<<(ostream& out, const Cat& c){
    return c.showAnimal(out);
}

//////////////////////////////////////////
class Dog:public Mammal{
private:
    bool wellbehaved;
    int barkVolume; //valoare 1-10
    string favToy;
public:
    Dog():Mammal(){};
    Dog(const string &name, const int &age, const float &weight, const string &species, const string &breed,
        const bool& domestic,const bool& wellbehaved, int barkVolume, const string &favToy) :
            Mammal(name, age, weight, species, breed,domestic),
            wellbehaved(wellbehaved), barkVolume(barkVolume), favToy(favToy) {}
    Dog(const Dog& c) = default;
    ~Dog() = default;

    //operatori
    istream& readAnimal(istream& in);
    ostream& showAnimal(ostream& out) const;
    Dog& operator=(const Dog& c);

    friend istream& operator>>(istream& in, Dog& c);
    friend ostream& operator<<(ostream& out, const Dog& c);
};

istream& Dog::readAnimal(istream &in) {
    Animal::readAnimal(in); //upcasting
    this->species = "dog";
    cout<<"Breed:";
    in>>this->breed;
    cout<<"Domestic? [1 true / 0 false]:"; //throw error aici !!
    string aux;
    in>>aux;
    this->domestic = checkBool(aux);
    cout<<"Well Behaved? [1 true / 0 false]:";
    in>>aux;
    this->wellbehaved = checkBool(aux);
    cout<<"Barking Volume [0-10]:"; //throw exception aici !!
    float aux2;
    in>>aux2;
    if(aux2 < 0 || aux2 > 10 || int(aux2) != aux2 || in.fail()) {
        in.clear(); // reset failbit
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw runtime_error("Expected an integer ranging 0-10.\n");
    }
    this->barkVolume = aux2;
    cout<<"Favorite Toy:";
    in>>this->favToy;
    cout<<endl;
    return in;
}

ostream& Dog::showAnimal(ostream &out) const {
    Mammal::showAnimal(out);
    out<<"Well Behaved: ";
    if(this->wellbehaved == true)
        out<<"true";
    else out<<"false";
    out<<"\nBarking Volume: "<< this->barkVolume;
    out<<"\nFavorite Toy: "<<this->favToy;
    return out;
}

Dog& Dog::operator=(const Dog& c)
{
    if(this!=&c)
    {
        Mammal::operator=(c);//upcasting
        this->wellbehaved = c.wellbehaved;
        this->barkVolume = c.barkVolume;
        this->favToy = c.favToy;
    }
    return *this;
}

istream& operator>>(istream& in, Dog& c){
    return c.readAnimal(in);
}

ostream& operator<<(ostream& out, const Dog& c){
    return c.showAnimal(out);
}

//////////////////////////////////////////
//!!meniul interactiv de tip singleton
class SingletonMenu{
private:
    static SingletonMenu* instance;
    SingletonMenu() = default;
public:
    static SingletonMenu* getInstance(){
        if(SingletonMenu::instance != NULL)
        {
            return SingletonMenu::instance;
        }
        else
        {
            instance = new SingletonMenu();
            return instance;
        }
    }
    void startMenu();
};
void SingletonMenu::startMenu(){
    vector<Animal*> animalList; // ca sa memoram toate animalele
    set<string> nameList; //ca sa asiguram ca toate animalele au nume unice
    list<Animal*> petList; //lista cu animalele care au fost adoptate
    int run = 1;
    while(run){
        cout<<"\n1.See all animals\n"; //inauntru pot alege sa editez sau sa sterg unul dintre ei
        cout<<"2.Add an animal\n";
        cout<<"3.Adopt an animal\n";
        cout<<"4.See all pets\n";
        cout<<"5.Exit\n";
        int comanda;
        cin>>comanda;
        try {
        switch (comanda) {
            case 1:{//de aici pot vedea un animal, edita, sterge, vedea in ordine de varsta(multimap)
                cout<<"\nAnimal list: \n";
                cout<<"0.View animals ordered by age\n";
                int i;
                for(i = 0; i<animalList.size(); i++)
                {
                    cout<<i+1<<".";
                    Pet<Mammal> aux(dynamic_cast<Mammal&>(*animalList[i]));//downcast ca sa am access la getSpecies!
                    aux.getTitle();
                    cout<<endl;
                }
                cout<<i+1<<".Exit.\n";
                int index;
                cin>>index;
                switch(index)
                {
                    case 0:{
                        //multimap, cheie varsta, valori numeelanimalelor.
                        //este o functie strict de afisare! deci va fi string si int
                        multimap<int,string> ageOrder;
                        for(auto animal:animalList)
                        {
                            ageOrder.insert(pair<int,string>(animal->getAge(),animal->getName()));
                        }
                        cout<<"\nAnimals ordered by age:\n";
                        multimap<int,string>::iterator itr;
                        for(itr = ageOrder.begin(); itr != ageOrder.end(); ++itr)
                        {
                            cout<<itr->second<<", "<<itr->first<<" years old\n";
                        }
                        break;
                    }

                    default:{
                        //aici afisam toate detaliile animalului, apoi vine edit delete exit
                        if(index>animalList.size())
                            break;
                        index--;
                        try{
                            cout<<dynamic_cast<Cat&>(*animalList[index]); //downcast ca sa afisam pisica
                        }
                        catch(bad_cast)
                        {try{
                                cout<<dynamic_cast<Dog&>(*animalList[index]); //downcast ca sa afisam cainele
                            }
                            catch(bad_cast)
                            {
                                cout<<dynamic_cast<Mammal&>(*animalList[index]);
                            }
                        }
                        cout<<"\n1.Edit animal name.\n2.Delete animal.\n3.Exit\n";
                        int ed;
                        cin>>ed;
                        switch (ed) {
                            case 1:{
                                changeName<Animal>(*animalList[index]);
                                break;
                            }
                            case 2:{
                                animalList.erase(animalList.begin()+index);
                                break;
                            }
                            case 3:{
                                break;
                            }
                        }
                        break;
                    }
                }
                break;
            }
            case 2:{
                cout<<"\nTo enter a new animal, it must have a unique name.\n";
                cout<<"!The check will be done after you enter all animal details!\n";
                cout<<"1.Insert a cat\n2.Insert a dog.\n3.Insert a different mammal.\n4.Exit\n";
                int readCommand;
                cin>>readCommand;
                switch (readCommand) {
                    case 1:{
                            try
                            {
                                Cat* c = new Cat;
                                cin >> *c;
                                checkName(*c,nameList);
                                animalList.push_back(c);
                                nameList.insert((*c).getName());
                                break;
                            }
                            catch (const exception& e)
                            {
                                cout<<e.what();
                                break;
                            }

                    }
                    case 2:{
                            try
                            {
                                Dog* c = new Dog;
                                cin >> *c;
                                checkName(*c,nameList);
                                animalList.push_back(c);
                                nameList.insert((*c).getName());
                                break;
                            }
                            catch (const exception& e)
                            {
                                cout<<e.what();
                                break;
                            }

                    }
                    case 3:{
                            try
                            {
                                Mammal* c = new Mammal;
                                cin >> *c;
                                checkName(*c,nameList);
                                animalList.push_back(c);
                                //cout<<(typeid(*animalList[0])== typeid(Mammal))<<"AAA\n";
                                nameList.insert((*c).getName());
                                break;
                            }
                            catch (const exception& e)
                            {
                                cout<<e.what();
                                break;
                            }

                    }
                    case 4:{
                        break;
                    }
                }
                break;
            }
            case 3:{
                cout<<"\nEnter the number of the animal you'd like to adopt.";
                cout<<"\n0.Exit\n";
                for(int i=0; i<animalList.size(); i++)
                    cout<<i+1<<"."<<animalList[i]->getName()<<endl;
                int nr;
                cin>>nr;
                int run2=1;
                while(run2) {
                    switch (nr) {
                        case 0: {
                            run2=0;
                            break;
                        }
                        default: {
                            if(nr>animalList.size())
                                break;
                            nr--;
                            //il scoatem din lista, il bagam la petList, afisam mesaj;
                            petList.push_back(animalList[nr]);
                            Pet<Mammal> p(dynamic_cast<Mammal&>(*animalList[nr]));
                            p.adoptionMsg();
                            animalList.erase(animalList.begin()+nr);
                            nr = 0;
                            break;
                        }

                    }
                }
                break;
            }
            case 4:{
                cout<<"\nAdopted Pets List:\n";
                for(auto pet: petList)
                {
                    Pet<Mammal> aux(dynamic_cast<Mammal&>(*pet));//downcast ca sa am access la getSpecies!
                    aux.getTitle();
                    cout<<endl;
                }
                break;
            }
            case 5:{
                run = 0;
                break;
            }

                default: {
                    throw range_error("That command doesn't exist\n");
                }
            }

        }
        catch (const exception& e)
        {
            cout<<e.what();
        }

    }

    //cleanup
    for(auto animal:animalList)
        delete animal;

    for(auto pet:petList)
        delete pet;

}

SingletonMenu* SingletonMenu::instance = NULL;
/////////////////////////////////////
int main() {
   SingletonMenu* menu = SingletonMenu::getInstance();
    menu->startMenu();

    return 0;
}
