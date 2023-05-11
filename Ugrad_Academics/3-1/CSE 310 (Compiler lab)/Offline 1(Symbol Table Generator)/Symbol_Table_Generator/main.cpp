#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>

using namespace std;

ofstream fout("output.txt");


vector<string> tokens;

// creating custom split() function
void split (string str, char seperator)
{
    int currIndex = 0, i = 0;
    int startIndex = 0, endIndex = 0;
    while (i <= str.length())
    {
        if (str[i] == seperator || i == str.length())
        {
            endIndex = i;
            string subStr = "";
            subStr.append(str, startIndex, endIndex - startIndex);
            // cout << subStr << endl;
            tokens.push_back(subStr);

            currIndex += 1;
            startIndex = endIndex + 1;
        }
        i++;
    }
}

//Symbol info class
class SymbolInfo
{
private:
    string Name;
    string Type;
    int hashtable_position;
    int linked_list_position;

public:

    SymbolInfo *Next;
    SymbolInfo *Previous;

    SymbolInfo(string name,string type)
    {
        Name = name;
        Type = type;
        Next = NULL;
        Previous = NULL;
        hashtable_position = 0;
        linked_list_position = 0;

    }

    void setName(string name)
    {
        Name = name;
    }
    void setType(string type)
    {
        Type = type;
    }

    void set_hashtable_position (int hp)
    {
        hashtable_position = hp;

    }

    void set_linked_list_position (int lp)
    {
        linked_list_position = lp;

    }

    int get_hashtable_position()
    {
        return hashtable_position;
    }

    int get_linked_list_position()
    {
        return linked_list_position;
    }





    string getName()
    {
        return Name;
    }
    string getType()
    {
        return Type;
    }

    ~SymbolInfo()
    {
        delete Next;
        delete Previous;
    }



};


class ScopeTable
{

private:

    SymbolInfo **scope_table;
    int scope_table_size; //hash table size
    ScopeTable *parent_scope;
    string id;


public:
    int total_child;

    ScopeTable(int bucket_no)
    {
        scope_table_size = bucket_no;
        total_child=0;
        scope_table = new SymbolInfo*[scope_table_size];

        for(int i=0; i< scope_table_size ; i++)
        {
            scope_table[i] = NULL;
        }


        parent_scope = NULL;
    }

    int sdbmhash(string st)
    {
        const char *str = st.c_str();
        unsigned int hash = 0;
        int c;

        while (c = *str++)
            hash = c + (hash << 6) + (hash << 16) - hash;

        return hash;

    }


    int Hash_function(string str)
    {
        return (sdbmhash(str) % scope_table_size);
    }

    void set_parent_scope(ScopeTable *ps)
    {
        parent_scope = ps;
    }

    ScopeTable* get_parent_scope()
    {
        return parent_scope;
    }

    void set_scope_table_id(string ID)
    {
        id = ID;
    }

    string get_scope_table_id()
    {
        return id;
    }

    ~ScopeTable()
    {
        //cout << "destroyed " << "ScopeTable# "<<id;
        for (int i=0; i<scope_table_size ; i++)
        {
            delete scope_table[i];
        }

        delete scope_table;

    }


    SymbolInfo* Look_up(string name)
    {
        for(int i=0; i<scope_table_size; i++)
        {
            SymbolInfo *current_node = scope_table[i];
            int iteration = 0;

            while(current_node != NULL)
            {
                if(current_node->getName() == name)
                {
                    cout <<"Found in ScopeTable# " << get_scope_table_id() <<" at position "<< i<<", "<<iteration << endl<<endl;
                    fout <<"Found in ScopeTable# " << get_scope_table_id() <<" at position "<< i<<", "<<iteration << endl<<endl;

                    return current_node;
                }

                else
                {
                    current_node = current_node->Next;
                    iteration++;
                }
            }

        }

        //if not found
        return NULL;
    }


    bool insert(string name,string type)
    {
        //if the symbol already exists in the scope
        SymbolInfo *found_symbol = Look_up(name);
        if(found_symbol != NULL)
        {
            cout << "< " << found_symbol->getName() << ","<<found_symbol->getType() <<" >"
                 << " already exist in the currentScopeTable"<<endl<<endl;

            fout << "< " << found_symbol->getName() << ","<<found_symbol->getType() <<" >"
                 << " already exist in the currentScopeTable"<<endl<<endl;
            return false;
        }

        SymbolInfo *new_symbol = new SymbolInfo(name,type);

        int hashing_position = Hash_function(name);

        if(scope_table[hashing_position] == NULL)
        {
            scope_table[hashing_position] = new_symbol;

            new_symbol->set_hashtable_position(hashing_position);
            new_symbol->set_linked_list_position(0);

            cout << "Inserted in ScopeTable# "<< get_scope_table_id() <<" at position "<<hashing_position<<", "<<0 <<endl<<endl;
            fout << "Inserted in ScopeTable# "<< get_scope_table_id() <<" at position "<<hashing_position<<", "<<0 <<endl<<endl;

            return true;
        }

        else
        {
            int iteration = 1;
            SymbolInfo *current_node = scope_table[hashing_position];

            while(current_node->Next != NULL)
            {
                current_node = current_node->Next;
                iteration++;
            }
            current_node->Next = new_symbol;
            current_node = current_node;

            new_symbol->set_hashtable_position(hashing_position);
            new_symbol->set_linked_list_position(iteration);

            cout << "Inserted in ScopeTable# "<< get_scope_table_id() <<" at position "<<hashing_position<<", "<<iteration << endl<<endl;

            fout << "Inserted in ScopeTable# "<< get_scope_table_id() <<" at position "<<hashing_position<<", "<<iteration << endl<<endl;

            return true;
        }


        return false;



    }





    bool Delete(string name)
    {

        SymbolInfo *temp = Look_up(name);
        if(temp == NULL)  //if the symbol to be deleted is not exist in current scope
        {
            cout << name <<" not found"<< endl;
            fout << name <<" not found"<< endl;

            return false;
        }

        else
        {
            for(int i=0; i<scope_table_size; i++)
            {
                SymbolInfo *current_node = scope_table[i];

                while(current_node != NULL)
                {
                    if(current_node->getName() == name)
                    {

                        if(current_node->Previous == NULL && current_node->Next == NULL  )
                        {

                            scope_table[i] = current_node->Next;
                            delete current_node;
                        }

                        else if(current_node->Previous == NULL && current_node->Next != NULL  )
                        {
                            scope_table[i] = current_node->Next;
                            current_node->Next->Previous = NULL;
                            current_node->Next = NULL;
                            delete current_node;
                        }

                        else if(current_node->Previous != NULL && current_node->Next == NULL )
                        {
                            current_node->Previous->Next = NULL;
                            current_node->Previous = NULL;
                            delete current_node;
                        }

                        else
                        {
                            current_node->Next->Previous = current_node->Previous;
                            current_node->Previous->Next = current_node->Next;
                            current_node->Next = NULL;
                            current_node->Previous = NULL;
                            delete current_node;
                        }

                        cout <<"Deleted entry at " << current_node->get_hashtable_position()<<","<<
                             current_node->get_linked_list_position() <<" in the current scopetable"<<endl<<endl;
                        fout <<"Deleted entry at " << current_node->get_hashtable_position()<<","<<
                             current_node->get_linked_list_position() <<" in the current scopetable"<<endl<<endl;

                        return true;
                    }

                    else
                    {
                        current_node = current_node->Next;
                    }
                }

            }

        }

        return false;


    }


    void print()
    {
        cout << "ScopeTable #" << id << endl << endl;
        fout << "ScopeTable #" << id << endl << endl;


        for(int i=0; i< scope_table_size; i++)
        {
            cout << i <<" --> ";
            fout << i <<" --> ";


            SymbolInfo *current_node = scope_table[i];

            while(current_node != NULL)
            {
                cout << " < " <<current_node->getName() << " : " << current_node->getType() << " > ";
                cout << "  ";

                fout << " < " <<current_node->getName() << " : " << current_node->getType() << " > ";
                fout << "  ";

                current_node = current_node->Next;

            }
            cout << endl;
            fout << endl;


        }
    }





};


class SymbolTable
{
private:
    ScopeTable *current_scope_table;
    int each_hash_table_size;

public:
    int scope_generation_no;

    SymbolTable(int Each_hash_table_size )
    {
        each_hash_table_size = Each_hash_table_size;
        //by default there is a scopetable of ID = 1 initially
        current_scope_table = new ScopeTable(each_hash_table_size);
        current_scope_table->set_scope_table_id("1");

        scope_generation_no = 1;
    }

    void set_current_scope_table(ScopeTable *current_scopeTable)
    {
        current_scope_table = current_scopeTable;
    }
    ScopeTable* get_current_scope_table()
    {
        return current_scope_table;
    }

    void set_each_hash_table_size(int bucket_no)
    {
        each_hash_table_size = bucket_no;
    }
    int get_each_hash_table_size()
    {
        return each_hash_table_size;
    }


    void Enter_Scope()
    {
        ScopeTable *new_scopeTable = new ScopeTable(each_hash_table_size);

        new_scopeTable->set_parent_scope(current_scope_table);
        current_scope_table = new_scopeTable;

        if(current_scope_table->get_parent_scope() == NULL)
        {
            //scope_generation_no++;
            //converting the integer "scope_generation_no" to string

            stringstream ss;
            ss << scope_generation_no;
            //char *scope_generation_no_char_ptr = new char[5] ;
            //itoa(scope_generation_no,scope_generation_no_char_ptr,10);
            string scope_generation_no_str = ss.str();

            current_scope_table->set_scope_table_id(scope_generation_no_str);

        }

        else
        {
            current_scope_table->get_parent_scope()->total_child++;


            //converting the integer "total_child" to a string


            //char *total_child_char_ptr = new char [5] ;
            int parent_total_child =current_scope_table->get_parent_scope()-> total_child;
            //itoa( parent_total_child,total_child_char_ptr,10);

            stringstream ss;
            ss << parent_total_child ;

            string total_child_str=ss.str();
            string table_ID = current_scope_table->get_parent_scope()->get_scope_table_id() + "." + total_child_str;
            current_scope_table->set_scope_table_id(table_ID);
        }


        cout << "New ScopeTable with id "<< current_scope_table->get_scope_table_id()+" created" << endl<<endl;
        fout << "New ScopeTable with id "<< current_scope_table->get_scope_table_id()+" created" << endl<<endl;

    }

    void Exit_Scope()
    {
        ScopeTable *temp = current_scope_table;

        if(temp == NULL)
        {
            cout <<"NO CURRENT SCOPE"<<endl<<endl;
            fout <<"NO CURRENT SCOPE"<<endl<<endl;

            return;
        }

        current_scope_table = current_scope_table->get_parent_scope();

        cout << "ScopeTable with id "<< temp->get_scope_table_id() <<" removed" <<endl<<endl;
        fout << "ScopeTable with id "<< temp->get_scope_table_id() <<" removed" <<endl<<endl;

        delete temp;
    }

    bool Insert(string name,string type)
    {
        bool isInserted = current_scope_table->insert(name,type);

        return isInserted;


    }

    bool Remove(string name)
    {
        bool isDeleted = current_scope_table->Delete(name);
        return isDeleted;
    }


    //jodi same symbol multiple scope a thake tahole ?

    //dhorlam 1st founded symbol ta print korte hobe
    SymbolInfo* Look_up(string name)
    {
        ScopeTable *curr_scope = current_scope_table;

        while(curr_scope != NULL)
        {
            SymbolInfo *found_symbol = curr_scope->Look_up(name);
            if(found_symbol != NULL)
            {
                return found_symbol;
            }
            curr_scope = curr_scope->get_parent_scope();

        }

        cout << "Not found"<<endl<<endl;
        fout << "Not found"<<endl<<endl;

        return NULL;



    }


    void Print_Current_Scope_Table()
    {
        current_scope_table->print();
    }

    void Print_All_Scope_Table()
    {
        cout << endl;
        fout << endl;

        ScopeTable *curr_scope = current_scope_table;

        while(curr_scope != NULL)
        {
            curr_scope->print();

            curr_scope = curr_scope->get_parent_scope();
            cout << endl;
            fout << endl;

        }
    }

    //deleting all existing scope table
    ~SymbolTable()
    {
        if(current_scope_table != NULL)
        {
            ScopeTable *curr = current_scope_table;
            ScopeTable *parent = current_scope_table->get_parent_scope();

        while(curr != NULL)
        {
            delete curr;
            curr = parent;

            if(parent != NULL)
            parent = parent->get_parent_scope();
        }

        }
    }



};







int main()
{
    ifstream fin("input.txt");


    if(!fin)
    {

        cout << "file did not open" <<endl;
    }
    string line;
    char space =' ';
    bool bucket_flag = false;
    int bucket_no;
    SymbolTable *symbol_table;

    while(getline(fin,line))
    {

        split(line,space);

        /* if(tokens[0] == "I")
         {
             cout << tokens[0] << " " << tokens[1] << " "<< tokens[2]<<endl;
         }
         else if(tokens[0] == "L")
         {
                        cout << tokens[0] << " " << tokens[1] << endl;

         }
         else if(tokens[0] == "P")
         {
                        cout << tokens[0] << " " << tokens[1] << endl;

         }
         else if(tokens[0] == "S")
         {
                                   cout << tokens[0] << endl;

         }
         else if(tokens[0] == "D")
         {
                                   cout << tokens[0] << " " << tokens[1] << endl;

         }
         else if(tokens[0] == "E")
         {
                                              cout << tokens[0] << endl;

         }*/

        //just for converting the input "bucket_no" string to integer in very 1st line"
        if(bucket_flag == false)
        {
            bucket_no = atoi(tokens[0].c_str());
            // cout << bucket_no << endl;
            symbol_table = new SymbolTable(bucket_no);
            bucket_flag = true;
            //tokens.clear();
            //continue;
        }

        else if(tokens[0] == "I")
        {

            cout << tokens[0] <<" " << tokens[1]<<" "<<tokens[2]  <<endl <<endl;
            fout << tokens[0] <<" " << tokens[1]<<" "<<tokens[2]<<endl <<endl;


            if(symbol_table->get_current_scope_table() == NULL)
            {
                symbol_table->Enter_Scope();


                symbol_table->get_current_scope_table()->insert(tokens[1],tokens[2]);

            }

            else
            {

                symbol_table->get_current_scope_table()->insert(tokens[1],tokens[2]) ;
            }
        }

        else if(tokens[0] == "L")
        {
            cout << tokens[0] <<" " << tokens[1] <<endl <<endl;
            fout << tokens[0] <<" " << tokens[1]<<endl <<endl;


            symbol_table->Look_up(tokens[1]);

        }
        else if(tokens[0] == "D")
        {
            cout << tokens[0] <<" " << tokens[1]<<endl<<endl;
            fout << tokens[0] <<" " << tokens[1]<<endl<<endl;

            symbol_table->Remove(tokens[1]);

        }
        else if(tokens[0] == "P")
        {
            cout << tokens[0] <<" " << tokens[1]<<endl<<endl;
            fout << tokens[0] <<" " << tokens[1]<<endl<<endl;

            if(tokens[1] == "C")
            {
                symbol_table->get_current_scope_table()->print();
            }
            else if(tokens[1] == "A")
            {
                symbol_table->Print_All_Scope_Table();
            }
        }
        else if(tokens[0] == "S")
        {
            cout << tokens[0] <<endl<<endl;
            fout << tokens[0] <<endl<<endl;

            symbol_table->Enter_Scope();
        }
        else if(tokens[0] == "E")
        {
            cout << tokens[0] <<endl<<endl;
            fout << tokens[0] <<endl<<endl;
            symbol_table->Exit_Scope();
        }



        // cout << endl;


        tokens.clear();



    }













    return 0;
}
