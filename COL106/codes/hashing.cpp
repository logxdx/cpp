#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <cstdlib>


size_t sampleHash(const std::string& s) {

  static const int hashPrime = 997;

   int sum = 0;
  for (char c : s) {
    sum += static_cast<int>(c);
    // why this is bad?                                                        
  }
  return sum % hashPrime;

}

class HashFunctionTester {
private:
    std::vector<std::string> randomStrings;
    size_t (*hashFunc)(const std::string&);

public:

   HashFunctionTester(size_t (*func)(const std::string&), int numStrings = 10\
00) : hashFunc(func) {
        // Generate random strings                                             
        for (int i = 0; i < numStrings; ++i) {
            randomStrings.push_back(generateRandomString());
	}
    }

  
  std::string generateRandomString(int length = 10) {
        const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghi\
jklmnopqrstuvwxyz";
        std::string result;

        for (int i = 0; i < length; ++i) {
            result += alphanum[rand() % (sizeof(alphanum) - 1)];
        }

        return result;
    }

  void testUniformity() {
        std::unordered_map<size_t, int> hashCounts;

        for (const auto& s : randomStrings) {
            size_t hashValue = hashFunc(s);
            hashCounts[hashValue]++;
        }

        double averageCount = static_cast<double>(randomStrings.size()) / hashCounts.size();
        std::cout << "Average count per bucket: " << averageCount << std::endl;
  }

  void testCollisionRate(){
    //TODO
  }

  void timeTaken(){
    //TODO
  }

  void avalancheEffect(){
    //TODO
  }
  
};

int main() {

    HashFunctionTester tester(sampleHash);

    std::cout << "Testing Uniformity..." << std::endl;
    tester.testUniformity();

    std::cout << "\nTime taken..." << std::endl;
    tester.timeTaken();

    std::cout << "\nTesting Collision Rate..." << std::endl;
    tester.testCollisionRate();

    std::cout << "\nTesting Avalanche Effect..." << std::endl;
    tester.avalancheEffect();
    

    return 0;
}

