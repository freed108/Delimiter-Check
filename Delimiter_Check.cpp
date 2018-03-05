#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
	stack<char> GenStack;
    
    char Top;
    
    double incorrect = 0.0;
    double ignore = 0.0;
    //Used to tell the program to ignore anything between /* and */
    double ignore2 = 0.0;
    //Used to tell the program to ignore anything between ' and '
    double ignore3 = 0.0;
    //Used to tell the program to avoid comments
    double ignore4A = 0.0;
    double ignore4B = 0.0;
    //Used to tell the program to ignore anything between " and "
    
    string TextFile = "TestFile.cpp";
    
    cout << "Enter the name of the file" << endl;
    cin >> TextFile;
    
    ifstream inFile(TextFile);
    
    if(inFile.fail())
    {
        cerr << "Error Opening File" << endl;
    }
    
    string line;
    double LineNumber = 0.0;
    
    while(!inFile.eof() && incorrect == 0)
    {
        getline(inFile, line);
        
        LineNumber++;
        
        ignore3 = 0.0;
        
        for(int i = 0; i < line.length() + 1; i++)
        {
            if(line[i] == '/' && line[i + 1] == '/')
            {
                ignore3 = 1.0;
            }
            
            else if(line[i] == '/' && line[i + 1] == '*')
            {
                ignore = 1.0;
            }
            
            else if(line[i] == '*' && line[i + 1] == '/')
            {
                ignore = 0.0;
            }
            
            else if(line[i] == *"'" && line[i + 2] == *"'")
            {
                i = i + 1;
                ignore2 = 1.0;
            }
            
            else if(line[i] == '"' && ignore4A == 1.0)
            {
                ignore4A = 0.0;
                ignore4B = 1.0;
                //cout << "Found end quote" << endl;
            }
            
            else if(line[i] == '"' && ignore4B == 0.0)
            {
                ignore4A = 1.0;
                //cout << "Found start quote" << endl;
            }
            
            else if(line[i] == *"(" && ignore == 0 && ignore2 == 0 && ignore3 == 0 && ignore4A == 0)
            {
                GenStack.push('(');
                //cout << "Line " << LineNumber << ": found (" << endl;
            }
            
            else if(line[i] == *"[" && ignore == 0 && ignore2 == 0 && ignore3 == 0 && ignore4A == 0)
            {
                GenStack.push('[');
                //cout << "Line " << LineNumber << ": found [" << endl;
            }
            
            else if(line[i] == *"{" && ignore == 0 && ignore2 == 0 && ignore3 == 0 && ignore4A == 0)
            {
                GenStack.push('{');
                //cout << "Line " << LineNumber << ": found {" << endl;
            }
            
            else if(line[i] == *")" && ignore == 0 && ignore2 == 0 && ignore3 == 0 && ignore4A == 0)
            {
                if(!GenStack.empty())
                {
                    Top = GenStack.top();
                    if(Top == '(')
                    {
                        GenStack.pop();
                        //cout << "Line " << LineNumber << ": found )" << endl;
                    }
                    
                    else if(Top == '[')
                    {
                        cout << "Line " << LineNumber << ": expected ] and found )" << endl;
                        incorrect = 1.0;
                    }
                    
                    else if(Top == '{')
                    {
                        cout << "Line " << LineNumber << ": expected } and found )" << endl;
                        incorrect = 1.0;
                    }
                }
                
                else
                {
                    cout << "Line " << LineNumber << ": found ) without a (" << endl;
                    incorrect = 1.0;
                }
            }
            
            else if(line[i] == *"]" && ignore == 0 && ignore2 == 0 && ignore3 == 0 && ignore4A == 0)
            {
                if(!GenStack.empty())
                {
                    Top = GenStack.top();
                    if(Top == '[')
                    {
                        GenStack.pop();
                        //cout << "Line " << LineNumber << ": found ]" << endl;
                    }
                    
                    else if(Top == '(')
                    {
                        cout << "Line " << LineNumber << ": expected ) and found ]" << endl;
                        incorrect = 1.0;
                    }
                    
                    else if(Top == '{')
                    {
                        cout << "Line " << LineNumber << ": expected } and found ]" << endl;
                        incorrect = 1.0;
                    }
                }
                
                else
                {
                    cout << "Line " << LineNumber << ": found ] without a [" << endl;
                    incorrect = 1.0;
                }
            }
            
            else if(line[i] == *"}" && ignore == 0 && ignore2 == 0 && ignore3 == 0 && ignore4A == 0)
            {
                if(!GenStack.empty())
                {
                    Top = GenStack.top();
                    if(Top == '{')
                    {
                        GenStack.pop();
                        //cout << "Line " << LineNumber << ": found }" << endl;
                    }
                    
                    else if(Top == '(')
                    {
                        cout << "Line " << LineNumber << ": expected ) and found }" << endl;
                        incorrect = 1.0;
                    }
                    
                    else if(Top == '[')
                    {
                        cout << "Line " << LineNumber << ": expected ] and found }" << endl;
                        incorrect = 1.0;
                    }
                }
                
                else
                {
                    cout << "Line " << LineNumber << ": found } without a {" << endl;
                    incorrect = 1.0;
                }
            }
            
            ignore2 = 0.0;
            ignore4B = 0.0;
        }
    }
    
    inFile.close();
    
    if(!GenStack.empty() && incorrect == 0)
    {
        Top = GenStack.top();
        if(Top == '(')
        {
            cout << "Reached end of file: missing )" << endl;
        }
        
        else if(Top == '[')
        {
            cout << "Reached end of file: missing ]" << endl;
        }
        
        else if(Top == '{')
        {
            cout << "Reached end of file: missing }" << endl;
        }
    }
    
    else
    {
        cout << "All delimiters in " << TextFile << " are perfectly matched" << endl;
    }
}
