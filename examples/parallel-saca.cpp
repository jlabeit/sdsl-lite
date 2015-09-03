#include <sdsl/construct_sa.hpp>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace sdsl;
using namespace std;

// Note: For files larger than 2^32 replace use int64_t instead int32_t

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " input file" << endl;
        cout << "(1) Reads an input file with byte alphabet" << endl;
        cout << "(2) Builds the suffix array in parallel" << endl;
        cout << "(3) Prints the result" << endl;
        return 1;
    }
    string input_file(argv[1]);

    // Read input file
    int32_t length;
    ifstream file;
    file.open(input_file);
    file.seekg(0, ios::end);
    length = file.tellg();
    file.seekg(0, ios::beg);
    unsigned char* buffer = new unsigned char[length];
    file.read((char*)buffer, length);
    file.close();

    // Construct suffix array
    int32_t* SA = new int32_t[length];
    auto start = chrono::steady_clock::now();
    divsufsort<int32_t>(buffer, SA, length);
    auto end = chrono::steady_clock::now();
    auto elapsed = end - start;

    // Print result
    cout<<"Constructed suffix array in " << chrono::duration<double, milli>(elapsed).count() / 1000.0 << " seconds " << endl;	    

    // Cleanup
    delete[] buffer;
    delete[] SA;
    return 0;
}
