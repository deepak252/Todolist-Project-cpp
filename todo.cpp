#include <bits/stdc++.h>
using namespace std;

int countTodo=0;

//getting date in "yyyy-mm-dd"
string yyyymmdd()
{
    const int MAXLEN = 80;
    char s[MAXLEN];
    time_t t = time(0);
    strftime(s, MAXLEN, "%Y-%m-%d", localtime(&t));
    return s;
}
//Printing Usage
void help(){
//    cout<<"Usage :-"<<endl;
//    printf("%-25s %s\n", "$ ./todo add \"todo item\"", "# Add a new todo");
//    printf("%-25s %s\n", "$ ./todo ls", "# Show remaining todos");
//    printf("%-25s %s\n", "$ ./todo del NUMBER", "# Delete a todo");
//    printf("%-25s %s\n", "$ ./todo done NUMBER", "# Complete a todo");
//    printf("%-25s %s\n", "$ ./todo help", "# Show usage");
//    printf("%-25s %s", "$ ./todo report", "# Statistics");
    cout<<"Usage :-"<<endl;
    cout<<"$ ./todo add \"todo item\"  # Add a new todo"<<"\n";
    cout<<"$ ./todo ls               # Show remaining todos"<<endl;
    cout<<"$ ./todo del NUMBER       # Delete a todo"<<endl;
    cout<<"$ ./todo done NUMBER      # Complete a todo"<<endl;
    cout<<"$ ./todo help             # Show usage"<<endl;
    cout<<"$ ./todo report           # Statistics";




}
// Counting number of line in "todo.txt" file
void countLines(string fileName)
{
    ifstream file;
    file.open("todo.txt");
    countTodo=-1;
    string line;
    while(file)
    {
        getline(file,line);
        countTodo++;
    }
    file.close();

}
// deleting a todo from todo.txt file...at index  "num"
void deleteTodo(int num)
{
    ifstream todo;
    ofstream temp;
    todo.open("todo.txt");
    temp.open("temp.txt");

    if(num==countTodo)
    {
        char c;
        while(todo.get(c))
        {
            if(c=='\n')
                break;
        }
        while(todo.get(c))
        {
            temp<<c;
        }

    }
    else
    {
        string line;
        int lineNo=-1;
        while(todo)
        {
            lineNo++;
            getline(todo,line);
            if(lineNo!=(countTodo-num))
            {
                if(lineNo==0)
                    temp<<line;

                else
                    temp<<endl<<line;
            }
        }
    }
    todo.close();
    temp.close();
    remove("todo.txt");
    rename("temp.txt","todo.txt");
}
//Converting a string type number to Integer type
int convertToInt(string s)
{
    stringstream ss(s);
    int num=0;
    ss>>num;
    return num;
}


int main(int argc, char* argv[])
{
    fstream todo,done,temp;

    string line;
    todo.open("todo.txt",ios::app|ios::in|ios::out);
    temp.open("temp.txt",ios::app|ios::in|ios::out);
    done.open("done.txt",ios::app|ios::in|ios::out);

    countLines("todo.txt");
    if(argc==1||!strcmp(argv[1],"help"))
    {
        help();
        return 0;
    }
    if(!strcmp(argv[1],"add"))
    {
        if(argc==2)
        {
            cout<<"Error: Missing todo string. Nothing added!";
            return 0;
        }
        temp<<argv[2];
        while(todo)
        {
            getline(todo,line);
            temp<<endl<<line;
        }
        todo.close();
        temp.close();

        remove("todo.txt");
        rename("temp.txt","todo.txt");
        todo.seekg(0,ios::beg);
        cout<<"Added todo: \""<<argv[2]<<"\"";
    }
    if(!strcmp(argv[1],"ls"))
    {
        int i=countTodo;
        if(i==0)
        {
            cout<<"There are no pending todos!";
            return 0;
        }
        while(todo&&i)
        {
            getline(todo,line);
            cout<<"["<<i<<"] "<<line<<endl;
            i--;
        }
    }

    if(!strcmp(argv[1],"del"))
    {
        if(argc==2)
        {
            cout<<"Error: Missing NUMBER for deleting todo.";
            return 0;
        }

        int num=convertToInt(argv[2]);
        if(num>countTodo||num<1)
            cout<<"Error: todo #"<<num<<" does not exist. Nothing deleted."<<endl;
        else
        {
            todo.close();
            temp.close();
            deleteTodo(num);
            cout<<"Deleted todo #"<<num<<endl;
        }

    }

    if(!strcmp(argv[1],"done"))
    {
        if(argc==2)
        {
            cout<<"Error: Missing NUMBER for marking todo as done.";
            return 0;
        }
        int num=convertToInt(argv[2]);
        if(num>countTodo ||num<1)
            cout<<"Error: todo #"<<num<<" does not exist."<<endl;
        else
        {
            int currentLine=-1;

            while(todo)
            {
                currentLine++;
                getline(todo,line);
                if(currentLine==(countTodo-num))
                {
                    temp<<"x "<<yyyymmdd()<<" "<<line;
                    break;
                }
            }
            while(done)
            {
                getline(done,line);
                temp<<endl<<line;
            }
            todo.close();
            temp.close();
            done.close();

            remove("done.txt");
            rename("temp.txt","done.txt");

            deleteTodo(num);
            cout<<"Marked todo #"<<num<<" as done."<<endl;
        }
    }

    if(!strcmp(argv[1],"report"))
    {
        int pending,completed=-1;
        pending=countTodo;

        while(done)
        {
            getline(done,line);
            completed++;
        }
        cout<<yyyymmdd()<<" Pending : "<<pending<<" Completed : "<<completed<<endl;

    }

    temp.close();
    todo.close();
    done.close();
    return 0;
}
