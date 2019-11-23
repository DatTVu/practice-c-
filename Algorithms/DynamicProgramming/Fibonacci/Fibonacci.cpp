#include <iostream>

long fibonacci_dp(int num_th) {
	int* fibo= new int[num_th+2];
	fibo[0] = 0;
	fibo[1] = 1;	
	for (int i = 2; i <= num_th; i++) {
		fibo[i] = fibo[i - 1] + fibo[i - 2];
	}
	return fibo[num_th];	
}

int main()
{
	int input;
	std::cout << "Please enter the ordinal"<<std::endl;
	std::cin >> input;
    std::cout << "Our fibonnaci number is: " <<fibonacci_dp(input)<<std::endl; 
	system("pause");
}

 