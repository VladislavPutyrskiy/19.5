#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool file_in_vector(ifstream& file, vector<string>& vec)
{
    if (file.is_open())
    {
        while (!file.eof())
        {
            char str[50];
            file.getline(str, 50);
            vec.push_back(str);
        }
        //Возможно лишнее
        file.clear();
        file.seekg(0);

        file.close();
        return true;
    }
    else
    {
        return false;
    }
}

int main() {
    ifstream questions;
    questions.open("questions.txt");
    vector<string> asked;

    ifstream answers;
    answers.open("answers.txt");
    vector<string> responded;

    if (file_in_vector(questions, asked) && file_in_vector(answers, responded))
    {
        int player_points = 0;
        int spectator_points = 0;
        int offset = 0;

        while ((player_points + spectator_points < 13))
        {
            cout << "Please. Input the offset value: ";

            cin >> offset;
            offset = offset % (asked.size());

            while (asked[offset] == "-")
            {
                offset = offset >= asked.size() ? offset % (asked.size()) : offset++;
            }

            cout << asked[offset] << endl;

            string answer;
            cin >> answer;

            if (answer == responded[offset])
            {
                player_points++;
                cout << "Right answer!" << endl;
            }
            else
            {
                spectator_points++;
                cout << "Correct answer: " << responded[offset] << endl;
            }
            asked[offset] = "-";
        }

        if (player_points > spectator_points)
        {
            cout << "Player won!" << endl;
        }
        else
        {
            cout << "Spectator won!" << endl;
        }
    }
    else
    {
        cout << "Files are not open." << endl;
    }
}