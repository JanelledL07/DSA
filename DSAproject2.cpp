#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <fstream>

using namespace std;

void saveToHistory(string content)
{
    ofstream file("history.txt", ios::app);
    file << content << "\n------------------------\n";
    file.close();
}

void viewHistory()
{
    ifstream file("history.txt");
    string line;

    cout << "\n===== HISTORY =====\n";

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}

int main()
{
    string subject;
    int groupSize;

    cout << "Enter Subject: ";
    getline(cin, subject);

    if (subject == "")
    {
        cout << "No subject entered.\n";
        return 0;
    }

    vector<string> students;
    string input;

    cout << "\nEnter student names (type END to stop):\n";

    while (true)
    {
        getline(cin, input);

        if (input == "END")
            break;

        if (input != "")
        {
            students.push_back(input);
        }
    }

    if (students.size() == 0)
    {
        cout << "No students entered.\n";
        return 0;
    }

    vector<string> roles;
    string roleInput;

    cout << "\nEnter roles (comma separated): ";
    getline(cin, roleInput);

    string temp = "";

    for (char c : roleInput)
    {
        if (c == ',')
        {
            if (temp != "")
            {
                roles.push_back(temp);
                temp = "";
            }
        }
        else
        {
            temp += c;
        }
    }

    if (temp != "")
    {
        roles.push_back(temp);
    }

    if (roles.size() == 0)
    {
        cout << "No roles entered.\n";
        return 0;
    }

    cout << "Enter group size: ";
    cin >> groupSize;

    if (groupSize <= 0)
    {
        cout << "Invalid group size.\n";
        return 0;
    }

    random_device rd;
    mt19937 g(rd());

    shuffle(students.begin(), students.end(), g);

    vector<vector<string>> groups;
    int i = 0;

    while (i < students.size())
    {
        vector<string> group;

        for (int j = 0; j < groupSize && i < students.size(); j++)
        {
            group.push_back(students[i]);
            i++;
        }

        groups.push_back(group);
    }

    string result = "Subject: " + subject + "\n\n";

    int groupNum = 1;

    for (int x = 0; x < groups.size(); x++)
    {
        result += "Group " + to_string(groupNum) + "\n";

        shuffle(roles.begin(), roles.end(), g);

        for (int y = 0; y < groups[x].size(); y++)
        {
            string role = roles[y % roles.size()];
            result += "   " + groups[x][y] + " - " + role + "\n";
        }

        result += "\n";
        groupNum++;
    }

    cout << "\n"
         << result;

    saveToHistory(result);

    char choice;
    cout << "\nView history? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        viewHistory();
    }

    return 0;
}