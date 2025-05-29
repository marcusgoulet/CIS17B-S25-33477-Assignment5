#include <iostream>
#include <string>
#include <array>
#include <typeinfo>

template<typename T>  // original template to determine typename, converts type t name into readable string
struct TypeName {
  static std::string get() { return "unknown"; }
};

// specializations for different data types
template<> // Used to determine if typename is int (specialization)
struct TypeName<int> {
  static std::string get() { return "int"; }
};

template<>
struct TypeName<std::string> {
  static std::string get() { return "std::string"; }
};

template<> //Used to determine if typename is double (specialization)
struct TypeName<double> {
  static std::string get() { return "double"; }
};

// Generic package that handles all types
template<typename T>
class Package {
private:
  T item;
public:
  Package(T i) : item(i) {}
  // label that converts type T to readable string
  void label() {
    std::cout << "Generic package containing: " << TypeName<T>::get() << "\n";
  }
};

// Specialization for std::string
template<>
class Package<std::string> {
private:
  std::string item;
public:
  Package(std::string i) : item(i) {}
  void label() {
    std::cout << "Book package: \"" << item << "\"\n";
  }
};

// Partial specialization for pointers
template<typename T>
class Package<T*> {
private:
  T* item;
public:
  Package(T* i) : item(i) {}
  void label() {
    std::cout << "Fragile package for pointer to type: " << TypeName<T>::get() << "\n";
  }
};

template<typename T, int Size>
class Box {
private:
  std::array<T, Size> items;
  int count = 0;
public:
  bool addItem(const T& item) {
    if (count < Size) {
      items[count++] = item;
      std::cout << "Added item to box: \"" << item << "\"\n";
      return true;
    }
    return false;
  }

  void printItems() const {
    std::cout << "Box contents:\n";
    for (int i = 0; i < count; ++i) {
      std::cout << " - " << items[i] << "\n";
    }
  }
};

template<typename T>
void shipItem(const T& item) {
  std::cout << "Shipping item of type: " << TypeName<T>::get() << "\n";
}

template<>
void shipItem(const double& item) {
  std::cout << "Shipping temperature-controlled item: " << item << "°C\n";
}

int main() {

  Package<int> intPackage(23);
  intPackage.label();

  Package<std::string> bookPackage("Harry Potter and The Goblet of Fire");
  bookPackage.label();

  double temp = 23.34;
  Package<double*> pointerPackage(&temp);
  pointerPackage.label();

  std::cout << "\n";

  Box<std::string, 3> movieBox; // initialize box and add 3 items
  movieBox.addItem("Dune 2");
  movieBox.addItem("Blade Runner 2049");
  movieBox.addItem("The Babadook"); // unrelated to this assignment, but watch this film
  movieBox.printItems();

  std::cout << "\n";

  shipItem(100);
  shipItem(std::string("Apple USB-C type Charger"));
  shipItem(2.2);

  return 0;
}