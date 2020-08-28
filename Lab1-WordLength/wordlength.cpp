#include <iostream>
#include <string> 
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
  ifstream dataset{"project_rover.txt"};

  // Handles File Not Found or Empty File
  if (dataset.peek() == std::ifstream::traits_type::eof())
  {
   cerr << "ERROR: Empty File. Program Exiting." << endl;
   cin.clear();
   return 1;
  }

  string word;
  string word_w_smallest_length;
  string word_w_longest_length;
  float number_of_words{0.0};
  float total_length{0.0};
  float avg{0.0};
  int current{0};
  
  /* What's the longest human or English word? 1000? */
  int smallest_length{1000};
  int longest_length{0};
  int count{1};

  while(dataset >> word)
  {
    current = word.length();
    if (current <= smallest_length)
    {
        smallest_length = current;
        word_w_smallest_length = word;
        /* Shows it picks last possible occurrence */
        //cout<<"@....:"<< count << endl;
    }

    if (current >= longest_length)
    {
        longest_length = current;
        word_w_longest_length = word;
    } 
    
    total_length += word.length();
    ++number_of_words;
    count+=1;
  }

  avg = total_length / number_of_words;

  cout <<"There are " << number_of_words << " words in the file." << endl;
  cout <<"The shortest word was \"" << word_w_smallest_length 
       <<"\" with " << smallest_length << " character(s)." << endl;
  cout <<"The longest word was \"" << word_w_longest_length 
       <<"\" with " <<longest_length << " character(s)." << endl;
  cout <<"The average length was " << fixed << setprecision(2) << avg 
       << " character(s)." << endl;

  return 0;
}
