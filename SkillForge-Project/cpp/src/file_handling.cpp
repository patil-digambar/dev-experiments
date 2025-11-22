#include<iostream>
#include<fstream>
#include <string>
int main()
{
    std::cout<<"Hello File handling\n";
    std::ofstream outfile("example.txt",std::ios::out);
    if(outfile.is_open())
    {
        outfile<<"This is an example of file handling in C++.\n";
        outfile<<"Writing to a file using ofstream.\n";
        outfile.close();
    }

    std::ifstream infile("example.txt",std::ios::in);
    infile.seekg(0, std::ios::end); // move to end
    std::streampos size=infile.tellg();// get position which is size
    std::cout<<size <<std::endl; // get file size
    infile.seekg(0); // back to beginning
    if(infile.is_open())
    {
        std::string line;
        while(std::getline(infile,line))
        {
            std::cout<<line<<std::endl;
        }
    }
  
    infile.close();
    return 0;
}