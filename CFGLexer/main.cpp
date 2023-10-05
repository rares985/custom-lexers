#include <iostream>
#include <string>
#include <algorithm>


#include <token_types.h>
#include <error.h>
#include <grammar.h>
#include <utils.h>

extern int yylex();
extern char* yytext;
extern int yylineno;

int main(int argc, char** argv) {

	/* Program must take exactly one argument */

	if (argc != 2) {
		printError(INCORRECT_ARGUMENT_FORMAT);
		return 0;
	}

	/* activate the flags according to command-line parameters */

	bool has_e_flag = (std::string(argv[1]) == "--has-e");
	bool is_void_flag = (std::string(argv[1]) == "--is-void");
	bool useless_nonterminals_flag = (std::string(argv[1]) == "--useless-nonterminals");

	/* if the flag is garbage, output error */

	if (!has_e_flag && !is_void_flag && !useless_nonterminals_flag) {
		printError(INCORRECT_ARGUMENT_FORMAT);
		return 0;
	}
	

	ContextFreeGrammar G;

	int token_type;
	token_type = yylex();
	
	/* If the input text does not respect the CFG-format, output error */

	if (token_type != CFG) {
		printError(SYNTAX_ERROR);
		return 0;
	}

	std::string cfg(yytext);

	/* there must be no other text in the file, after the CFG */

	if (yylex()) {
		printError(SYNTAX_ERROR);
		return 0;
	}

	/* Ignore the white spaces ( remove them ) */
	
	squeeze(cfg, ' ');

	std::vector<std::string> split_cfg = split(cfg,'}');

	/* Build the grammar that will be used */

	G.V = split_cfg[0].substr(2);
	squeeze(G.V,',');
	G.E = split_cfg[1].substr(2);
	squeeze(G.E,',');


	std::string rules = split_cfg[2].substr(2,split_cfg[2].length()-2);
	std::vector<std::string> split_rules = split(rules,'(');

	for(int i = 0; i < split_rules.size(); i ++) {
		char left_side = split_rules[i][0];

		size_t endRulePos = split_rules[i].find(")");
		std::string right_side = split_rules[i].substr(2,endRulePos);
		squeeze(right_side,',');
		squeeze(right_side,')');

		auto new_rule = std::make_pair(left_side,right_side);
		G.R.push_back(new_rule);
	}

	squeeze(split_cfg[3],')');
	squeeze(split_cfg[3],',');

	G.S = split_cfg[3][0];


	/* G must be semantically valid */

	if (!isValid(G)) {
		printError(SEMANTIC_ERROR);
		return 0;
	}



	/* Produce output according to command-line parameters */

	if (has_e_flag) {
		std::cout << (hasE(G) ? "\nYes" : "\nNo") << "\n";
	}
	else if (is_void_flag) {
		std::cout << (IsVoid(G) ? "\nYes" : "\nNo") << "\n";
	}
	else if (useless_nonterminals_flag) {
		std::string useless_nonterminals = GetUselessNonterminals(G);
		for(int i = 0; i < useless_nonterminals.size(); i++) {
			std::cout  <<"\n" << useless_nonterminals[i] << "\n";
		}
	}
	return 0;
}