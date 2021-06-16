#include "utils.h"
#include <math.h>
namespace ADT {
	bool IsPrime(int n) {
		bool result = false;
		if (n <= 1)
			return false;

		for (int i = 2; i < sqrt(n); ++i) {
			if (n % i == 0)
				return false;
		}
		return  true;
	}

	int GetNextPrime(int n) {
		while (!IsPrime(n)) {
			++n;
		}
		return n;
	}
}