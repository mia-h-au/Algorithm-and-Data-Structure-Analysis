#include <bits/stdc++.h> 
using namespace std; 
  
// School Method for Integer Addition
string addSchool(string strI1, string strI2, int b) { 
    
    string bigStr, smallStr;

    // Find the longer int
    if (strI1.length() < strI2.length()) {
        bigStr = strI1;
        smallStr = strI2; 
    }

    else {
        bigStr = strI2;
        smallStr = strI1;         
    }

    // Initiate string result and carry
    string str = "";
    int carry = 0; 
  
    // Calculate string lengths
    int l1 = bigStr.length(), l2 = smallStr.length(); 
    int lenDiff = l2 - l1; 
  
    // Traverse from end of both strings 
    for (int i = l1 - 1; i >= 0; i--) { 
        // Use School Method for Integer Addition
        int sum = ((bigStr[i]-'0') + 
                   (smallStr[i + lenDiff]-'0') + 
                   carry); 
        str.push_back(sum % b + '0'); 
        carry = sum / b; 
    } 
  
    // Add remaining digits of smallStr
    for (int i = l2 - l1 - 1; i >= 0; i--) { 
        int sum = ((smallStr[i] - '0') + carry); 
        str.push_back(sum % b + '0'); 
        carry = sum / b; 
    } 
  
    // Add remaining carry 
    if (carry) {
        str.push_back(carry + '0'); 
    }
  
    // reverse string result
    reverse(str.begin(), str.end()); 
  
    return str; 
} 

// School Method for Integer Subtraction
string subSchool(string strI1, string strI2, int b) {

    int diff; // diff of each pair of digits of I1 and I2
    string result, str; // initiate final & temp result strings
    // bool positive; // whether result is positive

    // Find the bigger int
    string bigStr, smallStr;
    int i = 0; // for comparison

    if (strI1.length() > strI2.length()) {
        bigStr = strI1;
        smallStr = strI2; 
        // positive = true;
    }

    else if (strI1.length() < strI2.length()) {
        bigStr = strI2;
        smallStr = strI1;  
        // positive = false;       
    }
    
    // strI1.length() == strI2.length()
    else {

        while (i < strI1.length()) {
            if (strI1[i] > strI2[i]) {
                bigStr = strI1;
                smallStr = strI2;
                //positive = true;
                break;
            }            
            else if (strI1[i] < strI2[i]) {
                bigStr = strI2;
                smallStr = strI1;
                //positive = false;
                break;
            }
            else
                i++;
        }        
    }

    if (i == strI1.length())
        result = "0";
    
    else {

        // make smaller str have the same length as bigger string
        while (smallStr.length() < bigStr.length())
            smallStr.insert(0, "0");

        // School Method for Integer Subtraction
        for (int i = bigStr.length() - 1; i >= 0; --i) {
            diff = (bigStr[i] - '0') - (smallStr[i] - '0');

            if (diff >= 0) {
                str.insert(0, to_string(diff));
            }
            
            else {
                // get 1 from the more significant digit of I1
                int j = i - 1;
                while (j >= 0) {
                    bigStr[j] = ((bigStr[j] - '0') - 1) % b + '0';
                    if (bigStr[j] != 9)
                        break;
                    else
                        j--;
                }
                str.insert(0, to_string(diff + b));
            }

        }
    }
    
    // remove leading 0s
    result = str.erase(0, str.find_first_not_of('0'));

/*    if (!positive) {
        result = "-" + result;
    }*/ // Simplify based on conditions of assignment

    return result;

}

// Karatsuba Method for Integer Multiplication
// I1 and I2 are nonnegative
string mulKarat(string strI1, string strI2, int b) {
    

    int len = max(strI1.length(), strI2.length());

    // Make I1 and I2 have same length
    while (strI1.length() < len) 
        strI1.insert(0, "0");
    while (strI2.length() < len) 
        strI2.insert(0, "0");

    // Multiply two 1-digit numbers using addition
    if (len == 1) {        
        
        string tmp = "0";

        int intI2;

        istringstream iss (strI2);
        iss >> intI2;


        for (int i = 0; i < intI2; ++i) {
            tmp = addSchool(tmp, strI1, b);
        } 

        return tmp;
    }

    // I1 =  a1 * B^k + a0
    string a1 = strI1.substr(0, len / 2);
    string a0 = strI1.substr(len / 2, len - (len / 2));
    // I2 =  b1 * B^k + b0
    string b1 = strI2.substr(0, len / 2);   
    string b0 = strI2.substr(len / 2, len - (len / 2));

    // p2 = a1 * b1
    string p2 = mulKarat(a1, b1, b);
    // p0 = a0 * b0
    string p0 = mulKarat(a0, b0, b);
    // p1 = (a1 + a0) * (b1 + b0)
    string p1 = mulKarat(addSchool(a1, a0, b), addSchool(b1, b0, b), b);
    // p3 = (p1 - (p2 + p0))
    string p3 = subSchool(p1, addSchool(p2, p0, b), b);

    for (int i = 0; i < 2 * (len - (len / 2)); i++) {
        p2.append("0");
    }

    for (int i = 0; i < (len - (len / 2)); i++) {
        p3.append("0");
    }

    // p = I1 * I2 = p2 * B^(2*k) + p3 * B^k + p0
    string result = addSchool(addSchool(p2, p0, b), p3, b);
    // remove leading 0s
    result = result.erase(0, result.find_first_not_of('0'));

    return result;

} 

// Check if I1 >= I2 when strI1.length() >= strI2.length()
bool I1notSmaller(string strI1, string strI2, int b) {

    bool I1notSmaller = false;
    int i = 0;

    if (strI1.length() > strI2.length()) {
        I1notSmaller = true;
    }

    else if (strI1.length() == strI2.length()) {
        
        while (i < strI1.length()) {
            if (strI1[i] > strI2[i]) {
                //cout << i << " " << strI1[i] << " " << strI2[i] << endl;
                I1notSmaller = true;
                break;
            }
            else if (strI1[i] == strI2[i]) {
                i++;
            }
            else {
                I1notSmaller = false;
                break;                
            }
        }
    }

    if (i == strI1.length()) {
        I1notSmaller = true;
    }

    return I1notSmaller;      
}

// Division using Subtraction
string divSub(string strI1, string strI2, int b) {    

    // I1 < I2
    if (strI1.length() < strI2.length()) {
        //cout << "line1 \n";
        return "0";            
    } 
    // Check when strI1.length() >= strI2.length()
    // I1 < I2 
    else if (!I1notSmaller(strI1, strI2, b)) {
        //cout << "line2: strI1 = " << strI1 << " \n"; 
        return "0";          
    }
    // I1 >= I2
    else {
        int lenDiff = strI1.length() - strI2.length();
        string tmp = "1";

        if (lenDiff >= 1) {
            for (int i = 0; i < lenDiff - 1; i++) {
                tmp.append("0");
            }            
        }

        strI1 = subSchool(strI1, mulKarat(strI2, tmp, b), b); // strI1 = strI1 - (strI2 * tmp); 
        //cout << "line3: strI1 = " << strI1 << " \n";      
        return addSchool(divSub(strI1, strI2, b), tmp, b); // result + tmp
    }

}

// Main method
int main() { 
    
    string strIn;
    getline(cin, strIn);

    // Extract I1 from input
    string strI1 = strIn.substr(0, strIn.find(' '));
    strIn = strIn.erase(0, strI1.length() + 1);    

    // Extract I2 from input
    string strI2 = strIn.substr(0, strIn.find(' '));
    strIn = strIn.erase(0, strI2.length() + 1);

    int B;
    istringstream iss (strIn);
    iss >> B;

    cout << addSchool(strI1, strI2, B) << " " << mulKarat(strI1, strI2, B) << " " << divSub(strI1, strI2, B) << "\n"; 
    // cout << divSub(strI1, strI2, B) << "\n";

    return 0; 
} 