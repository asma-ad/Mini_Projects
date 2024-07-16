#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class clsString
{
private:
    string _Value;

public:
    // constractors
    clsString()
    {
        _Value = "";
    }
    clsString(string Value)
    {
        _Value = Value;
    }

    // get & set funtions
    void setValue(string Value)
    {
        _Value = Value;
    }
    string getValue()
    {
        return _Value;
    }
    // Property declaration
    __declspec(property(get = getValue, put = setValue)) string value;

    // ---length---
    static short Length(string text)
    {
        return text.length();
    };
    short Length()
    {
        return _Value.length();
    };

    // ---count words methods---
    static short countWords(string text)
    {

        string delim = " ";
        short counter = 0;
        short pos = 0;
        string sWord;

        // use find() function to get the position of the delimiters
        while ((pos = text.find(delim)) != std::string::npos)
        {
            sWord = text.substr(0, pos); // store the word
            if (sWord != "")
            {
                counter++;
            }
            // erase() until positon and move to next word.
            text.erase(0, pos + delim.length());
        }
        if (text != "")
        {
            counter++; // it counts the last word of the string.
        }

        return counter;
    }
    short countWords()
    {
        return countWords(_Value);
    };

    // ---upper first letters of each word---
    static string upperFirstLetterOfEachWord(string text)
    {
        bool isFirstLetter = true;

        for (short i = 0; i < text.length(); i++)
        {

            if (text[i] != ' ' && isFirstLetter)
            {
                text[i] = toupper(text[i]);
            }
            isFirstLetter = (text[i] == ' ' ? true : false);
        }

        return text;
    }
    void upperFirstLetterOfEachWord()
    {
        _Value = upperFirstLetterOfEachWord(_Value);
    }

    // ---lower First Letter Of Each Word---
    static string lowerFirstLetterOfEachWord(string text)
    {
        bool isFirstLetter = true;

        for (short i = 0; i < text.length(); i++)
        {

            if (text[i] != ' ' && isFirstLetter)
            {
                text[i] = tolower(text[i]);
            }

            isFirstLetter = (text[i] == ' ' ? true : false);
        }
        return text;
    }
    void lowerFirstLetterOfEachWord()
    {
        _Value = lowerFirstLetterOfEachWord(_Value);
    }

    // ---Upper all string---
    static string upperAllString(string text)
    {
        for (short i = 0; i < text.length(); i++)
        {
            text[i] = toupper(text[i]);
        }
        return text;
    }
    void upperAllString()
    {
        _Value = upperAllString(_Value);
    }

    // ---Lower all string---
    static string lowerAllString(string text)
    {
        for (short i = 0; i < text.length(); i++)
        {
            text[i] = tolower(text[i]);
        }
        return text;
    }
    void lowerAllString()
    {
        _Value = lowerAllString(_Value);
    }

    // ---Invert Letter Case---
    static char invertLetterCase(char c)
    {
        return isupper(c) ? tolower(c) : toupper(c);
    }

    // ---Invert All Letters Case---
    static string invertAllLettersCase(string text)
    {
        for (short i = 0; i < text.length(); i++)
        {
            text[i] = invertLetterCase(text[i]);
        }
        return text;
    }
    void invertAllLettersCase()
    {
        _Value = invertAllLettersCase(_Value);
    }

    // ---Count letters---
    enum enWhatToCount
    {
        SmallLetters = 0,
        CapitalLetters = 1,
        All = 3
    };
    static short countLetters(string text, enWhatToCount WhatToCount = enWhatToCount::All)
    {
        if (WhatToCount == enWhatToCount::All)
        {
            return text.length();
        }

        short counter = 0;
        for (short i = 0; i < text.length(); i++)
        {
            if (WhatToCount == enWhatToCount::CapitalLetters && isupper(text[i]))
                counter++;

            if (WhatToCount == enWhatToCount::SmallLetters && islower(text[i]))
                counter++;
        }

        return counter;
    }

    // ---count capital letters---
    static short countCapitalLetters(string text)
    {
        short counter = 0;
        for (short i = 0; i < text.length(); i++)
        {
            if (isupper(text[i]))
                counter++;
        }
        return counter;
    }
    short countCapitalLetters()
    {
        return countCapitalLetters(_Value);
    }

    // ---count small letters---
    static short countSmallLetters(string text)
    {
        short counter = 0;
        for (short i = 0; i < text.length(); i++)
        {
            if (islower(text[i]))
                counter++;
        }
        return counter;
    }
    short countSmallLetters()
    {
        return countSmallLetters(_Value);
    }

    // ---Count Specific Letter---
    static short countSpecificLetter(string text, char Letter, bool MatchCase = true)
    {
        short counter = 0;
        for (short i = 0; i < text.length(); i++)
        {
            if (MatchCase)
            {
                if (text[i] == Letter)
                    counter++;
            }
            else
            {
                if (tolower(text[i]) == tolower(Letter))
                    counter++;
            }
        }

        return counter;
    }
    short countSpecificLetter(char Letter, bool MatchCase = true)
    {
        return countSpecificLetter(_Value, Letter, MatchCase);
    }

    // ---is vowel---
    static bool isVowel(char Ch1)
    {
        Ch1 = tolower(Ch1);

        return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));
    }

    // ---Count Vowels---
    static short countVowels(string text)
    {
        short counter = 0;
        for (short i = 0; i < text.length(); i++)
        {
            if (isVowel(text[i]))
                counter++;
        }

        return counter;
    }
    short countVowels()
    {
        return countVowels(_Value);
    }

    // --- Split ---
    static vector<string> Split(string text, string Delim)
    {
        vector<string> vString;
        short pos = 0;
        string sWord;

        // use find() function to get the position of the delimiters
        while ((pos = text.find(Delim)) != std::string::npos)
        {
            // store the word
            sWord = text.substr(0, pos);
            // add word to vec
            // if (sWord != "")
            //{
            vString.push_back(sWord);
            //}
            // erase() until positon and move to next word
            text.erase(0, pos + Delim.length());
        }
        // add the last word of the string
        if (text != "")
        {
            vString.push_back(text);
        }
        return vString;
    }
    vector<string> Split(string Delim)
    {
        return Split(_Value, Delim);
    }

    // ---Trim methods---
    static string trimLeft(string text)
    {
        for (short i = 0; i < text.length(); i++)
        {
            if (text[i] != ' ')
            {
                return text.substr(i, text.length() - i);
            }
        }
        return "";
    }
    void trimLeft()
    {
        _Value = trimLeft(_Value);
    }

    static string trimRight(string text)
    {

        for (short i = text.length() - 1; i >= 0; i--)
        {
            if (text[i] != ' ')
            {
                return text.substr(0, i + 1);
            }
        }
        return "";
    }
    void trimRight()
    {
        _Value = trimRight(_Value);
    }

    static string Trim(string text)
    {
        return (trimLeft(trimRight(text)));
    }
    void Trim()
    {
        _Value = Trim(_Value);
    }

    // ---Join String---
    static string joinString(vector<string> vString, string Delim)
    {
        string text = "";
        for (string& s : vString)
        {
            text = text + s + Delim;
        }

        return text.substr(0, text.length() - Delim.length());
    }
    static string joinString(string arrString[], short Length, string Delim)
    {
        string text = "";
        for (short i = 0; i < Length; i++)
        {
            text = text + arrString[i] + Delim;
        }

        return text.substr(0, text.length() - Delim.length());
    }

    // ---Reverse words in string---
    static string reverseWordsInString(string str)
    {
        vector<string> vString;
        string str2 = "";
        vString = Split(str, " ");
        vector<string>::iterator i = vString.end(); // iterator
        while (i != vString.begin())
        {
            --i;
            str2 += *i + " ";
        }
        str2 = str2.substr(0, str2.length() - 1); // remove last space
        return str2;
    }
    void reverseWordsInString()
    {
        _Value = reverseWordsInString(_Value);
    }

    // ---replac eWord---
    static string replaceWord(string text, string StringToReplace, string sRepalceTo, bool MatchCase = true)
    {
        vector<string> vString = Split(text, " ");
        for (string& s : vString)
        {
            if (MatchCase)
            {
                if (s == StringToReplace)
                {
                    s = sRepalceTo;
                }
            }
            else
            {
                if (lowerAllString(s) == lowerAllString(StringToReplace))
                {
                    s = sRepalceTo;
                }
            }
        }
        return joinString(vString, " ");
    }
    string teplaceWord(string StringToReplace, string sRepalceTo)
    {
        return replaceWord(_Value, StringToReplace, sRepalceTo);
    }

    // ---remove Punctuation---
    static string removePunctuations(string text)
    {
        string str = "";
        for (short i = 0; i < text.length(); i++)
        {
            if (!ispunct(text[i]))
            {
                str += text[i];
            }
        }
        return str;
    }
    void removePunctuations()
    {
        _Value = removePunctuations(_Value);
    }
};

