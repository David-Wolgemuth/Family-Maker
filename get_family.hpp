#ifndef GUARD_GET_FAMILY
#define GUARD_GET_FAMILY

#include <string>
#include <vector>

// Used to explain how everyone is related
struct family_member{
	std::string first, surname, relation;
};

// Main person structure
struct person
{
	bool gender, sexuality;
	std::string first, surname;
	int age, year;
	std::vector<std::string> hobbies;
	std::vector<family_member> family;
};

// Get basic details about person
bool get_gender(); // 50% true/false >> male == true
bool get_sexuality(); // ~1.5 percent false (homosexual)
int get_age(int, int); // Returns age based on parents' ages
int get_year(int); // Returns year based on age
std::string get_name(bool); // Returns a first name based on gender
std::string get_name(); // Returns a last name
std::vector<std::string> get_hobbies(); // Returns a vector of hobbies
person get_person(); // Get initial person

// Family Members and Title
std::string get_title(std::string, bool); // Returns "Brother" / "Husband" etc. based on input type / gender
family_member get_family_member(person, std::string); // Returns member with first / last name and title

// Within Generation get relationships
person get_spouse(person&); // Returns a spouse based on input person & alters input person's info
int get_sibling(person&, std::vector<person>&); // Alters the family info for input person a all in input vector

// Add children to next generation
int how_many_children(int , int); // Returns number of children based on parents' ages
int how_many_children(person, person); // Returns number of children based on parents
person get_child(person&, person&); // Returns a child and alters family info of parents

// Build the family
std::vector<person> get_generation(std::vector<person>&); // Returns a new generation based on previous generation
std::vector<std::vector<person> > get_family(); // Returns a vector of generations

#endif