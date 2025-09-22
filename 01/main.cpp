#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

std::string convertTextToSound(std::string text) 
{
    if (text.empty()) return "";

    char first = std::toupper(text[0]);

    std::string res = "";
    res += std::tolower(first);
    for (size_t i = 1; i < text.size(); ++i) {
        char c = std::tolower(text[i]);
        if (c != 'h' && c != 'w')
            res += c;
    }

    for (size_t i = 0; i < res.size(); ++i) {
        char c = res[i];
        if (c == 'b' || c == 'f' || c == 'p' || c == 'v') res[i] = '1';
        else if (c == 'c' || c == 'g' || c == 'j' || c == 'k' || 
                 c == 'q' || c == 's' || c == 'x' || c == 'z') res[i] = '2';
        else if (c == 'd' || c == 't') res[i] = '3';
        else if (c == 'l') res[i] = '4';
        else if (c == 'm' || c == 'n') res[i] = '5';
        else if (c == 'r') res[i] = '6';
    }

    std::string noDups;
    noDups += res[0];
    for (size_t i = 1; i < res.size(); ++i)
        if (res[i] != res[i - 1]) noDups += res[i];

    std::string noVowels;
    noVowels += noDups[0];
    for (size_t i = 1; i < noDups.size(); ++i) {
        char c = noDups[i];
        if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && 
            c != 'u' && c != 'y' && !std::isdigit(noDups[i])) noVowels += noDups[i];
        else if (std::isdigit(noDups[i])) noVowels += noDups[i];
    }

    res = noVowels;
    res[0] = first;

    if (res.size() > 4) res = res.substr(0, 4);
    else {
        while (res.size() < 4) res += '0';
    }

    return res;
}

bool isEqual(std::string text1, std::string text2)
{
    return convertTextToSound(text1) == convertTextToSound(text2);
}

int main() {
    std::string text1{"Ashcraft"};
    std::string text2{"Ashcroft"};
    assert(isEqual(text1, text2));
    std::cout << "Test 1 passed: Ashcraft == Ashcroft" << std::endl;
    
    assert(convertTextToSound("Ashcraft") == std::string{"A261"});
    std::cout << "Test 2 passed: convertTextToSound('Ashcraft') == 'A261'" << std::endl;
    
    assert(convertTextToSound("") == "");
    std::cout << "Test 3 passed: Empty string" << std::endl;
    
    assert(convertTextToSound("A") == "A000");
    std::cout << "Test 4 passed: Single letter handled correctly" << std::endl;

    assert(convertTextToSound("Bob") == "B100");
    std::cout << "Test 5 passed: Short word handled correctly" << std::endl;
    
    assert(convertTextToSound("Whale") == "W400");
    assert(convertTextToSound("Hello") == "H400");
    std::cout << "Test 6 passed: h and w removing" << std::endl;
    
    assert(convertTextToSound("Fab") == "F100");
    assert(convertTextToSound("Pop") == "P100");
    assert(convertTextToSound("Viv") == "V100");
    std::cout << "Test 7 passed: Group 1 letters" << std::endl;
    
    assert(convertTextToSound("Chris") == "C620");
    assert(convertTextToSound("George") == "G620");
    assert(convertTextToSound("Jack") == "J200");
    std::cout << "Test 8 passed: Group 2 letters" << std::endl;
    
    assert(convertTextToSound("David") == "D130");
    assert(convertTextToSound("Thomas") == "T520");
    std::cout << "Test 9 passed: Group 3 letters work correctly" << std::endl;
    
    assert(convertTextToSound("Pfister") == "P236");
    assert(convertTextToSound("Tymczak") == "T522");
    std::cout << "Test 10 passed: Duplicate digit removing" << std::endl;
    
    assert(convertTextToSound("Implementation") == "I514");
    std::cout << "Test 11 passed: Long word" << std::endl;
    
    assert(isEqual("ASHCRaFT", "ashcroft"));
    std::cout << "Test 12 passed: Case difference" << std::endl;
    
    assert(convertTextToSound("Robert") == "R163");
    assert(convertTextToSound("Rupert") == "R163");
    assert(isEqual("Robert", "Rupert"));
    std::cout << "Test 13 passed: Known Soundex examples" << std::endl;
    
    std::cout << "\nAll tests passed successfully!" << std::endl;
    
    return 0;
}