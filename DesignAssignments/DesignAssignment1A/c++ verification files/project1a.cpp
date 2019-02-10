#include <iostream>
#include <cmath>
using namespace std;

int main()
{

	int multiplicand, multiplier;

	cout << "Multiplicand(16-bit value) = ";
	cin >> hex >> multiplicand;
	cout << "Multiplier(8-bit value) = ";
	cin >> hex >> multiplier;

	int result = multiplicand * multiplier;
	cout << hex << result << endl;

return 0;
}
