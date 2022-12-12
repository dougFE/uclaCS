#include <iostream>
#include <string>
#include <cassert>
using namespace std;

bool invalidInput(const string a[], int n) { // Helper function
	if (n < 0)
		return true;
	return false;
}

int appendToAll(string a[], int n, string value) {
	if (invalidInput(a,n))
		return -1;
	for (int i = 0; i < n; i++) {
		a[i] += value;
	}
	return n;
}

int lookup(const string a[], int n, string target) {
	if (invalidInput(a, n))
		return -1;
	for (int i = 0; i < n; i++) {
		if (a[i] == target)
			return i;
	}
	return -1;
}

int positionOfMax(const string a[], int n) {
	if (invalidInput(a, n))
		return -1;
	string maxStr = a[0];
	int maxInd = -1;
	for (int i = 0; i < n; i++) {
		if (a[i] > maxStr) {
			maxStr = a[i];
			maxInd = i;
		}
	}
	return maxInd;
	
}

int rotateLeft(string a[], int n, int pos) {
	if (invalidInput(a, n) || pos < 0 || pos >= n)
		return -1;
	string save = a[pos];

	for (int i = pos+1; i < n; i++) {
		a[i - 1] = a[i];
	}
	a[n - 1] = save;
	return pos;
}

int countRuns(const string a[], int n) {
	if (invalidInput(a, n))
		return -1;

	if (n == 1)
		return 1;

	string last = a[0] + "!"; // Guarantee that last is not equal to any value of first string
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] != last) {
			// New run started
			count++;
			last = a[i];
		}
	}
	return count;
}

int flip(string a[], int n) {
	if (invalidInput(a, n))
		return -1;
	string save = "";
	for (int i = 0; i < (n-1)-i; i++) { // Swap char with it's mirrored position
		save = a[i];
		a[i] = a[(n - 1) - i];
		a[(n - 1) - i] = save;
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
	if (invalidInput(a1, n1) || invalidInput(a2, n2))
		return -1;
	int min;
	if (n1 > n2)
		min = n2;
	else
		min = n1;
	for (int i = 0; i < min; i++) {
		if (a1[i] != a2[i])
			return i;
	}
	return min;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
	if (invalidInput(a1, n1) || invalidInput(a2, n2) || n1 < n2)
		return -1;
	int currenta2 = 0; // Counter for which char of 
	int start = 0; // Position where sequence starts
	for (int i = 0; i < n1; i++) {
		if (a1[i] == a2[currenta2]) {
			if (currenta2 == 0) // Mark where streak starts
				start = i;
			currenta2++;
		}
		else
			currenta2 = 0;
		if (currenta2 == n2) // 
			return start;
	}
	return -1;

}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	if (invalidInput(a1, n1) || invalidInput(a2, n2))
		return -1;
	for (int i = 0; i < n1; i++) { // For each element in a1
		for (int j = 0; j < n2; j++) { // Check if it matches any element in a2
			if (a1[i] == a2[j])
				return i;
		}
	}
	return -1;
}

// Kind of cheating, but I just ignored the splitter and sorted the whole list
// Implementation is (probably) easier, and achieves the same thing but better
int split(string a[], int n, string splitter) {
	if (invalidInput(a, n))
		return -1;
	string save;
	if (n == 1)
		return n;
	
	for (int i = 0; i < n; i++) { // bubble sort the array
		for (int j = 0; j < n - 1; j++) {
			if (a[j] > a[j + 1]) { // If left element greater, swap places
				save = a[j];
				a[j] = a[j + 1];
				a[j + 1] = save;
			}
		}
	}

	for (int i = 0; i < n; i++) { // Find first item not < splitter
		if (a[i] >= splitter)
			return i;
	}
	return n;
}

int main() {	
	string g[4] = { "rishi", "margaret", "liz", "theresa" };
	string e[4] = { "gordon", "tony", "", "john" };

	string h[7] = { "rishi", "margaret", "gordon", "tony", "", "john", "liz" };
	string j[5] = {}; // Empty array
	string k[5] = { "", "", "", "dog", "" }; // Array with empty strings

	assert(lookup(h, 7, "john") == 5);
	assert(lookup(h, 7, "gordon") == 2);
	assert(lookup(h, 2, "gordon") == -1);
	assert(lookup(h, 7, "rishi") == 0);
	assert(lookup(h, 0, "rishi") == -1);
	assert(lookup(h, 3, "") == -1);
	assert(lookup(h, 7, "") == 4);
	assert(lookup(j, 0, "david") == -1);

	assert(positionOfMax(h, 7) == 3);
	assert(positionOfMax(h, 0) == -1);
	assert(positionOfMax(j, 0) == -1);
	assert(positionOfMax(k, 5) == 3);
	
	string odd[5] = { "a", "b", "c", "d", "e" };
	assert(rotateLeft(odd, 5, 0) == 0 && odd[0] == "b" && odd[4] == "a" && odd[2] == "d");
	assert(rotateLeft(odd, 3, 0) == 0 && odd[0] == "c" && odd[2] == "b" && odd[4] == "a");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "liz" && g[3] == "margaret" && g[0] == "rishi");
	assert(rotateLeft(j, 0, 0) == -1);
	assert(rotateLeft(odd, 5, 6) == -1);

	
	assert(differ(h, 4, g, 4) == 1);
	assert(differ(h, 1, g, 1) == 1);
	assert(differ(h, 0, g, 0) == 0);

	string l[1] = { "Dog" };
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "rishi?" && g[3] == "margaret?");
	assert(appendToAll(l, 1, "go") == 1 && l[0] == "Doggo");
	assert(appendToAll(g, -5, "Dog") == -1);
	assert(appendToAll(g, 2, "!") == 2 && g[0] == "rishi?!" && g[3] == "margaret?");

	string d[5] = { "margaret", "margaret", "margaret", "tony", "tony" };
	string m[10] = { "", "Dog", "Dog", "Cat", "Cat", "Cat", "Dog", "Cat", "Animal", "Reptile" };
	assert(countRuns(d, 5) == 2);
	assert(countRuns(d, 3) == 1);
	assert(countRuns(d, 0) == 0);
	assert(countRuns(m, 10) == 7);
	assert(countRuns(k, 5) == 3);
	
	string f[3] = { "liz", "gordon", "tony" };
	assert(flip(f, 3) == 3 && f[0] == "tony" && f[2] == "liz");
	assert(flip(k, 5) == 5 && k[1] == "dog");
	assert(flip(k, 0) == 0);
	assert((flip(m, 10) == 10) && m[1] == "Animal");
	assert(m[4] == "Cat" && m[3] == "Dog" && m[9] == "");
	assert(flip(g, -5) == -1);

	string n[10] = { "", "Dog", "Dog", "Cat", "Cat", "Cat", "Dog", "Dave", "Animal", "Reptile" };
	string o[3] = { "Dog", "Dog"};	
	string p[3] = { "Dave", "Sandra", "Jamie"};
	assert(subsequence(n, 10, o, 2) == 1);	
	assert(subsequence(n, 10, p, 3) == -1);
	assert(subsequence(n, 10, p, 1) == 7);
	assert(subsequence(n, 10, p, 0) == 0);
	assert(subsequence(n, 0, p, 3) == -1);

	string q[5] = { "a", "b", "c", "d", "e" };
	string r[5] = { "five", "dog", "", "", "c" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(lookupAny(q, 5, r, 5) == 2);
	assert(lookupAny(q, 0, r, 5) == -1);
	assert(lookupAny(q, 5, r, 4) == -1);
	assert(lookupAny(j, 0, r, 5) == -1);
	assert(lookupAny(q, 5, j, 0) == -1);

	string s[5] = { "e", "d", "b", "c", "a" };
	assert(split(s, 5, "c") == 2);
	assert(s[0] == "a" && s[1] == "b" && s[2] == "c" && s[3] == "d" && s[4] == "e");
	assert(split(s, 1, "c") == 1);
	assert(split(h, 7, "liz") == 3);
	assert(split(k, 5, "David") == 4 && k[4] == "dog");
	assert(split(k, 0, "danny") == 0);
	
	cout << "All tests succeeded" << endl;
	//for (int i = 0; i < 4; i++) {
	//	cout << i << ": " << g[i] << endl;
	//}
	
}