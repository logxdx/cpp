## Porter Stemmer Class

### Methods

1. **`my_any_of`**
    - **Description**: Custom implementation of `std::any_of` to check if any element in a range satisfies a given predicate.
    - **Parameters**:
        - `InputIt first`: Iterator to the beginning of the range.
        - `InputIt last`: Iterator to the end of the range.
        - `UnaryPredicate p`: Unary predicate function.
    - **Return Type**: `bool`

2. **`isCons`**
    - **Description**: Checks if a given character is a consonant.
    - **Parameters**:
        - `char letter`: The character to check.
    - **Return Type**: `bool`

3. **`isConsonant`**
    - **Description**: Checks if a character at a given index in a word is a consonant.
    - **Parameters**:
        - `const std::string &word`: The word.
        - `int i`: Index of the character in the word.
    - **Return Type**: `bool`

4. **`isVowel`**
    - **Description**: Checks if a character at a given index in a word is a vowel.
    - **Parameters**:
        - `const std::string &word`: The word.
        - `int i`: Index of the character in the word.
    - **Return Type**: `bool`

5. **`endsWith`**
    - **Description**: Checks if a string ends with a given substring.
    - **Parameters**:
        - `const std::string &stem`: The string to check.
        - `const std::string &letter`: The substring to check for at the end.
    - **Return Type**: `bool`

6. **`containsVowel`**
    - **Description**: Checks if a string contains a vowel.
    - **Parameters**:
        - `const std::string &stem`: The string to check.
    - **Return Type**: `bool`

7. **`doubleCons`**
    - **Description**: Checks if a string has double consonants at the end.
    - **Parameters**:
        - `const std::string &stem`: The string to check.
    - **Return Type**: `bool`

8. **`getForm`**
    - **Description**: Gets the form of a word based on its consonant and vowel pattern.
    - **Parameters**:
        - `const std::string &word`: The word.
    - **Return Type**: `std::string`

9. **`makelps`**
    - **Description**: Computes the Longest Proper Prefix which is also Suffix (LPS) for the Knuth-Morris-Pratt (KMP) algorithm.
    - **Parameters**:
        - `std::string pat`: The pattern.
    - **Return Type**: `std::vector<int>`

10. **`kmp`**
    - **Description**: Performs the Knuth-Morris-Pratt (KMP) algorithm for pattern matching.
    - **Parameters**:
        - `std::string txt`: The text.
        - `std::string pat`: The pattern.
    - **Return Type**: `std::vector<int>`

11. **`getM`**
    - **Description**: Gets the count of the "VC" pattern in the form of a word.
    - **Parameters**:
        - `const std::string &word`: The word.
    - **Return Type**: `int`

12. **`cvc`**
    - **Description**: Checks if a word follows the "cvc" pattern.
    - **Parameters**:
        - `const std::string &word`: The word.
    - **Return Type**: `bool`

13. **`replace`**
    - **Description**: Replaces a substring in a word.
    - **Parameters**:
        - `const std::string &orig`: The original word.
        - `const std::string &rem`: The substring to be replaced.
        - `const std::string &rep`: The replacement substring.
    - **Return Type**: `std::string`

14. **`replaceM0`**
    - **Description**: Replaces a substring in a word if the count of "VC" pattern is greater than 0.
    - **Parameters**:
        - `const std::string &orig`: The original word.
        - `const std::string &rem`: The substring to be replaced.
        - `const std::string &rep`: The replacement substring.
    - **Return Type**: `std::string`

15. **`replaceM1`**
    - **Description**: Replaces a substring in a word if the count of "VC" pattern is greater than 1.
    - **Parameters**:
        - `const std::string &orig`: The original word.
        - `const std::string &rem`: The substring to be replaced.
        - `const std::string &rep`: The replacement substring.
    - **Return Type**: `std::string`

16. **`step1a`**
    - **Description**: Implements Step 1a of the Porter stemming algorithm.
    - **Parameters**:
        - `std::string word`: The word.
    - **Return Type**: `std::string`

17. **`step1b`**
    - **Description**: Implements Step 1b of the Porter stemming algorithm.
    - **Parameters**:
        - `std::string word`: The word.
    - **Return Type**: `std::string`

18. **`step1c`**
    - **Description**: Implements Step 1c of the Porter stemming algorithm.
    - **Parameters**:
        - `std::string word`: The word.
    - **Return Type**: `std::string`

19. **`step2`**
    - **Description**: Implements Step 2 of the Porter stemming algorithm.
    - **Parameters**:
        - `std::string word`: The word.
    - **Return Type**: `std::string`

20. **`step3`**
    - **Description**: Implements Step 3 of the Porter stemming algorithm.
    - **Parameters**:
        - `std::string word`: The word.
    - **Return Type**: `std::string`

21. **`step4`**
    - **Description**: Implements Step 4 of the Porter stemming algorithm.
    - **Parameters**:
        - `std::string word`: The word.
    - **Return Type**: `std::string`

22. **`step5a`**
    - **Description**: Implements Step 5a of the Porter stemming algorithm.
    - **Parameters**:
        - `std::string word`: The word.
    - **Return Type**: `std::string`

23. **`step5b`**
    - **Description**: Implements Step 5b of the Porter stemming algorithm.
    - **Parameters**:
        - `std::string word`: The word.
    - **Return Type**: `std::string`

24. **`stem`**
    - **Description**: Implements the complete Porter stemming algorithm by applying all steps.
    - **Parameters**:
        - `std::string word`: The word.
    - **Return Type**: `std::string`


<br>

## **Steps -> 1 to 5**

### Step 1: Preprocesses

#### Step 1a: SSES, IES, SS, S
```cpp
std::string step1a(std::string word)
{
    if (endsWith(word, "sses"))
        word = replace(word, "sses", "ss");
    else if (endsWith(word, "ies"))
        word = replace(word, "ies", "i");
    else if (endsWith(word, "ss") || endsWith(word, "s"))
        word = replace(word, "s", "");
    return word;
}
```

- **Description**: The function handles specific endings in words. If a word ends with "sses," it replaces it with "ss." If it ends with "ies," it replaces it with "i." If it ends with "ss" or "s," it removes the trailing "s."

---

#### Step 1b: EED, ED, ING
```cpp
std::string step1b(std::string word)
{
    bool flag = false;
    if (endsWith(word, "eed"))
    {
        std::string base = word.substr(0, word.length() - 3);
        if (getM(base) > 0)
            word = base + "ee";
    }
    else if (endsWith(word, "ed"))
    {
        std::string base = word.substr(0, word.length() - 2);
        if (containsVowel(base))
        {
            word = base;
            flag = true;
        }
    }
    else if (endsWith(word, "ing"))
    {
        std::string base = word.substr(0, word.length() - 3);
        if (containsVowel(base))
        {
            word = base;
            flag = true;
        }
    }

    if (flag)
    {
        // Additional checks and modifications based on conditions
    }
    return word;
}
```

- **Description**: This function addresses words ending with "eed," "ed," or "ing." If a word ends with "eed," it may replace it with "ee" based on a condition. If it ends with "ed" or "ing," and the base word contains a vowel, it might modify the word further based on additional conditions.

---

#### Step 1c: Y
```cpp
std::string step1c(std::string word)
{
    if (endsWith(word, "y"))
    {
        std::string base = word.substr(0, word.length() - 1);
        if (containsVowel(base))
            word = base + "i";
    }
    return word;
}
```

- **Description**: This step handles words ending with "y." If a word ends with "y," it may replace it with "i" if the base word contains a vowel.

---

### Step 2: Suffix Removals
```cpp
std::string step2(std::string word)
{
    // Multiple rules for suffix removals
    return word;
}
```

- **Description**: Step 2 involves applying various suffix removal rules to the input word. The rules are related to specific suffixes and their replacements. The actual rules are implemented in the `step2` function, and they are applied to the word accordingly.


---

### Step 3: Suffix Removals
```cpp
std::string step3(std::string word)
{
    // Multiple rules for suffix removals
    return word;
}
```

- **Description**: Step 3 is similar to Step 2 but involves a different set of suffix removal rules. These rules are applied to the input word to modify or remove certain suffixes.


---

### Step 4: Suffix Removals
```cpp
std::string step4(std::string word)
{
    // Multiple rules for suffix removals
    return word;
}
```

- **Description**: Step 4 follows the pattern of Step 2 and Step 3 but with a distinct set of rules. It involves additional checks and modifications based on various suffixes.


---

### Step 5: Suffix Removals
```cpp
std::string step5a(std::string word)
{
    // Additional checks and removals based on specific conditions
    return word;
}
```

```cpp
std::string step5b(std::string word)
{
    // Additional checks and removals based on specific conditions
    return word;
}
```

- **Description**: Step 5 is split into two sub-steps, 5a and 5b, each with its specific conditions. They involve additional checks and removals based on specific conditions. In 5a, it deals with certain suffixes, and in 5b, it addresses words with a double consonant at the end.


---

## Summary:

- **Step 1**: Preprocesses the word by handling specific endings.
- **Step 2-5**: Apply various rules for suffix removal and modification based on specific conditions.

---

### These steps collectively form the Porter Stemmer algorithm, which aims to reduce words to their root or stem by removing or modifying suffixes. The effectiveness of the stemming process relies on the proper application of linguistic rules and conditions.