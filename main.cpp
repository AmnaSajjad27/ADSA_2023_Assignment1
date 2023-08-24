// Assignment 1

#include <iostream>
#include <string>

using namespace std;

//school method of addition 
string addition(string num1, string num2, string base)
{
    // convert base string to an integer
    int _base = std::stoi(base);

    /* check base given is less than 10 
    if (_base > 10)
    {
        cout << "The base is too big!\n" <<endl;
        return 0;
    }
    */
    // add leading zeros 
    int length_num1 = num1.length();
    int length_num2 = num2.length();

    // if length of num1 > num2, then add add zeros to num2
    if (length_num1 > length_num2)
    {
        for(int i = 0; i < (length_num1 - length_num2); i++)
        {
            num2 = "0" + num2;
        }
    }
    else if (length_num2 > length_num1)
    {
        for(int i = 0; i < (length_num2 - length_num1); i++)
        {
            num1 = "0" + num1;
        }
    }
    // append another 0 to make the sum, for carry over if needed 
    num1 = "0" + num1;
    num2 = "0" + num2;

    // initalise sum and carry 
    string sum;
    int carry = 0;

    for (int i = (num1.length() - 1); i >= 0; i --)
    {
        int one = num1[i] - '0';
        int two = num2[i] - '0';

        // from rightmost to leftmost, digits are coverted to integers 
        // if sum of the two digits and the carry is more than the base, there will be carry over
        if (one + two + carry >= _base)
        {
            sum = to_string(one + two + carry - _base) + sum;
            carry = 1;
        }
        else 
        {
            sum = to_string(one + two + carry) + sum;
            carry = 0;
        }
    }
    // remove any leading zeros 
    if (sum[0] == '0')
    {
        sum = sum.substr(1, sum.length());
    }
    return sum;
}

// primitive multiplication
string pri_Mul(string num1, string num2, string base)
{
    // function to multiply when either of operands is one digit
    int _base = std::stoi(base);
    /*
    // base no bigger than 10
    if (_base > 10)
    {
        cout << "The base is too big!\n" << endl;
        return 0;
    }
    */
    string operand;
    int product;
    // check where num1 or num2 is 1 digit long 
    if (num1.length() == 1)
    {
        product = num1[0] - '0';
        // append a zero to allign the numbers 
        operand = "0" + num2;
    }
    else 
    {
        product = num2[0] - '0';
        operand = "0" + num1;
    }

    string product_final;
    int carry = 0;

    // iteriate through each digit in the opernd string (LSD first)
    // perform multiplication with the product value
    for (int i = (operand.length() - 1); i >= 0; i--)
    {
        // if there is carry
        int op = operand[i] - '0';
        if (op * product + carry >= _base)
        {
            product_final = to_string((op * product + carry) % _base) + product_final;
            carry = (op * product + carry) / _base;
        }
        else
        {
            product_final = to_string(op * product + carry) + product_final;
            carry = 0;
        }
    }
    // Remove leading zero from the product_final string
    // While loop to iteriate while the length of product_final string is greater than 1
    // And while the first character is '0'
    while (product_final.length() > 1 && product_final[0] == '0')
    {
        product_final = product_final.substr(1, product_final.length());
    }
    return product_final;
}

// subtract method
string subtract(string num1, string num2, string base)
{
    int _base = std::stoi(base);
    /*
    if (_base > 10)
    {
        cout << "The base is too big!\n" << endl;
        return 0;
    }
    */
    while (num2.length() < num1.length())
    {
        num2 = "0" + num2;
    }
    int carry = 0;
    string subtract;

    for (int i = (num1.length() - 1); i >= 0; i--)
    {
        int one = num1[i] - '0';
        int two = num2[i] - '0';

        if (one - two - carry < 0)
        {
            subtract = to_string(one + _base - two - carry) + subtract;
            carry = 1;
        }
        else
        {
            subtract = to_string(one - two - carry) + subtract;
            carry = 0;
        }
    }
    while (subtract.length() > 1 && subtract[0] == '0')
    {
        subtract = subtract.substr(1, subtract.length());
    }
    return subtract;
}

/* Karatsuba Multiplication */
// Multiply 

string karatsuba(string num1, string num2, string base)
{
    // base case
    if (num1.length() == 1 || num2.length() == 1)
    {
        return pri_Mul(num1, num1, base);
    }

    // split the operands
    int length_num1 = num1.length();
    int length_num2 = num2.length();
    // find which is longer
    int n = max(length_num1, length_num2);
    // half of max to split
    int half = n / 2;
    // substrings 
    string a, b, c, d;
    if (half >= length_num1)
    {
        a = "0";
        b = num1;
        c = num2.substr(0, length_num2 - half);
        d = num2.substr(length_num2 - half, half);
    }
    else if (half >= length_num2)
    {
        a = num1.substr(0, length_num1 - half);
        b = num1.substr(length_num1 - half, half);
        c = "0";
        d = num2;
    }
    else
    {
        a = num1.substr(0, length_num1 - half);
        b = num1.substr(length_num1 - half, half);
        c = num2.substr(0, length_num2 - half);
        d = num2.substr(length_num2 - half, half);
    }
    // multiply each string using privMult
    string ac = pri_Mul(a, c, base);
    string bd = pri_Mul(b, d, base);
    string ad_plus_bc = pri_Mul(addition(a, b, base), addition(c, d, base), base);
    ad_plus_bc = subtract(ad_plus_bc, ac, bd);
    ad_plus_bc = subtract(ad_plus_bc, bd, base);

    for(int i = 0; i < 2 * half; i++)
    {
        // USE DOUBLE QUOTES
        ac = ac + "0";
    }
    for(int i = 0; i < half; i++)
    {
        ad_plus_bc = ad_plus_bc + "0";
    }
    // Remove trailing zeros
    while(ac.length() > 1 && ac[0] == '0')
    {
        ac = ac.substr(1, ac.length());
    }
    while (ad_plus_bc.length() > 1 && ad_plus_bc[0] == '0')
    {
        ad_plus_bc = ad_plus_bc.substr(1, ad_plus_bc.length());
    }
    return(addition(addition(ac, ad_plus_bc, base), bd, base));
}

// STOLEN MAIN
int main(){
    string input;
    getline(cin,input);
    int end1 = input.find_first_of(" ");
    input[end1] = '*';
    int end2 = input.find(" ");
    string firstOperand = input.substr(0, end1);
    string secondOperand = input.substr(end1 + 1, end2 - end1 - 1);
    string base = input.substr(end2 + 1, input.length() - end2 - 1);    
    
    try
    {
        string sum = addition(firstOperand, secondOperand, base);
        string product = karatsuba(firstOperand, secondOperand, base);
        cout << sum << " " << product << endl;
    }
    catch(const char* msg)
    {
        cerr << msg << endl;
    }
    
    return 0;
}