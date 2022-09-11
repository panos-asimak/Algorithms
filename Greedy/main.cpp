#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <cstdlib>
#define telh_MinSeiras 0.08 // Define to poso pou SeiraEpanalispishrwneis otan distance <30 km
#define telh_max 0.12		// Define to poso pou SeiraEpanalispishrwneis otan distance >30 km
#define costAnaKm 0.65		// Define to poso poy SeiraEpanalispishrwneis ana km

using namespace std;

int main()
{
	ofstream detailed("detailedOutput.txt");
	int TSP_array[10][10]; // o pinakas dedomenwn
	int k, j;

	fstream in_file;
	in_file.open("TSP_ARRAY.txt");
	if (!in_file.is_open())
	{
		detailed << "Could not open file!";
		exit(1);
	}

	// OPEN FILE
	int i = 0;
	string ch;
	int ind;
	getline(in_file, ch);

	while (!in_file.eof())
	{
		for (k = 0; k < 10; k++)
		{
			for (j = 0; j < 10; j++)
				in_file >> TSP_array[k][j]; // pernaw ta noumera tou arxeiou.txt ston 2D pinaka
		}
		i++;
	}
	ind = i - 1;
	in_file.close(); // END OPEN FILE
	detailed << "   ";
	for (k = 0; k < 10; k++)
		detailed << "S" << k + 1 << "  ";
	detailed << endl;
	for (k = 0; k < 10; k++)
	{
		detailed << "S" << k + 1 << "  ";
		for (j = 0; j < 10; j++)
			detailed << TSP_array[k][j] << "  "; // Emfanizw ton pinaka ths ekfwnhshs
		detailed << endl;
	}
	int l = 0; // deikths gia na vrei to 1o stoixeio tou pinaka
	int MinSeiras;
	int SeiraEpanalispis = 0;	   // to shmeio pou vriskomai: 1h epanalhpsh einai 0 grammh meta an paw 7 polh paw sthn 6h grammh
	int visitedStations[10] = {0}; // pinakas mhdenikwn 8eseon apo 0 ews 10 opou an h polh einai hdh sthn lush tote ginetai 1 gi na mhn thn parw 3ana
	int index_MinSeiras = 0;
	double sum_cost = 0.0;	// to sunoliko kostos hn diadromhs
	int CountDiadromes = 0; // enas counter gia na vlepw poses diadromes exw kanei

	int print_diadromes[10]; // pinakas diadromwn
	print_diadromes[0] = 1;	 // 1 prwth diadromh einai panta 1
	print_diadromes[10] = 1; // h teleutaia diadromh einai panta 1

	int print_count = 1;
	detailed << endl;

	while (CountDiadromes < 9) // to while gia 9 epanalipseis
	{
		while (l < 10)
		{
			if (TSP_array[SeiraEpanalispis][l] != 0 && visitedStations[l] == 0) // vale MinSeiras to proto mh mhdeniko ths seiras
			{
				MinSeiras = TSP_array[SeiraEpanalispis][l];
				break;
			}
			else
			{
				l++;
			}
		} // while gia na 8etw ws MinSeiras to prwto mh mhdeniko ths seiras
		for (k = 0; k < 10; k++)
		{
			if (TSP_array[SeiraEpanalispis][k] != 0 && TSP_array[SeiraEpanalispis][k] <= MinSeiras && visitedStations[k] == 0)
			{ // vres to MinSeiras ths seiras
				MinSeiras = TSP_array[SeiraEpanalispis][k];
				index_MinSeiras = k;
			}
		} // for k

		if (MinSeiras >= 30)
		{ // vres costos analoga thn apostash
			sum_cost += MinSeiras * costAnaKm + telh_max * MinSeiras;
		}
		else
		{
			sum_cost += MinSeiras * costAnaKm + telh_MinSeiras * MinSeiras;
		}

		detailed << "                      | ITERATION " << CountDiadromes + 1 << "|" << endl;
		detailed << "Destination No:" << CountDiadromes + 1 << " from " << SeiraEpanalispis + 1 << " to " << index_MinSeiras + 1 << " with distance " << MinSeiras << " and total cost: " << sum_cost << endl;

		print_diadromes[print_count] = index_MinSeiras + 1;
		print_count++;
		CountDiadromes++;
		visitedStations[SeiraEpanalispis] += 1;

		detailed << "Banned destinations=";
		for (k = 0; k < 10; k++)
			detailed << visitedStations[k] << " ";
		detailed << endl;

		SeiraEpanalispis = index_MinSeiras;

		if (CountDiadromes == 9) // sthn telikh diadromh gia thn epistrofh kanw ksexwristo if mesa sth while
		{
			detailed << endl;
			index_MinSeiras = 0;
			MinSeiras = TSP_array[SeiraEpanalispis][index_MinSeiras];

			if (MinSeiras >= 30)
			{
				sum_cost += MinSeiras * costAnaKm + telh_max * MinSeiras;
			}
			else
			{
				sum_cost += MinSeiras * costAnaKm + telh_MinSeiras * MinSeiras;
			}
			detailed << "                  | FINAL ITERATION " << CountDiadromes + 1 << "|" << endl;
			detailed << "Destination No:" << CountDiadromes + 1 << " from " << SeiraEpanalispis + 1 << " to " << index_MinSeiras + 1 << " with distance " << MinSeiras << " and total cost: " << sum_cost << endl;
			print_diadromes[print_count] = index_MinSeiras + 1;
			print_count++;
		} // from 8 to 1 thelw
		detailed << endl;
	} // while megalo

	detailed << "------------solution-------------" << endl
			 << "Destinations-->";
	for (j = 0; j < 11; j++)
		detailed << "S" << print_diadromes[j] << "-";
	detailed << endl;
	detailed << "With total sum-->" << sum_cost << endl;

	return 0;
}