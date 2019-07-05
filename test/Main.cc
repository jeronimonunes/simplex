#include <iostream>
#include <dirent.h>
#include <sys/types.h>

//NOT DONE

using namespace std;

const char PATH_SEPARATOR =
#ifdef _WIN32
                            '\\';
#else
                            '/';
#endif

int main(int argc, char** argv) {

    if(argc != 3) {
        cout << "Usage: " << argv[0] << " <inputFolder> <outputFolder>" << endl;
        return -1;
    }

    string output = argv[2];
    if(output[output.length()-1] != PATH_SEPARATOR) {
        output += PATH_SEPARATOR;
    }

    string input = argv[1];
    if(input[input.length()-1] != PATH_SEPARATOR) {
        input += PATH_SEPARATOR;
    }

    DIR* dir = opendir(argv[1]);

    if(dir == NULL) {
        cout << "It was not possible to find input folder" << endl;
        return -1;
    }

    struct dirent *entry;
    
    while((entry = readdir(dir)) != NULL) {
        auto infile = input + entry->d_name;
        auto outfile = output + entry->d_name;

        cout << infile << "\t" << outfile << endl;
    }


    closedir(dir);
    
}