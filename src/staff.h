#pragma once

namespace staff {

class Staff {
 public:
    Staff(const char* name, int age, int salary);
    virtual ~Staff();
    virtual void show() const;

 protected:
    char* name;
    int age;
    int salary;
};

class Worker : protected Staff {
 public:
    Worker(const char* name, int age, int salary, int experience);
    ~Worker() override;
    void show() const override;

 protected:
    int experience;
};

class Engineer : protected Staff {
 public:
    Engineer(const char* name, int age, int salary, const char* specialization);
    ~Engineer() override;
    void show() const override;

 protected:
    char* specialization;
};

class Admin : protected Staff {
 public:
    Admin(const char* name, int age, int salary, int countOfSubordinates);
    ~Admin() override;
    void show() const override;

 protected:
    int countOfSubordinates;
};

}  // namespace staff
