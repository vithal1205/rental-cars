#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

class Car
{
private:
    string carId;
    string brand;
    string model;
    double basePricePerDay;
    bool isAvailable;

public:
    Car(string carId, string brand, string model, double basePricePerDay)
    {
        this->carId = carId;
        this->brand = brand;
        this->model = model;
        this->basePricePerDay = basePricePerDay;
        this->isAvailable = true;
    }

    string getCarId() const
    {
        return carId;
    }

    string getBrand() const
    {
        return brand;
    }

    string getModel() const
    {
        return model;
    }

    double calculatePrice(int rentalDays) const
    {
        return basePricePerDay * rentalDays;
    }

    bool getIsAvailable() const
    {
        return isAvailable;
    }

    void rent()
    {
        isAvailable = false;
    }

    void returnCar()
    {
        isAvailable = true;
    }
};

class Customer
{
private:
    string customerId;
    string name;

public:
    Customer(string customerId, string name)
    {
        this->customerId = customerId;
        this->name = name;
    }

    string getCustomerId() const
    {
        return customerId;
    }

    string getName() const
    {
        return name;
    }
};

class Rental
{
private:
    Car *car;
    Customer *customer;
    int days;

public:
    Rental(Car *car, Customer *customer, int days)
    {
        this->car = car;
        this->customer = customer;
        this->days = days;
    }

    Car *getCar() const
    {
        return car;
    }

    Customer *getCustomer() const
    {
        return customer;
    }

    int getDays() const
    {
        return days;
    }
};

class CarRentalSystem
{
private:
    vector<Car> cars;
    vector<Customer> customers;
    vector<Rental> rentals;

public:
    void addCar(const Car &car)
    {
        cars.push_back(car);
    }

    void addCustomer(const Customer &customer)
    {
        customers.push_back(customer);
    }

    void rentCar(Car *car, Customer *customer, int days)
    {
        if (car->getIsAvailable())
        {
            car->rent();
            rentals.push_back(Rental(car, customer, days));
        }
        else
        {
            cout << "Car is not available for rent.\n";
        }
    }

    void returnCar(Car *car)
    {
        car->returnCar();
        auto it = rentals.begin();
        while (it != rentals.end())
        {
            if (it->getCar() == car)
            {
                it = rentals.erase(it);
                cout << "Car returned successfully.\n";
                return;
            }
            else
            {
                ++it;
            }
        }
        cout << "Car was not rented.\n";
    }

    void menu()
    {
        while (true)
        {
            cout << "===== Car Rental System =====\n";
            cout << "1. Rent a Car\n";
            cout << "2. Return a Car\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer

            if (choice == 1)
            {
                string customerName;
                cout << "\n== Rent a Car ==\n";
                cout << "Enter your name: ";
                getline(cin, customerName);

                cout << "\nAvailable Cars:\n";
                for (const auto &car : cars)
                {
                    if (car.getIsAvailable())
                    {
                        cout << car.getCarId() << " - " << car.getBrand() << " " << car.getModel() << "\n";
                    }
                }

                cout << "\nEnter the car ID you want to rent: ";
                string carId;
                getline(cin, carId);

                cout << "Enter the number of days for rental: ";
                int rentalDays;
                cin >> rentalDays;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer

                Customer newCustomer("CUS" + to_string(customers.size() + 1), customerName);
                addCustomer(newCustomer);

                Car *selectedCar = nullptr;
                for (auto &car : cars)
                {
                    if (car.getCarId() == carId && car.getIsAvailable())
                    {
                        selectedCar = &car;
                        break;
                    }
                }

                if (selectedCar != nullptr)
                {
                    double totalPrice = selectedCar->calculatePrice(rentalDays);
                    cout << "\n== Rental Information ==\n";
                    cout << "Customer ID: " << newCustomer.getCustomerId() << "\n";
                    cout << "Customer Name: " << newCustomer.getName() << "\n";
                    cout << "Car: " << selectedCar->getBrand() << " " << selectedCar->getModel() << "\n";
                    cout << "Rental Days: " << rentalDays << "\n";
                    cout << fixed << setprecision(2) << "Total Price: $" << totalPrice << "\n";

                    cout << "\nConfirm rental (Y/N): ";
                    string confirm;
                    getline(cin, confirm);

                    if (confirm == "Y" || confirm == "y")
                    {
                        rentCar(selectedCar, &customers.back(), rentalDays);
                        cout << "\nCar rented successfully.\n";
                    }
                    else
                    {
                        cout << "\nRental canceled.\n";
                    }
                }
                else
                {
                    cout << "\nInvalid car selection or car not available for rent.\n";
                }
            }
            else if (choice == 2)
            {
                cout << "\n== Return a Car ==\n";
                cout << "Enter the car ID you want to return: ";
                string carId;
                getline(cin, carId);

                Car *carToReturn = nullptr;
                for (auto &car : cars)
                {
                    if (car.getCarId() == carId && !car.getIsAvailable())
                    {
                        carToReturn = &car;
                        break;
                    }
                }

                if (carToReturn != nullptr)
                {
                    returnCar(carToReturn);
                }
                else
                {
                    cout << "Invalid car ID or car is not rented.\n";
                }
            }
            else if (choice == 3)
            {
                break;
            }
            else
            {
                cout << "Invalid choice. Please enter a valid option.\n";
            }
        }
        cout << "\nThank you for using the Car Rental System!\n";
    }
};

int main()
{
    CarRentalSystem rentalSystem;

    rentalSystem.addCar(Car("C001", "Toyota", "Camry", 60.0));
    rentalSystem.addCar(Car("C002", "Honda", "Accord", 70.0));
    rentalSystem.addCar(Car("C003", "Mahindra", "Thar", 150.0));

    rentalSystem.menu();
    return 0;
}
