#include <iostream>
#include <string>

using namespace std;

struct Country
{
    string name;
    uint legalAge;
};

struct Person
{
    string firstname;
    string lastname;
    uint age;
    Country nationality;

    bool isAnAdult()
    {
        return this->age >= this->nationality.legalAge;
    }

};

int main(int argc, char const *argv[])
{
    Country france = {"France", 18};
    Country usa = {"USA", 21};

    Person thomas = {"Thomas", "Le Goff", 27, france};

    cout << thomas.firstname << endl;
    cout << thomas.age << endl;

    if (thomas.isAnAdult()) {
        cout << thomas.age << endl;
    }

    Person martin = {"Martin", "Matin", 10, usa};

    cout << martin.firstname << endl;
    cout << martin.age << endl;

    if (martin.isAnAdult()) {
        cout << martin.age << endl;
    }

    return 0;
}