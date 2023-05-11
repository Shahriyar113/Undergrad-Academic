%{
//#include<bits/stdc++.h>
#include"Symbol_Table.cpp"

int yyparse(void);
int yylex(void);

extern FILE *yyin; //aita na likhle bison "yyin" k chinbe na

ofstream f_log_out("log.txt");
ofstream f_error_out("error.txt");
ofstream f_code("code.asm");
ofstream f_optimized_code("optimized_code.asm");
ifstream f_read_code;
int line_count = 1;
int total_errors = 0;

SymbolTable st(30); 

string type;
vector<SymbolInfo*> *function_definition_parameter_list;
//this variable is for creating new scope (without function definition)

bool function_scope_flag = true;  //jokhn function scope "true" thakbe tokhn "{" dekha mane oi kono akti function er scope shuru hocche


void yyerror(char *s){
	f_log_out << "Error at line " << line_count << ": Syntax Error\n";
	f_error_out << "Error at line " << line_count << ": Syntax Error\n";
	total_errors++;
}

int temp_variable_count = 0;
int label_count = 0;
string initial_code = "";
vector<pair<string, string>> data_list;

//converting a_1.1 to a_1_1
string makeScopeID(string id){
	string x = ".";
	string y = "_";
	size_t pos;
	while ((pos = id.find(x)) != std::string::npos) {
        id.replace(pos, 1, y);
    }
	return id;
}

string newTemp(){
	string temp_variable  = "t" + to_string(temp_variable_count);
	temp_variable_count++;
	data_list.push_back({temp_variable,"0"});
	return temp_variable;
}

string newLabel(){
	string label  = "l" + to_string(label_count);
	label_count++;
	return label;
}

void Optimized_Code(string filename){
	f_read_code.open(filename);
	//f_optimized_code.open("optimized_code.asm");
	string first_line;
	string second_line;
	string first_words;
	string final_first_words;
	string second_words;
	string final_second_words;

	while(getline(f_read_code,first_line)){
		vector <string> first_tokens;
		vector <string> second_tokens;
		stringstream check_first(first_line);
      
		// Tokenizing w.r.t. space ' '
		while(getline(check_first, first_words, ' ')){	
			stringstream check_first_word(first_words);
			while(getline(check_first_word, final_first_words, ',')){
				first_tokens.push_back(final_first_words);
			}
		}
		
		if(first_tokens.size() == 3 && first_tokens.at(0) == "\tmov"){
			getline(f_read_code,second_line);
			
			stringstream check_second(second_line);

			while(getline(check_second, second_words, ' ')){
				stringstream check_second_word(second_words);
				while(getline(check_second_word, final_second_words, ',')){
					second_tokens.push_back(final_second_words);
				}
			}
			if(second_tokens.size() == 3 && second_tokens.at(0) == "\tmov"){
				int match = first_tokens.at(1).compare(second_tokens.at(2));
				int match2 = first_tokens.at(2).compare(second_tokens.at(1));

				if(match == 0 && match2 == 0)
				{
				//mov ax,t1
				//mov t1,ax type found
				
				f_optimized_code <<first_line << "\n";
				f_optimized_code <<";\t"<< second_line<<"; peepholed" << "\n";	
				
				
				}
				else{
					f_optimized_code << first_line << "\n";
					//f_optimized_code << second_line << "\n";
					f_read_code.seekg(-second_line.size()-1,ios::cur);
				}	
			}
			else
			{	f_optimized_code << first_line << "\n";
				f_optimized_code << second_line << "\n";	
			}
		}	
		else
		{
		
		f_optimized_code << first_line << "\n";
		}	
	}
	f_optimized_code << "END main" << "\n";
	f_read_code.close();
	f_optimized_code.close();
}





%}

%union{

int integer_val;
double double_val;
char char_val;
SymbolInfo *symbol;
vector<SymbolInfo*> *symbols;



}





%token<symbol> IF INT FOR DO WHILE FLOAT VOID SWITCH DEFAULT ELSE CHAR BREAK DOUBLE RETURN CASE CONTINUE ADDOP MULOP INCOP DECOP ASSIGNOP NOT RELOP LOGICOP LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON STRING PRINTLN ID

%token<symbol> CONST_INT


%token<symbol> CONST_FLOAT

%token<symbol> CONST_CHAR



%type<symbol> type_specifier

%type<symbols> declaration_list var_declaration func_declaration parameter_list unit factor unary_expression term simple_expression rel_expression logic_expression expression variable expression_statement arguments argument_list statement statements compound_statement func_definition program 

%nonassoc WITHOUT_ELSE
%nonassoc ELSE


%%

start : program
	{
		//write your code in this block in all the similar blocks below
		f_log_out << "Line " << line_count <<  ": start : program  \n\n\n";
		
		
			//assembly code
			if(total_errors == 0){
				initial_code += ".MODEL small\n.STACK 100h\n.DATA\n\tprint_var dw ?\n\tdigit_count dw ?\n\tbackup_cx dw ?\n\tret_temp dw ?\n";

				//$$->setCode(initial_code);
				for(int i = 0; i < data_list.size(); i++){
					
					//if the data is normal variable
					if(data_list.at(i).second == "0")
						initial_code += "\t" + data_list.at(i).first + " dw ?\n";	
					else //if the data is an array
						initial_code += "\t" + data_list.at(i).first + " dw " + data_list.at(i).second + " dup(?)\n";
				}
				initial_code += ".CODE\n";
				
				//print function

   
				initial_code += "print PROC\n";
				initial_code +=	"\tpush ax\n";
				initial_code += "\tpush bx\n"; 
				initial_code += "\tpush cx\n";
				initial_code += "\tpush dx\n";
				initial_code += "\tmov ax, print_var\n";
				initial_code += "\tmov bx, print_var\n";
				initial_code += "\tcmp ax, 0\n";
				initial_code += "\tjl negative\n";

				initial_code += "\tjmp non_negative\n";
				
				 
				initial_code += "negative:\n";
				initial_code += "\tneg ax\n";
				initial_code += "\tpush ax\n";
				initial_code += "\tmov ah, 2\n";
				initial_code += "\tmov dl, '-'\n";
				initial_code += "\tint 21h\n";

				initial_code += "\tpop ax\n";
				initial_code += "\tjmp integer_breaking_loop\n";
				
				
				initial_code += "non_negative:\n";
				initial_code += "\tcmp bx, 0\n";
				initial_code += "\tje print_zero\n";
				initial_code += "\tjmp integer_breaking_loop\n";
				initial_code += "print_zero:\n";
				initial_code += "\tmov ah, 2\n";
				initial_code += "\tmov dl, 48\n";
				initial_code += "\tint 21h\n";
				
			
	                         initial_code += "\tmov ah, 2\n";
	                         initial_code += "\tmov dl, 10\n";
	                         initial_code += "\tint 21h\n";
	                         initial_code += "\tmov dl, 13\n";
	                         initial_code += "\tint 21h\n";
	                         initial_code += "\tpop dx\n";
	                         initial_code += "\tpop cx\n";
	                         initial_code += "\tpop bx\n";
	                         initial_code += "\tpop ax\n";
	                         
	                         
				initial_code += "\tret\n";
				
						
				initial_code += "integer_breaking_loop:\n";
				initial_code += "\tcmp ax, 0\n";
				initial_code += "\tje end_integer_breaking\n";
				initial_code += "\tmov dx, 0\n";
				initial_code += "\tmov bx, 10\n";
				initial_code += "\tdiv bx\n";
				initial_code += "\tpush dx\n";
				
				initial_code += "\tinc digit_count\n";
				
				initial_code += "\tjmp integer_breaking_loop\n";
				initial_code += "end_integer_breaking:\n";
				
				initial_code += "\tmov backup_cx, cx\n";
				initial_code += "\tmov cx, digit_count\n";
				
	
     
     				initial_code += "\tprint_integer_loop:\n";
				initial_code += "\tpop dx\n";
				
						
				initial_code += "\tadd dx, 48\n";
				initial_code += "\tmov ah, 2\n";
				initial_code += "\tint 21h\n";
				initial_code += "\tloop print_integer_loop\n";
				initial_code += "\tmov cx, backup_cx\n";
				initial_code += "\tmov ax, digit_count\n";
				initial_code += "\txor ax, ax\n";
				
				initial_code += "\tmov digit_count, ax\n";
				
				initial_code += "\tmov ah, 2\n";
				initial_code += "\tmov dl, 10\n";
				
				initial_code += "\tint 21h\n";
				initial_code += "\tmov dl, 13\n";
				initial_code += "\tint 21h\n";
				
				initial_code += "\tpop dx\n";
				initial_code += "\tpop cx\n";
				initial_code += "\tpop bx\n";
				initial_code += "\tpop ax\n";
				initial_code += "\tret\n";
				initial_code += "print endp\n";

				


				f_code << initial_code;
				f_code << $1->at(0)->getCode();
				f_code << "END main\n";
			}	
	}
	;

program : program unit 

         {
                f_log_out << "Line " << line_count <<  ": program : program unit  \n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
			
			for(int i=0;i<$2->size();i++)
			{
			$$->push_back($2->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			  if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if($$->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if($$->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if($$->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if($$->at(i)->getName()=="}")
			  {
				f_log_out << endl<<endl;
			  }
			  
			}
			
			
  			f_log_out << endl << endl;
			//type = "INT";
			
		//assembly code
		$$->at(0)->setCode($$->at(0)->getCode() + $2->at(0)->getCode());
                
                
                }


	| unit //NTD
	{
                f_log_out << "Line " << line_count <<  ": program : unit  \n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			   if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if($$->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if($$->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if($$->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if($$->at(i)->getName()=="}")
			  {
				f_log_out << endl<<endl;
			  }
			  
			}
			
  			f_log_out << endl << endl << endl;;
			//type = "INT";
                
                
                }
	;
	
unit : var_declaration //NTD
 		{
                f_log_out << "Line " << line_count <<  ": unit : var_declaration \n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			  if($1->at(i)->getName() == "int" || $1->at(i)->getName() == "float" || $1->at(i)->getName() == "void")
			  {
				f_log_out << " ";
			  }
			  
			}
			
  			f_log_out << endl << endl << endl;;
			//type = "INT";
                
                
                }


     | func_declaration //NTD
     
     {
                f_log_out << "Line " << line_count <<  ": unit : func_declaration \n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			  if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
				f_log_out << " ";
			  }
			  
			}
			
  			f_log_out << endl << endl << endl;
			//type = "INT";
                
                
                }

     
     | func_definition //NTD
     
     {
                f_log_out << "Line " << line_count <<  ": unit : func_definition  \n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			   if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if($$->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if($$->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if($$->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if($$->at(i)->getName()=="}")
			  {
				f_log_out << endl<<endl;
			  }
			  
			}
			
  			f_log_out << endl << endl ;
			//type = "INT";
                
                
                }
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON //NTD

{ //declared function er name and parameters symbol gulo store kore rakha hocche

             
             function_definition_parameter_list = new vector<SymbolInfo*>();
             
             for(int i=0; i<$4->size();i++)
             {
             
             if($4->at(i)->getName() == "int" ||$4->at(i)->getName() == "float" )
             {
             
             if(i+1 < $4->size() && $4->at(i+1)->getName() != ",")
             {
             function_definition_parameter_list->push_back(new SymbolInfo($4->at(i+1)->getName(),"ID",$4->at(i)->getName(),"var",NULL));
             }
             
             else 
             {
             function_definition_parameter_list->push_back(new SymbolInfo($4->at(i)->getName(),$4->at(i)->getName(),$4->at(i)->getName(),"",NULL));
             
             }
             
             
             }
         
              
              }
           
              
              //inserting id for function in symbol table
              SymbolInfo *temp = st.Look_up($2->getName());
              
              if(temp == NULL) //the id name is not used before
              
              {  st.Insert($2->getName(),$2->getType(),$1->getName(),"func",function_definition_parameter_list,true);
              }
              
              else
              
              { //if the id name is already used before
              
              f_log_out << "Error at line " << line_count << ": Multiple declaration of " << temp->getName() << endl << endl;
			f_error_out << "Error at line " << line_count << ": Multiple declaration of " << temp->getName() << endl << endl;
			total_errors++;
              }
              
             
                
                
                   f_log_out << "Line " << line_count <<  ": func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
			$$->push_back($2);
			$$->push_back($3);
			
			for(int i=0;i<$4->size();i++)
			{
			$$->push_back($4->at(i));
			}
			
			$$->push_back($5);
			$$->push_back($6);
			
			
                 	for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			  if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			 
			  else if($$->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  
			}
			
			
  			f_log_out << endl << endl;
			
                
                
             

}
                 
		| type_specifier ID LPAREN RPAREN SEMICOLON //NTD
		
		{
		//inserting the declared non parameterized function in the gloabal scope of symbol table
		
		   SymbolInfo *temp = st.Look_up($2->getName());
              
              if(temp == NULL) //the id name is not used before
              {
		st.Insert($2->getName(),$2->getType(),$1->getName(),"func",NULL,true);
                }
                
               else  //the id name is already used before
               {
               
                
              f_log_out << "Error at line " << line_count << ": Multiple declaration of " << temp->getName() << endl << endl;
			f_error_out << "Error at line " << line_count << ": Multiple declaration of " << temp->getName() << endl << endl;
			total_errors++;
               }  
               
               
               
                  f_log_out << "Line " << line_count <<  ": func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n";
                 
                $$ = new vector<SymbolInfo*>();
		
		$$->push_back($1);
		$$->push_back($2);
		$$->push_back($3);
		$$->push_back($4);
		$$->push_back($5);
		
		f_log_out << $1->getName() <<" "<< $2->getName() << $3->getName() << $4->getName() << $5->getName()<<endl << endl<< endl;
			
                 
                 
                 
                 }
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN {


		function_definition_parameter_list = new vector<SymbolInfo*>();
             
             for(int i=0; i<$4->size();i++)
             {
             
             if($4->at(i)->getName() == "int" ||$4->at(i)->getName() == "float" )
             {
             
             if(i+1 < $4->size() && $4->at(i+1)->getName() != ",")
             {
             
             function_definition_parameter_list->push_back(new SymbolInfo($4->at(i+1)->getName(),"ID",$4->at(i)->getName(),"var",NULL));
             }
             
             else 
             {
             
             f_log_out<<"Error at line "<<line_count<<": Invalid parameter definition for function "<<$2->getName() << endl << endl;
              f_error_out<<"Error at line "<<line_count<<": Invalid parameter definition for function "<<$2->getName() << endl << endl;
              total_errors++;
             
             }
             
             
             }
         
              
              }
           
              

    
           SymbolInfo *temp=st.Look_up($2->getName());
           
     		if(temp == NULL)//if the function is not declared or defined before
             
            { 
                // f_log_out << $2->getName() << endl << endl ;
                 
            
              //inserting id for function in symbol table
                st.Insert($2->getName(),$2->getType(),$1->getName(),"func",function_definition_parameter_list);
                
                st.Enter_Scope(); //Entering a new scope for this function
                //function_scope_flag = true;
                
                
                //inserting the parameter variable into the scope of this function
                 for(int i=0; i<function_definition_parameter_list->size();i++)
                 {
                 st.Insert(function_definition_parameter_list->at(i)->getName(),"ID",function_definition_parameter_list->at(i)->getDataType(),"var",NULL);
                 
                 
        //assembly code
	string symbol = function_definition_parameter_list->at(i)->getName() + "_" + st.getCurrentScopeTableID();
	//setting assembly symbol in parameter as well as in the symbol table
	function_definition_parameter_list->at(i)->setAssemblySymbol(makeScopeID(symbol));
	
	(st.Look_up(function_definition_parameter_list->at(i)->getName()))->setAssemblySymbol(makeScopeID(symbol));
	
	data_list.push_back({makeScopeID(symbol),"0"});
	
						
                 
                 }
                 
                 

}

     else //if the function is declared before  or function name is used before or variable name used before
     {
     //f_log_out << "Hereeee1" << endl << endl << endl;
     if(temp->isDeclared() == true)  //if the function is declared but not define yet
     
     {
     
     
     
    // f_log_out << "Hereeeee2" << endl << endl << endl;
     
     temp->setDeclared(false);
     
     //parameter gula match kore kina dekhte hobe....na korle error..jodi match kore tahole
    // parameter gulo current scope a enter hobe
  
  //if declared function parameter number is not matched with the defined function parameter number
  
   //checking if the return type of declared function is matched with the defined one
    if(temp->getDataType() != $1->getName())
    {
   
      f_log_out<<"Error at line "<<line_count<<": Return type mismatch with function declaration in function "<<temp->getName() << endl << endl;
       f_error_out<<"Error at line "<<line_count<<": Return type mismatch with function declaration in function "<<temp->getName() << endl << endl;
       total_errors++;
    
    
    }
    
    
    else if(function_definition_parameter_list->size() != temp->getParameters()->size() )
    {
    f_log_out <<"Error at line "<<line_count<<": Total number of arguments mismatch with declaration in function "<<temp->getName() << endl << endl;
    f_error_out <<"Error at line "<<line_count<<": Total number of arguments mismatch with declaration in function "<<temp->getName() << endl << endl;
    total_errors++;
    
    }
    
    //if declared function parameter types is not matched with the defined function parameter types
    else if(function_definition_parameter_list->size() == temp->getParameters()->size())
    {
    
    for(int i=0;i<temp->getParameters()->size();i++)
    {
    	if(function_definition_parameter_list->at(i)->getDataType() != temp->getParameters()->at(i)->getDataType() )
    	{
    	 f_log_out <<"Error at line "<<line_count<<": Types of arguments mismatch with declaration in function "<<temp->getName() << endl << endl;
    	 f_error_out <<"Error at line "<<line_count<<": Types of arguments mismatch with declaration in function "<<temp->getName() << endl << endl;
    	 total_errors++;
    	 break;
    	
    	}
    	
    	
    }
    
    
    
    }
    
    
   
    
    
    st.Enter_Scope(); //Entering a new scope for this function
   // f_log_out <<"Yes"<<endl;
     //function_scope_flag = true;
                
            
                //inserting the parameter variable into the scope of this function
           
                
                  for(int i=0; i<temp->getParameters()->size();i++)
                 {
                 st.Insert(temp->getParameters()->at(i)->getName(),"ID",temp->getParameters()->at(i)->getDataType(),"var",NULL);
     
     }
     
     
     
     
     }
     
     
     else // function name is used before or variable name used before
     {
    // f_log_out << "Hereeeee3" << endl << endl << endl;
     
                     f_log_out << "Error at line " << line_count << ": Multiple declaration of " << temp->getName() << endl << endl;
			f_error_out << "Error at line " << line_count << ": Multiple declaration of " << temp->getName() << endl << endl;
			total_errors++;
			
			
			 st.Enter_Scope(); //Entering a new scope for this function
   // f_log_out <<"Yes"<<endl;
     //function_scope_flag = true;
                
              
                //inserting the parameter variable into the scope of this function
                
                  for(int i=0; i<function_definition_parameter_list->size();i++)
                 {
                 st.Insert(function_definition_parameter_list->at(i)->getName(),"ID",function_definition_parameter_list->at(i)->getDataType(),"var",NULL);
                 
                 }
                
                 
     
     }



  }
}


compound_statement{




}

 {
                f_log_out << "Line " << line_count <<  ": func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
			$$->push_back($2);
			$$->push_back($3);
			
			for(int i=0;i<$4->size();i++)
			{
			$$->push_back($4->at(i));
			}
			
			$$->push_back($5);
			
			for(int i=0;i<$7->size();i++)
			{
			$$->push_back($7->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			  if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if($$->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if($$->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if($$->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if($$->at(i)->getName()=="}")
			  {
				f_log_out << endl;
			  }
			  
			}
			
			
  			f_log_out << endl << endl;
  			
  			
  			//assembly code
			string segment_code = "";
			segment_code += $2->getName() + " PROC\n";
			if($2->getName() == "main")
				segment_code += "\tmov ax, @data\n\tmov ds, ax\n";
			else 
				segment_code += "\tpush ax\n\tpush bx\n\tpush cx\n\tpush dx\n";

			segment_code += $7->at(0)->getCode();
			if($2->getName() != "main")
				segment_code += "\tpop dx\n\tpop cx\n\tpop bx\n\tpop ax\n\tret\n";

			segment_code += $2->getName() + " ENDP\n";
			
			$$->at(0)->setCode($$->at(0)->getCode() + segment_code);
		
                
                
                }

		| type_specifier ID LPAREN RPAREN {
		
		
		 SymbolInfo *temp=st.Look_up($2->getName());
		
		if(temp == NULL) //if the function is not declared before
		
		{
		 
              //inserting id for function in symbol table
                st.Insert($2->getName(),$2->getType(),$1->getName(),"func",NULL);
                
                st.Enter_Scope(); //Entering a new scope for this function
                //function_scope_flag = true;
		}
		
		else  //if the function is declared before  or function name is used before or variable name used before
		
		{
		
		 if(temp->isDeclared() == true)  //if the function is declared but not define yet
     
    		 {
     
     		temp->setDeclared(false);
     		
     			//checking if the return type of declared function is matched with the defined one
          if(temp->getDataType() != $1->getName())
    {
      f_log_out<<"Error at line "<<line_count<<": Return type mismatch with function declaration in function "<<temp->getName() << endl << endl;
       f_error_out<<"Error at line "<<line_count<<": Return type mismatch with function declaration in function "<<temp->getName() << endl << endl;
       total_errors++;
    
    
    }
		
     
		
		st.Enter_Scope(); //Entering a new scope for this function
		//function_scope_flag = true;
		
		}
		
	
		else
		
		{
		  f_log_out << "Error at line " << line_count << ": Multiple declaration of " << temp->getName() << endl << endl;
			f_error_out << "Error at line " << line_count << ": Multiple declaration of " << temp->getName() << endl << endl;
			total_errors++;
		
		}
		
		
      }
		
		
		
}
		
		
		
		compound_statement
		
		{
		
		
		}
		
		
	{
		
		
		 f_log_out << "Line " << line_count <<  ": func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
			$$->push_back($2);
			$$->push_back($3);
			$$->push_back($4);
			
			for(int i=0;i<$6->size();i++)
			{
			$$->push_back($6->at(i));
			}
			
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			  if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if($$->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if($$->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if($$->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if($$->at(i)->getName()=="}")
			  {
				f_log_out << endl;
			  }
			  
			}
			
			
  			f_log_out << endl << endl;
  			
  			//assembly code
			string segment_code = "";
			segment_code += $2->getName() + " PROC\n";
			if($2->getName() == "main")
				segment_code += "\tmov ax, @data\n\tmov ds, ax\n";
			else 
				segment_code += "\tpush ax\n\tpush bx\n\tpush cx\n\tpush dx\n";

			segment_code += $6->at(0)->getCode();
			if($2->getName() != "main")
				segment_code += "\tpop dx\n\tpop cx\n\tpop bx\n\tpop ax\n\tret\n";
			else
			{
			segment_code+="\tmov ah,4ch\n\tint 21h\n"; 
			
			}

			segment_code += $2->getName() + " ENDP\n";
			
			$$->at(0)->setCode($$->at(0)->getCode() + segment_code);
		
		
		
		
		}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID //NTD
                {
                //int a,int b,int c......
                
                //checking if any parameter is declared multiple times or not
                
                for(int i=0;i<$1->size();i++)
                {
                
                if($1->at(i)->getName() == $4->getName())
                {
                f_log_out <<"Error at line "<<line_count<<": Multiple declaration of "<<$4->getName()<<" in parameter" << endl << endl;
                f_error_out <<"Error at line "<<line_count<<": Multiple declaration of "<<$4->getName()<<" in parameter" << endl << endl;
                 total_errors++;
                 break;
                
                }
                
                }
                
                
                
                f_log_out << "Line " << line_count <<  ": parameter_list : parameter_list COMMA type_specifier ID\n\n";
                 
                $$ = new vector<SymbolInfo*>();
                
  		for(int i=0;i<$1->size();i++)
	        {
		$$->push_back($1->at(i));
		}
                           		   
		$$->push_back($2);
		$$->push_back($3);
		$$->push_back($4);
		
		
		
		for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			  if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
				f_log_out << " ";
			  }
			  
			}
			
  			f_log_out << endl << endl;
  			
  			
		
 		
 		}
		
               
		| parameter_list COMMA type_specifier //NTD
		{
                //int a,int b,int......
                
           
                     f_log_out << "Line " << line_count <<  ": parameter_list : parameter_list COMMA type_specifier\n\n";
                 
                $$ = new vector<SymbolInfo*>();
                
  		for(int i=0;i<$1->size();i++)
	        {
		$$->push_back($1->at(i));
		}
                           		   
		$$->push_back($2);
		$$->push_back($3);
		
		
		
		
		for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			  if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
				f_log_out << " ";
			  }
			  
			}
			
  			f_log_out << endl << endl;
  			
  			
		
 		
 		}
		
		
		
 		| type_specifier ID //NTD
 		
 		{
 		
 		
 		 f_log_out << "Line " << line_count <<  ": parameter_list : type_specifier ID\n\n";
                 
                $$ = new vector<SymbolInfo*>();
		
		$$->push_back($1);
		$$->push_back($2);
		
		//f_log_out << "Here1" << endl;
		f_log_out << $1->getName() <<" "<< $2->getName() << endl << endl;
		
 		//f_log_out << "Here" << endl;
 		}
 		
		| type_specifier //NTD
		
		
 		{
 		
 		
 		 f_log_out << "Line " << line_count <<  ": parameter_list : type_specifier\n\n";
                 
                $$ = new vector<SymbolInfo*>();
		
		$$->push_back($1);
		
		//f_log_out << "Here1" << endl;
		f_log_out << $1->getName()<< endl << endl;
		
 		//f_log_out << "Here" << endl;
 		}
		
		
 		;

 		
compound_statement : LCURL statements RCURL

                   {
                f_log_out << "Line " << line_count <<  ": compound_statement : LCURL statements RCURL\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
			
			for(int i=0;i<$2->size();i++)
			{
			$$->push_back($2->at(i));
			}
			
			$$->push_back($3);
                
               
			
			
			 
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			 if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if($$->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if($$->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if($$->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if($$->at(i)->getName()=="}")
			  {
				f_log_out << endl;
			  }
			  
			  
			  
			}
			
			 
			 
			
  			f_log_out << endl << endl<<endl<<endl;
  			
  			
  		//exiting from current scope	
    	        st.Print_All_Scope_Table(f_log_out);
    	        st.Exit_Scope();
			//type = "INT";
			
		//assembly code
		$$->at(0)->setCode($$->at(0)->getCode() + $2->at(0)->getCode());
                
                
                }
 		    | LCURL RCURL //NTD
 		    
 		    {
                f_log_out << "Line " << line_count <<  ": compound_statement : LCURL RCURL\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
			
			$$->push_back($2);
                
               
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
			 
			f_log_out << endl << endl<<endl;
  			
  			
  		//exiting from current scope	
    	        st.Print_All_Scope_Table(f_log_out);
    	        st.Exit_Scope();
			//type = "INT";
                
                
                }
 		    
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON //NTD
                 {
                f_log_out << "Line " << line_count <<  ": var_declaration : type_specifier declaration_list SEMICOLON\n\n";
                
                if($1->getName()=="void")
                {
               
                f_log_out <<"Error at line "<<line_count<<": Variable type cannot be void" <<endl << endl;
                  f_error_out <<"Error at line "<<line_count<<": Variable type cannot be void" <<endl << endl;
                  total_errors++;
                
                
                }
                
                
                
                        $$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
			for(int i=0;i<$2->size();i++)
			{
			$$->push_back($2->at(i));
			}
			
			
			$$->push_back($3);
                
                
		
			f_log_out << $1->getName() << " ";
			
			for(int i=0;i<$2->size();i++)
			{
			  f_log_out << $2->at(i)->getName() ;
			}
			
			f_log_out << $3->getName() << " ";
			
  			f_log_out << endl << endl;
			
                
                
                }

 		 ;
 		 
type_specifier	: INT //NTD
                { //cout << "returned INT" << endl;
                
                f_log_out << "Line " << line_count <<  ": type_specifier : INT\n\n";
			f_log_out << $1->getName() << endl << endl;
			$$ = $1;
			type = "int";
                
                
                }
 		| FLOAT //NTD
 		
 		{
                f_log_out << "Line " << line_count <<  ": type_specifier : FLOAT\n\n";
			f_log_out << $1->getName()  << endl << endl;
			$$ = $1;
			type = "float";
                
                
                }
 		
 		| VOID //NTD
 		
 		{
 		
                f_log_out << "Line " << line_count <<  ": type_specifier : VOID\n\n";
			f_log_out << $1->getName()  << endl << endl;
			$$ = $1;
		    type = "void";
                
                
                }
 		
 		
 		
 		;
 		
declaration_list : declaration_list COMMA ID
                   {
                   
                   //inserting ID to symbol table
                 //variable insert korar shomoy current scope a look up korte hobe
 		SymbolInfo *temp = st.get_current_scope_table()->Look_up($3->getName());
                   
 		 if(temp != NULL)
 		 {
 		   
                     f_log_out << "Error at line " << line_count << ": Multiple declaration of " << $3->getName() << endl << endl;
			f_error_out << "Error at line " << line_count << ": Multiple declaration of " << $3->getName() << endl << endl;
			total_errors++;
                     
                     
 		 }
 		 
 		 else if(type == "int" || type == "float") //if the declared type is INT or FLOAT then add into symbol table
 		 {
 		 
 		 st.Insert($3->getName(),$3->getType(),type,"var",NULL);
 		 
 		 }
 		 
                   //cout << "declaration_list COMMA ID matched" << endl;
                     f_log_out << "Line " << line_count <<  ": declaration_list : declaration_list COMMA ID\n\n";
			
			$$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
			
			$$->push_back($2);
			$$->push_back($3);
			
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			}
			
  			f_log_out << endl << endl;
			
			//type = "INT";
			
			
			//assembly code
			string symbol = $3->getName() + "_" + st.getCurrentScopeTableID();
			//converting a_1.1 to a_1_1
			st.Look_up($3->getName())->setAssemblySymbol(makeScopeID(symbol));
			data_list.push_back({makeScopeID(symbol),"0"});
                
                
                  }



 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
 		  
 		  {
 		  
 		  //variable insert korar shomoy current scope a look up korte hobe
 		SymbolInfo *temp = st.get_current_scope_table()->Look_up($3->getName());
                   
 		 if(temp != NULL)
 		 {
 		   
                     f_log_out << "Error at line " << line_count << ": Multiple declaration of " << $3->getName() << endl << endl;
			f_error_out << "Error at line " << line_count << ": Multiple declaration of " << $3->getName() << endl << endl;
			total_errors++;
                     
                     
 		 }
 		 
 		 else if(type == "int" || type == "float") //if the declared type is INT or FLOAT then add into symbol table
 		 {
 		 
 		 st.Insert($3->getName(),$3->getType(),type,"array",NULL);
 		 
 		 }
 		  
 		   f_log_out << "Line " << line_count <<  ": declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n";
 		   
 		   
 		  //inserting ID to symbol table
 		  
 		  //this condition checks if the id is already inserted into symbol table or not
 		 
			
			$$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
			
			$$->push_back($2);
			$$->push_back($3);
			$$->push_back($4);
			$$->push_back($5);
			$$->push_back($6);
			
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			}
			
  			f_log_out << endl << endl;
			
 		 
 		 
			//assembly code
			string symbol = $3->getName() + "_" + st.getCurrentScopeTableID();
			//converting a_1.1 to a_1_1
			st.Look_up($3->getName())->setAssemblySymbol(makeScopeID(symbol));
			data_list.push_back({makeScopeID(symbol),$5->getName()});
 		 
 		 
 		  
 		  
 		  
 		  
 		  
 		  
 		  }
 		  | ID
 		  {
 		  
 		 // cout << "declaration_list: ID matched" << endl;
 		 
 		  //inserting ID to symbol table
 		  
 		 // st.Print_All_Scope_Table(f_log_out);

             //variable insert korar shomoy current scope a look up korte hobe
 		SymbolInfo *temp = st.get_current_scope_table()->Look_up($1->getName());
                   
 		 if(temp != NULL)
 		 {
 		   
                     f_log_out << "Error at line " << line_count << ": Multiple declaration of " << $1->getName() << endl << endl;
			f_error_out << "Error at line " << line_count << ": Multiple declaration of " << $1->getName() << endl << endl;
			total_errors++;
                     
                     
 		 }
 		 
 		 else if(type == "int" || type == "float") //if the declared type is INT or FLOAT then add into symbol table
 		 {
 		 
 		 st.Insert($1->getName(),$1->getType(),type,"var",NULL);
 		 
 		 }
 		  
 		 
 		  
                     f_log_out << "Line " << line_count <<  ": declaration_list : ID\n\n";
		     f_log_out << $1->getName()  << "\n\n";
		     
		     $$ = new vector<SymbolInfo*>();
		     $$->push_back($1);
			//type = "INT";
			
			
			//assembly code
			string symbol = $1->getName() + "_" + st.getCurrentScopeTableID();
			//converting a_1.1 to a_1_1
			st.Look_up($1->getName())->setAssemblySymbol(makeScopeID(symbol));
			//for "var" type id
			data_list.push_back({makeScopeID(symbol),"0"});
                
                
                  }
 		
 		  
 		  | ID LTHIRD CONST_INT RTHIRD
 		  
 		  {
 		  //inserting an array id to symbol table
 		  
 		  
 		 //variable insert korar shomoy current scope a look up korte hobe
 		SymbolInfo *temp = st.get_current_scope_table()->Look_up($1->getName());
                   
 		 if(temp != NULL)
 		 {
 		   
                     f_log_out << "Error at line " << line_count << ": Multiple declaration of " << $1->getName() << endl << endl;
			f_error_out << "Error at line " << line_count << ": Multiple declaration of " << $1->getName() << endl << endl;
			total_errors++;
                     
                     
 		 }
 		 
 		 else if(type == "int" || type == "float") //if the declared type is INT or FLOAT then add into symbol table
 		 {
 		 
 		 st.Insert($1->getName(),$1->getType(),type,"array",NULL);
 		 
 		 }
 		 
 		 f_log_out << "Line " << line_count <<  ": declaration_list : ID LTHIRD CONST_INT RTHIRD\n\n";
 		 
			
			$$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
			$$->push_back($2);
			$$->push_back($3);
			$$->push_back($4);
			
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			}
			
  			f_log_out << endl << endl;
			
			//type = "INT";
			
			//assembly code
			string symbol = $1->getName() + "_" + st.getCurrentScopeTableID();
			//converting a_1.1 to a_1_1
			st.Look_up($1->getName())->setAssemblySymbol(makeScopeID(symbol));
			data_list.push_back({makeScopeID(symbol),$3->getName()});
                
 		   
 		   
 		  }
 		  ;
 		  
statements : statement //NTD

            {
                f_log_out << "Line " << line_count <<  ": statements : statement\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			 if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if($$->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if($$->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if($$->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if($$->at(i)->getName()=="}")
			  {
				f_log_out << endl<<endl;
			  }
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                }
	
	   | statements statement
	   
	   {
                f_log_out << "Line " << line_count <<  ": statements : statements statement  \n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
			
			for(int i=0;i<$2->size();i++)
			{
			$$->push_back($2->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			   if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if($$->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if($$->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if($$->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if($$->at(i)->getName()=="}")
			  {
				f_log_out << endl;
			  }
			  
			}
			
  			f_log_out << endl ;
  			
  			
  		//assembly code
		$$->at(0)->setCode($$->at(0)->getCode() + $2->at(0)->getCode());
		
                
                
                }
	  
	   ;
	   
statement : var_declaration //NTD

{
  f_log_out << "Line " << line_count <<  ": statement : var_declaration\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			  if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
				f_log_out << " ";
			  }
			  else if($$->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if($$->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if($$->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if($$->at(i)->getName()=="}")
			  {
				f_log_out << endl<<endl;
			  }
			  
			}
			
  			f_log_out << endl << endl;

}
	  | expression_statement //NTD
	 {
                f_log_out << "Line " << line_count <<  ": statement : expression_statement  \n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			  if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
				f_log_out << " ";
			  }
			  
			}
			
  			f_log_out << endl << endl << endl;
			
                
                
                }
	  
	  |  {st.Enter_Scope();} compound_statement { /* st.Exit_Scope();*/} //NTD
	  {
	  
	   f_log_out << "Line " << line_count <<  ": statement : compound_statement  \n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$2->size();i++)
			{
			$$->push_back($2->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			  if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if($$->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if($$->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if($$->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if($$->at(i)->getName()=="}")
			  {
				f_log_out << endl<<endl;
			  }
			  
			}
			
  			f_log_out << endl;
			
	  
	  }
	  
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement
	  
	  {
                f_log_out << "Line " << line_count <<  ": statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
			$$->push_back($2);
			
			for(int i=0;i<$3->size();i++)
			{
			$$->push_back($3->at(i));
			}
			
		
			for(int i=0;i<$4->size();i++)
			{
			$$->push_back($4->at(i));
			}
			
			for(int i=0;i<$5->size();i++)
			{
			$$->push_back($5->at(i));
			}
			
			$$->push_back($6);
			
			for(int i=0;i<$7->size();i++)
			{
			$$->push_back($7->at(i));
			}
			
			
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			   if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if($$->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if($$->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if($$->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if($$->at(i)->getName()=="}")
			  {
				f_log_out << endl;
			  }
			  
			}
			
  			f_log_out << endl;
  			
  			
  			
  		//assembly code
		string label1 = newLabel();
		string label2 = newLabel();
		
		string segment_code = "";
		segment_code += $3->at(0)->getCode();
		segment_code += label1 + ":\n";
		segment_code += $4->at(0)->getCode();
		segment_code += "\tmov ax, " + $4->at(0)->getAssemblySymbol() + "\n";
		segment_code += "\tcmp ax, 0\n";
		segment_code += "\tje " + label2 + "\n";
		segment_code += $7->at(0)->getCode();
		segment_code += $5->at(0)->getCode();
		segment_code += "\tjmp " + label1 + "\n";
		segment_code += label2 + ":\n";

		$$->at(0)->setCode(segment_code);
  			
  		

                
                
                }
	  | IF LPAREN expression RPAREN statement %prec WITHOUT_ELSE
	  {
                f_log_out << "Line " << line_count <<  ": statement : IF LPAREN expression RPAREN statement\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
			$$->push_back($2);
			
			for(int i=0;i<$3->size();i++)
			{
			$$->push_back($3->at(i));
			}
			
			$$->push_back($4);
			
			for(int i=0;i<$5->size();i++)
			{
			$$->push_back($5->at(i));
			}
			
			
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			   if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if($$->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if($$->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if($$->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if($$->at(i)->getName()=="}")
			  {
				f_log_out << endl<<endl;
			  }
			  
			}
			
  			f_log_out << endl;
  			
  		//assembly code
		string label = newLabel();
		string segment_code = "";
		segment_code += "\tmov ax, " + $3->at(0)->getAssemblySymbol() + "\n";
		segment_code += "\tcmp ax, 0\n";
		segment_code += "\tje " + label + "\n";
		segment_code += $5->at(0)->getCode();
		segment_code += label + ":\n";

		$$->at(0)->setCode($$->at(0)->getCode() +$3->at(0)->getCode() + segment_code);

                
                
                }
	  
	  | IF LPAREN expression RPAREN statement ELSE statement
	  
	  {
                f_log_out << "Line " << line_count <<  ": statement : IF LPAREN expression RPAREN statement ELSE statement\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
			$$->push_back($2);
			
			for(int i=0;i<$3->size();i++)
			{
			$$->push_back($3->at(i));
			}
			
			$$->push_back($4);
			
			for(int i=0;i<$5->size();i++)
			{
			$$->push_back($5->at(i));
			}
			
			$$->push_back($6);
			
			for(int i=0;i<$7->size();i++)
			{
			$$->push_back($7->at(i));
			}
			
			
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			   if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if($$->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if($$->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if($$->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if($$->at(i)->getName()=="}")
			  {
				f_log_out << endl;
			  }
			  
			}
			
  			f_log_out << endl;
  			
  		//assembly code
		string label1 = newLabel();
		string label2 = newLabel();
		string segment_code = "";

		segment_code += "\tmov ax, " + $3->at(0)->getAssemblySymbol() + "\n";
		segment_code += "\tcmp ax, 0\n";
		segment_code += "\tje " + label1 + "\n";
		segment_code += $5->at(0)->getCode();
		segment_code += "\tjmp " + label2 + "\n";
		segment_code += label1 + ":\n";
		segment_code += $7->at(0)->getCode();
		segment_code += label2 + ":\n";

		$$->at(0)->setCode($$->at(0)->getCode()+$3->at(0)->getCode()+ segment_code);
  			
  			
	  }
	  | WHILE LPAREN expression RPAREN statement
	  {

                f_log_out << "Line " << line_count <<  ": statement : WHILE LPAREN expression RPAREN statement\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
			$$->push_back($2);
			
			for(int i=0;i<$3->size();i++)
			{
			$$->push_back($3->at(i));
			}
			
			$$->push_back($4);
			
			for(int i=0;i<$5->size();i++)
			{
			$$->push_back($5->at(i));
			}
			
			
           
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			   if($$->at(i)->getName() == "int" || $$->at(i)->getName() == "float" || $$->at(i)->getName() == "void")
			  {
			        f_log_out << " ";
			  }
			  else if($$->at(i)->getName()=="return")
			  {
				f_log_out << " ";
			  }
			  else if($$->at(i)->getName()==";")
			  {
				f_log_out << endl;
			  }
			  else if($$->at(i)->getName()=="{")
			  {
				f_log_out << endl;
			  }
			   else if($$->at(i)->getName()=="}")
			  {
				f_log_out << endl;
			  }
			  
			}
			
  			f_log_out << endl;
  			
  			
  			
  			//assembly code
  		
  		//1st a "expression" evaluate hobe
  		//then "expression" 1 naki 0 sheta check hobe
  		//"expression" 1 hole loop er moddhe "statement" execute hote thakbe
  		//"expressio" 0 hole loop theke ber hoye jabe
  		
		string label1 = newLabel();
		string label2 = newLabel();
		
		string segment_code = "";
		segment_code += label1 + ":\n";
		segment_code += $3->at(0)->getCode();
		segment_code += "\tmov ax, " + $3->at(0)->getAssemblySymbol() + "\n";
		segment_code += "\tcmp ax, 0\n";
		segment_code += "\tje " + label2 + "\n";
		segment_code += $5->at(0)->getCode();
		segment_code += "\tjmp " + label1 + "\n";
		segment_code += label2 + ":\n";

		$$->at(0)->setCode(segment_code);

                
                
                }
	  
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
	  
	  {

                f_log_out << "Line " << line_count <<  ": statment : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n";
                
                if(st.Look_up($3->getName()) == NULL) //if variable was not declared
                     
                     {  
			f_log_out << "Error at line " << line_count << ": Undeclared variable " << $3->getName() << "\n\n";
			f_error_out << "Error at line " << line_count << ": Undeclared variable " << $3->getName() << "\n\n";
			total_errors++;
		   }
		   
                
                
                
                        $$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
			$$->push_back($2);
			$$->push_back($3);
			$$->push_back($4);
			$$->push_back($5);
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl<<endl;
  			
  			
  		//assembly code
		string segment_code = "";
		segment_code += "\tmov ax, " + (st.Look_up($3->getName()))->getAssemblySymbol() + "\n";
		segment_code += "\tmov print_var, ax\n";
		segment_code +=	"\tcall print\n";

		$$->at(0)->setCode($$->at(0)->getCode() + segment_code);
    
                }
	  
	  
	  
	  | RETURN expression SEMICOLON
	  
	  {
                f_log_out << "Line " << line_count <<  ": statement : RETURN expression SEMICOLON\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
			for(int i=0;i<$2->size();i++)
			{
			$$->push_back($2->at(i));
			}
			
			$$->push_back($3);
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			
			f_log_out << $$->at(i)->getName() ;
			
			if($$->at(i)->getName()=="return")
			{
			f_log_out << " ";
			}
			  
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
			
			
		//assembly code
		string segment_code = "";
		segment_code += $2->at(0)->getCode();
		segment_code += "\tmov ax, " + $2->at(0)->getAssemblySymbol() + "\n";
		segment_code += "\tmov ret_temp, ax\n";

		$$->at(0)->setCode($$->at(0)->getCode() + segment_code);
                
                
                }
	  ;
	  
expression_statement 	: SEMICOLON //NTD


			 {
                f_log_out << "Line " << line_count <<  ": expression_statement : SEMICOLON\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
                
           		for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
			
			}

			
			| expression SEMICOLON 
			
			
			
			 {
                f_log_out << "Line " << line_count <<  ": expression_statement : expression SEMICOLON\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
			
			$$->push_back($2);
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
			
			//assembly code (Ai line na likhleo hoto)
			$$->at(0)->setCode($1->at(0)->getCode());
                
			
			}
			;
	  
variable : ID //this rule will match when a varible(not array) is used somewhere (declared or undeclared)
          {
           f_log_out << "Line " << line_count <<  ": variable : ID"<<endl<<endl;
 		 
 		 SymbolInfo *temp=st.Look_up($1->getName());
                    
                      //f_log_out << "Hereeeeeeeeeeeeeeeeeeeeee" << endl;
                     if(temp == NULL) //if variable was not declared
                     
                     {  
			f_log_out << "Error at line " << line_count << ": Undeclared variable " << $1->getName() << "\n\n";
			f_error_out << "Error at line " << line_count << ": Undeclared variable " << $1->getName() << "\n\n";
			total_errors++;
		   }
		   
		   else if(temp ->getIdType() == "array") //if array variable is used like normal variable
                     
                     {  
			f_log_out << "Error at line " << line_count << ": Type mismatch, " << $1->getName() << " is an array\n\n";
			f_error_out << "Error at line " << line_count << ": Type mismatch, " << $1->getName() << " is an array\n\n";
			total_errors++;
		   }
		   
		   if(temp != NULL)
		   {
		   
		   	$1->setDataType(temp->getDataType());
		   	$1->setIdType(temp->getIdType());
		   	//f_log_out << $1->getDataType() << endl;
		   	
		   }
		   
		   
		  
		     
		     
		     $$ = new vector<SymbolInfo*>();
		     $$->push_back($1);
			//type = "INT";
			
		   for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			}
			
  			f_log_out << endl << endl;
  			
  			
  		//assembly code
		$$->at(0)->setAssemblySymbol((st.Look_up($1->getName()))->getAssemblySymbol());
		
		$$->at(0)->setCode("");
                
                  }
		
	 | ID LTHIRD expression RTHIRD //this rule will match an array variable is used somewhere (declared or undeclared)
	 
	    {
 		
                     f_log_out << "Line " << line_count <<  ": variable : ID LTHIRD expression RTHIRD\n\n";
                     
                     SymbolInfo *temp=st.Look_up($1->getName());
                    
                      //f_log_out << "Hereeeeeeeeeeeeeeeeeeeeee" << endl;
                     if(temp == NULL) //if variable was not declared
                     
                     {  
			f_log_out << "Error at line " << line_count << ": Undeclared variable " << $1->getName() << "\n\n";
			f_error_out << "Error at line " << line_count << ": Undeclared variable " << $1->getName() << "\n\n";
			total_errors++;
		   }
		   
		   else if(temp ->getIdType() == "var") //if normal variable is used like array variable
                     
                     {  
			f_log_out << "Error at line " << line_count << ": " << $1->getName() << " not an array\n\n";
			f_error_out << "Error at line " << line_count << ": " << $1->getName() << " not an array\n\n";
			total_errors++;
		   }
		   
		   
		   if(temp != NULL)
		   {
		   
		   	$1->setDataType(temp->getDataType());
		   	$1->setIdType(temp->getIdType());
		   	
		   }
                     
                     if($3->at(0)->getType() == "CONST_FLOAT") //if array index is not integer
                     {
                     f_log_out << "Error at line " << line_count << ": Expression inside third brackets not an integer\n\n";
			f_error_out << "Error at line " << line_count << ": Expression inside third brackets not an integer\n\n";
			total_errors++;
                     
                     }

		     
		     
		     $$ = new vector<SymbolInfo*>();
		     $$->push_back($1);
		     $$->push_back($2);
			//type = "INT";
			
	           for(int i=0;i<$3->size();i++)
	           {
	           
	           $$->push_back($3->at(i));
	           
	           }	
	           
	            $$->push_back($4);
			
		   for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			}
			
  			f_log_out << endl << endl;
  			
  			
  		//assembly code
		$$->at(0)->setAssemblySymbol((st.Look_up($1->getName()))->getAssemblySymbol());

		string segment_code = "";
		segment_code += "\tmov di, " + $3->at(0)->getAssemblySymbol() + "\n";
		segment_code += "\tadd di, di\n";
		$$->at(0)->setCode(segment_code);
                
    }
	 
	 
	 ;
	 
 expression : logic_expression	//NTD
 
                 {
                f_log_out << "Line " << line_count <<  ": expression : logic_expression\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                }
	
	   | variable ASSIGNOP logic_expression 
	   
	   {
	    f_log_out << "Line " << line_count <<  ": expression : variable ASSIGNOP logic_expression \n\n";
	    
	    //Handling the type mismatch error
	    SymbolInfo *temp = st.Look_up($1->at(0)->getName());
	    
	   
	   //ASSIGNOP er right a jodi kono "void" function thake
	   
	   for(int i=0;i<$3->size();i++)
	   {
	   if($3->at(i)->getIdType() == "func" && $3->at(i)->getDataType() == "void" )
	   {
	    f_log_out <<"Error at line "<<line_count <<": Void function used in expression" << endl<< endl;
	     f_error_out <<"Error at line "<<line_count <<": Void function used in expression" << endl<< endl;
	     total_errors++;
	     break;
	   
	   }
	   
	   }
	   
	   //ASSIGNOP er Left variable INT but right variable er kono akti float tahole type mismatch
	   
	   if($1->at(0)->getDataType() == "int" )
	   {
	    for(int i=0;i<$3->size();i++)
	    {
	      if($3->at(i)->getIdType()=="var" && $3->at(i)->getDataType()=="float" )
	      {
	      {
	    //cout << temp->getName()<<"  "<< $3->at($3->size()-1)->getName()<< endl;
	    
	     f_log_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	     f_error_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	    total_errors++;
	    }
	    break;
	      
	      }
	      
	      else if($3->at(i)->getIdType()=="cons" &&  $3->at(i)->getDataType()=="float" )
	      {
	      
	      f_log_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	     f_error_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	    total_errors++;
	    break;
	      
	      }
	      
	       else if($3->at(i)->getIdType()=="array" && $3->at(i)->getDataType()=="float" )
	      {
	      
	      f_log_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	     f_error_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	    total_errors++;
	    break;
	      
	      }
	      
	      else if($3->at(i)->getIdType()=="func" && $3->at(i)->getDataType()=="float")
	      {
	       f_log_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	     f_error_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	    total_errors++;
	    break;
	      
	      }
	      
	      else if($3->at(i)->getIdType()=="array" && $3->at(i)->getDataType()=="float")
	      {
	      
	       f_log_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	     f_error_out << "Error at line "<<line_count<<": Type Mismatch" << endl << endl;
	    total_errors++;
	   
	    break;
	      
	      }
	      
	      else if($3->at(i)->getIdType()=="array" )
	      {
	       if(i+3 < $3->size())
	      {
	      i=i+3;
	      }
	      
	      
	      }
	      
	      else if($3->at(i)->getIdType() == "func") //if return type of function "INT"
	      {
	      
	      while(i<$3->size() && $3->at(i)->getName()!=")")
	      {
	      
	      i++; //ignoring all the function arguments;
	      }
	      
	      }
	      
	    
	    
	    }
	    
	    
	   }
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
			
			$$->push_back($2);
			
			for(int i=0;i<$3->size();i++)
			{
			$$->push_back($3->at(i));
			}
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
  			
  			
  			
  			//assembly code
			string ID_type = (st.Look_up($1->at(0)->getName()))->getIdType();
			string segment_code = "";
			string tempp;
			
			if($3->size() == 4){
				tempp = newTemp();
				segment_code += $3->at(0)->getCode();
				segment_code += "\tmov ax, " + $3->at(0)->getAssemblySymbol() + "[di]\n";
				segment_code += "\tmov " + tempp + ", ax\n";
				segment_code += $1->at(0)->getCode();
				if(ID_type != "array")
					segment_code += "\tmov " + $1->at(0)->getAssemblySymbol() + ", ax\n";
				else{
					segment_code += "\tmov ax, " + tempp + "\n"; 
					segment_code += "\tmov " + $1->at(0)->getAssemblySymbol() + "[di], ax\n";
				}
			}

			else{
				segment_code += $3->at(0)->getCode();
				segment_code += $1->at(0)->getCode();
				segment_code += "\tmov ax, " + $3->at(0)->getAssemblySymbol() + "\n";
				
				if(ID_type != "array")
					segment_code += "\tmov " + $1->at(0)->getAssemblySymbol() + ", ax\n";
				else
					segment_code += "\tmov " + $1->at(0)->getAssemblySymbol() + "[di], ax\n";
				
			}
			$$->at(0)->setCode(segment_code);
	   
	   
	   
	   }	
	   ;
			
logic_expression : rel_expression //NTD
                   {
                f_log_out << "Line " << line_count <<  ": logic_expression : rel_expression\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                }
	
		 | rel_expression LOGICOP rel_expression
		 
		 {
		 
                f_log_out << "Line " << line_count <<  ": rel_expression : rel_expression LOGICOP rel_expression\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
			$$->push_back($2);
			
			for(int i=0;i<$3->size();i++)
			{
			$$->push_back($3->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                	//assembly code
			string label1 = newLabel();
			string label2 = newLabel();
			string temp = newTemp();

			string segment_code = "";
			if($2->getName() == "&&"){
				segment_code += "\tcmp " + $1->at(0)->getAssemblySymbol() + ", 0\n";
				segment_code += "\tje " + label1 + "\n";
				segment_code += "\tcmp " +  $3->at(0)->getAssemblySymbol() + ", 0\n";
				segment_code += "\tje " + label1 + "\n";
				segment_code += "\tmov " + temp + ", 1\n";
				segment_code += "\tjmp " + label2 + "\n";
				segment_code += label1 + ":\n";
				segment_code += "\tmov " + temp + ", 0\n";
				segment_code += label2 + ":\n";
			}
			else if($2->getName() == "||"){
				segment_code += "\tcmp " + $1->at(0)->getAssemblySymbol() + ", 0\n";
				segment_code += "\tjne " + label1 + "\n";
				segment_code += "\tcmp " +  $3->at(0)->getAssemblySymbol() + ", 0\n";
				segment_code += "\tjne " + label1 + "\n";
				segment_code += "\tmov " + temp + ", 0\n";
				segment_code += "\tjmp " + label2 + "\n";
				segment_code += label1 + ":\n";
				segment_code += "\tmov " + temp + ", 1\n";
				segment_code += label2 + ":\n";
			}
			$$->at(0)->setCode($$->at(0)->getCode() + segment_code);
			$$->at(0)->setAssemblySymbol(temp);
                
                
		
		
		}	 	
		 ;
			
rel_expression	: simple_expression  //NTD

             {
                f_log_out << "Line " << line_count <<  ": rel_expression : simple_expression\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                }
		| simple_expression RELOP simple_expression
		
		{
		 
                f_log_out << "Line " << line_count <<  ": rel_expression : simple_expression RELOP simple_expression  \n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
			$$->push_back($2);
			
			for(int i=0;i<$3->size();i++)
			{
			$$->push_back($3->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
			
			string label1 = newLabel();
			string label2 = newLabel();
			string temp = newTemp();
			string segment_code = "";

			segment_code += $3->at(0)->getCode();
			segment_code += "\tmov ax, " + $1->at(0)->getAssemblySymbol() + "\n";
			segment_code += "\tcmp ax, " + $3->at(0)->getAssemblySymbol() + "\n";

			if($2->getName() == ">")
				segment_code += "\tjg " + label1 + "\n";
			else if($2->getName() == ">=")
				segment_code += "\tjge " + label1 + "\n";
			else if($2->getName() == "<")
				segment_code += "\tjl " + label1 + "\n";
			else if($2->getName() == "<=")
				segment_code += "\tjle " + label1 + "\n";
			else if($2->getName() == "==")
				segment_code += "\tje " + label1 + "\n";
			else if($2->getName() == "!=")
				segment_code += "\tjne " + label1 + "\n";

			segment_code += "\tmov " + temp + ", 0\n";
			segment_code += "\tjmp " + label2 + "\n";
			segment_code += label1 + ":\n";
			segment_code += "\tmov " + temp + ", 1\n";
			segment_code += label2 + ":\n";

			$$->at(0)->setCode($$->at(0)->getCode() + segment_code);
			$$->at(0)->setAssemblySymbol(temp);
                
                
                
		
		
		}	
		;
				
simple_expression : term //NTD

                  {
                f_log_out << "Line " << line_count <<  ": simple_expression : term\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                }
		  | simple_expression ADDOP term 
		  
		   {
                f_log_out << "Line " << line_count <<  ": simple_expression : simple_expression ADDOP term\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
			
			$$->push_back($2);
			
			for(int i=0;i<$3->size();i++)
			{
			$$->push_back($3->at(i));
			}
			
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
			
			
			//assembly code

			string temp = newTemp();

			string segment_code = "";
			segment_code += $3->at(0)->getCode();
			segment_code += "\tmov ax, " + $1->at(0)->getAssemblySymbol() + "\n";
			if($2->getName() == "+")
				segment_code += "\tadd ax, " + $3->at(0)->getAssemblySymbol() + "\n";
			else
				segment_code += "\tsub ax, " + $3->at(0)->getAssemblySymbol() + "\n";
			segment_code += "\tmov " + temp + ", ax\n";
			$$->at(0)->setCode($$->at(0)->getCode() + segment_code);
			$$->at(0)->setAssemblySymbol(temp);
                
                
                }
		  
		  
		  
		  ;
					
term :	unary_expression //NTD

{
                f_log_out << "Line " << line_count <<  ": term : unary_expression  \n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                }

     |  term MULOP unary_expression
     
     {
                f_log_out << "Line " << line_count <<  ": term : term MULOP unary_expression  \n\n";
                if($2->getName() == "%") //if MULOP = "%"
               {
                
                if($1->at(0)->getDataType() == "float" || $3->at(0)->getDataType() == "float")
                {
                f_log_out <<"Error at line "<<line_count<<": Non-Integer operand on modulus operator" << endl<<endl;
                f_error_out <<"Error at line "<<line_count<<": Non-Integer operand on modulus operator" << endl<<endl;
                total_errors++;
                
                }
                
               }
               
               
               //if right or left operand of MULOP is a void return type function
               
               if($3->at(0)->getIdType()=="func" && $3->at(0)->getDataType()=="void")
               {
                 f_log_out <<"Error at line "<<line_count<<": Void function used in expression" << endl<<endl;
                  f_error_out <<"Error at line "<<line_count<<": Void function used in expression" << endl<<endl;
                  total_errors++;
               
               
               }
               
               else if($1->at(0)->getIdType()=="func" && $1->at(0)->getDataType()=="void")
               {
               f_log_out <<"Error at line "<<line_count<<": Void function used in expression" << endl<<endl;
                  f_error_out <<"Error at line "<<line_count<<": Void function used in expression" << endl<<endl;
                  total_errors++;
               
               
               }
               
               
               //Modulas by zero or divided by zero
                if($2->getName() == "%" && $3->at(0)->getName()=="0") 
                {
                
                f_log_out <<"Error at line "<<line_count<<": Modulus by Zero" << endl<<endl;
                  f_error_out <<"Error at line "<<line_count<<": Modulus by Zero" << endl<<endl;
                  total_errors++;
               
                }
                
                else if($2->getName() == "/" && $3->at(0)->getName()=="0") 
                {
                
                 f_log_out <<"Error at line "<<line_count<<": Divied by Zero" << endl<<endl;
                  f_error_out <<"Error at line "<<line_count<<": Divided by Zero" << endl<<endl;
                  total_errors++;
                }


               
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
			
			$$->push_back($2);
			
                
                        for(int i=0;i<$3->size();i++)
			{
			 
			$$->push_back($3->at(i));
			  
			}
			
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			
			  
			}
			
			
			
  			f_log_out << endl << endl;
			//type = "INT";
			
			//assembly code

			string temp = newTemp();

			string segment_code = "";
			segment_code += $3->at(0)->getCode(); //unary expression calculation er code lekha holo
			segment_code += "\tmov ax, " + $1->at(0)->getAssemblySymbol() + "\n";
			segment_code += "\tmov bx, " + $3->at(0)->getAssemblySymbol() + "\n";

			if($2->getName() == "*"){
				segment_code += "\tmul bx\n";
				segment_code += "\tmov " + temp + ", ax\n";
			}
				
			else if($2->getName() == "/"){
				segment_code += "\txor dx, dx\n";
				segment_code += "\tdiv bx\n";
				segment_code += "\tmov " + temp + ", ax\n";
			}
			else{   //operator % 
				segment_code += "\txor dx, dx\n";
				segment_code += "\tdiv bx\n";
				segment_code += "\tmov " + temp + ", dx\n";
			}
			
			$$->at(0)->setCode($$->at(0)->getCode() + segment_code);
			$$->at(0)->setAssemblySymbol(temp); //propagating the calculated result of MULOP operation

			
			
			
                
                
                }
     ;

unary_expression : ADDOP unary_expression  //NTD

{
                f_log_out << "Line " << line_count <<  ": unary_expression : ADDOP unary_expression  \n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
			for(int i=0;i<$2->size();i++)
			{
			$$->push_back($2->at(i));
			}
			
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			 
			}
			
  			f_log_out << endl <<endl ;
  			
  			
  		//assembly code
		string temp_var = newTemp();
		string segment_code = ""; 
		
		segment_code += "\tmov ax, " + $2->at(0)->getAssemblySymbol() + "\n";
		if($1->getName()=="-")
		{
			segment_code += "\tneg ax \n"; 
			
		}
		segment_code += "\tmov "+temp_var+", ax"  + "\n"; 
		
		$$->at(0)->setCode($$->at(0)->getCode() + segment_code);
		$$->at(0)->setAssemblySymbol(temp_var);

                
                
                }
	   
		 | NOT unary_expression //NTD
		 
		 {
                f_log_out << "Line " << line_count <<  ": unary_expression : NOT unary_expression  \n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
			for(int i=0;i<$2->size();i++)
			{
			$$->push_back($2->at(i));
			}
			
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			 
			}
			
  			f_log_out << endl << endl; ;
		
                
                
                }
		 | factor  //NTD
		 
		 {
                f_log_out << "Line " << line_count <<  ": unary_expression : factor  \n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                }
		 ;
	
factor	: variable //NTD
       {
                f_log_out << "Line " << line_count <<  ": factor : variable  \n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
                
               
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                }
        
	| ID LPAREN argument_list RPAREN
	
	{
	
	//finding each argument and putting into "arguments"
	
	vector<SymbolInfo*> *arguments = new vector<SymbolInfo*> ();
	
	/*for(int i=0;i<$3->size();i++)
	{
	
	if($3->at(i)->getName()!=",")
	{
	
	if((i+1) < $3->size() && $3->at(i+1)->getName()=="[" )
	{
	
	SymbolInfo *temp2 = new SymbolInfo($3->at(i)->getName(),$3->at(i)->getType(),$3->at(i)->getDataType(),$3->at(i)->getIdType(),NULL);
	temp2->setName(temp2->getName() + "["+ $3->at(i+2)->getName()+"]");
	//cout << "pushing " << temp2->getName()<< " in "<<$1->getName() <<endl;
	 arguments -> push_back(temp2);
	 i=i+3;
	
	
	}
	
	
	else
	{
         arguments -> push_back($3->at(i));
         }
	}
	
	
	
	}*/
	bool float_flag = false; 

	//cout << $3->size() << endl;
	for(int i=0;i<$3->size();i++)
	{
	 while(i<$3->size() && $3->at(i)->getName() != ",")
	 {
	 	if(float_flag==false && $3->at(i)->getIdType()=="var" && $3->at(i)->getDataType()=="float")
	 	{
	 	arguments -> push_back(new SymbolInfo("float","float","float","",NULL));
	 	float_flag = true;
	 	
	 	}
	 	
	 	else if(float_flag==false && $3->at(i)->getIdType()=="cons" && $3->at(i)->getDataType()=="float")
	 	{
	 	arguments -> push_back(new SymbolInfo("float","float","float","",NULL));
	 	float_flag = true;
	 	//cout << line_count<<": " <<$3->at(i)->getName() << endl;
	 	
	 	}
	 	
	 	else if(float_flag==false && $3->at(i)->getIdType()=="array" && $3->at(i)->getDataType()=="float")
	 	{
	 	arguments -> push_back(new SymbolInfo("float","float","float","",NULL));
	 	float_flag = true;
	 	
	 	if(i+3 < $3->size())
	 	{
	 	i=i+3;
	 	}
	 	
	 	}
	 	
	 	
	 	else if(float_flag==false && $3->at(i)->getIdType()=="array" && $3->at(i)->getDataType()=="int")
	 	{
	 	
	 	if(i+3 < $3->size())
	 	{
	 	i=i+3;
	 	}
	 	
	 	}
	 	
	 	
	 	
	 	
	 	i++;
	 	
	 }
	 
	 if(float_flag == false)
	 {
	 arguments -> push_back(new SymbolInfo("int","int","int","",NULL));
	// cout << line_count <<$3->at(i)->getName() << endl;
	 }
	 
	 float_flag = false;
	
	}
	
	
                f_log_out << "Line " << line_count <<  ": factor : ID LPAREN argument_list RPAREN\n\n";
                
               
                
                
                //checking if the function call is valid
                
	SymbolInfo *temp = st.Look_up($1->getName());
	
	
	if(temp != NULL //declared or defined earlier
	&& temp->isDeclared() == false //if both declared and defined
        ) //if the function is defined earlier
        
        {
        //setting the id to pass the info of calling function upward through rules
        $1->setName(temp->getName());
        $1->setType(temp->getType());
        $1->setDataType(temp->getDataType());
        $1->setIdType(temp->getIdType());
        $1->setParameters(temp->getParameters());
        
    
        
        if(temp->getParameters() == NULL && arguments->size()!=0) //if callee function has no parameter but passing an argument to it from caller
        {
        
         //  cout << line_count << ": "<<temp->getName()<<" " << temp->getParameters()->size() << " " << arguments->size()<< endl; 
        f_log_out <<"Error at line "<<line_count<<": Total number of arguments mismatch in function "<<temp->getName() << endl << endl;
        f_error_out <<"Error at line "<<line_count<<": Total number of arguments mismatch in function "<<temp->getName() << endl << endl;
        total_errors++;
        }  
        
        else if(temp->getParameters() == NULL && arguments->size()==0) //calling a non parameterized function correctly 
        {
        //nothing to do
        }
        
        else if(temp->getParameters() != NULL  && temp->getParameters()->size() != arguments->size())   //checking if the argument number match with function parameter number
        {
        
      //  cout << line_count << ": "<<temp->getName()<<" " << temp->getParameters()->size() << " " << arguments->size()<< endl; 
        f_log_out <<"Error at line "<<line_count<<": Total number of arguments mismatch in function "<<temp->getName() << endl << endl;
        f_error_out <<"Error at line "<<line_count<<": Total number of arguments mismatch in function "<<temp->getName() << endl << endl;
        total_errors++;
        }
        
        else if(temp->getParameters() != NULL  && temp->getParameters()->size() == arguments->size()) //checking if the argument type match with function parameter number
        {
        
        for(int i=0;i<arguments->size();i++)
        {
        	if(arguments->at(i)->getDataType() != temp->getParameters()->at(i)->getDataType() )
        	{
        	
        	
        	//cout<<line_count<<": " << temp->getName() << " 1 " << arguments->at(i)->getDataType() << " 2 " << temp->getParameters()->at(i)->getDataType() << endl;
        	
        	//type convertion from int to float
        	if(arguments->at(i)->getDataType()=="int" && temp->getParameters()->at(i)->getDataType()=="float")
        	{
        	
        	continue;
        	}
        	    f_log_out <<"Error at line "<<line_count<<": "<< (i+1)<<"th argument mismatch in function "<<temp->getName()<<  endl << endl;
          f_error_out <<"Error at line "<<line_count<<": "<< (i+1)<<"th argument mismatch in function "<<temp->getName()<<  endl << endl;
        total_errors++;
        	    break;
        	}
        }
        
        }
        
        
        
        }
        
        else
        {
        
        //function was not defined
          f_log_out <<"Error at line "<<line_count<<": "<< "Undeclared function "<<$1->getName()<<  endl << endl;
         f_error_out <<"Error at line "<<line_count<<": "<< "Undeclared function "<<$1->getName()<< endl << endl;
        total_errors++;
        }
		
              
                
                
                
                        $$ = new vector<SymbolInfo*>();
			
			
			$$->push_back($1);
			$$->push_back($2);
			
			for(int i=0;i<$3->size();i++)
			{
			$$->push_back($3->at(i));
			}
			
			$$->push_back($4);
			
			
		
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                
               
                //assembly code
		string temp_var = newTemp();
		string segment_code = "";  
		int parameter_count=0;
		
		
	
		for(int i = 0; i < $3->size(); i++){
				if($3->at(i)->getAssemblySymbol() != ""){
					segment_code += "\tmov ax, " + $3->at(i)->getAssemblySymbol() + "\n";
					segment_code += "\tmov " + temp->getParameters()->at(parameter_count)->getAssemblySymbol() + ", ax\n";
					parameter_count++;
					
				}
			}
			segment_code += "\tcall " + $1->getName() + "\n";
			
			if(temp->getDataType() != "void")
			{
			segment_code += "\tmov ax, ret_temp\n";
			segment_code += "\tmov " + temp_var + ", ax\n";
			$$->at(0)->setCode($$->at(0)->getCode() + segment_code);
		        $$->at(0)->setAssemblySymbol(temp_var);
			}
			
			else
			{
			
			$$->at(0)->setCode($$->at(0)->getCode() + segment_code);
			
			}
			

		
         
         
		
		}
	| LPAREN expression RPAREN
	
	
	
	{
		 
                f_log_out << "Line " << line_count <<  ": factor : LPAREN expression RPAREN\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			$$->push_back($1);
			for(int i=0;i<$2->size();i++)
			{
			$$->push_back($2->at(i));
			}
			$$->push_back($3);
			
			
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                //assembly code
		$$->at(0)->setAssemblySymbol($2->at(0)->getAssemblySymbol());
		$$->at(0)->setCode($$->at(0)->getCode() + $2->at(0)->getCode());
                
		
		
		}	
		
	
		
	| CONST_INT 
	{
	
	f_log_out << "Line " << line_count <<  ": factor : CONST_INT  \n\n";
	
	$$ = new vector<SymbolInfo*>();
	$$->push_back($1);
	
	for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
  			
  	//assembly code
	$1->setAssemblySymbol($1->getName());
	
	
	}
	
	| CONST_FLOAT
	{
	
	
	f_log_out << "Line " << line_count <<  ": factor : CONST_FLOAT  \n\n";
	
	$$ = new vector<SymbolInfo*>();
	$$->push_back($1);
	
	for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
	
	

  	 f_log_out <<"Error at line "<<line_count<<": "<< "Float number is not supported"<<  endl << endl;
         f_error_out <<"Error at line "<<line_count<<": "<< "Float number is not supported"<< endl << endl;
          cout <<"Error at line "<<line_count<<": "<< "Float number is not supported"<< endl << endl;
        total_errors++;
        
	
	
	}
	
	
	| variable INCOP 
	
	  {
                f_log_out << "Line " << line_count <<  ": factor : variable INCOP\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
			$$->push_back($2);
			
				
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			  
			}
			
  			f_log_out << endl<<endl;
  			
  			
  			string temp = newTemp();
		string segment_code = "";

		string ID_type = (st.Look_up($1->at(0)->getName()))->getIdType();

		if(ID_type != "array"){
			segment_code += "\tmov ax, " + $1->at(0)->getAssemblySymbol() + "\n";
			segment_code += "\tmov " + temp + ", ax\n";
			segment_code += "\tinc " + $1->at(0)->getAssemblySymbol()   + "\n";
		}

		else if(ID_type == "array"){
			segment_code += "\tmov ax, " + $1->at(0)->getAssemblySymbol() + "[di]\n";
			segment_code += "\tmov " + temp + ", ax\n";
			segment_code += "\tinc " + $1->at(0)->getAssemblySymbol() + "[di]\n";
		}

		$$->at(0)->setAssemblySymbol(temp);
		$$->at(0)->setCode($$->at(0)->getCode() + segment_code);
	  }
	
	| variable DECOP
	
	 {
                f_log_out << "Line " << line_count <<  ": factor : variable DECOP\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
			$$->push_back($2);
			
				
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			  
			}
			
  			f_log_out << endl<<endl;
  			
  		//assembly code
		string temp = newTemp();
		string segment_code = "";

		string ID_type = (st.Look_up($1->at(0)->getName()))->getIdType();

		if(ID_type != "array"){
			segment_code += "\tmov ax, " + $1->at(0)->getAssemblySymbol() + "\n";
			segment_code += "\tmov " + temp + ", ax\n";
			segment_code += "\tdec " + $1->at(0)->getAssemblySymbol()   + "\n";
		}

		else if(ID_type == "array"){
			segment_code += "\tmov ax, " + $1->at(0)->getAssemblySymbol() + "[di]\n";
			segment_code += "\tmov " + temp + ", ax\n";
			segment_code += "\tdec " + $1->at(0)->getAssemblySymbol() + "[di]\n";
		}

		$$->at(0)->setAssemblySymbol(temp);
		$$->at(0)->setCode($$->at(0)->getCode() + segment_code);
	  }
	;
	
argument_list : arguments //NTD

{
		 
                f_log_out << "Line " << line_count <<  ": argument_list : arguments\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
			
			
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                
		
		
		}	


			  |
			  
			   {
			$$ = new vector<SymbolInfo*>();
		  	f_log_out << "Line no: " << line_count <<  " argument_list : \n\n";
	  		f_log_out << endl << endl;
		  }
			  ;
	
arguments : arguments COMMA logic_expression //NTD

 {
		 
                f_log_out << "Line " << line_count <<  ": arguments : arguments COMMA logic_expression\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
			
			$$->push_back($2);
			
			for(int i=0;i<$3->size();i++)
			{
			$$->push_back($3->at(i));
			}
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                
		
		
		}	
	      | logic_expression //NTD
	      
	      {
		 
                f_log_out << "Line " << line_count <<  ": arguments : logic_expression\n\n";
                
                
                        $$ = new vector<SymbolInfo*>();
			
			
			for(int i=0;i<$1->size();i++)
			{
			$$->push_back($1->at(i));
			}
			
			
			for(int i=0;i<$$->size();i++)
			{
			  f_log_out << $$->at(i)->getName() ;
			  
			}
			
  			f_log_out << endl << endl;
			//type = "INT";
                
                
                
		
		
		}	
	      ;
	      
%%


int main(int argc,char *argv[])
{



	if(argc!=2){
		cout << "Please provide input file name and try again\n";
		return 0;
	}
	
	FILE *input_file=fopen(argv[1],"r");
	if(input_file==NULL){
		cout << "Cannot open specified file\n";
		return 0;
	}
	
	yyin=input_file;
	
	
	yyparse();
	
	st.Print_All_Scope_Table(f_log_out);
	f_log_out << "Total lines: " << line_count-1 << endl;
        f_log_out << "Total errors: " << total_errors << endl<<endl;
	
	
	fclose(yyin);
	f_log_out.close();
	f_error_out.close();
	Optimized_Code("code.asm");
	
	
	return 0;
}

