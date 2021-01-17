#include <iostream>
#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include <exception>

using namespace std;

enum Color { PINK, BLUE };

enum ChildType { GOOD, BAD };

enum Gender { BOY, GIRL };

enum PackagingType { NOT_PACKAGED, BOY_PACKAGING, GIRL_PACKAGING };
/**declararea enumeratiilor*/

/** Clasa PresentObject
    Clasa de baza pentru obiectele care pot fi adaugate in cadou
*/
class PresentObject
{
private:
    double cost;

public:
    PresentObject(double pret)
    {
        this->cost = pret;
    }

    virtual ~PresentObject() = default;

    double getCost() const
    {
        return this->cost;
    }
    /** printDetails scrie detalii despre obiect
        Este o metoda pur virtuala care trebuie suprascrisa in fiecare clasa care mosteneste PresentObject*/
    virtual void printDetails() const = 0;
};
void PresentObject::printDetails() const
{
    cout << "Cadou default";
}

/**Clasa Coal adauga in cadourile copiilor rai */

class Coal : public PresentObject
{
public:
    Coal() : PresentObject(0.5) {};
    void printDetails() const override;
};
void Coal::printDetails() const
{
    cout << "Carbune - cost: " << getCost();
}

/** Clasa Candy
    Mosteneste de la PresentObject
    Este adaugata in cadou cand unui copil ii raman bani dupa adaugarea jucariilor dorite*/

class Candy : public PresentObject
{
public:
    Candy() : PresentObject(1) {};
    void printDetails() const override;
};

void Candy::printDetails() const
{
    cout << "Acadea - cost: " << getCost();
}

/** Clasa DefaultPresent
 Adauga in cadou in cazul in care nu mai este nimic in inventarul elfilor sau cand primul cadou din wishlist depaseste bugetul*/

class DefaultPresent : public PresentObject
{
public:
    DefaultPresent(int cost) : PresentObject(cost) {};

    void printDetails() const override;
};
void DefaultPresent::printDetails() const
{
    cout << "Cadou default - cost: " << getCost() << "\n";
}

/** Clasa Present
 Incapsuleaza datele unui cadou */

class Present
{
private:
    Gender _gender;
    PackagingType _packaging_type;
    ChildType _child_type;
    vector<PresentObject*> _objects;

public:
    Present(): _packaging_type(NOT_PACKAGED) {}/**constructor impachetat/neimpachetat*/
    ~Present()
    {
        for(auto i : _objects)
        {
            delete i;
        }
        _objects.clear();
    }

    double getCost() const;

    vector<PresentObject*> getObjects()
    {
        return _objects; //getter
    }/**returneza obiectele incapsulate */

    void addPresentObject(PresentObject* present_object);/**adauga obiect in lista */
    void setChildType(ChildType child_type);/**seteaza statusul copilului*/
    void setChildGender(Gender gender);/**seteaza genul copilului*/
    ChildType getChildType() const;/**returneaza statusul copilului*/
    Gender getChildGender() const;/**returneaza genul copilului*/
    void setPackagingType(PackagingType packaging_type);/**seteaza tipul de impachetare*/
    PackagingType getPackagingType() const;/**genereaza tipul de impachetare*/

};


void Present::addPresentObject(PresentObject* j)
{
    _objects.emplace_back(j);//setter
}

void Present::setChildType(ChildType type)
{
    _child_type = type;//setter
}

void Present::setChildGender(Gender gender)
{
    _gender = gender;//setter
}

ChildType Present::getChildType() const
{
    return _child_type;//getter
}

Gender Present::getChildGender() const
{
    return _gender;//getter
}

void Present::setPackagingType(PackagingType packaging_type)
{
    _packaging_type = packaging_type;//setter
}

double Present::getCost() const
{
    double cost = 0;
    for (const auto o : _objects)
    {
        cost += o->getCost();
    }/**calculeaza cost total cadou*/
    return cost;
}



class Toy : public PresentObject
{
private:
    string _name;
public:
    Toy(int pret, string nume) : PresentObject(pret), _name{nume} {}/**constructor*/
    void printDetails() const override;/**suprascriere*/
    const string& getName();//getter

};

void Toy::printDetails() const
{
    cout << "Jucarie - cost: " << getCost() << " nume: " << _name;
}

const string& Toy::getName()  //getter
{
    return _name;
}


/**  Exceptia BudgetExceededException
     Exceptia este folosita cand bugetul unui copil este depasit*/

struct BudgetExceededException : public exception
{
private:
    int _amount;
public:
    BudgetExceededException(int amount) : _amount(amount) {}

    const char* what() const noexcept override
    {
        return "Buget depasit!";
    }
    int getAmount()
    {
        return _amount;
    }

};


/**  Exceptia JucarieNotFound
     Exceptia este folosita cand jucaria nu este gasita in enventarul elfilor*/

class JucarieNotFound : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Jucaria nu a fost gasita!";
    }
};


/** Exceptia InventarGol
    Exceptia este folosita cand inventarul elfilor este gol si se cauta o jucarie in el*/

class InventarGol : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Inventar Gol";
    }
};


/** Exceptia BugetRamas
    Exceptia este folosita cand unui copil ii raman bani dupa adaugarea cadourilor*/

class BugetRamas : public exception
{
private:
    int _amount;
public:
    BugetRamas(int amount) : _amount(amount) {}
    const char* what() const noexcept override
    {
        return "Inventar Gol";//returneaza o eroare intr un anumit caz
    }

    int getAmount() const
    {
        return _amount;
    }

};

/** Clasa Letter
    Incapsuleaza datele unui copil*/

class Letter
{
private:
    int _age;
    string _city;
    string _name;
    string _surname;
    vector<string> _wishlist;
    Color _letter_color;
public:
    Letter(int age, string city, string name, string surname, vector<string> wishlist, Color letter_color)
        : _age(age), _city(city), _name(name), _surname(surname), _wishlist(wishlist), _letter_color(letter_color) {}//constructor
        //_age = age
    int getAge() const;
    const string& getCity() const;
    const string& getName() const;
    Color getLetterColor() const;
    const string& getSurname() const;
    vector<string> getWishlist() const;
    void ShowLetter()
    {
        cout << "\nSCRISOARE\n\n";
        cout << _name << " " << _surname << ", varsta " << _age<<"ani," << " din " << _city << " doreste de Craciun: \n";
        for(int i=0; i<(int)_wishlist.size(); i++ ){
            if(_wishlist.at(i) == _wishlist.back())
            {
                cout << _wishlist.at(i) << "." << endl << endl;
            }else{
                cout << _wishlist.at(i) << ", ";
            }
        }
    }

};

int Letter::getAge() const
{
    return _age;
}

Color Letter::getLetterColor() const
{
    return _letter_color;
}

const string& Letter::getCity() const
{
    return _city;
}

const string& Letter::getName() const
{
    return _name;
}

const string& Letter::getSurname() const
{
    return _surname;
}

vector<string> Letter::getWishlist() const
{
    return _wishlist;
}


/** Clasa ElfWorkshop
    Incapsuleaza functionalitatea din atelierul elfilor*/

class ElfWorkshop
{
private:
    int _candy_count;
    vector<string> _cities;
    vector<Toy*> _inventory;
    vector<Present*> _presents;
    vector<string> _good_children;
public:
    ElfWorkshop() : _candy_count(0), _cities(), _inventory(), _presents(), _good_children() {}
    ~ElfWorkshop()
    {
        for (auto* toy : _inventory)
        {
            delete toy;
        }
    }//destructor
    int getCandyAdded() const;

    /** getCityList
      returneaza lista de orase din care mosul a primit scrisori*/

    vector<string> getCityList() const;


    /** addToyInInventory
        @param added_toy pointer catre jucaria pe care dorim sa o adaugam*/

    void addToyInInventory(Toy* added_toy);


    /**  readLetters genereaza cadouri conform scrisorilor
        @param letters scrisorile copiilor
        @param presents vectorul de pointer in care se vor stoca cadourile*/

    void readLetters(const vector<Letter>& letters, vector<Present*>& presents);

    /**setGoodChildren seteaza lista cu copiii care au fost cuminti
       @param good_children lista cu copiii cuminti*/

    void setGoodChildren(const vector<string> good_children);



    void addCity(const string& city);//adaugare oras in lista

    Toy* searchToyInInventory(string toy, int budget);//functie care sa caute in inventar si sa returneze jucaria

    Present* createPresent(const Letter& christmas_letter);

    void addObjectsToPresent(const Letter& christmas_letter, int budget, Present* christmas_present);

    template <size_t cost>
    PresentObject* getDefaultPresentByCost()
    {
        switch (cost)
        {
        case 1:
        {
            return new Candy();
        }
        break;
        default:
            return new DefaultPresent(cost);
        }
    }
};
int ElfWorkshop::getCandyAdded() const
{
    return _candy_count;
}

vector<string> ElfWorkshop::getCityList() const
{
    return _cities;
}

void ElfWorkshop::readLetters(const vector<Letter>& letters, vector<Present*>& presents)
{
    /** Parcurge lista cu scrisori si genereaza cate un cadou pentru fiecare scrisoare*/
    for (const auto& letter : letters)
    {
        presents.emplace_back(createPresent(letter));
    }
}

void ElfWorkshop::setGoodChildren(const vector<string> good_children)
{
    _good_children = good_children;
}

void ElfWorkshop::addCity(const string& city)
{
    auto position =  find(_cities.begin(), _cities.end(), city);

    if (position == _cities.end())
    {
        _cities.emplace_back(city);
    }
}

Present* ElfWorkshop::createPresent(const Letter& letter)
{
    /** Adauga orasul din care a venit scrisoarea in lista de orase*/
    addCity(letter.getCity());

    /** Cauta numele copilului in lista de copii cuminti si seteaza corespunzator variabila cuminte*/
    bool cuminte = false;
    auto l =  find(_good_children.begin(), _good_children.end(), letter.getName() + " " + letter.getSurname());
    if (l != _good_children.end())
    {
        cuminte = true;
    }

    Present* present = new Present();

    switch (letter.getLetterColor())
    {
    case BLUE:
    {
        present->setChildGender(BOY);
    }
    break;
    case PINK:
    {
        present->setChildGender(GIRL);
    }
    break;
    }

    if (cuminte)
    {
        present->setChildType(GOOD);
    }
    else
    {
        present->setChildType(BAD);
    }

    try
    {
        /** Adaug in cadou jucariile de pe wishlist*/
        addObjectsToPresent(letter, cuminte ? 100 : 10, present);
    }
    catch (InventarGol& e)
    {
        /** In cazul in care inventarul elfilor este gol adaugam un cadou default cu valoarea corespunzatoare bugetului*/
        if (cuminte)
        {
            present->addPresentObject(getDefaultPresentByCost<100>());
        }
        else
        {
            present->addPresentObject(getDefaultPresentByCost<10>());
        }
    }
    catch (BugetRamas& e)
    {
        /** In cazul in care bugetul nu a fost consumat, adaugam acadele de restul banilor*/
        for (int i = 0; i < e.getAmount(); i++)
        {
            present->addPresentObject(getDefaultPresentByCost<1>());
            _candy_count++;
        }
    }
    return present;
}

void ElfWorkshop::addToyInInventory(Toy* added_toy)
{
    _inventory.emplace_back(added_toy);
}

void ElfWorkshop::addObjectsToPresent(const Letter& christmas_letter, int buget, Present* c)
{
    for (const auto& j : christmas_letter.getWishlist())
    {
        try
        {
            /** Cauta jucaria in inventar si scade costul din buget in cazul in care este gasita si ajung banii*/
            auto* jucarie = searchToyInInventory(j, buget);
            buget -= jucarie->getCost();
            c->addPresentObject(jucarie);
        }
        catch (JucarieNotFound& e)
        {
            /** In cazul in care jucaria nu este gasita, nu au fost adaugate jucarii in cadou, iar inventarul este gol, oferim cadou default*/
            if (_inventory.size() == 0 && c->getObjects().size() == 0)
            {
                throw InventarGol();
            }
            else
            {
                /** In cazul in care am adaugat deja jucarii inseamna ca jucaria costa mai mult decat bugetul disponibil*/
                throw BugetRamas(buget);
            }
        }
        catch (BudgetExceededException& e)
        {
            /** In cazul in care bugetul este depasit din start ofera cadoul default*/
            if (c->getObjects().size() == 0)
            {
                if (c->getChildType() == GOOD)
                {
                    c->addPresentObject(getDefaultPresentByCost<100>());
                }
                else
                {
                    c->addPresentObject(getDefaultPresentByCost<10>());
                }
                return;
            }
            else
            {
                /** Daca au mai fost adaugate jucarii*/
                throw BugetRamas(buget);
            }
        }
    }

    if (buget != 0)
    {
        throw BugetRamas(buget);
    }

    return;
}

Toy* ElfWorkshop::searchToyInInventory(string nume_jucarie, int buget)
{
    /** Caut jucaria in inventar dupa nume*/

    if (_inventory.size() == 0)
    {
        throw InventarGol();
    }

    auto i = _inventory.begin(); // il declar aici ca sa poata fi utilizat in continuare
    for (; i != _inventory.end(); i++)
    {
        if ((*i)->getName() == nume_jucarie)
        {
            break;
        }
    }
    if (i == _inventory.end())
    {
        throw JucarieNotFound();
    }

    if ((*i)->getCost() > buget)
    {
        throw BudgetExceededException((*i)->getCost() - buget);
    }
    /** Sterg jucaria din inventar in cazul in care nu exista erori*/
    Toy* toy = *i;
    _inventory.erase(i);

    return toy;
}



/** Clasa TrollWorkshop
    Incapsuleaza functionalitatea atelierului trollilor*/

class TrollWorkshop
{
private:
    int _boy_presents;
    int _girl_presents;
    int _coal_added;
public:
    TrollWorkshop();

    /**packPresents impacheteaza cadourile si adauga un carbune la cadourile care apartin copiilor care nu au fost cuminti*/
    void packPresents(vector<Present*>& presents);

    int getCoalAdded() const;
    int getGirlPresents() const;
    int getBoyPresents() const;


};

TrollWorkshop::TrollWorkshop() : _boy_presents(0), _girl_presents(0), _coal_added(0) {}

void TrollWorkshop::packPresents(vector<Present*>& presents)
{
    /** Parcurge vectorul cu cadouri si adauga carbuni la copiii rai*/
    for (auto* present : presents)
    {
        if (present->getChildType() == BAD)
        {
            present->addPresentObject(new Coal());
            _coal_added++;
        }
        /** Impacheteaza cadoul folosind ambalajul coresunzator*/
        switch (present->getChildGender())
        {
        case BOY:
        {
            present->setPackagingType(BOY_PACKAGING);
            _boy_presents++;
        }
        break;
        case GIRL:
        {
            present->setPackagingType(GIRL_PACKAGING);
            _girl_presents++;
        }
        break;
        }
    }
}

int TrollWorkshop::getCoalAdded() const
{
    return _coal_added;
}

int TrollWorkshop::getGirlPresents() const
{
    return _girl_presents;
}

int TrollWorkshop::getBoyPresents() const
{
    return _boy_presents;
}




/**clasa MissChristmas
   Incapsuleaza functionalitatea Doamnei Craciun*/

class MissChristmas
{
public:
    MissChristmas() {};

    /**  calculateExtraCost calculeaza costul extra pentru carbune si acadele
         coal_pieces numarul de bucati de carbune adaugate de trolli
         candy_pieces numarul de bucati de acadele adaugate de elfi*/

    double calculateExtraCost(int coal_pieces, int candy_pieces);


    /**  calculateTotalCost calculeaza costul total al cadourilor
         presents vector cu pointeri catre cadouri*/

    double calculateTotalCost(const vector<Present*> presents);
};


double MissChristmas::calculateExtraCost(int coal_pieces, int candy_pieces)
{
    return coal_pieces * 0.5 + candy_pieces;
}

double MissChristmas::calculateTotalCost(const vector<Present*> presents)
{
    double total_cost = 0;
    for (auto* present : presents)
    {
        total_cost += present->getCost();
    }//adauga pretul fiecarui cadou la costul total
    return total_cost;
}




/**  Clasa Santa
     Incapsuleaza functionalitatea lui Mos Craciun*/


class Santa
{
private:
    double getDistanceBetweenCities(const string& first, const string& other);
    const  array<const string, 6> cities_list = {"Reykjavik", "Alftanes",    "Neskaupstaour","Dalvik",    "Hvolsvollur", "Rovaniemi"};
    const  array<const array<double, 6>, 6> distances =
    {
        {   {0, 5.96, 408.08, 258.30, 94.84, 2173.48},           // Distantele dintre Reykjavik si restul oraselor
            {{5.96, 0, 413.18, 264.25, 96.28, 2178.98}},         // Alftanes
            {{408.08, 413.18, 0, 240.81, 349.52, 1771.14}},      // Neskaupstaour
            {{258.30, 264.25, 240.81, 0, 259.57, 1942.48}},      // Dalvik
            {{94.84, 96.28, 349.52, 259.57, 0, 2120.64}},        // Hvolsvollur
            {{2173.48, 2178.98, 1771.14, 1942.48, 2120.64, 0}}
        }, // Rovaniemi
    };
public:
    Santa() {}
    /** calculatePath calculeaza lungimea drumului care trece prin toate orasele date in ordine
        cities lista cu orase*/
    double calculatePath(const vector<string>& cities);


};

double Santa::calculatePath(const vector<string>& cities)
{
    double distance = 0;

    if (cities.size() == 0)
    {
        throw "No cities found in list!";
    }

    auto first_city = find(cities_list.begin(), cities_list.end(), "Rovaniemi"); //locul de plecare
    auto destination = find(cities_list.begin(), cities_list.end(), cities.front()); // returnez referinta catre primul element din acest vector

    for (size_t i = 0; i < cities.size(); i++)
    {
        /** Calculeaza distanta de la first_city la destination*/
        distance += getDistanceBetweenCities(*first_city, *destination);
        /** Schimba first_city cu destination*/
        first_city = destination;
        /** Seteaza destinatia pe urmatorul oras din lista*/
        destination++;
    }
    return distance;
}

double Santa::getDistanceBetweenCities(const string& first, const string& other)
{
    /** Cauta distanta dintre orase folosind matricea de distante*/
    int first_city_position = find(cities_list.begin(), cities_list.end(), first) - cities_list.begin();
    int other_city_position = find(cities_list.begin(), cities_list.end(), other) - cities_list.begin();

    return distances[first_city_position][other_city_position];
}


/**  printCities scrie pe ecran drumul parcurs de Mos Craciun*/

void printCities(const vector<string>& cities)
{
    cout << "Rovaniemi->";

    for (auto city = cities.begin(); city != cities.end(); city++)
    {
        cout << *city;
        if (city + 1 != cities.end())
        {
            cout << "->";
        }
    }
    cout << endl;
}

void runTest(const vector<Letter>& letters, const vector<Toy*>& toys,
             const vector<string>& good_children)
{
    /** Creeaza obiectele necesare*/
    ElfWorkshop elf_workshop{};
    TrollWorkshop troll_workshop{};
    MissChristmas miss_christmas{};
    Santa santa;

    /** Adauga jucariile in inventar*/
    for (const auto toy_ptr : toys)
    {
        elf_workshop.addToyInInventory(toy_ptr);
    }

    /** Seteaza lista cu copiii care au fost cuminti*/
    elf_workshop.setGoodChildren(good_children);

    /** Genereaza vectorul de cadouri*/
    vector<Present*> presents{};

    elf_workshop.readLetters(letters, presents);
    /** Impacheteaza cadourile*/
    troll_workshop.packPresents(presents);

    cout << "Trolii au impachetat " << troll_workshop.getBoyPresents() << " cadouri pentru baieti si "
         << troll_workshop.getGirlPresents() << " cadouri pentru fete." << endl;

    cout << "Doamna Craciun a calculat bugetul extra pentru carbuni si acadele: "
         << miss_christmas.calculateExtraCost(troll_workshop.getCoalAdded(), elf_workshop.getCandyAdded())
         <<  endl;

    cout << "Bugetul total pentru cadouri este: " << miss_christmas.calculateTotalCost(presents) << endl;

    cout << "Drumul parcurs de Mos Craciun: ";
    printCities(elf_workshop.getCityList());

    cout << "Drumul parcurs de Mos Craciun are lungime de " << santa.calculatePath(elf_workshop.getCityList())
         << "km." << endl;

    /** Sterge memoria alocata pentru cadouri ( deoarece au fost alocate cu "new" )*/

    for (auto* present : presents)
    {
        delete present;
    }
}

int main()
{
    vector<Letter> test_letters =
    {
        Letter(7, "Reykjavik", "Myrkjartan", "Friobjornsson", {"Figurina Batman"}, BLUE),
        Letter(8, "Alftanes", "Kjalar", "Mikkelsson", {"Scut", "Sabie"}, BLUE),
        Letter(11, "Neskaupstaour", "Ebenezer", "Aaronsson", {"Armura"}, BLUE),
        Letter(5, "Dalvik", "Soren", "Vioarsson", {"Laptop"}, BLUE),
        Letter(13, "Dalvik", "Elianna", "Dufbaksdottir", {"Boxa"}, PINK),
        Letter(15, "Hvolsvollur", "Jondora", "Valbergsdottir", {"Tastatura"}, PINK),
    };
    for(int i = 0; i < test_letters.size(); i++){
        test_letters.at(i).ShowLetter();
    }

    vector<Toy*> test_toys = {new Toy(70, "Figurina Batman"), new Toy(8, "Scut"), new Toy(5, "Sabie"),new Toy(14,"Armura"), new Toy(150, "Undita")};
    vector<string> test_good_children = {"Myrkjartan Friobjornsson", "Elianna Dufbaksdottir"};

    runTest(test_letters, test_toys, test_good_children);
}


