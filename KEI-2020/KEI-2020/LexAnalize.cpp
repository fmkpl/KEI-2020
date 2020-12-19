#include "stdafx.h"	
#include "Graphs.h"
#include "FST.h"
#include "LexAnalize.h"
#include "Error.h"


namespace Lexer
{
	bool flag2 = false;
	bool flag1 = false;
	Graph graph[N_GRAPHS] =   // ����� ��� �������� ���������
	{
		{ LEX_LIB, FST::FST(GRAPH_CStrLib) },
		{ LEX_LITERAL, FST::FST(GRAPH_NUMBER_LITERAL) },
		{ LEX_LITERAL, FST::FST(GRAPH_STRING_LITERAL) },
		{ LEX_SEPARATORS, FST::FST(GRAPH_SEPARATORS) },
		{ LEX_DIRSLASH, FST::FST(GRAPH_FORWARD_SLASH) },
		{ LEX_CREATE, FST::FST(GRAPH_CREATE) },
		{ LEX_KOREN, FST::FST(GRAPH_KOREN) },
		{ LEX_DEFIF, FST::FST(GRAPH_DEFIF) },
		{ LEX_DEFELSE, FST::FST(GRAPH_DEFELSE) },
		{ LEX_STEPEN, FST::FST(GRAPH_STEPEN) },
		{ LEX_STRCOP, FST::FST(GRAPH_STRCOP) },
		{ LEX_STRCON, FST::FST(GRAPH_STRCON) },
		{ LEX_CIRCLE, FST::FST(GRAPH_CIRCLE) },
		{ LEX_USLOVIEI, FST::FST(GRAPH_USLOVI) },
		{ LEX_USLOVIES, FST::FST(GRAPH_USLOVS) },
		{ LEX_LOG, FST::FST(GRAPH_LOG) },
		{ LEX_MATHSIN, FST::FST(GRAPH_MSIN) },
		{ LEX_MATHCOS, FST::FST(GRAPH_MCOS) },
		{ LEX_LESS, FST::FST(GRAPH_LESS) },
		{ LEX_MORE, FST::FST(GRAPH_MORE) },
		{ LEX_START, FST::FST(GRAPH_START) },
		{ LEX_ID_TYPE_I, FST::FST(GRAPH_INTEGER) },
		{ LEX_ID_TYPE_W, FST::FST(GRAPH_STRING) },
		{ LEX_FUNCTION, FST::FST(GRAPH_FUNCTION) },
		{ LEX_RETURN, FST::FST(GRAPH_RETURN) },
		{ LEX_OUT, FST::FST(GRAPH_OUT) },
		{ LEX_ID, FST::FST(GRAPH_ID) },
	};
	LEX Fill_LTIT(In::IN &InStruct, Log::LOG &log, Parm::PARM &parm) //������ ������������ �������
	{
		LEX Tables;
		Tables.Lextable = LT::Create(LT_MAXSIZE);  // �������� ������� ������
		Tables.IDtable = IT::Create(TI_MAXSIZE);  // �������� ������� ���������������

		bool isFunc = false;
		bool isParam = false;     //���� �� ��������
		int count_parm = 0;
		int MainBody = NULL;
		int MyFunc = NULL;
		int LibBody = NULL;
		int funcend = NULL;
		char buffer[255] = "";
		char tempTokenFunc[255] = ""; //����� ��� ����� �������
		char tempTokenFunction[255] = "";   //�����
		char tempToken[255] = "";    //�����

		IT::IDDATATYPE funcType;   // ��� �������
		IT::IDDATATYPE idType;   // ��� ��������������

		for (int i = 0; i < In::StToken::tokensSize; i++) // �������� �������� ������� ����
		{
			for (int j = 0; j < N_GRAPHS; j++)    // ���� ���������� ������� ��� �����	
			{
				FST::FST fstex(InStruct.tokens[i].token, graph[j].graph);   // ������� �������
				if (FST::execute(fstex)) // ���� ������ �������� �� 
				{
					switch (graph[j].lexema)     // ���� ���������� ���� ��� �������
					{

					case LEX_START:   // ���� ������� �-���
					{
						MainBody++;   //�������� � 0 �� 1 , �� ��������� , ���������� ����� 1 �� �-���
						if (MainBody > 1)    // ���� ������� ����� 1-�� ������� �-���
							Log::writeError(log.stream, Error::GetError(113, InStruct.tokens[i].line, NULL)); // ������ ������ � ������ ������

						strcpy_s(tempTokenFunc, "m");
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);   // ������ � ������� , � ��������� ������ ������ 
						LT::Add(Tables.Lextable, entrylt);    // ���������� ������� � ������� 
						break; //�����
					}
					case LEX_LIB:   // ���� ����������� ����������
					{
						LibBody++;
						if (LibBody > 1)    // ���� ������� ����� 1-�� ����������
							Log::writeError(log.stream, Error::GetError(403, InStruct.tokens[i].line, NULL)); // ������ ������ � ������ ������

						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);// ������ � ������� , � ��������� ������ ������ 
						LT::Add(Tables.Lextable, entrylt);// ���������� ������� � ������� 
						break; //�����
					}


					case LEX_KOREN:  // ������� ������� ������
					{
						MyFunc = 1;

						IT::Entry entryit("koren", i, IT::NUM, IT::F); // ������ ������� �� � ���������� ���� ��������� ������
						IT::Add(Tables.IDtable, entryit);						 // ��������� ��������� �������
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // ��������
																																		 // �������� ������� ������
						LT::Add(Tables.Lextable, entrylt); //��������� � ������� ������
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 1;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'n';
						break;
					}

					case LEX_DEFIF: 
					{
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token));
						LT::Add(Tables.Lextable, entrylt);
					}

					case LEX_DEFELSE: 
					{
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token));
						LT::Add(Tables.Lextable, entrylt);
					}

					case LEX_STEPEN: // ������� ������� �������	
					{
						MyFunc = 1;
						IT::Entry entryit("stepen", i, IT::NUM, IT::F); // ������ ������� �� � ���������� ���� ��������� ������
						IT::Add(Tables.IDtable, entryit);						 // ��������� ��������� �������
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // ��������
																																		 // �������� ������� ������
						LT::Add(Tables.Lextable, entrylt); //��������� � ������� ������
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 1;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'n';
						//Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[1] = 'n';
						break;
					}
					case LEX_STRCOP: 
					{
						MyFunc = 1;
						IT::Entry entryit("strcop", i, IT::STR, IT::F); // ������ ������� �� � ���������� ���� ��������� ������
						IT::Add(Tables.IDtable, entryit);						 // ��������� ��������� �������
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // ��������
																																		 // �������� ������� ������
						LT::Add(Tables.Lextable, entrylt); //��������� � ������� ������
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 1;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'w';
						break;
					}	

					case LEX_STRCON:
					{
						MyFunc = 1;
						IT::Entry entryit("strcon", i, IT::STR, IT::F); // ������ ������� �� � ���������� ���� ��������� ������
						IT::Add(Tables.IDtable, entryit);						 // ��������� ��������� �������
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // ��������
																																		 // �������� ������� ������
						LT::Add(Tables.Lextable, entrylt); //��������� � ������� ������
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 2;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'w';
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[1] = 'w';
						break;
					}

					case LEX_CIRCLE: 
					{
						MyFunc = 1;
						IT::Entry entryit("for", i, IT::STR, IT::F); // ������ ������� �� � ���������� ���� ��������� ������
						IT::Add(Tables.IDtable, entryit);						 // ��������� ��������� �������
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // ��������
																																		 // �������� ������� ������
						LT::Add(Tables.Lextable, entrylt); //��������� � ������� ������
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 1;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'w';
						break;
					}

					case LEX_USLOVIEI:
					{
						MyFunc = 1;
						IT::Entry entryit("ifIisN", i, IT::NUM, IT::F); // ������ ������� �� � ���������� ���� ��������� ������
						IT::Add(Tables.IDtable, entryit);						 // ��������� ��������� �������
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // ��������
																																		 // �������� ������� ������
						LT::Add(Tables.Lextable, entrylt); //��������� � ������� ������
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 1;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'n';
						break;
					}

					case LEX_USLOVIES:
					{
						MyFunc = 1;
						IT::Entry entryit("ifSisN", i, IT::STR, IT::F); // ������ ������� �� � ���������� ���� ��������� ������
						IT::Add(Tables.IDtable, entryit);						 // ��������� ��������� �������
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // ��������
																																		 // �������� ������� ������
						LT::Add(Tables.Lextable, entrylt); //��������� � ������� ������
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 1;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'w';
						break;
					}

					case LEX_LOG:
					{
						MyFunc = 1;
						IT::Entry entryit("ln", i, IT::NUM, IT::F); // ������ ������� �� � ���������� ���� ��������� ������
						IT::Add(Tables.IDtable, entryit);						 // ��������� ��������� �������
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // ��������
																																		 // �������� ������� ������
						LT::Add(Tables.Lextable, entrylt); //��������� � ������� ������
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 1;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'n';
						break;
					}

					case LEX_MATHSIN:
					{
						MyFunc = 1;
						IT::Entry entryit("mathSin", i, IT::NUM, IT::F); // ������ ������� �� � ���������� ���� ��������� ������
						IT::Add(Tables.IDtable, entryit);						 // ��������� ��������� �������
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // ��������
																																		 // �������� ������� ������
						LT::Add(Tables.Lextable, entrylt); //��������� � ������� ������
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 1;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'n';
						break;
					}

					case LEX_MATHCOS:
					{
						MyFunc = 1;
						IT::Entry entryit("mathCos", i, IT::NUM, IT::F); // ������ ������� �� � ���������� ���� ��������� ������
						IT::Add(Tables.IDtable, entryit);						 // ��������� ��������� �������
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // ��������
																																		 // �������� ������� ������
						LT::Add(Tables.Lextable, entrylt); //��������� � ������� ������
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 1;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'n';
						break;
					}

					case LEX_LESS:
					{
						MyFunc = 1;
						IT::Entry entryit("less", i, IT::NUM, IT::F); // ������ ������� �� � ���������� ���� ��������� ������
						IT::Add(Tables.IDtable, entryit);						 // ��������� ��������� �������
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // ��������
																																		 // �������� ������� ������
						LT::Add(Tables.Lextable, entrylt); //��������� � ������� ������
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 2;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'n';
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[1] = 'n';
						break;
					}

					case LEX_MORE:
					{
						MyFunc = 1;
						IT::Entry entryit("more", i, IT::NUM, IT::F); // ������ ������� �� � ���������� ���� ��������� ������
						IT::Add(Tables.IDtable, entryit);						 // ��������� ��������� �������
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // ��������
																																		 // �������� ������� ������
						LT::Add(Tables.Lextable, entrylt); //��������� � ������� ������
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 2;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'n';
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[1] = 'n';
						break;
					}

					case LEX_ID://������������
					{
						if (Tables.Lextable.table[i - 1].lexema != LEX_FUNCTION && IT::IsId(Tables.IDtable, InStruct.tokens[i].token) == -1)
						{
							strncpy(buffer, tempTokenFunc, ID_MAXSIZE - 1);
							strcat_s(buffer, InStruct.tokens[i].token);
							strncpy(InStruct.tokens[i].token, buffer, ID_MAXSIZE - 1);
						}

						strncpy_s(tempToken, InStruct.tokens[i].token, ID_MAXSIZE - 1); // ����������� ����� �������������
						strncpy_s(InStruct.tokens[i].token, InStruct.tokens[i].token, ID_MAXSIZE - 1); //����������� �����
						if (IT::IsId(Tables.IDtable, InStruct.tokens[i].token) == -1) // ���� ������ ������������� �� ������ �������� 
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_FUNCTION) // ���� ���������� �������� ���� ������� ��������
							{
								strncpy_s(tempTokenFunction, tempToken, ID_MAXSIZE - 1); // �������� ����������� �������������� � ����� ��������������
								strncpy_s(tempTokenFunc, tempToken, ID_MAXSIZE - 1);

								funcType = idType;     // ��������� ��� ��������������
								if (Tables.Lextable.table[i - 2].lexema == LEX_ID_TYPE_I) idType = IT::NUM;
								if (Tables.Lextable.table[i - 2].lexema == LEX_ID_TYPE_W) idType = IT::STR;
								IT::Entry entryit(tempTokenFunction, i, idType, IT::F); // ������ ������� �� � ���������� ���� ��������� ������
								IT::Add(Tables.IDtable, entryit); // ��������� ��������� �������
								LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // ��������
																																				 // �������� ������� ������
								LT::Add(Tables.Lextable, entrylt); //��������� � ������� ������
								isParam = true; // ������� ����������
								if (InStruct.tokens[i + 2].token[0] == LEX_RIGHTTHESIS) // ���� ������� ����� ���� ������� )
									isParam = false; // ��������� �����������
								isFunc = true;
								break;

							}
							else if (Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE_I) //���� ���������� ������ ���� �������� ������ ���� ������ 
							{
								if (Tables.Lextable.table[i - 2].lexema == LEX_CREATE)//���� ���������� ������ ���� type
								{
									if (Tables.Lextable.table[i - 2].lexema == LEX_SEPARATORS)//���� ���������� ������ ���� /*+-(){}...
									{
										std::cout << Tables.Lextable.table[i - 2].lexema << std::endl;
										Log::writeError(log.stream, Error::GetError(108, InStruct.tokens[i].line, NULL)); // ���� �� �������� ��� ������ � ��� ���
										flag1 = true;																		  //  ������ ���������������� �����������
									}
								}
								if (isParam == false) // ���� ������������� ���� ���������� �� �������� ����������
								{
									IT::Entry entryit(InStruct.tokens[i].token, i, idType, IT::V); // ������ ������� ���� ���
									IT::Add(Tables.IDtable, entryit); //������� � ���� ���
								}
								else if (isParam == true) // ����� ���� ��������
								{
									int qwe = i;
									while (Tables.IDtable.table[qwe].idtype != IT::F)
										qwe--;
									Tables.IDtable.table[qwe].parms[kol] = 'n';
									kol++;
									if (kol == INT_MAXSIZE_PARM)
									{
										Log::writeError(log.stream, Error::GetError(115, InStruct.tokens[i].line, NULL));
										flag1 = true;
									}
									IT::Entry entryit(InStruct.tokens[i].token, i, idType, IT::P);// ������ ������� ���� ���
									IT::Add(Tables.IDtable, entryit);//������� � ���� ���
																	 //
									if (InStruct.tokens[i + 1].token[0] == LEX_RIGHTTHESIS) // ���� ��������� ������� ������� )
									{
										isParam = false; // ��������� �����������
										int qwe = i;
										while (Tables.IDtable.table[qwe].idtype != IT::F)
											qwe--;
										Tables.IDtable.table[qwe].count_parm = kol;
										kol = 0;
									}
								}

								LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // �������� �������� ���� ����
								LT::Add(Tables.Lextable, entrylt); // ���������� � ���� ����
								break;
							}
							else if (Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE_W) //���� ���������� ������ ���� �������� ��������� ���� ������
							{
								if (isParam == false) // ���� ������������� ���� ���������� �� �������� ����������
								{
									IT::Entry entryit(InStruct.tokens[i].token, i, idType, IT::V); // ������ ������� ���� ���
									IT::Add(Tables.IDtable, entryit); //������� � ���� ���
								}
								else if (isParam == true) // ����� ���� ��������
								{
									int qwe = i;
									while (Tables.IDtable.table[qwe].idtype != IT::F)
										qwe--;
									Tables.IDtable.table[qwe].parms[kol] = 'w';
									kol++;
									if (kol == INT_MAXSIZE_PARM)
									{
										Log::writeError(log.stream, Error::GetError(103, InStruct.tokens[i].line, NULL));
										flag1 = true;
									}
									IT::Entry entryit(InStruct.tokens[i].token, i, idType, IT::P);// ������ ������� ���� ���
									IT::Add(Tables.IDtable, entryit);//������� � ���� ���
																	 //
									if (InStruct.tokens[i + 1].token[0] == LEX_RIGHTTHESIS) // ���� ��������� ������� ������� )
									{
										isParam = false; // ��������� �����������
										int qwe = i;
										while (Tables.IDtable.table[qwe].idtype != IT::F)
											qwe--;
										Tables.IDtable.table[qwe].count_parm = kol;
										kol = 0;
									}
								}

								LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // �������� �������� ���� ����
								LT::Add(Tables.Lextable, entrylt); // ���������� � ���� ����
								break;
							}
							Log::writeError(log.stream, Error::GetError(108, InStruct.tokens[i].line, NULL)); // ���� �� �������� �� ������ � ��� ���
							flag1 = true;																		  //  ������ ���������������� �����������
						}
						// ����� �������� �� ���������������	
						else // � ��������� ������ 
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE_I || Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE_W || Tables.Lextable.table[i - 1].lexema == LEX_FUNCTION) // ���� ����������
																																																	 //��� ��� ������ ��� ������� �������
							{
								Log::writeError(log.stream, Error::GetError(107, InStruct.tokens[i].line, NULL)); //����� ������ � ������� ���������������
								flag1 = true;
							}
							LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); //�������� �������� ���� ������
							LT::Add(Tables.Lextable, entrylt); // ��������� �������� � ������� ������
							break;
						}
						break;
					}
					case LEX_LITERAL: // ������� ��������
					{
						switch (Tables.Lextable.table[i - 1].lexema) // �������� ���������� �������
						{
						case LEX_EQUAL: // ������� =
						{
							IT::Entry entryit(LTRL, i, graph[j].graph.type, IT::L); // �������� �������� ���� �� � �������� �������
							IT::Add(Tables.IDtable, entryit); //���������� � �������
							IT::SetValue(Tables.IDtable, Tables.IDtable.size - 1, InStruct.tokens[i].token); // ������������ �������� ��������
							LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, Tables.IDtable.size - 1); // �������� �������� ���� ����
							LT::Add(Tables.Lextable, entrylt); // ���������� �������� � ���� ����
							if (Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token)].idtype == IT::F) // ���� ���������� ���� ���� �-���
							{
								Log::writeError(log.stream, Error::GetError(115, InStruct.tokens[i].line, NULL)); // ������ !!!  ������ ����������� �������� �-���
								flag1 = true;
							}
							if (Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token)].idtype == IT::V ||    //���� ����� = ���� ���������� ��� ��������
								Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token)].idtype == IT::P)
							{
								IT::SetValue(Tables.IDtable, IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token), InStruct.tokens[i].token); // ������������� �� �� �������� � ���� ���� ���������������
							}
							break;
						}

						// ���� ���������� �� �������� 
						case LEX_LEFTHESIS:  // ������� ����� ������� ��������
						case LEX_COMMA: //������� �������
						case LEX_OUT:  // ������� ��������� ������
						case LEX_RETURN: //������� ��������� ����������� ��������
						{

							IT::Entry entryit(LTRL, i, graph[j].graph.type, IT::L); // �������� �������� ���� �� � �������� �������
							IT::Add(Tables.IDtable, entryit); //���������� � �������
							IT::SetValue(Tables.IDtable, Tables.IDtable.size - 1, InStruct.tokens[i].token); // ������������ �������� ��������
							LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, Tables.IDtable.size - 1); // �������� �������� ���� ����
							LT::Add(Tables.Lextable, entrylt); // ���������� �������� � ���� ����
							break;
						}
						default:
							IT::Entry entryit(LTRL, i, graph[j].graph.type, IT::L); // �������� �������� ���� �� � �������� �������
							IT::Add(Tables.IDtable, entryit); //���������� � �������
							IT::SetValue(Tables.IDtable, Tables.IDtable.size - 1, InStruct.tokens[i].token); // ������������ �������� ��������
							LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, Tables.IDtable.size - 1); // �������� �������� ���� ����
							LT::Add(Tables.Lextable, entrylt); // ���������� �������� � ���� ����
						}
						break;
					}

					case LEX_SEPARATORS: // ������� �����������
					{
						if (Tables.Lextable.table[i - 1].lexema == LEX_SEPARATORS)
							Error::GetError(605, InStruct.tokens[i].line, NULL);
						switch (InStruct.tokens[i].token[0])
						{
						case LEX_SEPARATOR:
						{
							if (Tables.Lextable.table[i - 2].lexema == LEX_RETURN) // ����  ��������� �� 2 ���� ����� � ����� ������� return
							{
								int qwe = i; int qwe1 = i + 1;
								while (Tables.IDtable.table[qwe].idtype != IT::F)
									qwe--;
								if (Tables.IDtable.table[qwe].iddatatype != Tables.IDtable.table[Tables.Lextable.table[i - 1].idxTI].iddatatype)
								{
									Log::writeError(log.stream, Error::GetError(405, InStruct.tokens[i].line, NULL));  // ������������ �������� �� ��������� � ����� �������
									flag1 = true;
								}
								kol = 0;
								IT::IDDATATYPE retType; // �������� ���������� �������� �-���
								if (Tables.Lextable.table[i - 1].lexema == LEX_LITERAL) // ���� ���������� �������
									retType = Tables.IDtable.table[Tables.IDtable.size - 1].iddatatype; // ������ ������� � ���� ����� �-��� ��������
							}

						}

						default:
						{
							LT::Entry entrylt(InStruct.tokens[i].token[0], InStruct.tokens[i].line); // ������ ������� ���� ������
							LT::Add(Tables.Lextable, entrylt); // ��������� �������� � ������� ������
						}
						}
						break;
					}
					case LEX_ID_TYPE_W: // ������� ���� ������
					case LEX_ID_TYPE_I: // ������� ���� ������
						idType = graph[j].graph.type; // ���������� ���� ���� ������
					default:
					{
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line); // �������� ��. ���� ����.
						LT::Add(Tables.Lextable, entrylt); // ��������� � ����. ����
						break;
					}
					}
					break;
				}
			}
		}
		if (!MainBody) // ���� ������ �� �-���
		{
			flag1 = true;
			Log::writeError(log.stream, Error::GetError(400)); // ������ ���������� ������� �-���
		}
		if (LibBody == 0 && MyFunc == 1)
			Log::writeError(log.stream, Error::GetError(402)); // �� ���������� ����������
		for (int i = 0; i < Tables.Lextable.size; i++)
		{
			if (Tables.Lextable.table[i].lexema == LEX_SEPARATORS && Tables.Lextable.table[i - 1].lexema == LEX_SEPARATORS)
			{
				flag2 = true;
				Log::writeError(log.stream, Error::GetError(106, InStruct.tokens[i + 1].line, NULL));
			}
			else if (Tables.Lextable.table[i - 1].lexema == LEX_SEPARATORS && Tables.Lextable.table[i - 2].lexema == LEX_SEPARATORS)
			{
				flag2 = true;
				Log::writeError(log.stream, Error::GetError(106, InStruct.tokens[i + 1].line, NULL));
			}
			else if (Tables.Lextable.table[i - 2].lexema == LEX_SEPARATORS && Tables.Lextable.table[i - 3].lexema == LEX_SEPARATORS)
			{
				flag2 = true;
				Log::writeError(log.stream, Error::GetError(106, InStruct.tokens[i + 1].line, NULL));
			}
			else if (Tables.Lextable.table[i - 2].lexema == LEX_EQUAL && Tables.Lextable.table[i - 3].lexema == LEX_EQUAL)
			{
				flag2 = true;
				Log::writeError(log.stream, Error::GetError(106, InStruct.tokens[i + 1].line, NULL));
			}
		}

		if (flag1 == false && flag2 == false)
		{
			std::cout << "��� �������, �������� Gen.html "<<endl;
			for (int i = 0; i < Tables.Lextable.size; i++) // �������� �������� � �� ����������� �������
			{
				if (Tables.Lextable.table[i].lexema == LEX_ID || Tables.Lextable.table[i].lexema == LEX_LITERAL)
				{
					if (Tables.IDtable.table[Tables.Lextable.table[i].idxTI].idtype == IT::F)
					{
						if (Tables.Lextable.table[i + 1].lexema != LEX_LEFTHESIS)
							Log::writeError(log.stream, Error::GetError(409, InStruct.tokens[i + 1].line, NULL));
					}
				}
				if (Tables.Lextable.table[i].lexema == LEX_EQUAL && Tables.Lextable.table[i - 1].lexema == LEX_EQUAL)
					flag2 = true;
				if (Tables.Lextable.table[i].lexema == LEX_EQUAL && Tables.Lextable.table[i - 1].lexema == LEX_ID && Tables.Lextable.table[i + 1].lexema != LEX_LEFTHESIS) // ���� �� ������� �����, � �� ����� ����� �������������
				{
					if (Tables.Lextable.table[i - 1].lexema == LEX_MINUS)
						Log::writeError(log.stream, Error::GetError(118, InStruct.tokens[i + 1].line, NULL));
					if (Tables.IDtable.table[Tables.Lextable.table[i - 1].idxTI].iddatatype == IT::STR) // � ���� ������������� ���������� ���� 
					{
						if (Tables.IDtable.table[Tables.Lextable.table[i + 1].idxTI].iddatatype != IT::STR) // � ����� ����� ������������� �� ������ ���� ����
							Log::writeError(log.stream, Error::GetError(401, InStruct.tokens[i + 1].line, NULL));
						if (Tables.Lextable.table[i + 2].lexema != LEX_SEPARATOR && Tables.IDtable.table[Tables.Lextable.table[i + 1].idxTI].idtype != IT::F) // ��� �� �������
							Log::writeError(log.stream, Error::GetError(404, InStruct.tokens[i + 2].line, NULL));
					}
					if (Tables.IDtable.table[Tables.Lextable.table[i - 1].idxTI].iddatatype == IT::NUM) // � ���� ������������� �������������� ���� 
					{
						if (Tables.IDtable.table[Tables.Lextable.table[i + 1].idxTI].iddatatype == IT::STR) //���� ��������� ���������� ����, �� ������ 
							Log::writeError(log.stream, Error::GetError(401, InStruct.tokens[i + 1].line, NULL));
						int j = i, k = i;
						while (Tables.Lextable.table[j].lexema != LEX_SEPARATOR) //���� ;
						{
							if (Tables.Lextable.table[j].lexema == LEX_BRACELET)//���� ������ ����� ����������� �����������, �� ������
								Log::writeError(log.stream, Error::GetError(119, InStruct.tokens[i + 1].line, NULL));
							j++;
						}
						bool param = false;
						if (Tables.Lextable.table[j].lexema == LEX_SEPARATOR) // ���� ����� ;
						{
							while (k != j) // ��������� ���� ��������� ���������
							{
								if (Tables.Lextable.table[k].lexema == LEX_RIGHTTHESIS) // ���� ��� ���� ��������� �������
									param = false;
								if (Tables.Lextable.table[k].lexema == LEX_ID || Tables.Lextable.table[k].lexema == LEX_LITERAL) // ���� ��� �������������
								{
									if (Tables.IDtable.table[Tables.Lextable.table[k].idxTI].idtype == IT::F)
									{
										if (Tables.Lextable.table[k + 1].lexema == LEX_LEFTHESIS)
										{
											param = true;
										}
										else
										{
											Log::writeError(log.stream, Error::GetError(409, InStruct.tokens[i + 1].line, NULL));
										}
									}
									else
									{
										if (Tables.IDtable.table[Tables.Lextable.table[k].idxTI].iddatatype == IT::STR && param == false)
										{
											Log::writeError(log.stream, Error::GetError(402, InStruct.tokens[i + 1].line, NULL));
										}
									}
								}
								k++;
							}
						}
					}
				}
			}
			bool flag = false; int some_count = 0; char some_buffer[INT_MAXSIZE_PARM];
			for (int i = 0; i < Tables.Lextable.size; i++)
			{

				if (Tables.Lextable.table[i].lexema == LEX_FUNCTION && flag == false && flag2 == false)
				{

					int j = i, funct = i;
					while (Tables.Lextable.table[j].lexema != LEX_RIGHTTHESIS)
						j++;
					int count = 0;
					for (int p = i; p != j; p++)
					{
						if (Tables.Lextable.table[p].lexema == LEX_ID_TYPE_I)
						{
							Tables.IDtable.table[Tables.Lextable.table[funct + 1].idxTI].parms[count] = 'n';
							count++;
						}
						if (Tables.Lextable.table[p].lexema == LEX_ID_TYPE_W)
						{
							Tables.IDtable.table[Tables.Lextable.table[funct + 1].idxTI].parms[count] = 'w';
							count++;
						}
					}
				}
				if (Tables.Lextable.table[i].lexema == LEX_START)
					flag = true;

				if (flag == true)
				{
					if (Tables.Lextable.table[i].lexema == LEX_ID || Tables.Lextable.table[i].lexema == LEX_LITERAL)
					{
						if (Tables.IDtable.table[Tables.Lextable.table[i].idxTI].idtype == IT::F)
						{
							int param = 0;

							if (Tables.Lextable.table[i + 1].lexema == LEX_LEFTHESIS)
							{
								int k = i + 1;
								while (Tables.Lextable.table[k].lexema != LEX_RIGHTTHESIS)
								{
									if (Tables.Lextable.table[k].lexema == LEX_ID || Tables.Lextable.table[k].lexema == LEX_LITERAL)
									{
										if (Tables.IDtable.table[Tables.Lextable.table[k].idxTI].iddatatype == IT::STR)
											some_buffer[some_count] = 'w';
										if (Tables.IDtable.table[Tables.Lextable.table[k].idxTI].iddatatype == IT::NUM)
											some_buffer[some_count] = 'n';
										some_count++;
									}
									k++;
								}
								if (Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm < 0)
									Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 0;
								if (some_count != Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm)
								{
									Log::writeError(log.stream, Error::GetError(406, InStruct.tokens[i + 1].line, NULL));
								}
								for (int r = 0; r < some_count; r++)
									if (some_buffer[r] != Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[r])
									{
										Log::writeError(log.stream, Error::GetError(407, InStruct.tokens[i + 1].line, NULL));
									}
								some_count = 0;
							}
						}
					}
				}
			}
		}
		return Tables; // ���������� �� ��
	}
}