// file_viewer.cpp

#include <fstream>
using std::ifstream;
#include <iomanip>
using std::setw;
using std::skipws;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include<sstream>
using std::istringstream;
using std::ostringstream;
#include <string>
using std::string;
#include <vector>
using std::vector;

const int windowHeight = 10;
vector<string> link_number_files;
int link_number = 0;

bool check_for_anchor(const string & line)
{
    if(line.find("<") != -1)
        return true;
    else
        return false;
}

string get_anchor_file(string & anchor)
{
    istringstream iss;
    string anchor_file;
    ostringstream oss;
    int i;
    for(i = anchor.size(); anchor[i] != ' '; i--)
        anchor.resize(i);
    oss << anchor;
    iss.ignore('<');
    iss.ignore('a');
    iss >> skipws >> anchor_file;
    for(i = 0; i < anchor_file.size(); i++)
        if(anchor_file[i] == ' ')
            anchor_file.resize(i);

    return anchor_file;
}

string get_anchor_text(string & anchor)
{
    string dummy;
    istringstream iss;
    ostringstream oss(anchor);
    string anchor_text;
    iss.ignore('<');
    iss.ignore('a');
    iss >> skipws >> dummy >> skipws >> anchor_text;

    return anchor_text;
}

string format_anchor(string & anchor)
{
    istringstream iss;
    ostringstream oss;

    string anchor_text = get_anchor_text(anchor);
    string open_brackets = "<<";
    string close_brackets = ">>";
    string square_brackets = "[]";
    open_brackets += anchor_text;
    open_brackets += close_brackets;

    oss << link_number;
    string link_number_str = oss.str();
    square_brackets.insert(1,link_number_str);
    string new_anchor = open_brackets + square_brackets;
    return new_anchor;
}

void display(const string & file_name, const vector<string> & v_document_lines, int ix_current_line)
{
    cout << endl << file_name << endl;
    string long_separator(50, '-');
    cout << long_separator << endl;
    int ix_start_line = ix_current_line;
    int ix_stop_line = ix_current_line + windowHeight;
    for (int i = ix_start_line; i < ix_stop_line; ++i) {
        cout << setw(3) << i+1 << "  ";
        if (i < v_document_lines.size())
            cout << v_document_lines[i];
        cout << endl;
        cout << endl;
    }
    cout << long_separator << endl
         << "go  next  previous  open  quit" << endl;
    string short_separator(8, '-');
    cout << short_separator << endl;
}

void open_file(string & file_name, vector<string> & v_document_lines, int & ix_current_line)
{
    cout << "file: ";
    getline(cin, file_name);
    ifstream ifs_document(file_name.c_str());
    v_document_lines.clear();
    ix_current_line = 0;
    string line(70,' ');
    string anchor_file;
    string anchor_text;
    string display_anchor;
    int anchor_begin;
    int anchor_end;
    int anchor_length;
    while (getline(ifs_document, line)) //NOTE TO SELF: THIS IS WHERE TO READ FOR ANCHORS AND AMEND
        {
            if(check_for_anchor(line))
            {
                anchor_begin = line.find("<");
                anchor_end = line.find(">");
                anchor_length = anchor_end - anchor_begin + 1;      //Add 1 Because indexing begins at 0
                string anchor(line, anchor_begin, anchor_length);
                anchor_file = get_anchor_file(anchor);
                anchor_text = get_anchor_text(anchor);
                link_number_files.push_back(" ");
                link_number_files[link_number] = anchor_file;
                link_number++;
                display_anchor = format_anchor(anchor);
                line.erase(anchor_begin,anchor_length);
                line.insert(anchor_begin, display_anchor);
            }

            cout << endl << anchor_file << endl;

            v_document_lines.push_back(line);
        }
    ifs_document.close();
}

void run_file_viewer() {
    string file_name;
    vector<string> v_document_lines;
    int ix_current_line = 0;

    open_file(file_name, v_document_lines, ix_current_line);

    while (true) { // while command is not 'quit'
        display(file_name, v_document_lines, ix_current_line);

        cout << "command: ";
        char command = '-';
        cin.get(command);
        cin.get(); // '\n'

        switch (command) {
            case 'q': return;

            case 'o': {
                open_file(file_name, v_document_lines, ix_current_line);
                break;
            }

            case 'n': {
                if (ix_current_line + windowHeight
                        < v_document_lines.size())
                    ix_current_line += windowHeight;
                break;
            }

            case 'p': {
                if (ix_current_line - windowHeight >= 0)
                    ix_current_line -= windowHeight;
                break;
            }
            case 'g': {
                int link_number_input;
                cout << "link number: ";
                cin >> link_number_input;
                ix_current_line = 0;
                v_document_lines.clear();
                open_file(link_number_files[link_number_input], v_document_lines, ix_current_line);
            }
        }
    }
}

int main() {
    run_file_viewer();
    return 0;
}
