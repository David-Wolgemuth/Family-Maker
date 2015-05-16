#include <iostream>
#include <vector>
#include <string>
#include "print_family.hpp"
#include "get_family.hpp"

using namespace std;

// Returns "Male" / "Female" string
string print_gender(bool male)
{
	if(male)
		return "Male";
	return "Female";
}

// Returns "Relation: First Last" string
string print_family_member(family_member member)
{
	string line = member.relation;
	line += ": " + member.first + " " + member.surname;
	return line;
}

// Returns hobbies separated by ", " string
string print_hobbies(vector<string> hobbies)
{
	string line;
	for(int i=0; i!=hobbies.size(); ++i){
		if(i != hobbies.size()-1)
			line += hobbies[i] + ", ";
		else
			line += hobbies[i];
	}
	return line;
}

// Returns "Straight"/ "Homosexual" string
string print_sexuality(bool straight)
{
	if(straight)
		return "Straight";
	return "Homosexual";
}

// Returns a vector of strings of person's details
vector<string> print_all_details(person a)
{
	vector<string> lines;
	lines.push_back("Name: " + a.first + " " + a.surname);
	for(int i=0; i!=a.family.size(); ++i)
		lines.push_back(print_family_member(a.family[i]));
	lines.push_back("Gender: " + print_gender(a.gender));
	lines.push_back("Year: " + to_string(a.year) + " (" + to_string(a.age) + " years old)");
	if(a.age > 11)
		lines.push_back("Sexuality: " + print_sexuality(a.sexuality));
	if(a.age > 6)
		lines.push_back("Hobbies: " + print_hobbies(a.hobbies));
	return lines;
}

// Returns a string of person's details
string print_all_details(person a, string ch)
{
	vector<string> lines = print_all_details(a);
	string output = ch;
	for(int i=0; i!=lines.size(); ++i){
		output += lines[i] + ch;
	}
	return output;
}

// Returns a string of generation's details
string print_all_details(vector<person> people)
{
	string lines;
	for(int i=0; i!=people.size(); ++i)
		lines += print_all_details(people[i], "\n");
	return lines;
}

// Returns a string of a whole family's details
string print_all_details(vector<vector<person> > people)
{
	string lines;
	for(int i=0; i!=people.size(); ++i){
		lines += "<<----------Generation " + to_string(i+1) + "---------->>\n";
		lines += print_all_details(people[i]);
	}
	return lines;
}