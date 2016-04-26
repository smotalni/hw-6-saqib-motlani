#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;

/*function extracts certain digits from socials after file has been read in*/
int extraction(int number)
{
    string initial ="000000000"; //9 string to convert social to string. 
    char *Dat= new char[100];
    sprintf(Dat, "%i", number);
    string val = (string) Dat;
    
    int x=0;
    
    for( int i=0; i<val.size(); i++)
    {
        initial[i] = val[x];
        x++;
    }
    string final = "0000"; //extracting digits, 3, 5, 7, 8
    final[0] = initial[2];
    final[1] = initial[4];
     final[2] = initial[6];
     final[3] = initial[7];
   
    return atoi(final.c_str()); //returning digits extracted
    
}

int quadratic_probe(int Hashtable[], int ind, int max) // max is a parameter being passed in that will be equivalent to the user input in main.
{
    int pos,i, square;
    pos=ind%max;				//uses user input to determine index
   
    
        square = 1;
       

		/*for loop checks if positions attempting to place index is is 0. If it is, returns ind*/
        for(i=1; i<100000; i++)
        {
            if(Hashtable[pos+(max+i)*(max+1)]==0)
            {
				return ind;
            }
            
        }
        
    
    return -1;	//table overflow
}


int main()
{
    
    string line;							//stores a line from the file to be read in
    string nums;							//stores indivisual numbers read in from lines
	string filename;						//string to store file name to be opened
    ifstream in;
	cout << "enter file name" << endl;		//prompt user for file name to be opened
	cin >> filename;
	in.open(filename);	
    int User_input = 0;						//user will input a number to be passed into the quadratic_probe function
    

    int * hashtable;						//hastable of size 100000 created
    hashtable=new int [100000];			
    
    for (int i = 0; i < 100000; i++)
    {
        hashtable[i] = 0;					//all indexes of array set to 0
    }
    
   
	/*if file not found, will tell user to try another file name*/
    if(!in.is_open())
    {
        cout << "FIle not found. Please try again"<<endl;
        
    }
    
    vector<int> Num;						//vector where numbers will be stored after separating file by commas.

	/*read a line in from the file. Then each line is separted into numbers based on comma locations*/
    while(in)
    {
        getline(in,line);
        istringstream ss(line);
        while(getline(ss, nums,','))
        {
            Num.push_back(atoi(nums.c_str()));
        }
        
    
        
        cout << "Enter a number between 1 and 450 million ";  //prompts user for input to be used in quadratic probing function
        cin >> User_input;
        
        if (User_input < 1 || User_input > 450000000)
        {
            cout << "Number not in range"<<endl;
            cout << "Enter a number: ";
            cin >> User_input;
        }
        
        else
        {
            cout << "Number entered:  " << User_input << endl;
        }
        
        
        int index;
        for (int i = 0; i < Num.size(); i++)
        {
            //Hash all the numbers
            index = extraction(Num[i]);

			/*if statement adds checks if index is empty. 
			If it is, number is added to hashtable*/


            if (hashtable[index] == 0)				
			{
                hashtable[index] = Num[i];
                cout << Num[i] << ": No collisions" << endl;
            }


			/*if collision occurs, quadratic_probing function called to determine new 
			index of where the number should be stored*/

            else 
			{
                index = quadratic_probe(hashtable, index, User_input);
                if (index == -1) 
				{
                    cout << "Full" << endl;
                }
                else
				{
                    hashtable[index] = Num[i];
                    cout << Num[i] << ": Collison has occured. Moved to: " << index << endl;
                }
            }
        }


        ofstream out;
        out.open("hashed_socials.txt");  //writes out numbers in hashtable, comma separated. 
       

		/*add commas in out put file. No comma added after last number*/
        for( int i=0; i<100000;i++)
        {
            out << hashtable[i];
            if(i<99999)out << ',';
            
        }
		out.close();
                          
    }
    return 0;
}



























