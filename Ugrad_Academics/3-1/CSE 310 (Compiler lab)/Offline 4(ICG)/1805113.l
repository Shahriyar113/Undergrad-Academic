%option noyywrap

%x MULTI_LINE_COMMENT
%x STRING_STATE
%x STRING_STATE_2

%{
//#include<bits/stdc++.h>
#include "Symbol_Table.cpp"
#include "y.tab.h"


extern YYSTYPE yylval;
extern ofstream f_log_out;
extern ofstream f_error_out;

extern int line_count;
extern int total_errors;

extern SymbolTable st;
extern bool function_scope_flag; 
string multi_line_comment = "";
int multi_comment__line_track;

string str;
string inStr;
int begin_string_line;

%}

Whitespace [ \t\f\r\v]+
Letter [a-zA-Z]
Digit [0-9]
PP "++"
MM "--"
L_AND "&&"
L_OR "||"
ANY_CHAR .
METACHARS [nta'\\frbv0"]



%%
[ \t\f\r\v]+ {

//cout << "space" << endl;
}

"if"  {
	SymbolInfo *si = new SymbolInfo("if","");
	yylval.symbol =  si;

        return IF ;}

"int" {   
	SymbolInfo *si = new SymbolInfo("int","");
	yylval.symbol =  si;
        //cout << "INT got" << endl;
        return INT ;
    }

          
"for" {   
	SymbolInfo *si = new SymbolInfo("for","");
	yylval.symbol =  si;

        return FOR ;
    }

"do"  {   
	SymbolInfo *si = new SymbolInfo("do","");
	yylval.symbol =  si;

        return DO ;
    }
          
"while" {   
	SymbolInfo *si = new SymbolInfo("while","");
	yylval.symbol =  si;

        return WHILE ;
    }
          
"float" {   
	SymbolInfo *si = new SymbolInfo("float","");
	yylval.symbol =  si;

        return FLOAT ;
    }
          
"void" {   
	SymbolInfo *si = new SymbolInfo("void","");
	yylval.symbol =  si;

        return VOID ;
    }
                    
"switch" {   
	SymbolInfo *si = new SymbolInfo("switch","");
	yylval.symbol =  si;

        return SWITCH ;
    }
          
"default" {   
	SymbolInfo *si = new SymbolInfo("default","");
	yylval.symbol =  si;

        return DEFAULT ;
    }
          
"else" {   
	SymbolInfo *si = new SymbolInfo("else","");
	yylval.symbol =  si;

        return ELSE ;
    }

"char" {   
	SymbolInfo *si = new SymbolInfo("char","");
	yylval.symbol =  si;

        return CHAR ;
    }
          
"break" {   
	SymbolInfo *si = new SymbolInfo("break","");
	yylval.symbol =  si;

        return BREAK ;
    }

"double" {   
	SymbolInfo *si = new SymbolInfo("double","");
	yylval.symbol =  si;

        return DOUBLE ;
    }
          
"return" {   
	SymbolInfo *si = new SymbolInfo("return","");
	yylval.symbol =  si;

        return RETURN ;
    }
          
"case" {   
	SymbolInfo *si = new SymbolInfo("case","");
	yylval.symbol =  si;

        return CASE ;
    }
                    
"continue" {   
	SymbolInfo *si = new SymbolInfo("continue","");
	yylval.symbol =  si;

        return CONTINUE ;
    }

"println" {   
	SymbolInfo *si = new SymbolInfo("println","");
	yylval.symbol =  si;

        return PRINTLN ;
    }
                    
{Digit}+ { //for integer const
         
          
         // st.Insert(yytext,"CONST_FLOAT");
         SymbolInfo *si = new SymbolInfo(yytext,"CONST_INT","int","cons",NULL);
	yylval.symbol =  si;
       //cout << yytext << endl;
         //cout << yylval.integer_val << endl;
          return CONST_INT;
         
         
          }
          
{Digit}*(\.{Digit}+)?(E[+-]?{Digit}+)?   { //for float const
            
         //st.Insert(yytext,"CONST_FLOAT");
        //sscanf(yytext,"%lf", &yylval.double_val);
        
         SymbolInfo *si = new SymbolInfo(yytext,"CONST_FLOAT","float","cons",NULL);
	yylval.symbol =  si;
	
         return CONST_FLOAT;
        
          }
          
             
          
          





"\'"[^\\\']"\'"  { //for char const
        
         //st.Insert(yytext,"CONST_CHAR");
        // yylval.char_val = yytext[1];
        
         SymbolInfo *si = new SymbolInfo(yytext,"CONST_CHAR","char","cons",NULL);
	yylval.symbol =  si;
         return CONST_CHAR;
         
         
          }                                 

"\'""\\"[nt\\\'afrbv0]"\'"  {  //for special char cons
           
          //st.Insert(yytext,"CONST_CHAR");
          SymbolInfo *si = new SymbolInfo(yytext,"CONST_CHAR");
	yylval.symbol =  si;
          return CONST_CHAR;
           
        
          
          }
          
[+-]  {   
	SymbolInfo *si = new SymbolInfo(yytext,"ADDOP");
	yylval.symbol =  si;

        return ADDOP ;
    }
                     
[*/%]  {   
	SymbolInfo *si = new SymbolInfo(yytext,"MULOP");
	yylval.symbol =  si;

        return MULOP ;
    }                
          
{PP}   {   
	SymbolInfo *si = new SymbolInfo(yytext,"INCOP");
	yylval.symbol =  si;

        return INCOP ;
    }

{MM}   {   
	SymbolInfo *si = new SymbolInfo(yytext,"DECOP");
	yylval.symbol =  si;

        return DECOP ;
    }
             
"="   {   
	SymbolInfo *si = new SymbolInfo(yytext,"ASSIGNOP");
	yylval.symbol =  si;
	
	//cout << yytext << endl;
        return ASSIGNOP ;
    }

"!"     {   
	SymbolInfo *si = new SymbolInfo(yytext,"NOT");
	yylval.symbol =  si;

        return NOT ;
    }                                   

([<>=!][=]?)  {   
	SymbolInfo *si = new SymbolInfo(yytext,"RELOP");
	yylval.symbol =  si;

        return RELOP ;
    }
             
{L_AND}|{L_OR}  {   
	SymbolInfo *si = new SymbolInfo(yytext,"LOGICOP");
	yylval.symbol =  si;

        return LOGICOP ;
    }
                 

"("  {   
	SymbolInfo *si = new SymbolInfo(yytext,"LPAREN");
	yylval.symbol =  si;

        return LPAREN ;
    }
             

")"  {   
	SymbolInfo *si = new SymbolInfo(yytext,"RPAREN");
	yylval.symbol =  si;

        return RPAREN ;
    }
             
             
"{"  {

    	SymbolInfo *si = new SymbolInfo(yytext,"LCURL");
	yylval.symbol =  si;
	
   	return LCURL; 
   }                 

"}"  {

	SymbolInfo *si = new SymbolInfo(yytext,"RCURL");
	yylval.symbol =  si;
    	
    	
    	return RCURL; 
    	
    }           

"["  {

	SymbolInfo *si = new SymbolInfo(yytext,"LTHIRD");
	yylval.symbol =  si;

    	return LTHIRD; 
    }     
             
"]"  {

	SymbolInfo *si = new SymbolInfo(yytext,"RTHIRD");
	yylval.symbol =  si;
	
    	return RTHIRD; 
    }                                 

","  {

	SymbolInfo *si = new SymbolInfo(yytext,"COMMA");
	yylval.symbol =  si;
        //cout << yytext << endl;
    	return COMMA; 
    }     
             
";"  {

	SymbolInfo *si = new SymbolInfo(yytext,"SEMICOLON");
	yylval.symbol =  si;
	//cout << yytext << endl;
    	return SEMICOLON; 
    }     
             
             
[a-zA-Z_][a-zA-Z0-9_]*    { //for Identifier

    
	SymbolInfo *si = new SymbolInfo(yytext,"ID");
	yylval.symbol =  si;
       
        //cout << yytext << endl;
       // st.Insert(yytext,"ID"); //lex theke symbol table a id rakha jabe na
        
        return ID;

                 
          } 
          
 
 
["]		{
			begin_string_line = line_count;
			str ="\"";
			inStr = "\"";
			BEGIN STRING_STATE;
		
		}
		
<STRING_STATE>["]	{
			str += "\"";
			inStr += "\"";
			//fprintf(fout_token,"<STRING,%s> ",str.c_str());
			
			
			
			/*fprintf(fout,"\nLine no %d: TOKEN <STRING> Lexeme %s found --> <STRING, %s>\n",begin_string_line,inStr.c_str(), str.c_str());*/
			
			
			
			BEGIN INITIAL;
			return STRING;

		}
		
		
<STRING_STATE>[^"\n\\]* {
			//fprintf(logout, "At this time: %s\n",yytext);
			str += yytext;
			inStr += yytext;
		}
		
<STRING_STATE>[\n] {
			/*fprintf(fout,"\nError at line no %d: Unterminated string %s\n",begin_string_line, inStr.c_str());*/
			
			f_log_out << "Error at line no "<< begin_string_line << ": Unterminated string "<< inStr.c_str() << endl << endl;
			 
			line_count++;
			total_errors++;
			BEGIN INITIAL;
		}
		
<STRING_STATE>[\\]	{
			//fprintf(logout, "Going to String state 2...........\n\n\n\n");
			inStr += "\\";
			BEGIN STRING_STATE_2;
		}
		
		
<STRING_STATE_2>{Whitespace}*[\n]	{
			line_count++;
			inStr += "\n";
			//fprintf(logout,"\n\nin string state 2!......\n\n");
			BEGIN STRING_STATE;

		}
		
<STRING_STATE>[\\]{METACHARS} {
			//printf("Got a meta char in string.............\n\n");
			char b = yytext[1];
			if(b=='n') {
				str+= "\n"; inStr += "\\n"; }
			if(b=='t') {
				str+= "\t"; inStr += "\\t"; }
			if(b=='a') {
				str+= "\a"; inStr += "\\a"; }
			if(b=='f') {
				str+= "\f"; inStr += "\\f"; }
			if(b=='r') {
				str+= "\r"; inStr += "\\r"; }
			if(b=='b') {
				str+= "\b"; inStr += "\\b"; }
			if(b=='v') {
				str+= "\v"; inStr += "\\v"; }
			if(b=='\\') {
				str+="\\"; inStr += "\\\\"; }
			if(b=='\'') {
				str+= "'"; inStr += "\\'"; }
			if(b=='\0') {
				str+= "\0"; inStr += "\\0"; }
			if(b=='\"') {
				str+= "\""; inStr += "\\\""; }
			
			//fprintf(logout, "...............now string is %s ...............\n\n\n\n", str.c_str());
		}
		
<STRING_STATE_2>{ANY_CHAR} {
			
			str+= yytext[0];
			inStr+= "\\";
			inStr+= yytext[0];
			BEGIN STRING_STATE;
			
		}
		
 


"//"[^\\\n]*(("\\"[^\n]*)*|("\\""\n"[^\n]*)*)* { //for single line comment


  string s = yytext;
  int curr_line = line_count;
  
  for(int i=0;i<s.size();i++)
  {
  if(s[i] == '\n')
  line_count++;
  }




}



"/""\*" {

multi_comment__line_track = line_count;
multi_line_comment +=  yytext;
BEGIN MULTI_LINE_COMMENT;



}


<MULTI_LINE_COMMENT>"\*""/" {

   multi_line_comment +=  yytext;
   
   
  
          
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

  
   
    f_log_out <<"Error at Line: "<< multi_comment__line_track<<": "<<"Unfinished Comment "<<endl<<endl;
          
          total_errors++;
          
          multi_line_comment = "";
          BEGIN INITIAL;
          

}







          
     


{Digit}*"\."{Digit}*"\."[^\n;]*  {//decimal point error

         f_log_out <<"Error at line no "<< line_count<<": "<<"Too many decimal points "<<yytext<<endl<<endl ;
         total_errors++;
           
         }
         
          
          

            
          
          
{Digit}*(\.{Digit}+)?(E[+-]?{Digit}+\.{Digit}*)?    {//Ill foremd error
 

         f_log_out <<"Error at line no "<< line_count<<": "<<"Ill formed number "<<yytext<<endl<<endl ;
         total_errors++;
           
         }
         
         
         
{Digit}+{Letter}+  {//Invalid identifier or number
 

         f_log_out <<"Error at line no "<< line_count<<": "<<"Invalid prefix on ID or invalid suffix or Number "<<yytext<<endl<<endl ;
         total_errors++;
           
         }
         
         
         
"\'""\'"        {//empty character constant error 
 

         f_log_out <<"Error at line no "<< line_count<<": "<<"Empty character constant "<<yytext<<endl<<endl ;
         total_errors++;
           
         }           
         
         
         
"\'"[^\n\\\"]+"\'"        {//multi character constant error 
 

         f_log_out <<"Error at line no "<< line_count<<": "<<"Multi character constant error "<<yytext<<endl<<endl ;
         total_errors++;
           
         }  
         

"\'\\\'"  { //   if('\')  is seen    
      
      
      
      f_log_out <<"Error at line no "<< line_count<<": "<<"Unterminated character "<<yytext << endl<<endl ;
      total_errors++;
           
      }   
      
               
"\'"[^\n]    { // for handing ' , 'a ,  
      
      
      
      f_log_out <<"Error at line no "<< line_count<<": "<<"Unterminated character "<<yytext << endl<<endl ;
      total_errors++;
           
      }   
      
      
"\'""\\"[^\n]    { // for handing ' , '\t , '\n 
      
      
      
      f_log_out <<"Error at line no "<< line_count<<": "<<"Unterminated character "<<yytext << endl<<endl ;
      total_errors++;
           
      }         
         
                
                                         

[\n] {

//cout << "newline" << endl;
line_count++; 

}

<<EOF>> {
          /*fout << endl<<endl;;
          cout <<"Total Line Number:  "<<line_count <<endl<<endl;
          fout <<"Total Line Number:  "<<line_count <<endl;
          fout << "total errors: "<< total_errors << endl;*/


          return 0;
          }


. { 

    if(yytext[0]== '\"')
    {
     f_log_out <<"Error at line no "<< line_count<<": "<<"Unfinished String "<<yytext<<endl<<endl ;
         total_errors++;
         
    } 
    
    else
   { 
     f_log_out <<"Error at line no "<< line_count<<": "<<"Unrecognized character "<<yytext << endl<<endl ;
     total_errors++;
     }      


    }
%%


