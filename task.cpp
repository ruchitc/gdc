#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

/*
Class TaskFunctions
contains the methods which
interact with the files
task.txt and completed.txt
*/
class TaskFunctions
{
    public:
        /*
        add_item function
        adds a single entry to the
        specified file (file_var)

        This function adds the entry
        into its sorted place

        Old entries are read from task.txt
        New file temp.txt is created to add
        new entry with the existing ones.
        */
        void add_item(string pr, string task, string file_var)
        {
            int pr_int, pr_temp_int;
            string pr_temp, task_temp;

            ifstream fin;
            ofstream ftemp;

            fin.open(file_var.c_str(), ios::in);

            //checks if file exists and creates if it does not
            if(!fin)
            {
                fin.close();
                ofstream fout;
                fout.open(file_var.c_str(), ios::out);
                fout.close();
                fin.open(file_var.c_str(), ios::in);
            }

            ftemp.open("temp.txt", ios::out);
            fin.seekg(0);

            while(true)
            {
                fin>>pr_temp;
                fin.get();
                getline(fin, task_temp);

                if(fin.eof())
                {
                    //if end of file is encountered
                    //new entry is added at the end
                    ftemp<<pr<<" "<<task<<'\n';
                    break;
                }

                pr_int = stoi(pr);
                pr_temp_int = stoi(pr_temp);

                if(pr_int >= pr_temp_int)
                    ftemp<<pr_temp<<" "<<task_temp<<'\n';
                else
                {
                    /*
                    if the entry's place is found
                    it is added along with its
                    /succeeding entry

                    loop is broken since all
                    the next entries will have
                    a lower priority and would
                    not be added
                    */
                    ftemp<<pr<<" "<<task<<'\n';
                    ftemp<<pr_temp<<" "<<task_temp<<'\n';
                    break;
                }
            }

            /*
            this loop adds the
            remaining existing
            entries (if any)
            */
            while(true)
            {
                fin>>pr_temp;
                fin.get();
                getline(fin, task_temp);

                if(fin.eof())
                    break;

                ftemp<<pr_temp<<" "<<task_temp<<'\n';
            }

            fin.close();
            ftemp.close();

            remove(file_var.c_str());
            rename("temp.txt", file_var.c_str());
        }

        /*
        del_item function
        deletes an entry from specified file
        (file_var)
        based on index

        index is matched with the counter

        flag is returned to check
        if matching entry was found and deleted
        flag = -1 if not found
        flag = 0 if found and deleted
        */
        int del_item(string index, string file_var)
        {
            int counter, flag = -1;
            string pr, task;

            counter = 0;

            int index_int;
            index_int = stoi(index);

            ifstream fin;
            ofstream ftemp;

            fin.open(file_var.c_str(), ios::in);

            //checks file
            if(!fin)
            {
                fin.close();
                ofstream fout;
                fout.open(file_var.c_str(), ios::out);
                fout.close();
                fin.open(file_var.c_str(), ios::in);
            }

            ftemp.open("temp.txt", ios::out);

            while(true)
            {
                counter++;

                fin>>pr;
                fin.get();
                getline(fin, task);

                if(fin.eof())
                    break;

                /*
                if index found
                matching entry is not written
                in temp.txt
                */
                if(counter == index_int)
                {
                    flag = 0;
                    continue;
                }
                else
                    ftemp<<pr<<" "<<task<<'\n';

            }

            ftemp.close();
            fin.close();

            remove(file_var.c_str());
            rename("temp.txt", file_var.c_str());

            return flag;
        }

        /*
        mark_item function
        marks a task as done
        based on index

        removes it from task.txt file
        and adds it to completed.txt file

        flag is returned to check
        if matching entry was found and marked
        flag = -1 if not found
        flag = 0 if found and marked
        */
        int mark_item(string index, string task_var, string comp_var)
        {
            int counter, flag = -1;
            string pr, task;
            string task_temp;

            counter = 0;

            int index_int;
            index_int = stoi(index);

            ifstream fin;
            ofstream fout, ftemp;

            fin.open(task_var.c_str(), ios::in);

            //checks file
            if(!fin)
            {
                fin.close();
                fout.open(task_var.c_str(), ios::out);
                fout.close();
                fin.open(task_var.c_str(), ios::in);
            }

            fout.open(comp_var.c_str(), ios::app);
            ftemp.open("temp.txt", ios::out);

            while(true)
            {
                counter++;

                fin>>pr;
                fin.get();
                getline(fin, task);

                if(fin.eof())
                    break;

                /*
                if index is found
                task is added to completed.txt

                else
                tasks are added to task.txt
                */
                if(counter == index_int)
                {
                    fout<<task<<'\n';
                    flag = 0;
                }
                else
                    ftemp<<pr<<" "<<task<<'\n';

            }

            ftemp.close();
            fout.close();
            fin.close();

            remove(task_var.c_str());
            rename("temp.txt", task_var.c_str());

            return flag;
        }

        /*
        list_items function
        lists all entries in specified
        file (file_var)

        This function is used for both
        task.txt and completed.txt
        */
        void list_items(string file_var)
        {
            int index = 0;
            string pr, task;

            ifstream fin;

            fin.open(file_var.c_str(), ios::in);
            fin.seekg(0);

            //checks file
            if(!fin)
            {
                fin.close();
                ofstream fout;
                fout.open(file_var.c_str(), ios::out);
                fout.close();
                fin.open(file_var.c_str(), ios::in);
            }

            if(file_var == "task.txt")
            {
                while(true)
                {
                    index++;

                    fin>>pr;
                    fin.get();
                    getline(fin, task);

                    if(fin.eof())
                        break;

                    cout<<index<<". "<<task<<" ["<<pr<<"]"<<'\n';
                }
            }

            if(file_var == "completed.txt")
            {
                while(true)
                {
                    index++;

                    getline(fin, task);

                    if(fin.eof())
                        break;

                    cout<<index<<". "<<task<<'\n';
                }
            }


            fin.close();
            return;
        }

        /*
        count_items function
        To count entries in the specified
        file (file_var)

        counter is returned
        */
        int count_items(string file_var)
        {
            int counter = 0;
            string pr, task;

            ifstream fin;

            fin.open(file_var.c_str(), ios::in);
            fin.seekg(0);

            //checks file
            if(!fin)
            {
                ofstream fout;
                fout.open(file_var.c_str(), ios::out);
                fout.close();
                fin.open(file_var.c_str(), ios::in);
            }

            while(true)
            {
                getline(fin, task);

                if(fin.eof())
                    break;

                counter++;
            }

            fin.close();

            return counter;
        }
};

/*
Class TaskMenu
Interacts with the functions
of Class TaskFunctions

All error and success messages
are checked and displayed here
*/
class TaskMenu
{
    private:
        TaskFunctions tf;

    public:
        //function for printing 'help' page
        void help()
        {
            cout<<"Usage :-"<<'\n'
                <<"$ ./task add 2 hello world    # Add a new item with priority 2 and text \"hello world\" to the list"<<'\n'
                <<"$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order"<<'\n'
                <<"$ ./task del INDEX            # Delete the incomplete item with the given index"<<'\n'
                <<"$ ./task done INDEX           # Mark the incomplete item with the given index as complete"<<'\n'
                <<"$ ./task help                 # Show usage"<<'\n'
                <<"$ ./task report               # Statistics";
        }

        /*
        adds pending task to task.txt
        Uses add_item of TaskFunctions
        */
        void add_task(string pr, string task)
        {
            string file_name;

            file_name = "task.txt";
            tf.add_item(pr, task, file_name);

            cout<<"Added task: "<<"\""<<task<<"\""<<" with priority "<<pr<<'\n';
        }

        /*
        deletes task from pending
        Uses del_item of TaskFunctions
        Shows error or success
        */
        void del_task(string index)
        {
            int flag = 0;

            string file_name;

            file_name = "task.txt";
            flag = tf.del_item(index, file_name);

            if(flag == -1)
                cout<<"Error: task with index #"<<index<<" does not exist. Nothing deleted."<<'\n';
            else
                cout<<"Deleted task #"<<index<<'\n';
        }

        /*
        marks task as done
        Uses mark_item from TaskFunctions
        Shows error or success
        */
        void mark_task(string index)
        {
            int flag = 0;

            string task_file, comp_file;
            string task;

            task_file = "task.txt";
            comp_file = "completed.txt";
            flag = tf.mark_item(index, task_file, comp_file);

            if(flag == -1)
                cout<<"Error: no incomplete item with index #"<<index<<" exists."<<'\n';
            else
                cout<<"Marked item as done."<<'\n';

        }

        /*
        lists all tasks from task.txt
        Uses count_items to check
        if pending tasks are present

        Uses list_items to list all tasks
        */
        void ls_func()
        {
            int counter = 0;
            string file_name;

            file_name = "task.txt";

            counter = tf.count_items(file_name);

            if(counter == 0)
            {
                cout<<"There are no pending tasks!";
                return;
            }

            tf.list_items(file_name);
        }

        /*
        lists all tasks from
        task.txt and completed.txt
        Uses count_items to get
        number of tasks from files

        Uses list_items to list all tasks
        */
        void report_func()
        {
            int flag = 0;
            int total = 0;
            string file_name;

            file_name = "task.txt";
            total = tf.count_items(file_name);

            cout<<"Pending : "<<total<<'\n';
            tf.list_items(file_name);

            cout<<'\n';

            file_name = "completed.txt";
            total = tf.count_items(file_name);

            cout<<"Completed : "<<total<<'\n';
            tf.list_items(file_name);
        }
};

/*
Used to check if index
provided by user is an
integer or not
*/
bool check_number(char n[])
{
    int i = 0;

    if(n[0] == '-')
        i = 1;

    for(; n[i] != 0; i++)
    {
        if(!isdigit(n[i]))
            return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    TaskMenu taskm;

    if(argc == 1)
        taskm.help();

    if(argc > 1)
    {
        string cmd;
        cmd = argv[1];

        if(cmd == "help")
            taskm.help();

        if(cmd == "ls")
            taskm.ls_func();

        if(cmd == "report")
            taskm.report_func();

        if(cmd == "del")
        {
            if(argc == 2)
                cout<<"Error: Missing NUMBER for deleting tasks.";
            else
            {
                if(check_number(argv[2]))
                {
                    string index;
                    index = argv[2];

                    taskm.del_task(index);
                }
                else
                    cout<<"Please enter an integer value for index."<<'\n';

            }
        }

        if(cmd == "done")
        {
            if(argc == 2)
                cout<<"Error: Missing NUMBER for marking tasks as done.";
            else
            {
                if(check_number(argv[2]))
                {
                    string index;
                    index = argv[2];

                    taskm.mark_task(index);
                }
                else
                    cout<<"Please enter an integer value for index."<<'\n';
            }
        }

        if(cmd == "add")
        {
            if(argc < 4)
                cout<<"Error: Missing tasks string. Nothing added!";
            else if(argc > 4)
            {
                cout<<"Please ensure that the task is entered in double quotes."<<'\n';
                cout<<"Example: ./task add 1 \"Buy Groceries\""<<'\n';
            }
            else
            {
                if(check_number(argv[2]))
                {
                    string pr, task;
                    pr = argv[2];
                    task = argv[3];

                    int pr_int;
                    pr_int = stoi(pr);

                    if(pr_int < 0)
                        cout<<"Value of priority cannot be less than 0."<<'\n';
                    else
                        taskm.add_task(pr, task);
                }
                else
                    cout<<"Please enter an integer value for priority."<<'\n';
            }
        }
    }

    return 0;
}
