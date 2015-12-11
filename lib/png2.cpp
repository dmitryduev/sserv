/*
LodePNG Examples

Copyright (c) 2005-2012 Lode Vandevenne

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.
*/

#include "lodepng.h"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
//#include <functional>

//using namespace std;

#include <cerrno>

std::string get_file_contents(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw(errno);
}

void split(const std::string& s, char c, std::vector<std::string>& v) {
   std::string::size_type i = 0;
   std::string::size_type j = s.find(c);

   while (j != std::string::npos) {
      v.push_back(s.substr(i, j-i));
      i = ++j;
      j = s.find(c, j);

      if (j == std::string::npos)
         v.push_back(s.substr(i, s.length()));
   }
}

std::vector<std::vector<unsigned char>> cm_fire() {
   std::vector<std::vector<unsigned char>> fire { 
      {255, 255, 255},
      {255, 255, 253},
      {255, 255, 251},
      {255, 255, 249},
      {255, 255, 247},
      {255, 255, 245},
      {255, 255, 243},
      {255, 255, 241},
      {255, 255, 239},
      {255, 255, 237},
      {255, 255, 235},
      {255, 255, 233},
      {255, 255, 231},
      {255, 255, 229},
      {255, 255, 227},
      {255, 255, 225},
      {255, 255, 223},
      {255, 255, 221},
      {255, 255, 219},
      {255, 255, 217},
      {255, 255, 215},
      {255, 255, 213},
      {255, 255, 211},
      {255, 255, 209},
      {255, 255, 207},
      {255, 255, 205},
      {255, 255, 203},
      {255, 255, 201},
      {255, 255, 199},
      {255, 255, 197},
      {255, 255, 195},
      {255, 255, 193},
      {255, 255, 191},
      {255, 255, 189},
      {255, 255, 187},
      {255, 255, 185},
      {255, 255, 183},
      {255, 255, 181},
      {255, 255, 179},
      {255, 255, 177},
      {255, 255, 175},
      {255, 255, 173},
      {255, 255, 172},
      {255, 255, 170},
      {255, 255, 168},
      {255, 255, 166},
      {255, 255, 164},
      {255, 255, 162},
      {255, 255, 160},
      {255, 255, 158},
      {255, 255, 156},
      {255, 255, 154},
      {255, 255, 152},
      {255, 255, 150},
      {255, 255, 148},
      {255, 255, 146},
      {255, 255, 144},
      {255, 255, 142},
      {255, 255, 140},
      {255, 255, 138},
      {255, 255, 136},
      {255, 255, 134},
      {255, 255, 132},
      {255, 255, 130},
      {255, 255, 128},
      {255, 253, 126},
      {255, 251, 124},
      {255, 249, 122},
      {255, 247, 120},
      {255, 245, 118},
      {255, 242, 116},
      {255, 241, 114},
      {255, 238, 112},
      {255, 237, 110},
      {255, 235, 108},
      {255, 233, 106},
      {255, 231, 104},
      {255, 229, 102},
      {255, 227, 100},
      {255, 225, 98},
      {255, 223, 96},
      {255, 221, 94},
      {255, 219, 92},
      {255, 217, 90},
      {255, 215, 88},
      {255, 213, 86},
      {255, 211, 84},
      {255, 209, 81},
      {255, 207, 79},
      {255, 205, 77},
      {255, 203, 75},
      {255, 201, 73},
      {255, 199, 71},
      {255, 197, 69},
      {255, 195, 67},
      {255, 193, 65},
      {255, 191, 63},
      {255, 189, 61},
      {255, 187, 59},
      {255, 185, 57},
      {255, 183, 55},
      {255, 181, 53},
      {255, 179, 51},
      {255, 177, 49},
      {255, 175, 47},
      {255, 173, 45},
      {255, 171, 43},
      {255, 169, 41},
      {255, 167, 39},
      {255, 165, 37},
      {255, 163, 35},
      {255, 161, 33},
      {255, 159, 31},
      {255, 157, 29},
      {255, 155, 27},
      {255, 153, 25},
      {255, 151, 23},
      {255, 149, 21},
      {255, 147, 19},
      {255, 145, 17},
      {255, 143, 15},
      {255, 141, 13},
      {255, 138, 11},
      {255, 136, 9},
      {255, 134, 7},
      {255, 132, 5},
      {255, 131, 3},
      {255, 129, 1},
      {254, 126, 0},
      {252, 125, 0},
      {250, 122, 0},
      {248, 121, 0},
      {246, 118, 0},
      {244, 116, 0},
      {242, 115, 0},
      {240, 113, 0},
      {238, 111, 0},
      {236, 109, 0},
      {234, 107, 0},
      {232, 105, 0},
      {230, 102, 0},
      {228, 100, 0},
      {227, 98, 0},
      {225, 97, 0},
      {223, 94, 0},
      {221, 93, 0},
      {219, 91, 0},
      {217, 89, 0},
      {215, 87, 0},
      {213, 84, 0},
      {211, 83, 0},
      {209, 81, 0},
      {207, 79, 0},
      {205, 77, 0},
      {203, 75, 0},
      {201, 73, 0},
      {199, 70, 0},
      {197, 68, 0},
      {195, 66, 0},
      {193, 64, 0},
      {191, 63, 0},
      {189, 61, 0},
      {187, 59, 0},
      {185, 57, 0},
      {183, 54, 0},
      {181, 52, 0},
      {179, 51, 0},
      {177, 49, 0},
      {175, 47, 0},
      {174, 44, 0},
      {172, 42, 0},
      {170, 40, 0},
      {168, 39, 0},
      {166, 37, 0},
      {164, 34, 0},
      {162, 33, 0},
      {160, 31, 0},
      {158, 29, 0},
      {156, 27, 0},
      {154, 25, 0},
      {152, 22, 0},
      {150, 20, 0},
      {148, 18, 0},
      {146, 17, 0},
      {144, 14, 0},
      {142, 13, 0},
      {140, 11, 0},
      {138, 9, 0},
      {136, 6, 0},
      {134, 4, 0},
      {132, 2, 0},
      {130, 0, 0},
      {128, 0, 0},
      {126, 0, 0},
      {124, 0, 0},
      {122, 0, 0},
      {120, 0, 0},
      {118, 0, 0},
      {116, 0, 0},
      {114, 0, 0},
      {112, 0, 0},
      {110, 0, 0},
      {108, 0, 0},
      {106, 0, 0},
      {104, 0, 0},
      {102, 0, 0},
      {100, 0, 0},
      {98, 0, 0},
      {96, 0, 0},
      {94, 0, 0},
      {92, 0, 0},
      {90, 0, 0},
      {88, 0, 0},
      {86, 0, 0},
      {83, 0, 0},
      {81, 0, 0},
      {79, 0, 0},
      {77, 0, 0},
      {75, 0, 0},
      {73, 0, 0},
      {71, 0, 0},
      {69, 0, 0},
      {67, 0, 0},
      {65, 0, 0},
      {63, 0, 0},
      {61, 0, 0},
      {59, 0, 0},
      {57, 0, 0},
      {55, 0, 0},
      {53, 0, 0},
      {51, 0, 0},
      {49, 0, 0},
      {47, 0, 0},
      {45, 0, 0},
      {43, 0, 0},
      {41, 0, 0},
      {39, 0, 0},
      {37, 0, 0},
      {35, 0, 0},
      {33, 0, 0},
      {31, 0, 0},
      {29, 0, 0},
      {26, 0, 0},
      {24, 0, 0},
      {22, 0, 0},
      {20, 0, 0},
      {18, 0, 0},
      {16, 0, 0},
      {14, 0, 0},
      {12, 0, 0},
      {10, 0, 0},
      {8, 0, 0},
      {6, 0, 0},
      {4, 0, 0},
      {2, 0, 0},
      {0, 0, 0}
   };
   return fire;
}


std::vector<std::vector<unsigned char>> cm_dawn() {
   std::vector<std::vector<unsigned char>> dawn {
      {255, 255, 195},
      {255, 255, 194},
      {255, 255, 193},
      {255, 255, 191},
      {255, 255, 190},
      {255, 255, 189},
      {255, 255, 188},
      {255, 255, 187},
      {255, 255, 186},
      {255, 255, 185},
      {255, 255, 184},
      {255, 255, 183},
      {255, 255, 182},
      {255, 255, 181},
      {255, 255, 179},
      {255, 255, 178},
      {255, 255, 177},
      {255, 255, 176},
      {255, 255, 175},
      {255, 255, 174},
      {255, 255, 173},
      {255, 255, 172},
      {255, 255, 171},
      {255, 255, 170},
      {255, 255, 169},
      {255, 255, 167},
      {255, 255, 166},
      {255, 255, 165},
      {255, 255, 164},
      {255, 255, 163},
      {255, 255, 162},
      {255, 255, 161},
      {255, 255, 160},
      {255, 255, 159},
      {255, 255, 158},
      {255, 255, 157},
      {255, 255, 155},
      {255, 255, 154},
      {255, 255, 153},
      {255, 255, 152},
      {255, 255, 151},
      {255, 255, 150},
      {255, 255, 149},
      {255, 255, 148},
      {255, 255, 147},
      {255, 255, 146},
      {255, 255, 145},
      {255, 255, 143},
      {255, 255, 142},
      {255, 255, 141},
      {255, 255, 140},
      {255, 255, 139},
      {255, 255, 138},
      {255, 255, 137},
      {255, 255, 136},
      {255, 255, 135},
      {255, 255, 134},
      {255, 255, 133},
      {255, 255, 131},
      {255, 255, 130},
      {255, 255, 129},
      {255, 255, 128},
      {255, 255, 127},
      {255, 255, 126},
      {255, 255, 125},
      {255, 253, 125},
      {255, 251, 125},
      {255, 249, 125},
      {255, 247, 125},
      {255, 245, 125},
      {255, 242, 125},
      {255, 241, 125},
      {255, 238, 125},
      {255, 237, 125},
      {255, 235, 125},
      {255, 233, 125},
      {255, 231, 125},
      {255, 229, 126},
      {255, 227, 126},
      {255, 225, 126},
      {255, 223, 126},
      {255, 221, 126},
      {255, 219, 126},
      {255, 217, 126},
      {255, 215, 126},
      {255, 213, 126},
      {255, 211, 126},
      {255, 209, 126},
      {255, 207, 126},
      {255, 205, 126},
      {255, 203, 126},
      {255, 201, 126},
      {255, 199, 126},
      {255, 197, 126},
      {255, 195, 126},
      {255, 193, 126},
      {255, 191, 126},
      {255, 189, 126},
      {255, 187, 126},
      {255, 185, 126},
      {255, 183, 126},
      {255, 181, 126},
      {255, 179, 126},
      {255, 177, 126},
      {255, 175, 126},
      {255, 173, 126},
      {255, 171, 126},
      {255, 169, 126},
      {255, 167, 126},
      {255, 165, 126},
      {255, 163, 126},
      {255, 161, 126},
      {255, 159, 126},
      {255, 157, 126},
      {255, 155, 126},
      {255, 153, 126},
      {255, 151, 126},
      {255, 149, 126},
      {255, 147, 126},
      {255, 145, 127},
      {255, 143, 127},
      {255, 141, 127},
      {255, 138, 127},
      {255, 136, 127},
      {255, 134, 127},
      {255, 132, 127},
      {255, 131, 127},
      {255, 129, 127},
      {254, 126, 127},
      {252, 125, 127},
      {250, 122, 127},
      {248, 121, 127},
      {246, 118, 127},
      {244, 116, 127},
      {242, 115, 127},
      {240, 113, 127},
      {238, 111, 127},
      {236, 109, 127},
      {234, 107, 127},
      {232, 105, 127},
      {230, 102, 127},
      {228, 100, 127},
      {226, 98, 127},
      {224, 97, 127},
      {222, 94, 127},
      {220, 93, 127},
      {218, 91, 127},
      {216, 89, 127},
      {214, 87, 127},
      {212, 84, 127},
      {210, 83, 127},
      {208, 81, 127},
      {206, 79, 127},
      {204, 77, 127},
      {202, 75, 127},
      {200, 73, 127},
      {198, 70, 127},
      {196, 68, 127},
      {194, 66, 127},
      {192, 64, 127},
      {190, 63, 127},
      {188, 61, 127},
      {186, 59, 127},
      {184, 57, 127},
      {182, 54, 127},
      {180, 52, 127},
      {178, 51, 127},
      {176, 49, 127},
      {174, 47, 127},
      {171, 44, 127},
      {169, 42, 127},
      {167, 40, 127},
      {165, 39, 127},
      {163, 37, 127},
      {161, 34, 127},
      {159, 33, 127},
      {157, 31, 127},
      {155, 29, 127},
      {153, 27, 127},
      {151, 25, 127},
      {149, 22, 127},
      {147, 20, 127},
      {145, 18, 127},
      {143, 17, 127},
      {141, 14, 127},
      {139, 13, 127},
      {137, 11, 127},
      {135, 9, 127},
      {133, 6, 127},
      {131, 4, 127},
      {129, 2, 127},
      {127, 0, 127},
      {125, 0, 127},
      {123, 0, 127},
      {121, 0, 127},
      {119, 0, 127},
      {117, 0, 127},
      {115, 0, 127},
      {113, 0, 127},
      {111, 0, 127},
      {109, 0, 127},
      {107, 0, 127},
      {105, 0, 127},
      {103, 0, 127},
      {101, 0, 127},
      {99, 0, 127},
      {97, 0, 127},
      {95, 0, 127},
      {93, 0, 127},
      {91, 0, 127},
      {89, 0, 127},
      {87, 0, 126},
      {85, 0, 126},
      {83, 0, 126},
      {82, 0, 126},
      {80, 0, 126},
      {78, 0, 126},
      {76, 0, 126},
      {74, 0, 126},
      {72, 0, 126},
      {70, 0, 126},
      {68, 0, 126},
      {66, 0, 126},
      {64, 0, 126},
      {62, 0, 126},
      {60, 0, 126},
      {58, 0, 126},
      {56, 0, 126},
      {54, 0, 126},
      {52, 0, 126},
      {50, 0, 126},
      {48, 0, 126},
      {46, 0, 126},
      {44, 0, 126},
      {42, 0, 126},
      {40, 0, 126},
      {38, 0, 126},
      {36, 0, 126},
      {34, 0, 126},
      {32, 0, 126},
      {30, 0, 126},
      {28, 0, 126},
      {26, 0, 126},
      {24, 0, 126},
      {22, 0, 126},
      {20, 0, 126},
      {18, 0, 126},
      {16, 0, 126},
      {14, 0, 126},
      {12, 0, 126},
      {10, 0, 126},
      {8, 0, 126},
      {6, 0, 126},
      {4, 0, 126},
      {2, 0, 126},
      {0, 0, 126}
   };
   return dawn;
}

//g++ lodepng.cpp example_encode.cpp -ansi -pedantic -Wall -Wextra -O3

//Example 1
//Encode from raw pixels to disk with a single function call
//The image argument has width * height RGBA pixels or width * height * 4 bytes
void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

//saves image to filename given as argument. Warning, this overwrites the file without warning!
int main(int argc, char *argv[])
{
   // ----------- VICD  -------------
   //NOTE: this program will overwrite the file or vicd.png without warning!
   std::string output_dir("../public/");
   std::string f_v("/vicd.png");
   //const char* filename1;//("/Users/dmitryduev/web/sserv/public/vicd.png"); // default
   if (argc >= 2) {
      output_dir = (std::string)argv[1];
   }
   //filename1 = (const char *)((output_dir + f_v).c_str());
   //std::cout << filename << "\n";
   //const char* filename = argc == 2 ? argv[1] + "vicd.png" : "../public/vicd.png";
   
   // read in the status file into a std::string
   //std::ifstream ifs("/home/roboao/Status/vicd_image_status");
   std::string telemetry_dir("/Users/dmitryduev/web/sserv/telemetry");
   std::string f_v_s("/vicd_image_status");
   //std::ifstream ifs("/Users/dmitryduev/web/sserv/telemetry/vicd_image_status");
   if (argc == 3) {
      telemetry_dir = argv[2];
   }
   //std::ifstream ifs((telemetry_dir + f_v_s).c_str());
   //std::string content( (std::istreambuf_iterator<char>(ifs) ),
   //                     (std::istreambuf_iterator<char>()    ) );
   //std::cout << content;
   
   std::string content( get_file_contents((telemetry_dir + f_v_s).c_str()) );
   //std::cout << content;
   
   // split the string into a vector of strings 
   std::vector<std::string> v;
   split(content, ' ', v);
   v.erase(v.begin(), v.begin() + 4); // remove date and size from the vector
   
   // convert a vector of strings into a vector of doubles
   std::vector<double> img;
   std::transform(v.begin(), v.end(), std::back_inserter(img),
               [](const std::string& x) { return std::atof(x.c_str()); });
   //std::cout << atoi(v[0].c_str());
   // normalize to the maximum value at a later stage:
   double max_z {*std::max_element(img.begin(), img.end())};
   //std::cout << img[0] << "\n";
   //std::cout << max_z << "\n";
   
   // mean and std
   //double sum = std::accumulate(img.begin(), img.end(), 0.0);
   //double mean = sum / img.size();
   //double sq_sum = std::inner_product(img.begin(), img.end(), img.begin(), 0.0);
   //double stdev = std::sqrt(sq_sum / img.size() - mean * mean);
   //std::cout << mean << "\n";
   
   // median
   //std::vector<double> img_sorted(img);
   //std::sort (img_sorted.begin(), img_sorted.end());
   //double median {img_sorted[img_sorted.size()/2]};
   //std::cout << median  << "\n";
  
   // vicd: generate RGB image
   unsigned char grey;
   const unsigned w = 1024;
   const unsigned h = 1024;
   std::vector<unsigned char> image(w * h * 4);
   for(unsigned y = 0; y < h; y++)
   for(unsigned x = 0; x < w; x++)
   {
     int index = y * w * 4 + x * 4;
     //grey = std::max(0.0, (img[(h-y)*h-(w-x)] - median) / (max_z) * 255);
     grey = img[(h-y)*h-(w-x)] / (max_z) * 255;
     //std::cout << grey << "\n";
     image[index + 0] = grey;
     image[index + 1] = grey;
     image[index + 2] = grey;
     image[index + 3] = 255;
   }
 
   //output image
   //unsigned width = 1024, height = 1024;
   encodeOneStep((output_dir + f_v).c_str(), image, w, h);

   // ----------- WFS  -------------
   //filename = argc > 2 ? argv[2] : "../public/wfs.png";
   //const char* filename2;
   std::string f_w("/wfs.png");
   //filename2 = (const char*)((output_dir + f_w).c_str());
  
   // read in the status file into a std::string
   //std::ifstream ifs2("/home/roboao/Status/wfs_image_status_status");
   //std::ifstream ifs2("/Users/dmitryduev/web/sserv/telemetry/wfs_image_status_status");
   std::string f_w_s("/wfs_image_status_status");
   //std::ifstream ifs2((telemetry_dir + f_w_s).c_str());
   //std::string content2( (std::istreambuf_iterator<char>(ifs2) ),
   //                      (std::istreambuf_iterator<char>()    ) );

   //std::cout << content2;
   
   std::string content2( get_file_contents((telemetry_dir + f_w_s).c_str()) );
   
   // split the string into a vector of strings 
   std::vector<std::string> v2;
   split(content2, ' ', v2);
   v2.erase(v2.begin(), v2.begin() + 2); // remove date from the vector
   
   // convert a vector of strings into a vector of doubles
   std::vector<double> img2;
   std::transform(v2.begin(), v2.end(), std::back_inserter(img2),
               [](const std::string& x2) { return std::atof(x2.c_str()); });
   // normalize to the maximum value at a later stage:
   double max_z2 = *std::max_element(img2.begin(), img2.end());
   max_z2 = 255;
  
   // vicd: generate RGB image
   const unsigned w2 = 26;
   const unsigned h2 = 26;
   std::vector<unsigned char> image2(w2 * h2 * 4);
   for(unsigned y = 0; y < h2; y++)
   for(unsigned x = 0; x < w2; x++)
   {
     int index = y * w2 * 4 + x * 4;
     grey = img2[(h2-y)*h2-(w2-x)] / (max_z2) * 255;
     image2[index + 0] = grey;
     image2[index + 1] = grey;
     image2[index + 2] = grey;
     image2[index + 3] = 255;
   }
 
   //output image
   encodeOneStep((output_dir + f_w).c_str(), image2, w2, h2);

   // ----------- DM  -------------
   //filename = argc > 3 ? argv[3] : "../public/dm.png";
   //const char* filename3;
   std::string f_d("/dm.png");
   //filename3 = (const char*)((output_dir + f_d).c_str());
   //std::cout << filename3 << "\n"; 
   // read in the status file into a std::string
   //std::ifstream ifs3("/home/roboao/Status/new_pos_status_status");
   //std::ifstream ifs3("/Users/dmitryduev/web/sserv/telemetry/new_pos_status_status");
   std::string f_d_s("/new_pos_status_status");
   //std::ifstream ifs3((telemetry_dir + f_d_s).c_str());
   //std::string content3( (std::istreambuf_iterator<char>(ifs3) ),
   //                      (std::istreambuf_iterator<char>()    ) );

   std::string content3( get_file_contents((telemetry_dir + f_d_s).c_str()) );
   
   // split the string into a vector of strings 
   std::vector<std::string> v3;
   split(content3, ' ', v3);
   v3.erase(v3.begin(), v3.begin() + 2); // remove date from the vector
   
   // convert a vector of strings into a vector of doubles
   std::vector<double> img3;
   std::transform(v3.begin(), v3.end(), std::back_inserter(img3),
               [](const std::string& x3) { return std::atof(x3.c_str()); });
   // normalize to the maximum value at a later stage:
   double max_z3 = *std::max_element(img3.begin(), img3.end());
   max_z3 = 65536;

   // make palette:
   std::vector<std::vector<unsigned char>> cm = cm_fire();
   //std::vector<std::vector<unsigned char>> cm = cm_dawn();
   //std::cout << dawn[0][0] << "\n";

   // vicd: generate RGB image
   const unsigned w3 = 12;
   const unsigned h3 = 12;
   int running = 0;
   std::vector<unsigned char> image3(w3 * h3 * 4);
   for (unsigned y = 0; y < h3; y++)
   for (unsigned x = 0; x < w3; x++)
   {
     int index = y * w3 * 4 + x * 4;
     if ( ((y == 0 || y == 11) && (x==0 || x==1 || x==2 || x==9 || x==10 || x==11)) ||
          ((y == 1 || y == 10) && (x==0 || x==1 || x==10 || x==11)) || 
          ((y == 2 || y == 9) && (x==0 || x==11)) ){
        image3[index + 0] = 255;
        image3[index + 1] = 255;
        image3[index + 2] = 255;
        image3[index + 3] = 255; 
     }
     else {
        grey = img3[running] / (max_z3) * 255;
        //std::cout << int(grey) << "\n";
        running++;
     
        if (grey==0) {
           image3[index + 0] = 0;
           image3[index + 1] = 255;
           image3[index + 2] = 0;
           image3[index + 3] = 255; 
        }
        else if (grey==255) {
           image3[index + 0] = 0;
           image3[index + 1] = 0;
           image3[index + 2] = 255;
           image3[index + 3] = 255;
        }
        else {
           image3[index + 0] = cm[grey][0];
           image3[index + 1] = cm[grey][1];
           image3[index + 2] = cm[grey][2];
           image3[index + 3] = 255;
        }
     }
   } 
   //output image
   encodeOneStep((output_dir + f_d).c_str(), image3, w3, h3);

}
