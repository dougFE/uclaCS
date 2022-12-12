#include <iostream>
using namespace std;


#include <iostream>
using namespace std;

void removeS(char str[]) {
    char* ptr = str;
    while (*ptr != 0) {
        if (*ptr == 's' || *str == 'S') {
            while (*(ptr + 1) != '\0') {
                *ptr = *(ptr + 1);
                ptr++;
            }
            *ptr = '\0';
            ptr = str;
        }
        else
            ptr++;
    }
}

int main()
{
    char msg[50] = "She'll shave a massless princess.";
    removeS(msg);
    cout << msg;  // prints   he'll have a male prince.
}