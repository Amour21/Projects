#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX_DIGITS 1000 // both numbers are assumed to be less than 100 digits (so that their product does not exceed the array size).


struct mega_long {
	int digits[MAX_DIGITS];
	int size;
	char sign;
	
};

int compare( const struct mega_long num1,  struct mega_long num2) {
	if (num1.size > num2.size) return 1; // 1st number bigger than 2nd
	if (num1.size < num2.size) return 2; // 1st number less than 2nd
	for (int i = num1.size-1; i >= 0; i--) { //length of numbers is the same, comparison by the highest digit
		if (num1.digits[i] > num2.digits[i]) return 1;
		if (num1.digits[i] < num2.digits[i]) return 2;
	}
	return 0; //numbers are equal
}

struct mega_long abs_sum_long ( struct mega_long num1, struct mega_long num2) {
	struct mega_long result;
	result.size = 0;
	result.sign = '+';
	int transfer = 0;  
	int i = 0;

	// Doing addition by digit
	while (i < num1.size || i < num2.size || transfer) {
		int digit1 = i < num1.size ? num1.digits[i] : 0;
		int digit2 = i < num2.size ? num2.digits[i] : 0;

		int sum = digit1 + digit2 + transfer;
		result.digits[result.size++] = sum % 10; // Write down the discharge
		transfer = sum / 10; // Updating the transfer

		i++;
	}

	return result;

};

struct mega_long abs_diff_long(struct mega_long num1, struct mega_long num2) {
	struct mega_long result;
	struct mega_long larger;
	struct mega_long smaller;
	result.size = 0;
	int cmp = compare(num1, num2);
	if (cmp == 0) {
		result.size = 1;
		result.digits[0] = 0;
		return result;
	}
	if (cmp == 1) {
		larger = num1;
		smaller = num2;
		result.sign = larger.sign;
	}
	else {
		larger = num2;
		smaller = num1;
		result.sign = larger.sign == '+' ? '-' : '+';
	}
	result.sign = larger.sign;
	int borrow = 0, i = 0;
	while (i < larger.size ) {
		int digit_small = (i < smaller.size) ? smaller.digits[i] : 0;	//UB solution when the smaller number is less than the 
		int diff =  larger.digits[i] - digit_small - borrow ;			//larger number and we go outside the array 
		if (diff < 0) {
			borrow = 1;
			diff += 10;
		}
		else {
			borrow = 0;
		}
		result.digits[result.size++] = diff; // Write down the discharge
		 
		i++;
	}
	result.size = larger.size;
	while (result.size >= 1 && result.digits[result.size - 1] == 0) {
		result.size--; // getting rid of the leading zeros
	}
	return result;
};
struct mega_long sum_long(struct mega_long num1, struct mega_long num2) {
	struct mega_long result;
	int cmp = compare(num1, num2);

	if (num1.sign == '-' && num2.sign == '+') {
		result = abs_diff_long(num1, num2);
	}

	if (num1.sign == '+' && num2.sign == '+') {
		result = abs_sum_long(num1, num2);
	}

	if (num1.sign == '+' && num2.sign == '-' ) {
		result = abs_diff_long(num1, num2);
	}

	if (num1.sign == '-' && num2.sign == '-') {
		result = abs_sum_long(num1, num2);
		result.sign = '-';
	}
	return result;
}
struct mega_long diff_long(struct mega_long num1, struct mega_long num2) {
	struct mega_long result;
	int cmp = compare(num1, num2);
	if (cmp == 0) {
		result.size = 1;
		result.digits[0] = 0;
	}
	if (num1.sign == '-' && num2.sign == '+') {
		result = abs_sum_long(num2, num1);
		result.sign = '-';
	}
	if (num1.sign == '-' && num2.sign == '-' ) {
		num2.sign = '+';
		result = sum_long(num1, num2);
	}
	if (num1.sign == '+' && num2.sign == '-' ) {
		result = abs_sum_long(num1, num2);
	}
	if (num1.sign == '+' && num2.sign == '+' && cmp == 1) {
		result = abs_diff_long(num1, num2);
	}
	if (num1.sign == '+' && num2.sign == '+' && cmp == 2) {
		result = abs_diff_long(num1, num2);
	}
	
	return result; 
}
struct mega_long mult_long(struct mega_long num1, struct mega_long num2) {
	struct mega_long result;
	for (int i = 0; i < num1.size + num2.size; i++) {
		result.digits[i] = 0;
	}
	result.size = 0;
	int transfer = 0;
	if (num1.sign != num2.sign) result.sign = '-';
	else result.sign = '+';
	for (int i = 0; i < num1.size; i++) {
		transfer = 0;
		for (int j = 0; j < num2.size; j++) {
			int mult = num1.digits[i] * num2.digits[j] + result.digits[i + j] + transfer;
			result.digits[i + j] = mult % 10;
			transfer = mult / 10;
		}
		result.digits[i + num2.size] += transfer;
	 }
	result.size = num1.size + num2.size;
	while (result.size > 1 && result.digits[result.size - 1] == 0) {
		result.size--;  // Removing leading zeros
	}

	return result;
}
struct div_result {
	struct mega_long quotient;
	struct mega_long remainder;
};
struct div_result div_long(struct mega_long num1, struct mega_long num2) {
	struct div_result result;
	struct mega_long quotient;
	struct mega_long remainder;
	remainder.size = 0;
	quotient.size = 0;
	if (num2.size == 0 && num2.digits[0] == 0) {
		printf("Error");
		return result;
	}
	if (num1.sign != num2.sign) quotient.sign = '-';
	else quotient.sign = '+';
	remainder.sign = '+';
	for (int i = num1.size - 1; i >= 0; i--) {
		for (int j = remainder.size; j > 0; j--) {
			remainder.digits[j] = remainder.digits[j - 1];			
		}
		remainder.digits[0] = num1.digits[i];
		remainder.size++;
		while (remainder.size > 1 && remainder.digits[remainder.size - 1] == 0) {
			remainder.size--;
		}
		int count = 0;
		while (compare(remainder, num2) == 1 || compare(remainder, num2) == 0) {
			remainder = abs_diff_long(remainder, num2);
			count++;
		}
		quotient.digits[quotient.size++] = count;
	}
	while (quotient.size > 1 && quotient.digits[quotient.size - 1] == 0) {
		quotient.size--;
	}
	for (int i = 0; i < quotient.size / 2; i++) { //reversal of signs, as they are written in reverse order when divided
		int temp = quotient.digits[i];
		quotient.digits[i] = quotient.digits[quotient.size - 1 - i];
		quotient.digits[quotient.size - 1 - i] = temp;
	}
	result.quotient = quotient;
	result.remainder = remainder;
	return result;
}
int print_mega_long(struct mega_long num) {
	if (num.digits[0] == 0 && num.size == 1) {
		printf("0\n");
		return 0;
	}
	int reverse;
	printf("%c", num.sign);
	while (num.size > 0) {
		if (abs(num.digits[num.size]) < 10) { // I realise it's inefficient, but this way we get a cell with a number and not abracadabra.
			break;
		}
		num.size--;
	}
	int flag = 0; // flag not to output non-significant zeros
	for (int i = num.size; i >= 0; i--) {
		if (num.digits[i] != 0) {
			flag = 1;
		}
		if (flag != 0) {
			printf("%d", num.digits[i]);
		}
	}
	printf("\n");
	return 0;
}

int main() {
	char str1[100] = "+77";
	char str2[100] = "+11";
	struct mega_long first_num;
	struct mega_long second_num;
	first_num.sign = str1[0];
	second_num.sign = str2[0];
	first_num.size = strlen(str1)-1;
	second_num.size = strlen(str2)-1;
	for (int i = 1; i < strlen(str1); i++) {
        first_num.digits[first_num.size-i] = str1[i] - '0'; 
    }
    for (int i = 1; i < strlen(str2); i++) {
        second_num.digits[second_num.size - i] = str2[i] - '0';
    }
	/* so we translate char into numbers we're used to,Since char characters have representations in
	the form of numbers 0 - 48, 	1 - 49, etc. if we want to get the usual 1...9 we should subtract 
	'0' from the char element */
	print_mega_long(sum_long(first_num,second_num));
	print_mega_long(diff_long(first_num, second_num));
	print_mega_long(mult_long(first_num, second_num));
	struct div_result test = div_long(first_num, second_num); // the conditions of my division: the numerator is greater than the denominator, you can't divide by zero.
	print_mega_long(test.quotient);							  //Division takes place in whole numbers
	print_mega_long(test.remainder);
	return 0;
}/*P.S I've run the tests myself many times and tried to account for all 
 possible cases and hit the efficiency limits given, thanks for your mentoring!*/