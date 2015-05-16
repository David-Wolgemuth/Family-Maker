#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include "get_family.hpp"

using namespace std;

// 50% true/false >> male == true
bool get_gender()
{
	return rand() % 2 == 0;
}

// ~1.5 percent false (homosexual)
bool get_sexuality()
{
	return rand() % 65 != 0;
}

// Returns age based on parents' ages
int get_age(int spouse, int parent)
{
	if(!parent && !spouse){
		return rand() % 70 + 30; // Initial Person, age 30 - 100
	}

	if(!parent && spouse){
		int min = (spouse/2) + 7;	// "Half your age plus 7" rule
		int max = 2 * (spouse - 7);
		if(max > 98) max = 98;		// Unless over 98 or under 18
		if(min < 18) min = 18;
		return rand() % (max - min) + min;
	}

	int min, max = parent - 16;		// Children's age
	if (max > 25){
		min = max - 25;
	return rand() % 25 + min;
	}

	min = 0;
	return rand() % (parent-16);
}

// Returns year based on age
int get_year(int age)
{
	time_t now = time(0);
	int year = 1900 + localtime(&now)->tm_year;
	return year - age;
}

// Returns a first name based on gender
string get_name(bool male)
{
	ifstream boys ("word_lists/boy_names.txt");
	ifstream girls ("word_lists/girl_names.txt");

	vector<string> names;
	string name;

	if(male)
		while(getline(boys, name))
			names.push_back(name);
	else
		while(getline(girls, name))
			names.push_back(name);
	int i = rand() % names.size();
	return names[i];
}

// Returns a last name
string get_name()
{
	ifstream input ("word_lists/last_names.txt");

	vector<string> all_surnames;
	string surname;
	
	while(getline(input, surname))
		all_surnames.push_back(surname);
	
	int i = rand() % all_surnames.size();
	return all_surnames[i];
}

// Returns a vector of hobbies
vector<string> get_hobbies()
{
	ifstream hobbies ("word_lists/hobbies.txt");

	vector<string> all_hobbies;
	string hobby;

	while(getline(hobbies, hobby))
		all_hobbies.push_back(hobby);

	int num_of_hobbies = rand() % 6;	// No more than 6 hobbies

	vector<string> persons_hobbies;
	for(int i=0; i!=num_of_hobbies; ++i)
		persons_hobbies.push_back(all_hobbies[rand() % all_hobbies.size()]);

	return persons_hobbies;
}

// Get initial person
person get_person()
{
	person guy;
	guy.gender = get_gender();
	guy.first = get_name(guy.gender);
	guy.sexuality = get_sexuality();
	guy.age = get_age(0, 0);
	guy.year = get_year(guy.age);
	guy.surname = get_name();
	guy.hobbies = get_hobbies();
	return guy;
}

// Returns "Brother" / "Husband" etc. based on input type / gender
string get_title(string type, bool gender)
{
	if(type == "spouse"){
		if(gender)
			return "Husband";
		else
			return "Wife";
	}
	if(type == "parent"){
		if(gender)
			return "Father";
		else
			return "Mother";
	}
	if(type == "child"){
		if(gender)
			return "Son";
		else
			return "Daughter";
	}
	if(type == "sibling"){
		if(gender)
			return "Brother";
		else
			return "Sister";
	}
	return "No Relation";
}

// Returns member with first / last name and title
family_member get_family_member(person a, string type)
{
	family_member member;
	member.first = a.first;
	member.surname = a.surname;
	member.relation = get_title(type, a.gender);
	return member;
}

// Returns a spouse based on input person & alters input person's info
person get_spouse(person& first)
{
	person spouse;

	if(first.age < 18 || rand() % 4 == 0) // No spouse if under 18 or 25%
		return spouse;

	spouse.age = get_age(first.age, 0);
	spouse.year = get_year(spouse.age);
	if(first.sexuality)
		spouse.gender = !first.gender;
	else
		spouse.gender = first.gender;
	spouse.first = get_name(spouse.gender);
	spouse.sexuality = first.sexuality;

	if(spouse.sexuality){
		if(first.gender)	// Husband's last name is used
			spouse.surname = first.surname;
		else{
			spouse.surname = get_name(); 
			first.surname = spouse.surname;
		}
	}
	else
		spouse.surname = get_name(); // Homosexual couples keep original names
	spouse.hobbies = get_hobbies();
	
	first.family.push_back(get_family_member(spouse, "spouse"));
	spouse.family.push_back(get_family_member(first, "spouse"));

	return spouse;
}

// Alters the family info for input person a all in input vector
int get_sibling(person& sib, vector<person>& family)
{
	family_member osib;	// input person's family member info
	osib.first = sib.first;
	osib.surname = sib.surname;
	osib.relation = get_title("sibling", sib.gender);

	
	for(int i=0; i != family.size(); ++i){
		family_member sibling;
		if(family[i].first != sib.first){
			sibling.relation = get_title("sibling", family[i].gender);
			sibling.first = family[i].first;
			sibling.surname = family[i].surname;
			sib.family.push_back(sibling);		// Add's sibling info to input's family
			family[i].family.push_back(osib);	// Add's input's info into sibling
		}
	}
	return 0;
}

// Returns number of children based on parents' ages
int how_many_children(int one_age, int two_age)
{
	int parent_age = min(one_age, two_age), number=0;
	if(parent_age < 17)	// Too young
		return 0;
	if(parent_age < 25){	
		while(rand() % 3){
			if(number < 3)	// Likely to have 1/2, chances fall dramatically after
				++number;
			else{
				if(rand() % 2)
					++number;
			}
		}
	}
	if(24 < parent_age && parent_age < 35){
		while(rand() % 3)
			if(number < 4)	// Likely to have 2/3, chances fall dramatically after
				++number;
			else{
				if(rand() % 2)
					++number;
			}
	}
	else{
		while(rand() % 4)
			if(number < 5)	// Likely to have 3/4, chances fall dramatically after
				++number;
			else{
				if(rand() % 2)
					++number;
			}
	}
	return number;
}

// Returns number of children based on parents
int how_many_children(person one, person two)
{
	if(!one.sexuality)
		return 0;
	return how_many_children(one.age, two.age);
}

// Returns a child and alters family info of parents
person get_child(person& one, person& two)
{
	person child; // child's basic info
	child.gender = get_gender();
	child.first = get_name(child.gender);
	child.surname = one.surname;

	int min_age = min(one.age, two.age); // Youngest parent
	child.age = get_age(0, min_age);
	child.year = get_year(child.age);
	if(child.age > 10)	// Too young to have sexuality
		child.sexuality = get_sexuality();
	if(child.age > 4)	// Too young to have hobbies
		child.hobbies = get_hobbies();

	child.family.push_back(get_family_member(one, "parent"));
	child.family.push_back(get_family_member(two, "parent"));

	one.family.push_back(get_family_member(child, "child"));
	two.family.push_back(get_family_member(child, "child"));

	return child;
}

// Returns a new generation based on previous generation
vector<person> get_generation(vector<person>& old_gen)
{
	vector<person> new_gen;
	if(!old_gen.size()){
		person first_person=get_person();
		new_gen.push_back(first_person);
		return new_gen;
	}

	int old_gen_size = old_gen.size();
	for(int i=0; i!=old_gen_size; ++i){
		person spouse = get_spouse(old_gen[i]);
		if(spouse.first.size() > 0){
			int how_many = how_many_children(old_gen[i], spouse);
			vector<person> im_family; // Immediate Family (used to add family member info)
			for(int j=0; j!=how_many; ++j){
				person child = get_child(old_gen[i], spouse);
				get_sibling(child, im_family);
				im_family.push_back(child);
			}
			old_gen.push_back(spouse);
			for(int i=0; i!=im_family.size(); ++i)
				new_gen.push_back(im_family[i]);
		}
	}
	return new_gen;
}

// Returns a vector of generations
vector<vector<person> > get_family()
{
	vector<vector<person> > all_people;

	vector<person> a;
	bool adding = true;
	all_people.push_back(get_generation(a));
	int i=0;
	while(adding){
		a = get_generation(all_people[i]);
		if(!a.size()) // No more children
			adding = false;
		else
			all_people.push_back(a);
		++i;
	}
	return all_people;
}