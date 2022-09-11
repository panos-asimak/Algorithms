#include <iostream>
#include <istream>
#include <string>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <cmath>
#include <math.h>
#include <fstream>

using namespace std;

int main()
{
	ofstream detailed("detailedOutput.txt");
	double cost_pleonektiko = 169.92;
	double cost_stochastiko = 248.31;
	int k, j, count = 0;
	int diadromes_pleonekikou[11];
	int diadromes_stoxastikou[11];

	fstream in_file;

	in_file.open("GreedyResults.txt");
	if (!in_file.is_open())
	{
		detailed << "Could not open file!";
		exit(1);
	}

	// OPEN FILE
	int i = 0;
	string ch;
	int ind;
	int ind2;
	getline(in_file, ch);

	while (!in_file.eof())
	{

		in_file >> diadromes_pleonekikou[count];
		count++;
	}
	i++;

	ind = i - 1;
	in_file.close(); // END OPEN FILE

	count = 0;
	in_file.open("StochasticResults.txt");
	if (!in_file.is_open())
	{
		detailed << "Could not open file!";
		exit(1);
	}

	// OPEN FILE

	getline(in_file, ch);

	while (!in_file.eof())
	{

		in_file >> diadromes_stoxastikou[count];
		count++;
	}
	k++;

	ind2 = k - 1;
	in_file.close(); // END OPEN FILE
	detailed << "Greedy_solution-->";
	for (j = 0; j < 11; j++)
	{
		detailed << "S" << diadromes_pleonekikou[j] << "-";
	}
	detailed << endl
			 << "With total cost-->" << cost_pleonektiko << endl;
	detailed << endl;
	detailed << "Stochastic_solution-->";
	for (j = 0; j < 11; j++)
	{
		detailed << "S" << diadromes_stoxastikou[j] << "-";
	}
	detailed << endl;
	detailed << "With total cost-->" << cost_stochastiko << endl;
	detailed << endl
			 << "--------------------------------------------------" << endl;

	if (cost_pleonektiko - cost_stochastiko < 0)
	{
		detailed << "Best solution out of those two---->Greedy" << endl
				 << "With less cost =" << -1 * (cost_pleonektiko - cost_stochastiko) << endl;
	}
	else
	{
		detailed << "Best solution out of those two---->Stochastic" << endl
				 << "With less cost =" << cost_pleonektiko - cost_stochastiko << endl;
	} /* code */

} // end main