#ifndef GUARD_PRINT_FAMILY
#define GUARD_PRINT_FAMILY

#include <string>
#include <vector>
#include "get_family.hpp"

// Return Details to Strings
std::string print_gender(bool); // Returns "Male" / "Female" string
std::string print_family_member(family_member); // Returns "Relation: First Last" string
std::string print_hobbies(std::vector<std::string>); // Returns hobbies separated by ", " string
std::string print_sexuality(bool); // Returns "Straight"/ "Homosexual" string

// Return Groups of Details to Strings
std::vector<std::string> print_all_details(person); // Returns a vector of strings of person's details
std::string print_all_details(person, std::string); // Returns a string of person's details
std::string print_all_details(std::vector<person>); // Returns a string of generation's details
std::string print_all_details(std::vector<std::vector<person> >); // Returns a string of a whole family's details


#endif