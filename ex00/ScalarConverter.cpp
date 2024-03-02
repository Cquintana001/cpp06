#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include "ScalarConverter.hpp"





static int ft_stoi(const std::string& str)
{
    int num;
    std::stringstream ss(str);

    ss >> num;
    return num;
}

static float ft_stof(const std::string& str)
{
    float num;
    std::stringstream ss(str);

    ss >> num;
    return num;
}

static double ft_stod(const std::string& str)
{
    double num;
    std::stringstream ss(str);

    ss >> num;
    return num;
}
enum literal_type {
    error,
    _pseudo_literal,
    _char,
    _int,
    _float,
    _double,
};

static bool isChar(const std::string& str)
{
	// Check if the length of the string is not equal to 1, indicating it's not a single character.
    if (str.length() != 1
	||str.at(0) < std::numeric_limits<char>::min()		// Check if the first character of the string is outside the range of char type or is a digit.
    || str.at(0) > std::numeric_limits<char>::max()
    || isdigit(str.at(0)))
            return false;
    return true;		// If all conditions are met, return true, indicating that the string represents a valid char.
}


static bool isInt(const std::string& str)
{
    // Loop through each character in the string
    for (size_t i = str.at(0) == '-' ? 1 : 0; i < str.length(); i += 1) {
        // Check if the character is not a digit
        if (!isdigit(str.at(i)))
            return false;
    }
    // If all characters are digits, return true, indicating that the string represents an integer.
    return true;
}


static bool isFloat(const std::string& str)
{
    bool decimal_point;

    // Check for special cases: "-inff", "+inff", "nanf"
    if (str == "-inff" || str == "+inff" || str == "nanf")
        return true;

    // Check if the last character is 'f'
    if (str.at(str.length() - 1) != 'f')
        return false;

    // Initialize found_point flag to false
    decimal_point = false;

    // Loop through each character in the string, except the last one
    for (size_t i = 0; i < str.length() - 1; i += 1)
    {
        // Check if the character is a point and it's already found
        if (str.at(i) == '.' && decimal_point)
            return false;
        // If the character is a point, set found_point flag to true
        else if (str.at(i) == '.')
        {
            decimal_point = true;
            continue; // Skip to the next iteration
        }
        // Check if the character is not a digit
        if (!isdigit(str.at(i)))
            return false;
    }
    // If all conditions are met, return true, indicating that the string represents a float
    return true;
}



static void literalChar(char ch)
{
    std::cout << "char: '" << ch << "'" << std::endl;
    std::cout << "int: " << static_cast<int>(ch) << std::endl;
    std::cout << "float: " << static_cast<float>(ch) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(ch) << ".0" << std::endl;
}
static bool isDouble(const std::string& str)
{
    bool decimal_point = false;

    // Check for special cases: "-inf", "+inf", "nan"
    if (str == "-inf" || str == "+inf" || str == "nan")
        return true;

    // Loop through each character in the string
    for (size_t i = 0; i < str.length(); i += 1)
    {
        // Check if the character is a decimal point and it's already found
        if (str.at(i) == '.' && decimal_point)
            return false;
        // If the character is a decimal point, set found_point flag to true
        else if (str.at(i) == '.')
        {
            decimal_point = true;
            continue; // Skip to the next iteration
        }
        // Check if the character is not a digit
        if (!isdigit(str.at(i)))
            return false;
    }
    // If all conditions are met, return true, indicating that the string represents a double
    return true;
}

static bool isPseudoLiteral(const std::string& literal) {
    if (literal == "-inff" || literal == "+inff" || literal == "nanf"
          || literal == "-inf" || literal == "+inf"  || literal == "nan")

		return(true);
	else	
		return(false);
}

static literal_type getType(const std::string& str)
{
    if (isChar(str))
        return _char;
    if (isInt(str))
        return _int;
    if (isFloat(str))
       return _float;
    if (isDouble(str))
       return _double;
    return error;
}

static void literalInt(int number)
{
    if (std::isprint(number))
        std::cout << "char: '" << static_cast<char>(number) << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    std::cout << "int: " << number << std::endl;
    std::cout << "float: " << static_cast<float>(number) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(number) << ".0" << std::endl;
}

static void literalFloat(float number)
{
    if (std::isprint(number))
        std::cout << "char: '" << static_cast<char>(number) << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    std::cout << "int: " << static_cast<int>(number) << std::endl;
    std::cout << "float: " << number << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(number) << ".0" << std::endl;
}


static void literalDouble(double number)
{
    if (std::isprint(number))
        std::cout << "char: '" << static_cast<char>(number)  << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
    std::cout << "int: " << static_cast<int>(number) << std::endl;
    std::cout << "float: " << static_cast<float>(number) << ".0f" << std::endl;
    std::cout << "double: " << number << ".0" << std::endl;
}

static void pseudoLiteral(literal_type dest_type, const std::string& pseudo_literal)
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl; 
    if (dest_type == _float)
    {
        std::cout << "float: " << pseudo_literal << std::endl;
        std::cout << "double: " << pseudo_literal.substr(0, pseudo_literal.length() - 1) << std::endl;
    }
    else if (dest_type == _double)
    {
        std::cout << "float: " << pseudo_literal + "f" << std::endl;
        std::cout << "double: " << pseudo_literal << std::endl;
    }
}

void ScalarConverter::convert(const std::string& str)
{
    switch (getType(str))
    {
        case _char:
            literalChar(str.at(0));
            break;

        case _int:
            literalInt(ft_stoi(str));
            break;

        case _float:
            if (isPseudoLiteral(str))
                pseudoLiteral(_float, str);
            else
                literalFloat(ft_stof(str));
            break;

        case _double:
            if (isPseudoLiteral(str))
                pseudoLiteral(_double, str);
            else
                literalDouble(ft_stod(str));
            break;

        default:
            std::cout << "Type incorrect" << std::endl;
            break;
    }
}