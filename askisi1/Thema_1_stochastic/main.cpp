#include<iostream>
#include<fstream>
#include<istream>
#include<string>
#include<cstdlib>
#include<vector>
#include<time.h>

#define telh_min 0.08 // define to poso pou plhrwneis otan distance <30 km 
#define telh_max 0.12 // define to poso pou plhrwneis otan distance >30 km
#define costAnaKm 0.65 // define to poso poy plhrwneis ana km

using namespace std;

int main()
{
	ofstream detailed("detailedOutput.txt");
    srand(time(0));
	int TSP_ARRAY[10][10];// o pinakas dedomenwn
	int  k, j;

	fstream in_file;
	in_file.open("TSP_ARRAY.txt");
	if (!in_file.is_open()) { detailed << "Could not open file!"; exit(1); }

	//OPEN FILE
	int i = 0; string ch; int ind;
	getline(in_file, ch);

	while (!in_file.eof()) {
		for (k = 0; k < 10; k++)
		{
			for (j = 0; j < 10; j++)
				in_file >> TSP_ARRAY[k][j]; //pernaw ta noumera tou arxeiou.txt ston 2D pinaka
		}
		i++;
	}
	ind = i - 1;
	in_file.close();//END OPEN FILE

	detailed << "   ";
	for (k = 0; k < 10; k++)
		detailed << "S" << k + 1 << "  ";
	detailed << endl;
	for (k = 0; k < 10; k++)
	{
		detailed << "S" << k + 1 << "  ";
		for (j = 0; j < 10; j++)
			detailed << TSP_ARRAY[k][j] << "  ";// o pinakas ths ekfwnhshs
		detailed << endl;
	}// print o pinakas ths ekfwnhshs

	double random[100]; // pinakas random timwn
	int countRandom = 0;//enas counter gia na vazw diaforetiko rand ka8e fora

	for (i = 0; i < 80; i++)
	{ 
		random[i] = ((double)rand() / (RAND_MAX));
		//detailed << random[i] << " ||";
	}//random generator array
	detailed << endl;

	int diadromes = 0;
	int segs= 9;// arxika exw 9 segments na xwrisw apo 0 mexri 1
	int pL = 0; // h seira pou koitaw--to pL pairnei times analgoga to pou paw apo to taksidi

	vector <double> segments;
	vector <int> values;
	vector <int> id;
	segments.clear();
	values.clear();
	id.clear();

	int count_seg = 0;
	int ban_lush[10] = { 0 };//edw opoia polh exw episkeftei ginetai 1
	double seg_portion;
	int pivot; // to pivot mou leei se pio segments eimai kai poia polh thelw	
	double sum_cost = 0.0; // TOTAL COST
	int a[11];

	while (diadromes<9) // h loupa gia tis diadromes
	{	
		detailed<<"           | ITERATION"<<diadromes+1<<" |"<<endl;
		seg_portion = 1.0 / segs * 1.0; // to kommati ka8e segment

		for(j=0;j<10;j++)
			if(TSP_ARRAY[pL][j] !=0 && ban_lush[j]==0)//vriskei ston sta8mo pou einai poioys sta8mous exw hdh paei
				{ 
				segments.push_back((count_seg + 1.0)*seg_portion);
				id.push_back(j);
				values.push_back(TSP_ARRAY[pL][j]);
				count_seg++;
				//detailed<<"inserted values"<<segments.back()<<"  "<<id.back()<<" "<<values.back()<<" -------------------"<<endl;
			}		
		detailed << "  No" << diadromes + 1 << " RANDOM NUMBER " << random[countRandom] << endl;

			if (random[countRandom] < segments.front())// an random < 1ou segment phgaine 1o dynato sta8mo
			{
				pivot = 0;
			}
			for (j = 0; j < count_seg; j++) {
				if (random[countRandom] > segments[j] && random[countRandom] < segments[j + 1])// vriskei se poio stha8mo paei analoga th rand
					pivot = j + 1;	
			}
			if (random[countRandom] > segments.back())// an random > tou final segment phgaine ston last dynato sta8mo
			{
				pivot = count_seg; 
			}
			//detailed<<"pivot----------"<<pivot+1<<endl;
		if (values[pivot] >= 30) // des an apostash megalyterh h mikroterh gia na vgaleis to analogo cost
		{
			sum_cost += values[pivot] * costAnaKm + telh_max * values[pivot];
		}
		else { sum_cost += values[pivot] * costAnaKm + telh_min * values[pivot]; }

		detailed << "TRAVEL No: " << diadromes + 1 << " from " << pL+1  << " to " << id[pivot] +1<< " WITH DISTANCE " << values[pivot] << " AND WITH TOTAL COST:  " << sum_cost << endl;
		
		a[diadromes+1] = id[pivot]+1;
		ban_lush[0]++; // bannarw 
		ban_lush[id[pivot]] += 1;// bannarw opou exw paei
		pL = id[pivot]; // allazw seira toy 2D pinaka dld se poio sta8mo paw
		pivot = 0;
		count_seg = 0;
		segs--; // meiwnw ta segments dioti meiwnontai oi pithanes lyseis

		segments.clear();
		values.clear();
		id.clear();

		diadromes++;
		countRandom++;

		if (diadromes == 9) // an diadromes =9 epestepse apo opou eisai ston sthathmo 1
		{
			detailed << endl;
			detailed<<"           | Final iteration |"<<endl;
			
			int index = 0;
			int return_cost = TSP_ARRAY[pL][0];
			if (return_cost >= 30)
			{
				sum_cost += return_cost * costAnaKm + telh_max * return_cost;
			}
			else { sum_cost += return_cost * costAnaKm + telh_min * return_cost; }

			detailed << "TRAVEL No: " << diadromes + 1 << " from " << pL + 1 << " to " <<index + 1 << " WITH DISTANCE " << return_cost << " AND WITH TOTAL COST:  " << sum_cost << endl;
			a[10] = 1;
		}
	detailed<<endl;
	}//loop while

	a[0] =  1;
	detailed<<endl;

	detailed << "---------SOLUTION---------" << endl;
	for (j = 0; j < 11; j++)
		detailed << "S" << a[j] << "-";
	detailed << endl;
	detailed << "total money spent ->" << sum_cost << endl;

	return 0;
}