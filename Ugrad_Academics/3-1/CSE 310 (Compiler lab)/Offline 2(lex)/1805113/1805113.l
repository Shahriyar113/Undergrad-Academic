%option noyywrap yylineno

%x MULTI_LINE_COMMENT
%{
#include "Symbol_Table.cpp"

int line_count=1;
int total_errors =0;

SymbolTable st(7);
string multi_line_comment = "";
int multi_comment__line_track;

%}

Letter [a-zA-Z]
Digit [0-9]
PP "++"
MM "--"
L_AND "&&"
L_OR "||"
ANY_CHAR .



%%
[ \t\f\r\v]+ {}

if {fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"IF"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "IF" <<"> " ;
          }

int {     fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"INT"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "INT" <<"> " ;
          }
          
for {     fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"FOR"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "FOR" <<"> " ;
          }
          
do {     fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"DO"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "DO" <<"> " ;
          }
          
while {     fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"WHILE"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "WHILE" <<"> " ;
          }
          

float {     fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"FLOAT"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "FLOAT" <<"> " ;
          }
          
void {     fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"VOID"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "VOID" <<"> " ;
          }
                    
switch {     fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"SWITCH"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "SWITCH" <<"> " ;
          }
          
default {     fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"DEFAULT"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "DEFAULT" <<"> " ;
          }
          
else {     fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"ELSE"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "ELSE" <<"> " ;
          }
          
char {     fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"CHAR"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "CHAR" <<"> " ;
          }
          
          
break {     fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"BREAK"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "BREAK" <<"> " ;
          }
double {     fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"DOUBLE"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "DOUBLE" <<"> " ;
          }
          
return {     fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"RETURN"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "RETURN" <<"> " ;
          }
          
case {     fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"CASE"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
    
          fout_token << "<" << "CASE" <<"> " ;
          }
                    
continue {     fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"CONTINUE"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "CONTINUE" <<"> " ;
          }
                    
{Digit}+ { //for integer const
         fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"CONST_INT"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          if(st.Insert(yytext,"CONST_INT"))
          {
          st.Print_All_Scope_Table();
          }
          
          fout_token << "<" << "CONST_INT, "<<yytext <<"> " ;
          }
          
{Digit}*(\.{Digit}+)?(E[+-]?{Digit}+)?   { //for float const
              fout <<"Line no "<< line_count<<": "<<"Token "
          
          <<"<"<<"CONST_FLOAT"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
         if(st.Insert(yytext,"CONST_FLOAT"))
          {
          st.Print_All_Scope_Table();
          }
          
          
          fout_token << "<" << "CONST_FLOAT, "<<yytext <<"> " ;
          }   
          
          





           

"\'"[^\\\']"\'"  { //for char const
        fout <<"Line no "<< line_count<<": "<<"Token "
          
          <<"<"<<"CONST_CHAR"<<">"<<" lexeme "<<yytext<<" found " <<" --> "
          
           << "<" << "CONST_CHAR, "<<yytext[1] <<"> "<<endl<<endl;
          
        if(st.Insert(yytext,"CONST_CHAR"))
          {
          st.Print_All_Scope_Table();
          }
          
          
          fout_token << "<" << "CONST_CHAR, "<<yytext[1] <<"> " ;
          }                                 

"\'""\\"[nt\\\'afrbv0]"\'"  {  //for special char cons
           
           
          
           
          if(yytext[2] == 't')
          {
          fout <<"Line no "<< line_count<<": "<<"Token "
          
          <<"<"<<"CONST_CHAR"<<">"<<" lexeme "<<yytext<<" found " <<" --> "
          
           << "<" << "CONST_CHAR, "<< '\t' <<"> "<<endl<<endl;
           
          
          fout_token << "<" << "CONST_CHAR, "<<'\t' <<"> " ;
          
          
           if(st.Insert(yytext,"CONST_CHAR"))
          {
          st.Print_All_Scope_Table();
          }
          
          
          

          }
          
          
          
          
          else if(yytext[2] == 'n')
          {
               fout <<"Line no "<< line_count<<": "<<"Token "
          
          <<"<"<<"CONST_CHAR"<<">"<<" lexeme "<<yytext<<" found " <<" --> "
          
           << "<" << "CONST_CHAR, "<< '\n' <<"> "<<endl<<endl;
           
          
          fout_token << "<" << "CONST_CHAR, "<<'\n' <<"> " ;
          
           if(st.Insert(yytext,"CONST_CHAR"))
          {
          st.Print_All_Scope_Table();
          }
          
          
          

          }
          
          
          
          else if(yytext[2] == 'b')
          {
               fout <<"Line no "<< line_count<<": "<<"Token "
          
          <<"<"<<"CONST_CHAR"<<">"<<" lexeme "<<yytext<<" found " <<" --> "
          
           << "<" << "CONST_CHAR, "<< '\b' <<"> "<<endl<<endl;
           
          
          fout_token << "<" << "CONST_CHAR, "<<'\b' <<"> " ;
          
           if(st.Insert(yytext,"CONST_CHAR"))
          {
          st.Print_All_Scope_Table();
          }
          
          
          

          }
          
          
          
           else if(yytext[2] == '0')
          {
               fout <<"Line no "<< line_count<<": "<<"Token "
          
          <<"<"<<"CONST_CHAR"<<">"<<" lexeme "<<yytext<<" found " <<" --> "
          
           << "<" << "CONST_CHAR, "<< '\0' <<"> "<<endl<<endl;
           
          
          fout_token << "<" << "CONST_CHAR, "<<'\0' <<"> " ;
          
           if(st.Insert(yytext,"CONST_CHAR"))
          {
          st.Print_All_Scope_Table();
          }
          
          
          

          }
          
          
          
          
          else if(yytext[2] == 'v')
          {
               fout <<"Line no "<< line_count<<": "<<"Token "
          
          <<"<"<<"CONST_CHAR"<<">"<<" lexeme "<<yytext<<" found " <<" --> "
          
           << "<" << "CONST_CHAR, "<< '\v' <<"> "<<endl<<endl;
           
          
          fout_token << "<" << "CONST_CHAR, "<<'\v' <<"> " ;
          
          
           if(st.Insert(yytext,"CONST_CHAR"))
          {
          st.Print_All_Scope_Table();
          }
          
          
          

          }
          
          
          
          
          else if(yytext[2] == 'r')
          {
               fout <<"Line no "<< line_count<<": "<<"Token "
          
          <<"<"<<"CONST_CHAR"<<">"<<" lexeme "<<yytext<<" found " <<" --> "
          
           << "<" << "CONST_CHAR, "<< '\r' <<"> "<<endl<<endl;
           
          
          fout_token << "<" << "CONST_CHAR, "<<'\r' <<"> " ;
          
          
           if(st.Insert(yytext,"CONST_CHAR"))
          {
          st.Print_All_Scope_Table();
          }
          
          
          

          }
          
          
          
          
          else if(yytext[2] == '0')
          {
               fout <<"Line no "<< line_count<<": "<<"Token "
          
          <<"<"<<"CONST_CHAR"<<">"<<" lexeme "<<yytext<<" found " <<" --> "
          
           << "<" << "CONST_CHAR, "<< '\0' <<"> "<<endl<<endl;
           
          
          fout_token << "<" << "CONST_CHAR, "<<'\0' <<"> " ;
          
          
           if(st.Insert(yytext,"CONST_CHAR"))
          {
          st.Print_All_Scope_Table();
          }
          
          
          

          }
          
          
          
          
          else if(yytext[2] == '\\')
          {
               fout <<"Line no "<< line_count<<": "<<"Token "
          
          <<"<"<<"CONST_CHAR"<<">"<<" lexeme "<<yytext<<" found " <<" --> "
          
           << "<" << "CONST_CHAR, "<< '\\' <<"> "<<endl<<endl;
           
          
          fout_token << "<" << "CONST_CHAR, "<<'\\' <<"> " ;
          
          
           if(st.Insert(yytext,"CONST_CHAR"))
          {
          st.Print_All_Scope_Table();
          }
          
          
          

          }
          
          
          
          
          else if(yytext[2] == '\'')
          {
               fout <<"Line no "<< line_count<<": "<<"Token "
          
          <<"<"<<"CONST_CHAR"<<">"<<" lexeme "<<yytext<<" found " <<" --> "
          
           << "<" << "CONST_CHAR, "<< '\'' <<"> "<<endl<<endl;
           
          
          fout_token << "<" << "CONST_CHAR, "<<'\'' <<"> " ;
          
          
           if(st.Insert(yytext,"CONST_CHAR"))
          {
          st.Print_All_Scope_Table();
          }
          
          
          

          }
          
          
          
          
          else if(yytext[2] == 'a')
          {
               fout <<"Line no "<< line_count<<": "<<"Token "
          
          <<"<"<<"CONST_CHAR"<<">"<<" lexeme "<<yytext<<" found " <<" --> "
          
           << "<" << "CONST_CHAR, "<< '\a' <<"> "<<endl<<endl;
           
          
          fout_token << "<" << "CONST_CHAR, "<<'\a' <<"> " ;
          
          
           if(st.Insert(yytext,"CONST_CHAR"))
          {
          st.Print_All_Scope_Table();
          }
          
          
          

          }
          
          
          
          
          else if(yytext[2] == 'f')
          {
               fout <<"Line no "<< line_count<<": "<<"Token "
          
          <<"<"<<"CONST_CHAR"<<">"<<" lexeme "<<yytext<<" found " <<" --> "
          
           << "<" << "CONST_CHAR, "<< '\f' <<"> "<<endl<<endl;
           
          
          fout_token << "<" << "CONST_CHAR, "<<'\f' <<"> " ;
          
          
           if(st.Insert(yytext,"CONST_CHAR"))
          {
          st.Print_All_Scope_Table();
          }
          
          
          

          }
          
          
          
          
          else
          {
          fout <<"Error at line no "<< line_count<<": "<<"Unrecognized character "<<yytext << endl ;
          }
          
          }
          
          
       
          
          
                                      
          
          
           
 
[+-]  { 
        fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"ADDOP"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "ADDOP, "<<yytext <<"> " ;
          }                 
                              
                    
[*/%]  {     fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"MULOP"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
           fout_token << "<" << "MULOP, "<<yytext <<"> " ;
          }                     
          
{PP}|{MM} { // for ++ or --
           fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"INCOP"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "INCOP, "<<yytext <<"> " ;
             }   
             
"="   { 
           fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"ASSIGNOP"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "ASSIGNOP, "<<yytext <<"> " ;
             }   
"!"     { 
           fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"NOT"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
        fout_token << "<" << "NOT, "<<yytext <<"> " ;
             }                                              

([<>=!][=]?)  { //for <,<=,>,>=,==,!=
           fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"RELOP"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
           fout_token << "<" << "RELOP, "<<yytext <<"> " ;
             } 
             
             
{L_AND}|{L_OR}   { 
           fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"LOGICOP"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
           fout_token << "<" << "LOGICOP, "<<yytext <<"> " ;
             }              

"("  { 
           fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"LPAREN"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "LPAREN, "<<yytext <<"> " ;
             }    
")"  { 
           fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"RPAREN"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "RPAREN, "<<yytext <<"> " ;
             } 
             
"{"  { 
           fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"LCURL"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "LCURL, "<<yytext <<"> " ;
          
          st.Enter_Scope();
             }                    

"}"  { 
           fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"RCURL"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "RCURL, "<<yytext <<"> " ;
          
          st.Exit_Scope();
             }                    

"["  { 
           fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"LTHIRD"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
         fout_token << "<" << "LTHIRD, "<<yytext <<"> " ;
          
          
             }   
             
"]"  { 
           fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"RTHIRD"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "RTHIRD, "<<yytext <<"> " ;
          
          
             }                                  

","  { 
           fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"COMMA"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "COMMA, "<<yytext <<"> " ;
          
          
             }    
             
";"  { 
           fout <<"Line no "<< line_count<<": "<<"Token "
          <<"<"<<"SEMICOLON"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
          fout_token << "<" << "SEMICOLON, "<<yytext <<"> " ;
          
          
             }    
             
             
[a-zA-Z_][a-zA-Z0-9_]*    { //for Identifier
                      fout <<"Line no "<< line_count<<": "<<"Token "
                      <<"<"<<"ID"<<">"<<" lexeme "<<yytext <<" found"<<endl<<endl;
          
                    
        if(st.Insert(yytext,"ID"))
          {
          st.Print_All_Scope_Table();
          }
          
                     fout_token << "<" << "ID, "<<yytext <<"> " ;
          } 
          
 




  
[\"][^\n\\\"]*("\\"[\n\\\"tnfabrv0][^\n\\\"]*)*[\"] { //for all string

           
       
          string s = yytext;
           
            
           
            int curr_line = line_count;
            
            
           
            
            for(int i=0;i<s.size();i++)
            {
            if(s[i] == '\\')
            {
            //cout << "found " << i << endl;
            if(s[i+1] == '\n')
             {  
             s[i] = ' ';
             s[i+1] = ' ';
             line_count++;
             }
             
             else if (s[i+1] == '\"')
            { s[i] = ' ';
            s[i+1] = '\"';
            }
             
             
            else if (s[i+1] == 'n')
            { s[i] = ' ';
            s[i+1] = '\n';
            }
            
            else if (s[i+1] == 't')
            { s[i] = ' ';
            s[i+1] = '\t';
            }
            
            else if (s[i+1] == 'b')
            { s[i] = ' ';
            s[i+1] = '\b';
            }
            
            else if (s[i+1] == '\\')
            { s[i] = ' ';
            s[i+1] = '\\';
            }
            
            else if (s[i+1] == 'r')
            { s[i] = ' ';
            s[i+1] = '\r';
            }
            
            else if (s[i+1] == 'f')
            { s[i] =  ' ';
            s[i+1] = '\f';
            }
            
            else if (s[i+1] == 'v')
            { s[i] = ' ';
            s[i+1] = '\v';
            }
            
             else if (s[i+1] == '0')
            { s[i] = ' ';
            s[i+1] = '\0';
            }
            
            
            
            
            
            }
            
            
           
            
            
            
            } 
                     
              //cout << "here" << endl;
            cout << s << endl;
                   
         fout <<"Line no "<< curr_line<<": "<<"Token "
          
          <<"<"<<"STRING"<<">"<<" lexeme " <<yytext<<" found " <<" --> "
          
           << "<" << "STRING, "<<s <<"> "<<endl<<endl;
          
         
           fout_token << "<" << "STRING, "<<s <<"> " ;
           
          
          



}


"//"[^\\\n]*(("\\"[^\n]*)*|("\\""\n"[^\n]*)*)* { //for single line comment


  string s = yytext;
  int curr_line = line_count;
  
  for(int i=0;i<s.size();i++)
  {
  if(s[i] == '\n')
  line_count++;
  }



fout <<"Line no "<< curr_line<<": "<<"Token "
          
          <<"<"<<"COMMENT"<<">"<<" lexeme " <<yytext<<" found " <<endl<<endl ;
          
          
}



"/""\*" {

multi_comment__line_track = line_count;
multi_line_comment +=  yytext;
BEGIN MULTI_LINE_COMMENT;



}


<MULTI_LINE_COMMENT>"\*""/" {

   multi_line_comment +=  yytext;
   
   
   fout <<"Line no "<< multi_comment__line_track<<": "<<"Token "
          
          <<"<"<<"COMMENT"<<">"<<" lexeme " <<multi_line_comment<<" found " <<endl<<endl ;
          
          
          multi_line_comment = "";
          BEGIN INITIAL;
          


}



<MULTI_LINE_COMMENT>{ANY_CHAR} {

   multi_line_comment +=  yytext;
   


}


<MULTI_LINE_COMMENT>"\n" {

   multi_line_comment +=  yytext;
   
   line_count++;


}


<MULTI_LINE_COMMENT><<EOF>> {

  
   
    fout <<"Error at Line: "<< multi_comment__line_track<<": "<<"Unfinished Comment "<<endl<<endl;
          
          total_errors++;
          
          multi_line_comment = "";
          BEGIN INITIAL;
          

}







          
     


{Digit}*"\."{Digit}*"\."[^\n]*  {//decimal point error

         fout <<"Error at line no "<< line_count<<": "<<"Too many decimal points "<<yytext<<endl<<endl ;
         total_errors++;
           
         }
         
          
          

            
          
          
{Digit}*(\.{Digit}+)?(E[+-]?{Digit}+\.{Digit}*)?    {//Ill foremd error
 

         fout <<"Error at line no "<< line_count<<": "<<"Ill formed number "<<yytext<<endl<<endl ;
         total_errors++;
           
         }
         
         
         
{Digit}+{Letter}+  {//Invalid identifier or number
 

         fout <<"Error at line no "<< line_count<<": "<<"Invalid prefix on ID or invalid suffix or Number "<<yytext<<endl<<endl ;
         total_errors++;
           
         }
         
         
         
"\'""\'"        {//empty character constant error 
 

         fout <<"Error at line no "<< line_count<<": "<<"Empty character constant "<<yytext<<endl<<endl ;
         total_errors++;
           
         }           
         
         
         
"\'"[^\n\\\"]+"\'"        {//multi character constant error 
 

         fout <<"Error at line no "<< line_count<<": "<<"Multi character constant error "<<yytext<<endl<<endl ;
         total_errors++;
           
         }  
         

"\'\\\'"  { //   if('\')  is seen    
      
      
      
      fout <<"Error at line no "<< line_count<<": "<<"Unterminated character "<<yytext << endl<<endl ;
      total_errors++;
           
      }   
      
               
"\'"[^\n]    { // for handing ' , 'a ,  
      
      
      
      fout <<"Error at line no "<< line_count<<": "<<"Unterminated character "<<yytext << endl<<endl ;
      total_errors++;
           
      }   
      
      
"\'""\\"[^\n]    { // for handing ' , '\t , '\n 
      
      
      
      fout <<"Error at line no "<< line_count<<": "<<"Unterminated character "<<yytext << endl<<endl ;
      total_errors++;
           
      }         
         
                
                                         

[\n] {line_count++; }

<<EOF>> {
          fout << endl<<endl;;
          cout <<"Total Line Number:  "<<line_count <<endl<<endl;
          fout <<"Total Line Number:  "<<line_count <<endl;
          fout << "total errors: "<< total_errors << endl;


          return 0;
          }


. { 

    if(yytext[0]== '\"')
    {
     fout <<"Error at line no "<< line_count<<": "<<"Unfinished String "<<yytext<<endl<<endl ;
         total_errors++;
         
    } 
    
    else
   { 
     fout <<"Error at line no "<< line_count<<": "<<"Unrecognized character "<<yytext << endl<<endl ;
     total_errors++;
     }      


    }
%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	

	yyin= fin;
	yylineno = 1;
	yylex();
	fclose(yyin);
	return 0;
}
