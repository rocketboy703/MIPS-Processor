#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

/*
Created by Jah-Mali Brathwaite and William Swann
29 November 2023

The program should be able to accept a hex instruction.
Convert the instruction to binary
Parse the binary number into Register format:
op-code- Instruction opcode
rs – The 1st register source operand
rt – The 2nd register source operand
rd – The destination register
shamt – Shift amount
funct – Function code

Keep in mind which format of instruction (R or I)
R-format
6 bits - 5 bits - 5 bits - 5 bits - 5 bits - 6 bits

I-format 
6 bits - 5 bits - 5 bits - 16 bits

Perform tasks based on the opcode
Display the content in each register
After each instruction maintain the previous instructions in the registers(both).
Also print and show the actual instruction: i.e. add 
*/

struct ParsedVariables 
{
  string rs = "";
  string rt = "";
  string rd = "";
  string funct = "";
  string opCode = "";
  string address = "";
  bool isRType;
};

int charToInt(char c);
bool isBinary (string number);
bool isHexadecimal (string number);
int binaryToDec(string input);
string decToBinary(int decimal);
string binaryToHex(string input);
string hexToBinary(string input);
int stringToInt(string input);
bool isRType(string input);
ParsedVariables parseBinaryNumber(string binaryNumber);

string AND(string operand1, string operand2);
string OR(string operand1, string operand2);
string XOR(string operand1, string operand2);
string ADD(string operand1, string operand2);
string SUB(string operand1, string operand2);
string LW(string operand1, string operand2);
string SW(string operand1, string operand2);
bool BEQ(string operand1, string operand2);
bool BNE(string operand1, string operand2);
string ADDI(string operand1, string operand2);

int main ()
{
  string hexNum;
  char again;

  string registers[16] = {"0000", "0001", "0002", "0003", "0004", "0005", "0006", "0007", "0008", "0009", "000A", "000B", "000C", "000D", "000E", "000F"};

  string memory[16] = {"0000", "0001", "0002", "0003", "0004", "0005", "0006", "0007", "0008", "0009", "000A", "000B", "000C", "000D", "000E", "000F"};

  cout << "Welcome to Our Mips Proccessor!!\n\n";
  
  do 
  {

    for (int i = 0; i < 16; i++) 
    {
      if (i < 10) 
      {
        cout << "Register  " << i << ": " << registers[i];
        cout << "\tMemory  " << i << ": " << memory[i] << endl;
      } 
      else 
      {
        cout << "Register " << i << ": " << registers[i] << " ";
        cout << "\tMemory " << i << ": " << memory[i] << endl;
      }
    }

    cout << "\nEnter in your 8 Digit Hexadecimal Number: ";
    cin >> hexNum;

    while (!isHexadecimal(hexNum)) 
    {
      cout << "Invalid Hexadecimal Number. Please Try Again: ";
      cin >> hexNum;
    }

    string binaryNumber = hexToBinary(hexNum);

    ParsedVariables parsedVariables = parseBinaryNumber(binaryNumber);

    if (parsedVariables.isRType) 
    {    
      //AND
      if (parsedVariables.funct == "36") 
      {
        cout << "and " << "$" << binaryToDec(parsedVariables.rd) << ", " << "$" << binaryToDec(parsedVariables.rs) << ", " << "$" << binaryToDec(parsedVariables.rt) << endl << endl;
        registers[binaryToDec(parsedVariables.rd)] = AND(hexToBinary(registers[binaryToDec(parsedVariables.rs)]), hexToBinary(registers[binaryToDec(parsedVariables.rt)]));
      } 

      //OR
      else if (parsedVariables.funct == "37") 
      {
        cout << "or " << "$" << binaryToDec(parsedVariables.rd) << ", " << "$" << binaryToDec(parsedVariables.rs) << ", " << "$" << binaryToDec(parsedVariables.rt) << endl << endl;
        registers[binaryToDec(parsedVariables.rd)] = OR(hexToBinary(registers[binaryToDec(parsedVariables.rs)]), hexToBinary(registers[binaryToDec(parsedVariables.rt)]));
      } 

      //XOR
      else if (parsedVariables.funct == "24")
      {
        cout << "xor " << "$" << binaryToDec(parsedVariables.rd) << ", " << "$" << binaryToDec(parsedVariables.rs) << ", " << "$" << binaryToDec(parsedVariables.rt) << endl << endl;
        registers[binaryToDec(parsedVariables.rd)] = XOR(hexToBinary(registers[binaryToDec(parsedVariables.rs)]), hexToBinary(registers[binaryToDec(parsedVariables.rt)]));
      }

      //ADD
      else if (parsedVariables.funct == "32") 
      {
        cout << "add " << "$" << binaryToDec(parsedVariables.rd) << ", " << "$" << binaryToDec(parsedVariables.rs) << ", " << "$" << binaryToDec(parsedVariables.rt) << endl << endl;
        registers[binaryToDec(parsedVariables.rd)] = ADD(hexToBinary(registers[binaryToDec(parsedVariables.rs)]), hexToBinary(registers[binaryToDec(parsedVariables.rt)]));
      } 

      //SUB
      else if (parsedVariables.funct == "34") 
      {
        cout << "sub " << "$" << binaryToDec(parsedVariables.rd) << ", " << "$" << binaryToDec(parsedVariables.rs) << ", " << "$" << binaryToDec(parsedVariables.rt) << endl << endl;
        registers[binaryToDec(parsedVariables.rd)] = SUB(hexToBinary(registers[binaryToDec(parsedVariables.rs)]), hexToBinary(registers[binaryToDec(parsedVariables.rt)]));
      }
    }

    else
    { 
      //LW
      if (parsedVariables.opCode == "35") 
      {
        cout << "lw " << "$" << binaryToDec(parsedVariables.rt) << ", " << binaryToDec(parsedVariables.rs) << " ($" << binaryToDec(parsedVariables.address) << ")" << endl << endl;
        registers[binaryToDec(parsedVariables.rt)] = memory[binaryToDec(LW(hexToBinary(registers[binaryToDec(parsedVariables.rs)]), parsedVariables.address))];
      } 

      //SW
      else if  (parsedVariables.opCode == "43") 
      {
        memory[binaryToDec(SW(hexToBinary(registers[binaryToDec(parsedVariables.rs)]), parsedVariables.address))] = registers[binaryToDec(parsedVariables.rt)];

        cout << "sw " << "$" << binaryToDec(parsedVariables.rt) << ", " << binaryToDec(parsedVariables.rs) << " ($" << binaryToDec(parsedVariables.address) << ")" << endl << endl;
        registers[binaryToDec(parsedVariables.rt)] = memory[binaryToDec(LW(hexToBinary(registers[binaryToDec(parsedVariables.rs)]), parsedVariables.address))];
      } 

      //BEQ
      else if (parsedVariables.opCode == "4") 
      {
        
        if (BEQ(parsedVariables.rs, parsedVariables.rt)) 
        {
          cout << "beq True"<<endl;
        } 
        else 
        {
          cout << "beq False" << endl;
        }

      } 

      //BNE
      else if (parsedVariables.opCode == "5") 
      {
        if (BNE(parsedVariables.rs, parsedVariables.rt)) 
        {
          cout << "BNE True" << endl;
        } 
        else 
        {
          cout << "BNE False\n";
        }
      } 

      //ADDI
      else if (parsedVariables.opCode == "8")
      {
        registers[binaryToDec(parsedVariables.rt)] = ADDI(hexToBinary(registers[binaryToDec(parsedVariables.rs)]), parsedVariables.address);

        cout << "addi " << "$" << binaryToDec(parsedVariables.rt) << ", $" << binaryToDec(parsedVariables.rs) << ", " << binaryToDec(parsedVariables.address) << endl << endl;
        registers[binaryToDec(parsedVariables.rt)] = memory[binaryToDec(LW(hexToBinary(registers[binaryToDec(parsedVariables.rs)]), parsedVariables.address))];
      }
    }

    for (int i = 0; i < 16; i++) 
    {
      if (i < 10) 
      {
        cout << "Register  " << i << ": " << registers[i];
        cout << "\tMemory  " << i << ": " << memory[i] << endl;
      } 
      else 
      {
        cout << "Register " << i << ": " << registers[i] << " ";
        cout << "\tMemory " << i << ": " << memory[i] << endl;
      }
    }
    
    cout << "\nWould you like to use the proccessor again (Y/N) ? ";
    cin >> again;

    while (again != 'y' && again != 'Y' && again != 'N' && again != 'n') 
    {
        cout << "Invalid Entry. Try Agian: (Y/N) ";
        cin >> again;
    }

    cout << endl;
    
  } while (again == 'y' || again == 'Y'); 
}

/*---------------------------------------------------------
Takes an integer stored as a char and returns the integer 
equivalent
---------------------------------------------------------*/
int charToInt(char c)
{
  return (c - '0');
}

/*---------------------------------------------------------
Takes a number and returns true if the number is in binary
format and false otherwise
---------------------------------------------------------*/
bool isBinary (string number) 
{
    for (char c : number) 
    {
        if (c != '0' && c != '1') 
        {
            return false;
        }
    }
    return true;
}

/*---------------------------------------------------------
Returns true if the input is in proper hexadecimal format
and false otherwise
---------------------------------------------------------*/
bool isHexadecimal (string number) 
{
  if (number.length() != 8) 
  {
    return false;
  }

  for (int i = 0; i < 8; i++) 
  {
    if (number[i] != '0' && number[i] != '1' && number[i] != '2' && number[i] != '3' && number[i] != '4' && number[i] != '5' && number[i] != '6' && number[i] != '7' &&  number[i] != '8' && number[i] != '9' && number[i] != 'A' && number[i] != 'a' && number[i] != 'B' && number[i] != 'b' && number[i] != 'C' && number[i] != 'c' && number[i] != 'D' && number[i] != 'd' && number[i] != 'E' && number[i] != 'e' && number[i] != 'F' && number[i] != 'f')
    {
      return false;
    }
  }
  return true;
}

/*---------------------------------------------------------
Returns true if the instruction number is R-Type and
false otherwise
---------------------------------------------------------*/
bool isRType(string input)
{
  for (int i = 0; i < 6; i++)
  {
    if (input[i] == '1')
    {
      return false;
    }
  }
  return true;
}

/*---------------------------------------------------------
Parses the instruction into opCode, RS, RT, RD, funct
and address
---------------------------------------------------------*/
ParsedVariables parseBinaryNumber(string binaryNumber)
{
  string rs = "";
  string rt = "";
  string rd = "";
  string funct = "";
  string address = "";
  string opCode = "";

  ParsedVariables results;
  results.isRType = isRType(binaryNumber);

  if (results.isRType)
  {
    opCode = "0";

    for (int i = 6; i < 11; i++) 
    {
      rs += binaryNumber[i];
    }


    for (int i = 11; i < 16; i++) 
    {
      rt += binaryNumber[i];
    }

    for (int i = 16; i < 21; i++) 
    {
      rd += binaryNumber[i];
    }

    for (int i = 26; i < 32; i++) 
    {
      funct += binaryNumber[i];
    }

    funct = to_string(binaryToDec(funct));
    cout << "\nThis is a R-Type Instruction.\n";
    cout << "OpCode: " << opCode << endl;
    cout << "rs: $" << binaryToHex(rs)[1] << endl;
    cout << "rt: $" << binaryToHex(rt)[1] << endl;
    cout << "rd: $" << binaryToHex(rd)[1] << endl;
    cout << "funct: " << funct << endl;
  } 

  else 
  {
    for (int i = 0; i < 6; i++) 
    {
      opCode += binaryNumber[i];
    }

    opCode = to_string(binaryToDec(opCode));

    for (int i = 6; i < 11; i++) 
    {
      rs += binaryNumber[i];
    }

    for (int i = 11; i < 16; i++) 
    {
      rt += binaryNumber[i];
    }

    for (int i = 16; i < 32; i++) 
    {
      address += binaryNumber[i];
    }

    cout << "\nThis is an I-Type Instruction.\n";
    cout << "Opcode: " << opCode << endl;
    cout << "rs: $" << binaryToHex(rs)[1] << endl;
    cout << "rt: $" << binaryToHex(rt)[1] << endl;
    cout << "Address: " << binaryToDec(address) << endl;
  }
    results.rs = rs;
    results.rt = rt;
    results.rd = rd;
    results.funct = funct;
    results.opCode = opCode;
    results.address = address;

    return results;
}

/*---------------------------------------------------------
Converts user input from binary to decimal
---------------------------------------------------------*/
int binaryToDec(string input) 
{
  int output = 0;

  for (int i = input.length() - 1; i >= 0; i--) 
  {
    if (input[i] == '1') 
    {
      output += 1 << (input.length() - 1 - i);
    }
  }
  return output;
}

/*---------------------------------------------------------
Converts user input from decimal to binary
---------------------------------------------------------*/
string decToBinary(int decimal) 
{
  string binary = "";

  while (decimal > 0) 
  {
    int remainder = decimal % 2;
    binary = to_string(remainder) + binary;
    decimal /= 2;
  }

  while (binary.length() < 8) 
  {
    binary = '0' + binary;
  }

  return binary;
}

/*---------------------------------------------------------
Converts user input from hexadecimal to binary
---------------------------------------------------------*/
string hexToBinary(string input) 
{
  string output = "";

  for (int i = 0; i < input.length(); i++) 
  {
    char hexDigit = input[i];
    int decimal;

    if (hexDigit >= '0' && hexDigit <= '9') 
    {
      decimal = hexDigit - '0';
    } 

    else if (hexDigit >= 'A' && hexDigit <= 'F') 
    {
      decimal = hexDigit - 'A' + 10;
    } 

    else if (hexDigit >= 'a' && hexDigit <= 'f') 
    {
      decimal = hexDigit - 'a' + 10;
    } 

    else 
    {
      cerr << "Invalid hexadecimal character: " << hexDigit << endl;
      continue;
    }

    for (int j = 3; j >= 0; j--) 
    {
      int bit = (decimal >> j) & 1;
      output += to_string(bit);
    }
  }

  return output;
}

/*---------------------------------------------------------
Converts user input from binary to hexadecimal
---------------------------------------------------------*/
string binaryToHex (string input) 
{
    string hexStr = "";
    int binaryLength = input.length();
    int padding = (4 - (binaryLength % 4)) % 4;

    input = string(padding, '0') + input;

    for (int i = 0; i < binaryLength; i += 4) 
    {
        string fourBits = input.substr(i, 4);
        int decimalValue = stoi(fourBits, nullptr, 2);
        char hexDigit = '0' + decimalValue;

        if (decimalValue >= 10) 
        {
          hexDigit = 'A' + (decimalValue - 10);
        }
        hexStr += hexDigit;
    }
    return hexStr;

}

/*---------------------------------------------------------
Converts string to int
---------------------------------------------------------*/
int stringToInt(string input) 
{
  int num = 0;

  for (int i = 0; i < input.length(); i++) 
  {
    if (input[i] >= '0' && input[i] <= '9') 
    {
      num = num * 10 + (input[i] - '0');
    }
  }

  return num;
}

/*---------------------------------------------------------
Performs OR operation on two 16-bit binary strings and
returns the result in hexadecimal format
---------------------------------------------------------*/
string OR(string operand1, string operand2)
{
  string output = "";
  
  for (int i = 0; i < operand1.length(); i++)
  {
    if (operand1[i] == '1' || operand2[i] == '1')
    {
      output += '1';
    }

    else
    {
      output += '0';
    }
  }
  output = binaryToHex(output);
  
  return output;
}

/*---------------------------------------------------------
Performs AND operation on two 16-bit binary strings and
returns the result in hexadecimal format
---------------------------------------------------------*/
string AND(string operand1, string operand2)
{
  string output = "";

  for (int i = 0; i < operand1.length(); i++)
  {
    if (operand1[i] == '1' && operand2[i] == '1')
    {
      output += '1';
    }

    else
    {
      output += '0';
    }
  }
  output = binaryToHex(output);

  return output;
}

/*---------------------------------------------------------
Performs XOR operation on two 16-bit binary strings and
returns the result in hexadecimal format
---------------------------------------------------------*/
string XOR(string operand1, string operand2)
{
  string output = "";

  for (int i = 0; i < operand1.length(); i++)
  {
    if ((operand1[i] == '1' || operand2[i] == '1') && (operand1[i] != '1' && operand2[i] != '1'))
    {
      output += '1';
    }

    else
    {
      output += '0';
    }
  }
  output = binaryToHex(output);

  return output;
}

/*---------------------------------------------------------
Adds two binary numbers and returns the sum in hexadecimal
format
---------------------------------------------------------*/
string ADD(string operand1, string operand2)
{
  string output = "";
  int carry = 0;
  int sum;

  for (int i = 15; i >= 0; i--)
  {
    sum = (operand1[i] - '0') + (operand2[i] - '0') + carry;
    carry = sum / 2;
    output = to_string(sum % 2) + output;
  }

  if (carry > 0)
  {
    output = "1" + output;
  }

  output = binaryToHex(output);
  
  return output;
}

/*---------------------------------------------------------
Subtracts a binary number from another binary number and 
returns the difference in binary format
---------------------------------------------------------*/
string SUB(string operand1, string operand2)
{
  string output = "";
  bool negative = false;

  if (binaryToDec(operand1) < binaryToDec(operand2))
  {
    negative = true;
  }

  for (int i = operand1.length() - 1; i >= 0; i--)
  {
    if (operand1[i] == '1' && operand2[i] == '1')
    {
      output = "0" + output;
    }

    else if (operand1[i] == '0' && operand2[i] == '0')
    {
      output = "0" + output;
    }

    else if (operand1[i] == '1' && operand2[i] == '0')
    {
      output = "1" + output;
    }

    else if (operand1[i] == '0' && operand2[i] == '1')
    {
      output = "1" + output;
      operand1[i - 1] = '0';
    }
  }

  if (negative)
  {
    output = "0000000000000000";
  }
  
  output = binaryToHex(output);

  return output;
}

/*---------------------------------------------------------
Loads memory at (address + RS) into register at RT
---------------------------------------------------------*/
string LW(string operand1, string operand2)
{
  string output = "";
  int carry = 0;
  int sum;

  for (int i = 15; i >= 0; i--)
  {
    sum = (operand1[i] - '0') + (operand2[i] - '0') + carry;
    carry = sum / 2;
    output = to_string(sum % 2) + output;
  }

  if (carry > 0)
  {
    output = "1" + output;
  }

  return output;
}

/*---------------------------------------------------------
Stores register at (address + RT) into memory at RT
---------------------------------------------------------*/
string SW(string operand1, string operand2)
{
  string output = "";
  int carry = 0;
  int sum;

  for (int i = 15; i >= 0; i--)
  {
    sum = (operand1[i] - '0') + (operand2[i] - '0') + carry;
    carry = sum / 2;
    output = to_string(sum % 2) + output;
  }

  if (carry > 0)
  {
    output = "1" + output;
  }

  return output;
}

/*---------------------------------------------------------
Returns true if operands are equal and false otherwise 
---------------------------------------------------------*/
bool BEQ(string operand1, string operand2)
{
  for (int i = 0; i < operand1.length(); i++)
  {
    if (operand1[i] != operand2[i])
    {
      return false;
    }
  }
  return true;
}

/*---------------------------------------------------------
Returns true if operands are not equal and false otherwise 
---------------------------------------------------------*/
bool BNE(string operand1, string operand2)
{
  {
    for (int i = 0; i < operand1.length(); i++)
    {
      if (operand1[i] != operand2[i])
      {
        return true;
      }
    }
    return false;
  }
}

/*---------------------------------------------------------
Adds intermediate value to RS and returns the result in
hexadecimal format
---------------------------------------------------------*/
string ADDI(string operand1, string operand2)
{
  string output = "";
  int carry = 0;
  int sum;

  for (int i = 15; i >= 0; i--)
  {
    sum = (operand1[i] - '0') + (operand2[i] - '0') + carry;
    carry = sum / 2;
    output = to_string(sum % 2) + output;
  }

  if (carry > 0)
  {
    output = "1" + output;
  }

  output = binaryToHex(output);
  
  return output;
}
