#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>

#include <token_types.h>
#include <string_utils.h>

using namespace std;

string names[] = {"NULL","STRUCT","IDENTIFIER","END_STRUCT","TYPENAME","POINTER","OSB","CSB","WHITESPACE","FIELD","SIZE","UNDEFINED_CHAR"};


extern int yylex();
extern char* yytext;

int main(void) {
	

	vector<string> struct_names;

	int name_token, value_token;

	name_token = yylex();

	while(name_token) {

		if (name_token == STRUCT) {

			string matched_text(yytext);
			squeeze(matched_text,' ');

			string identifier(matched_text.substr(6));
			identifier.resize(identifier.size()-1);

			struct_names.push_back(identifier); 
			value_token = yylex(); 


			cout << identifier << "\n"; /* Output struct name */

			while(value_token != END_STRUCT) {
			
				string type_name;
				string identifier;
				string pointer;
				string size;
			
				int size_count = 0;
				bool found_identifier;

				if (value_token == TYPENAME) {

					type_name = yytext;
					found_identifier = true;
				}
				else if (value_token == IDENTIFIER) {
					string identif(yytext);

					if (!identif.empty()) {

						if (find(struct_names.begin(),struct_names.end(),identif) == struct_names.end()) {
							cout << "Type " << identif << " was not declared in this scope!\n";
							found_identifier = false;
						}
						else {
							type_name = identif;
							found_identifier = true;
						}					
					}
				}
				value_token = yylex();										


				if (value_token == POINTER) {
					pointer += yytext;
					value_token = yylex();
				}
				if (value_token == IDENTIFIER) {
					identifier = yytext;
					value_token = yylex();
				}
				if (value_token == POINTER) {
					pointer += yytext;
					value_token = yylex();
				}
				if (value_token == SIZE) {
					size += yytext[1];
					size_count += 1;
					value_token = yylex();
				}
				while (value_token == SIZE) {
					size += '*';
					size += yytext[1];
					size_count += 1;
					value_token = yylex();
				}


				if (found_identifier) {
					cout << "\t" << identifier;
					cout  << " (" << pointer;
					if (size_count == 1) {
						cout << size << " ";
					}
					cout << type_name;
					if (size_count > 1) {
						cout <<  " [" << size << "]";
					}
					cout << ")\n";
				}
			}
		}



		name_token = yylex();
	}
}
