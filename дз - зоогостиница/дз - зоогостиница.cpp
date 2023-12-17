#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <map>
/*
реализована работа с массивом: добавление / удаление элементов / вывод всех / поиск
работа с файлами: добавление / вывод всех

*/

class Animal
{
public:
    Animal(std::string name, std::string type, int age) :name_(name),type_(type), age_(age) {}

    void SetName(std::string n)
    {
        name_ = n;
    }
    std::string GetName()
    {
        return name_;
    }

    void SetType(std::string t)
    {
        type_ = t;
    }
    std::string GetType()
    {
        return type_;
    }

    void SetAge(int a)
    {
        age_ = a;
    }
    int GetAge()
    {
        return age_;
    }

private:
    std::string name_;
    std::string type_;
    int age_;
};

class Zoo
{
public:
    Zoo() = default;

    //добавить
    void AddAnimal(Animal *obj)
    {
        bool is_in = zoo_.find(obj) != zoo_.end();
        if (is_in)
        {
            std::cout << "Eror! this animal already exist.\n";
        }
        else {
            zoo_.insert(obj);
            std::cout << "Successfully!\n\n";
        }
    }

    //удалить из массива
    void DeleteAnimal(Animal* obj)
    {
        auto it = zoo_.find(obj);
        zoo_.erase(it);
    }

    //для пользователя::удалить из файла и из массива
    //не работает
    void SearchToDelete(std::string name, std::string type, int age)
    {
        for (auto& el : zoo_)
        {
            if (el->GetAge() == age )//&& el->GetName() == name && el->GetType() == type)
            {
                DeleteAnimal(el);
                std::fstream file;
                file.open("zoo.txt");
                std::string text;
                std::getline(file, text);
                std::string str1 = name;
                std::string str2 = type;
                std::string str3 = std::to_string(age);
                int pos1 = text.find(str1);
                int pos2 = text.find(str2);
                int pos3 = text.find(str3);
                text.erase(pos1, str1.size() + 2);
                text.erase(pos2, str2.size() + 2);
                text.erase(pos3, str3.size());
                file.close();
                file.open("zoo.txt", std::ios::out);
                file << text;
                file.close();
                std::cout << "Successfully!\n";
            }
        }
    }

    //список всех
    void ShowAll()
    {
        std::cout << "-----------------\nList of animals:\n";
        for (auto& el : zoo_)
        {
            std::cout << el->GetName() << ", " << el->GetType() << ", " << el->GetAge() << "\n";
        }
    }

    //поиск
    void SearchByName(std::string name)
    {
        for (auto &el:zoo_)
        {
            std::cout << "Search by name '" << name << "' results:\n";
            if (el->GetName() == name)
            {
                std::cout << el->GetName() << ", " << el->GetType() << ", " << el->GetAge() << "\n";
            }
            else {
                std::cout << "Not found :(";
            }

        }
    }

    void SearchByAge(int age)
    {
        for (auto& el : zoo_)
        {
            std::cout << "Search by age '" << age << "' results:\n";
            if (el->GetAge() == age)
            {
                std::cout << el->GetName() << ", " << el->GetType() << ", " << el->GetAge() << "\n";
            }
            else {
                std::cout << "Not found :(";
            }

        }
    }

    void SearchByType(std::string type)
    {
        for (auto& el : zoo_)
        {
            std::cout << "Search by type '" << type << "' results:\n";
            if (el->GetType() == type)
            {
                std::cout << el->GetName() << ", " << el->GetType() << ", " << el->GetAge() << "\n";
            }
            else {
                std::cout << "Not found :(";
            }

        }
    }

private:
    std::set<Animal*> zoo_;
};

void Interface();


int main()
{
    Interface();
    return 0;
}


void Interface()
{
    std::fstream file;
    file.open("zoo.txt", std::ios::app);
    Zoo zoo;
    int command;
    std::string name, type;
    int age;
    std::string art = R"(
   |\      _,,,---,,_
   /,`.-'`'    -.  ;-;;,_
  |,4-  ) )-,_..;\ (  `'-'
 '---''(_/--'  `-'\_) 
    )";    

    std::cout << art << "\n";
    std::cout << "\t\tHotel for animals\n";
    std::cout << "Hello! ";
    if (file.is_open())
    {
        do {

            std::cout << "List of commands : \n1 - add a new animal\n2 - delete an animal\n3 - show all animals in the zoo\n4 - exit\n"
                << "\nEnter a number to achieve the corresponding command: ";
            std::cin >> command;

            if (command == 1)
            {
                std::cout << "To add a new animal enter a name: ";
                std::cin >> name;
                std::cout << "Enter a type: ";
                std::cin >> type;
                std::cout << "Enter an age: ";
                std::cin >> age;
                Animal animal(name, type, age);
                zoo.AddAnimal(&animal);
                file << "\n" << "\n" << name << ", " << type << ", " << age;
                file.close();
                file.close();
            }
            else if (command == 2)
            {
                std::cout << "To delete a new animal enter a name: ";
                std::cin >> name;
                std::cout << "Enter a type: ";
                std::cin >> type;
                std::cout << "Enter an age: ";
                std::cin >> age;
                zoo.SearchToDelete(name, type, age);
            }

        } while (command != 4);
    }
    
}
    