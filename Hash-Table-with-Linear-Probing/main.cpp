#include <bits/stdc++.h> 
using namespace std; 

int capacity;

class HashTable
{
	public:
	char values[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	string keys[26];
	int statuses[26]; // 0: never used - 1: tombstone - 2: occupied
};

int search(string givenKey, HashTable *hashTable)
{
	char givenVal = givenKey[givenKey.size() - 1];
	int corSlot = givenVal - '0' - 49;

	// First try the corresponding table slot, if the objective key is there, then you have found it.
	if (hashTable->keys[corSlot].compare(givenKey) == 0)
	{
		//cout << "search1\n";
		return corSlot;
	}

	// If the corresponding slot is never used, terminate because we are certain that the objective is not in the table.
	else if (hashTable->statuses[corSlot] == 0)
	{
		//cout << "search2\n";
		return -1;
	}

	// If the slot is occupied but it’s not the objective, or the slot is a “tombstone”
	else
	{
		//cout << "search3\n";
		// move on to the next slot
		for (int i = corSlot + 1; i < corSlot + 26; ++i)
		{
			int modifiedI;
			// wrap around the table if the current slot is the last one
			if (i <= 25)
			{
				modifiedI = i;
			}
			else
			{
				modifiedI = i - 26;
			}
			
			if (hashTable->keys[modifiedI].compare(givenKey) == 0)
			{
				return modifiedI;
			}
		}
	}

	// only reach here if givenKey not found in table
	return -1;
}

void insert(string givenKey, HashTable *hashTable)
{
	// First perform searching to ensure that the key does not exist.
	// If it already exists, then do nothing.
	
	// If it does not
	if (search(givenKey, hashTable) == -1)
	{
		
		// take the last character of a key as the hash value
		char givenVal = givenKey[givenKey.size() - 1];
		int corSlot = givenVal - '0' - 49;
		//cout << "corSlot = " << corSlot << ", statuses[corSlot] = " << hashTable->statuses[corSlot];

		// If the corresponding table slot is not occupied (either “never used” or “tombstone”)
		if (hashTable->statuses[corSlot] != 2)
		{
			//cout << "insert1\n";
			// put the key there 
			hashTable->keys[corSlot] = givenKey;
			//the slot is now occupied
			hashTable->statuses[corSlot] = 2;
		}

		// If the corresponding slot is already occupied, try the next slot. 
		// Repeat trying until you find an unoccupied slot.
		else
		{
			//cout << "insert2\n";
			int foundPos;

			for (int i = corSlot + 1; i < corSlot + 26; ++i)
			{
				int modifiedI;
				// wrap around the table if the current slot is the last one
				if (i <= 25)
				{
					modifiedI = i;
				}
				else
				{
					modifiedI = i - 26;
				}

				if (hashTable->statuses[modifiedI] != 2)
				{
					foundPos = modifiedI;
					break;
				}				
			}
			
			// put the key there 
			hashTable->keys[foundPos] = givenKey;
			//the slot is now occupied
			hashTable->statuses[foundPos] = 2;
		}

	}

}

void remove(string givenKey, HashTable *hashTable)
{
	// given a key, use the searching process to locate its slot
	int givenPos = search(givenKey, hashTable);	

	// If the key is not in the table, then do nothing
	if (givenPos != -1)
	{
		//cout << "remove1\n";
		hashTable->keys[givenPos] = "empty";
		hashTable->statuses[givenPos] = 1;
	}
}

void printOutput(HashTable *hashTable)
{
	for (int i = 0; i < 26; ++i)
	{
		if (hashTable->statuses[i] == 2)
		{
			cout << hashTable->keys[i] << " ";
		}
	}
	cout << endl;
}

int main()
{
	HashTable *table = new HashTable();
	// Initiliase hash table
	for (int i = 0; i < 26; ++i)
	{
		table->statuses[i] = 0; // never used
		table->keys[i] = "empty";
	}

/*	// Test
	for (int i = 0; i < 26; ++i)
	{
		cout << table->values[i] << " " << table->statuses[i] << " " << table->keys << endl;
	}*/

	vector<string> moves;
	vector<string> modifications;
	vector<string> keys;
	string line, tmpMove, tmpMod;
	string tmpKey;
	getline(cin, line);
	stringstream ss(line);

	while (ss >> tmpMove) 
	{
		moves.push_back(tmpMove);
	}

	for (int i = 0; i < moves.size(); i++)
	{
		tmpMod = moves[i].substr(0, 1);
		modifications.push_back(tmpMod);
		moves[i].erase(0, 1);
		
		tmpKey = moves[i];
		keys.push_back(tmpKey);
	}

	for (int i = 0; i < keys.size(); ++i)
	{
		if (modifications[i].compare("A") == 0)
		{
			//cout << "add:" << keys[i] << " ";
			insert(keys[i], table);
		}
		else if (modifications[i].compare("D") == 0)
		{
			//cout << "delete:" << keys[i] << " ";
			remove(keys[i], table);
		}
		//cout << endl;
	}

	printOutput(table);
	
	return 0;
}