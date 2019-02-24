#include <iostream>
using namespace std;

int main()
{
	int num = 11;
	int div3sum, notdiv3sum;

	for (int i = 0; i < 99; i++)
	{
		if ((num % 3) != 0)
			notdiv3sum += num;
		else
			div3sum += num;
		num++;
	}

	cout << "Sum of numbers divisible by 3 = " << hex << div3sum << endl;
	cout << "Sum of numbers not divisible by 3 = " << hex << notdiv3sum << endl;

return 0;
}
