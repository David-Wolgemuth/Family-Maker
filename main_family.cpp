#include <ctime>
#include <iostream>
#include <vector>
#include "get_family.hpp"
#include "print_family.hpp"

using namespace std;

int main()
{
	srand(time(NULL)); // Reset random seed
	
	vector<vector<person> > all_people = get_family();
	cout << print_all_details(all_people) << endl;

	return 0;
}