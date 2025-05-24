#pragma once

namespace staff {

class Staff {
 public:
    Staff() = default;
    Staff(const Staff& other);
    Staff(const char* name, int age, int salary);
    virtual ~Staff();
    virtual void show() const;

    Staff& operator=(const Staff& other);

 protected:
    char* name;
    int age;
    int salary;
};

class Worker : public Staff {
 public:
    Worker(const char* name, int age, int salary, int experience);
    ~Worker() override;
    void show() const override;

 protected:
    int experience;
};

class Engineer : public Staff {
 public:
    Engineer(const char* name, int age, int salary, const char* specialization);
    ~Engineer() override;
    void show() const override;

 protected:
    char* specialization;
};

class Admin : public Staff {
 public:
    Admin(const char* name, int age, int salary, int countOfSubordinates);
    ~Admin() override;
    void show() const override;

 protected:
    int countOfSubordinates;
};

}  // namespace staff
