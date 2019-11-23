#include <iostream>

int min(int x, int y) {
    return (x < y) ? x : y;
}

long bionomial_coefficient(int n, int k) {
    int* bionomial_matrix = new int[(n + 1)*(k + 1)];
    memset(bionomial_matrix, 0, sizeof(bionomial_matrix)*(n+1)*(k+1));
    int i, j;
    #define bionomial_matrix(i, j)  bionomial_matrix[i+j*(n+1)]        
    for (i = 0; i <= n; ++i)
        for (j = 0; j <= min(i, k); ++j) {
            if (j==0 || j== i)
            { 
                bionomial_matrix(i, j) = 1;
            }
            else
            {                
                bionomial_matrix(i, j) = bionomial_matrix[(i-1) + (j-1)*(n+1)] + bionomial_matrix[(i-1) + j*(n+1)];
            }            
        }            
    return bionomial_matrix(n, k);
}

int main()
{
    int n, k;
    std::cout << "N choose k program" << std::endl;
    std::cout << "Please enter N: " << std::endl;
    std::cin>>n;
    std::cout << "Please enter k: " << std::endl;
    std::cin >>k;
    std::cout << "Our bionomial coefficient is: \n" <<bionomial_coefficient(n,k)<<std::endl; 
    system("pause");
}

