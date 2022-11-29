//
// Created by qiwentao on 22-8-15.
//

#ifndef UNTITLED_PERSON_H
#define UNTITLED_PERSON_H

#include <bits/stdc++.h>

#include <utility>

using namespace std;

struct Person;
void read(istream &is, Person &person);



struct Person{
    friend void read(istream &is, Person &person);
    friend void print(ostream &os, const Person& person);

    static constexpr double rate = 6.5;
    static const int vecSize = 20;
    static vector<double> vec;
    static double weight;
private:
    string address;
    string name;
public:
    static int na1;
    static int na2;
    static int na3;
    static int na4;
    static int na5;

    [[nodiscard]] auto getName() const->string const & {return name;}
    [[nodiscard]] auto getAddress() const->string const & {return address;}
    Person() =default;
    Person(string  name,string  address):name(std::move(name)),address(std::move(address)){}
    explicit Person(istream &is){read(is,*this);}
};

void read(istream &is, Person &person){
    is>>person.name>>person.address;
}

void print(ostream &os, const Person& person){
    os<<person.name<<person.address;
}
double Person::weight=1.0;

constexpr double Person::rate;
vector<double> Person::vec(Person::vecSize);


#endif //UNTITLED_PERSON_H
