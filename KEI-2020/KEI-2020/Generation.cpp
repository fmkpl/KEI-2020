#include "stdafx.h"
#include "Generation.h"

ofstream fout("Gen.html");
void Head()
{
	fout << "<html>" << endl;
	fout << "<head>" << endl;
	fout << "<title>" << endl;
	fout << "KEI-2020 (RESULTS)" << endl;
	fout << "</title" << endl;
	fout << "<body>" << endl;
	fout << "<script>" << endl << endl;
}
void Down()
{
	fout << "</script>" << endl;
	fout << "</body>" << endl;
	fout << "</head>" << endl;
	fout << "</html>" << endl;
	fout.close();
}



void Generation(LT::LexTable &Lextable, In::StToken *tokens)
{
	Head();
	for (int i = 0; i < Lextable.size; i++)
	{
		switch (Lextable.table[i].lexema)
		{
		case LEX_PLUS:
		{
			fout << " " << Lextable.table[i].lexema << " ";
			break;
		}
		case LEX_STAR:
		case LEX_MINUS:
		case LEX_DIRSLASH:
		case  LEX_EQUAL:
		{
			fout << " " << Lextable.table[i].lexema << " ";
			break;
		}
		case LEX_COMMA:
		case SPACE:
		{
			fout << Lextable.table[i].lexema << " ";
			break;
		}

		case LEX_RIGHTTHESIS:
		case LEX_LEFTHESIS:
		{
			fout << Lextable.table[i].lexema;
			break;
		}
		case LEX_LEFTBRACE:
		{

			fout << endl << Lextable.table[i].lexema << endl;
			break;
		}
		case LEX_BRACELET:
		{

			fout << Lextable.table[i].lexema << endl << endl;
			break;
		}
		case LEX_SEPARATOR:
		{
			fout << Lextable.table[i].lexema << endl;
			break;
		}
		case  LEX_CREATE:
		{	
			fout << "var ";
			break;
		}
		case LEX_LITERAL:
		case LEX_ID:
		{
			fout << tokens[i].token;
			break;
		}
		case LEX_OUT:
		{
			fout << "document.write(" << tokens[i + 2].token << "+'</br>');" << endl;
		
			break;
		}
		case tochka:
		{
			fout << endl;
			break;
		}
		case LEX_FUNCTION:
		{
			fout << "function ";
			break;
		}
		case LEX_RETURN:
		{
			fout << "return ";
			break;
		}

		case LEX_KOREN:
		{
			fout << "Math.sqrt(" << tokens[i + 2].token << ")";
			i = i + 3;
			break;
		}
		case LEX_STEPEN:	
		{
			fout << "Math.pow(" << tokens[i + 2].token << ", ";
			i = i + 3;
			break;
		}
		case LEX_STRCOP:
		{
			fout << tokens[i + 2].token << ".concat(" << tokens[i + 2].token << ")";
			i = i + 3;
			break;
		}
		case LEX_STRCON: 
		{
			fout << tokens[i + 2].token <<  "+(";
			i = i + 3;
			break;
		}
		case LEX_CIRCLE: 
		{
			fout << "for(var i=0;i<5;i++){document.writeln(" << tokens[i + 2].token << ");}";
			i = i + 3;
			break;
		}
		case LEX_USLOVIEI: 
		{
			fout << "if(" << tokens[i + 2].token << "==0) { document.writeln('NUMBER EQUALS NULL!'); } else { document.writeln('NUMBER NOT EQUALS NULL!'); }";
			i = i + 3;
			break;
		}
		case LEX_USLOVIES:
		{
			fout << "if(" << tokens[i + 2].token << "== null) { document.writeln('STRING EQUALS NULL!'); } else { document.writeln('STRING NOT EQUALS NULL!'); }";
			i = i + 3;
			break;
		}
		case LEX_DEFIF:
		{
			fout << "if";
			
			break;
		}
		case LEX_DEFELSE: 
		{
			fout << "else";
			break;
		}
		case LEX_LOG:
		{
			fout << "Math.log(" << tokens[i + 2].token << ")";
			i = i + 3;
			break;
		}
		case LEX_MATHSIN: 
		{
			fout << "Math.sin(" << tokens[i + 2].token << ")";
			i = i + 3;
			break;
		}
		case LEX_MATHCOS: 
		{
			fout << "Math.cos(" << tokens[i + 2].token << ")";
			i = i + 3;
			break;
		}
		case LEX_LESS: 
		{
			fout << "if(" << tokens[i + 2].token << "<" << tokens[i + 4].token << " ) { document.writeln(' _TRUE_ '); } else { document.writeln(' _FALSE_ '); }";
		}
		case LEX_MORE:
		{
			fout << "if(" << tokens[i + 2].token << ">" << tokens[i + 4].token << " ) { document.writeln(' _TRUE_ '); } else { document.writeln(' _FALSE_ '); }";
		}
		}
	}
	Down();

}
