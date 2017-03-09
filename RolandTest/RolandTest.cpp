// RolandTest.cpp : main project file.
/*    Numeric To String Simple App     */
/* Created By : Roland Antonius Kondoy */
/* Email : roland.antonius@gmail.com   */
/* github: https://github.com/jedi1983 */

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <sstream>

using namespace std;

class numberToString
{

	//protected properties
protected:	
	map<int,string> dataOne;
	map<int,string> dataTenth;
	map<int, string> ending;
	virtual void process(vector<int> input, string & ret) = 0;
	
	//public access
public:
	//virtual methods
	virtual string getDataToStringConv(vector<int> input) = 0;
	virtual void setDataOne() = 0;
	virtual void setDataTenth() = 0;
	
};

class numberToEng : numberToString
{
	//private variables
private:
	string tentSmall = "teen";
	string tenthEnd = "ty";
	//map<int, string> ending;

	void setDataOne()
	{
		dataOne[1] = "one";
		dataOne[2] = "two";
		dataOne[3] = "three";
		dataOne[4] = "four";
		dataOne[5] = "five";
		dataOne[6] = "six";
		dataOne[7] = "seven";
		dataOne[8] = "eight";
		dataOne[9] = "nine";

	}
	void setDataTenth()
	{
		dataTenth[1] = "ten";
		dataTenth[2] = "twenty";
		dataTenth[3] = "thirty";
		dataTenth[4] = "forty";
		dataTenth[5] = "fifty";
		dataTenth[11] = "eleven";
		dataTenth[12] = "twelve";
		dataTenth[13] = "thirteen";
		dataTenth[14] = "fourteen";
		dataTenth[15] = "fifteen";
	}
	void setEnding()
	{
		ending[4] = "thousand";
		ending[7] = "million";
		ending[10] = "billion";
		ending[13] = "trillion";
	}
    //private Methods

	string onePieceReturn(int dataIn)
	{
		string ret = "";
		ret = dataOne[dataIn];
		return ret;
	}

	string tenthPieceReturn(int dataIn)
	{
		string ret = "";
		if (dataIn < 6 && dataIn > 1)
			ret = dataTenth[dataIn];
		else if (dataIn > 1 && dataIn > 5)
			ret = dataOne[dataIn] + tenthEnd;
		else if (dataIn == 1)
			ret = "proc";
		return ret;
	}
	string tenthPieceReturnWithSmall(int Data_1, int Data_2)
	{
		string ret = "";
		if (Data_2 == 0)
			ret = dataTenth[Data_1];
		else if (Data_2 != 0 && Data_2 < 6)
			ret = dataTenth[((Data_1 * 10) + (Data_2 * 1))];
		else if (Data_2 > 5)
			ret = dataOne[Data_2] + tentSmall;
		return ret;
	}

	void process(vector<int> input, string & ret)
	{
		int digit = input.size();
		int sep = digit - 1;
		int holdData = 0;
		bool printSpace = false;
		bool printEnding = false;
		string tempStore = "";

		//getting data from Vector
		for (int x = sep; x >= 0; x--)
		{

			if (digit % 3 == 0 && input[x]!=0)//3 Digit Marker
			{
				tempStore = onePieceReturn(input[x]);
				tempStore = tempStore + " hundred";
				ret = ret + tempStore;
				tempStore = "";
				printSpace = true;
				printEnding = true;
			}
			else if ((digit + 1) % 3 == 0 || tempStore == "proc")//tenth
			{
				if (tempStore == "proc")
				{
					tempStore = tenthPieceReturnWithSmall(holdData, input[x]);
					holdData = 0;
					ret = ret +  tempStore;
					tempStore = "";
					printSpace = true;
					printEnding = true;
				}
				else
				{
					if(input[x]!=0)//if it is zero skip this part
					{
						tempStore = tenthPieceReturn(input[x]);
						if (tempStore != "proc")
						{
							ret = ret + tempStore;
							printSpace = true;
							printEnding = true;
						}
					}
					
					
				}


				if (tempStore == "proc")
					holdData = input[x];
			}
			else//smallest number
			{
				if(input[x]!=0)
				{
					tempStore = onePieceReturn(input[x]);
					ret = ret + tempStore;
					tempStore = "";
					printSpace = true;
					printEnding = true;
				}
				
			}
			if (tempStore != "proc" && x != 0)
			{
				if (printSpace != false)
					ret = ret + " ";
			}
			//check decimal
			if (digit == 4 && printEnding == true)//thousands
			{
				ret = ret + ending[digit]+" ";
				printEnding = false;
			}
			else if (digit == 7 && printEnding == true)//million
			{
				ret = ret + ending[digit] + " ";
				printEnding = false;
			}	
			else if (digit == 10 && printEnding == true)//billion
			{
				ret = ret + ending[digit] + " ";
				printEnding = false;
			}	
			else if (digit == 13 && printEnding == true)//trillion
			{
				ret = ret + ending[digit] + " ";
				printEnding = false;
			}	
			digit -= 1;//decrement digit
			printSpace = false;
			if (x == 0)//erasing if there are any accidental adding space issue
			{
				int point = ret.length()-1;				
				if (ret[point] == ' ')
					ret.erase(point, 1);
			}
		}
	}

	//public methods
public:

	numberToEng()
	{
		setDataOne();
		setDataTenth();
		setEnding();
	}

	string getDataToStringConv(vector<int> input)
	{
		string ret = "";
		process(input, ret);
		return ret;
	}

	
};

	class numberToVectorSize
	{
		//private properties
	private:

		vector<int> myVec;
		int calculate = 0;
		bool sanityTest = true;

		//public properties
	public:
		//changing the long Integer Number to As Vector Size iteratively by one,tenth,hundred,thousands,millions,billions 
		void changeToVec(long dataIn)
		{
			if (sanityTest == true)
			{
				calculate = 0;
				calculate = dataIn % 10;
				myVec.push_back(calculate);
				dataIn = dataIn / 10;
				if (dataIn != 0)
				{
					sanityTest = true;
					changeToVec(dataIn);
				}
				else
				{
					sanityTest = false;
					return;
				}
			}
		}
		//returning the Value
		vector<int> getVector()
		{
			return myVec;
		}
		//validate Data
		bool validNumber(string number)
		{
			int sep = number.length();

			if (sep == 0)
				return false; // have to input something

			for (int i = 0; i < sep; i++)
			if (number[i] >= '9')
				return false; // There is other Character That Is Not Number

			return true; //Data Valid
		}


	};


int main()
{
		
		numberToVectorSize dataIn;
		vector<int> myGG;
		long input = 0;
		string inputKbd;
		cout << "Please Insert Number \n";
		//cin >> input;
		getline(cin, inputKbd);
		
		if (dataIn.validNumber(inputKbd) == false)
		{
			cout << "there is Character That Is Not Number This Is Not Allowed \n";
			getline(cin, inputKbd);
			return 0;
		}
		
		stringstream (inputKbd) >> input;
	

		dataIn.changeToVec(input);
		myGG = dataIn.getVector();
		numberToEng tryEng;
		string testOut = "";
		testOut = tryEng.getDataToStringConv(myGG);
		cout << testOut;
		getline(cin,inputKbd);
		return 0;
}