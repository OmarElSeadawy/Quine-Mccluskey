#include <iostream>
#include<cmath>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;
struct group
{
	string binary;
	int no_ones;
	int originalminterm;
};
group grouping;
vector<group> binaryarray;
vector <group> column2;
vector<vector<char>> decimalToBinary(vector <int> x, int n);
vector <int> read_validate_input(int n);
void binary(int num, vector<char>& bin);
int counting1s(group grouping, string s);
vector<group> sorting(vector<group>& binaryarray);
bool foundinvector(vector <string> v, string c);
bool onebitdiff(string, string);
string combine2minterms(string, string);
vector<vector<string>> callstringfromstruct(vector<group> binaryarray);
vector<string> produceminterms(vector<string>);
void removerepeating(vector<group>& column2);
void copying(vector<int> x, vector<group>& column2);
int main()
{
	int n;
	cout << "Hello" << endl;
	do
	{
		cout << "Please enter the number of values you need to work on ranging from 1 up to 16 variables:" << endl;
		cin >> n;

	} while (n<1 || n>16);
	vector<int> x = read_validate_input(n);
	vector<vector<char>> k = decimalToBinary(x, n);

	for (int i = 0; i<x.size(); i++)
	{
		string s(k[i].begin(), k[i].end());
		grouping.no_ones = counting1s(grouping, s);
		grouping.binary = s;
		binaryarray.push_back(grouping);
	}
	cout << "Before Sorting: " << endl;
	cout << "BINARY NUMBER         NUMBER OF ONES         CORRESPONDING MINTERM" << endl;
	for (int i = 0; i<x.size(); i++)
	{
		cout << "     " << binaryarray[i].binary << "                     " << binaryarray[i].no_ones << "                          " << x[i] << endl;
	}
	for (int i = 0; i<x.size(); i++)
	{
		binaryarray[i].originalminterm = x[i];
	}
	cout << "After Sorting: " << endl;
	cout << "BINARY NUMBER         NUMBER OF ONES         CORRESPONDING MINTERM" << endl;
	sorting(binaryarray);

	for (int i = 0; i<x.size(); i++)
	{
		cout << "     " << binaryarray[i].binary << "                     " << binaryarray[i].no_ones << "                          " << binaryarray[i].originalminterm << endl;

	}
	
	cout << endl;
	vector<vector <string>> returnedbinaries;
	returnedbinaries.reserve(10);
	cout << "Hi1";
	returnedbinaries = callstringfromstruct(binaryarray);
	cout << "Hi2";
	produceminterms(returnedbinaries);
	cout << "Hi3";
	for (int i = 0; i<returnedbinaries.size(); i++)
	{
		grouping.binary = returnedbinaries[i];
		column2.push_back(grouping);
	}
	cout << "COLUMN2:::::" << endl;
	for (int i = 0; i<returnedbinaries.size(); i++)
	{
		cout << "     " << column2[i].binary << endl;
	}
	//copying(x,column2);
	//removerepeating(column2);
	return 0;
}
// Function that reads the inputs from the user and validates them.
vector <int> read_validate_input(int n)
{
	int minterms;
	int dontcares;
	int g;
	do
	{
		cout << "Please enter the number of the minterms: " << endl;
		cin >> minterms;
		cout << "Please enter the number of the don'tcare terms: " << endl;
		cin >> dontcares;
	} while ((minterms + dontcares)>pow(2, n));
	vector <int> inputvalues;
	cout << "Please enter the minterms in order then enter the don'tcare terms:(make sure that numbers are not repeated or out of range): " << endl;
	for (int i = 0; i<(minterms + dontcares); i++)
	{
		cin >> g;
		inputvalues.push_back(g);
	}
	
	bool flag = false;
	for (int i = 0; i<(minterms + dontcares); i++)
	{
		if (inputvalues[i]<0 || inputvalues[i]>(pow(2, n) - 1))
		{
			cout << inputvalues[i] << " is an incorrect value!, Please enter the values again!" << endl;
			inputvalues.clear();
			flag = true;
		}
	}
	
	if (flag)
	{
		for (int i = 0; i<(minterms + dontcares); i++)
		{
			cin >> g;
			inputvalues.push_back(g);
		}
	}
	
	for (int i = 0; i<(minterms + dontcares); i++)
	{
		for (int j = i + 1; j < (minterms + dontcares); j++)
		{
			if (inputvalues[i] == inputvalues[j])
			{
				cout << "Repeated Values!, Please start all over again!" << endl;
				break;
			}
		}
	}
	
	return inputvalues;
}

// Function that converts from decimal to binary
vector<vector<char>> decimalToBinary(vector <int> x, int n)
{
	vector<vector<char>> bins;
	for (int i = 0; i<x.size(); i++)
	{
		vector<char> bin;
		binary(x[i], bin);
		long int m = bin.size();
		reverse(bin.begin(), bin.end());
		for (int k = 0; k< n - m; k++)
		{
			bin.push_back('0');
		}
		reverse(bin.begin(), bin.end());
		bins.push_back(bin);
	}

	return bins;
}
void binary(int num, vector<char>& bin)
{
	int rem;
	if (num <= 1)
	{
		char s = '0' + num;
		bin.push_back(s);
		return;
	}
	rem = num % 2;
	binary((num / 2), bin);
	char s = '0' + rem;
	bin.push_back(s);
}
int counting1s(group grouping, string s)
{
	int count = 0;
	for (int i = 0; i<s.length(); i++)
	{
		if (s.at(i) == '1')
		{
			count++;
		}
	}
	return count;
}

vector<group> sorting(vector<group>& binaryarray)
{
	bool swapped;
	for (long int i = (binaryarray.size()) - 1; i >= 1; i--)
	{
		swapped = false;
		for (int j = 0; j < i; j++)
		{
			if (binaryarray[j].no_ones > binaryarray[j + 1].no_ones)
			{
				swap(binaryarray[j], binaryarray[j + 1]);
				swapped = true;
			}
		}
	}
	return binaryarray;
}
bool onebitdiff(string c, string v)
{
	int flag = 0;
	for (int i = 0; i<c.length(); i++)
	{
		if (c[i] != v[i])
		{
			flag++;
		}

	}
	return (flag == 1);
}
string combine2minterms(string c, string v)
{
	string t = NULL;
	for (int i = 0; i<v.length(); i++)
	{
		if (c[i] != v[i])
		{
			t += "*";
		}
		else
		{
			t += c[i];
		}
	}
	return t;
}
vector<vector<string>> callstringfromstruct(vector<group> binaryarray)
{
	vector< vector<string> > v;
	v.reserve(binaryarray.size());
	for (int i = 0; i<binaryarray.size(); i++)
	{
		for (int j = 0; j<binaryarray[i].binary.length(); j++)
		{
			v[i][j] = binaryarray[i].binary[j];
		}

	}
	return v;
}
vector<string> produceminterms(vector<string> v)
{
	int *used;
	used = new int[v.size()];
	vector <string> returnedbinaries;
	for (int i = 0; i<v.size(); i++)
	{
		for (int j = i + 1; j<v.size(); j++)
		{
			if (onebitdiff(v[i], v[j]))
			{
				used[i] = 1;
				used[j] = 1;
				if (!foundinvector(returnedbinaries, combine2minterms(v[i], v[j])))
				{
					returnedbinaries.push_back(combine2minterms(v[i], v[j]));
				}
			}
		}

	}
	for (int i = 0; i<v.size(); i++)
	{
		cout << "check if this minterm is used:       " << used[i] << endl;
		if (used[i] == 0 && !foundinvector(returnedbinaries, v[i]))
		{
			returnedbinaries.push_back(v[i]);
		}
	}
	cout << "Column 2:" << endl;
	for (int i = 0; i<returnedbinaries.size(); i++)
	{
		cout << returnedbinaries[i] << endl;
	}
	return returnedbinaries;
}
bool foundinvector(vector <string> v, string c)
{
	for (int i = 0; i<v.size(); i++)
	{
		if (v[i].compare(c) == 0)
		{
			return true;
		}
	}
	return false;
}
void removerepeating(vector<group>& column2)
{
	for (int i = 0; i<column2.size(); i++)
	{
		for (int j = i + 1; j<column2.size(); j++)
		{
			if (column2[i].binary[i] == column2[i].binary[j])
			{
				column2[i].binary[i - 1] = column2[i].binary[i];
			}
		}
		column2.pop_back();
	}
}
void copying(vector<int> x, vector<group>& column2)
{
	for (int i = 0; i<column2.size(); i++)
	{
		column2[i].originalminterm = x[i];
		cout << column2[i].originalminterm << endl;
	}
}




