#include "PassportProcessing.h"

#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>

// =============== PART 2 VALIDATION RULES ==============

namespace PassportRules {

    constexpr int NUM_YEAR_DIGITS = 4;
    constexpr int MIN_BIRTH_YEAR = 1920;
    constexpr int MAX_BIRTH_YEAR = 2002;
    constexpr int MIN_ISSUE_YEAR = 2010;
    constexpr int MAX_ISSUE_YEAR = 2020;
    constexpr int MIN_EXPIRY_YEAR = 2020;
    constexpr int MAX_EXPIRY_YEAR = 2030;

    const std::string HEIGHT_UNIT_CM = "cm";
    const std::string HEIGHT_UNIT_IN = "in";
    constexpr int MIN_HEIGHT_CM = 150;
    constexpr int MAX_HEIGHT_CM = 193;
    constexpr int MIN_HEIGHT_IN = 59;
    constexpr int MAX_HEIGHT_IN = 76;
    
    constexpr int HAIR_COLOR_LENGTH = 7;
    constexpr char HAIR_COLOR_PREFIX = '#';
    
    constexpr int PASSPORT_ID_LENGTH = 9;

    const std::string ECL_AMB = "amb";
    const std::string ECL_BLU = "blu";
    const std::string ECL_BRN = "brn";
    const std::string ECL_GRY = "gry";
    const std::string ECL_GRN = "grn";
    const std::string ECL_HZL = "hzl";
    const std::string ECL_OTH = "oth";
};

// =============== PUZZLE INPUT & HELPERS ===============

void Passport::setField(const std::string& key, const std::string& value) {

    if (key == "byr") byr = value;
    else if (key == "iyr") iyr = value;
    else if (key == "eyr") eyr = value;
    else if (key == "hgt") hgt = value;
    else if (key == "hcl") hcl = value;
    else if (key == "ecl") ecl = value;
    else if (key == "pid") pid = value;
    else if (key == "cid") cid = value;
}

bool Passport::isValidPart1() const {

    // if any of the seven required other than 'cid' are missing, not valid
    if (byr.empty() || iyr.empty() || eyr.empty() || hgt.empty() || 
        hcl.empty() || ecl.empty() || pid.empty()) {
            return false;
    }
    else {
        return true;
    }
}

void Scanner::readPuzzleInput() {

    // clear previous (if needed)
    passports.clear();

    std::ifstream file(puzzleInput);
    if (!file.is_open()) {
        throw std::runtime_error("Could not read puzzle input");
    }

    Passport current;
    std::string line;
    bool hasData = false;

    // parse each line from input
    while (std::getline(file, line)) {

        // if we hit a blank line 
        if (line.empty()) {
            // and current passport has been parsed
            if (hasData) {
                // push into vector, reset for next one
                passports.push_back(current);
                current = Passport();
                hasData = false;
            }
            // otherwise, we keer parsing
            continue;
        }

        // for each passport data line, we parse the  "key:value" pairs (token)
        std::istringstream ss(line);
        std::string token; 
        while (ss >> token) {
            // we find the delimiting ':'
            size_t delimPos = token.find(':');
            // if found, we split and store key/value into passport
            if (delimPos != std::string::npos) {
                std::string key = token.substr(0, delimPos);
                std::string value = token.substr(delimPos + 1);
                current.setField(key, value);
                hasData = true;
            }
        }
    }

    // check for not potentially skipping very last passport
    if (hasData) {
        passports.push_back(current);
    }

    // optional, close the stream
    file.close();
}

// =============== PART 1 ===============

int Scanner::solvePart1() const {

    // guard
    if (passports.empty()) {
        return 0;
    }

    int valid = 0;
    for (int i = 0; i < (int)passports.size(); i++) {
        if (passports[i].isValidPart1()) {
            valid++;
        }
    }

    return valid;
}

// =============== PART 2 ===============

// checks if string is made up entirely of digits
bool Passport::isAllDigits(const std::string& str) const {

    using namespace PassportRules;

    // guard
    if (str.empty()) {
        return false;
    }

    // check that all characters are digits
    for (int i = 0; i < (int)str.length(); i++) {
        if (!std::isdigit(static_cast<unsigned char>(str[i]))) {
            return false;
        }
    }

    return true;
}

// validates year fields
bool Passport::isValidYear(const std::string& str, int min, int max) const {

    using namespace PassportRules;

    // check that length is exactly 4 and that they are all digits
    if (str.length() != NUM_YEAR_DIGITS || !isAllDigits(str)) {
        return false;
    }

    // convert to number and validate against given constraints
    int year = std::stoi(str);
    return ( (year >= min) && (year <= max) );
}

// validates height field
bool Passport::isValidHeight() const {

    using namespace PassportRules;
    
    // base check
    if (hgt.empty() || hgt.length() < 3) {
        return false;
    }

    // split the string into "number" + "unit"
    std::string unit = hgt.substr(hgt.length() - 2);
    std::string height = hgt.substr(0, hgt.length() - 2);

    // check that all leading characters are digits 
    if (!isAllDigits(height)) {
        return false;
    }

    // convert height and validate against specific unit constraints
    int value = std::stoi(height);
    if (unit == HEIGHT_UNIT_IN) {
        return ( (value >= MIN_HEIGHT_IN) && (value <= MAX_HEIGHT_IN) );
    }
    else if (unit == HEIGHT_UNIT_CM) {
        return ( (value >= MIN_HEIGHT_CM) && (value <= MAX_HEIGHT_CM) );
    }

    // otherwise, unit suffix is invalid
    return false;
}

// validates hair color field
bool Passport::isValidHairColor() const {

    using namespace PassportRules;

    // guard
    if (hcl.empty()) {
        return false;
    }

    // must have length of exactly 7 and first character must be '#'
    if (hcl.length() != HAIR_COLOR_LENGTH || hcl[0] != HAIR_COLOR_PREFIX) {
        return false;
    }
    
    // all remaining 6 characters must be valid hex characters 0-9, a-f, A-F
    for (int i = 1; i < (int)hcl.length(); i++) {
        if (!std::isxdigit(static_cast<unsigned char>(hcl[i]))) {
            return false;
        }
    }
    return true;
}

// validates eye color field
bool Passport::isValidEyeColor() const {

    using namespace PassportRules;

    // must match with exactly one of given values
    if (ecl != ECL_AMB && ecl != ECL_BLU && ecl != ECL_BRN && ecl != ECL_GRY && 
        ecl != ECL_GRN && ecl != ECL_HZL && ecl != ECL_OTH) {
        return false;
    }
    return true;
}

// validates passport id field
bool Passport::isValidPassportID() const {

    using namespace PassportRules;

    // must be exactly 9 digits
    if (pid.length() != PASSPORT_ID_LENGTH || !isAllDigits(pid)) {
        return false;
    }
    return true;
}

bool Passport::isValidPart2() const {

    using namespace PassportRules;

    // validate with Part 1
    if (!isValidPart1()) {
        return false;
    }

    // validate year fields
    if (!isValidYear(byr, MIN_BIRTH_YEAR, MAX_BIRTH_YEAR)) return false;
    if (!isValidYear(iyr, MIN_ISSUE_YEAR, MAX_ISSUE_YEAR)) return false;
    if (!isValidYear(eyr, MIN_EXPIRY_YEAR, MAX_EXPIRY_YEAR)) return false;

    // validate height and passportd ID
    if (!isValidHeight() || !isValidPassportID()) return false;

    // validate eye color and hair color
    if (!isValidEyeColor() || !isValidHairColor()) return false;

    // if no violations, passport is valid
    return true;
}

int Scanner::solvePart2() const {
    
    // guard 
    if (passports.empty()) {
        return 0;
    }

    int valid = 0;
    // count valid passports applying Part 2 rules
    for(int i = 0; i < (int)passports.size(); i++) {
        if (passports[i].isValidPart2()) {
            valid++;
        }
    }
    return valid;
}


