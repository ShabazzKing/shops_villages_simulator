#ifndef FACILITY_HPP
#define FACILITY_HPP

class Facility
{
private:
    unsigned x;
    unsigned y;
public:
    Facility(unsigned, unsigned);
    virtual unsigned get_x() const;
    virtual unsigned get_y() const;
};

class Shop : public Facility
{
private:
    unsigned customers;
    unsigned villages;
public:
    Shop(unsigned, unsigned);
    unsigned get_customers() const;
    void set_customers(unsigned);
    unsigned get_villages() const;
    void set_villages(unsigned);
};

class Village : public Facility
{
private:
    unsigned citizens;
    Shop * nearest;
    double distance;
public:
    Village(unsigned, unsigned, unsigned);
    unsigned get_citizens() const;
    Shop & get_shop() const;
    void set_shop(Shop &);
    double get_distance() const;
};

#endif
