#include "stdafx.h"
#include "Parm.h"
#include "Log.h"
#include "Error.h"
#include "In.h"


namespace Log
{

	LOG getstream(wchar_t  logfile[])//�� �������� -in �����
	{
		LOG stream;
		stream.stream = new std::ofstream;
		(*stream.stream).open(logfile);
		if (!(*stream.stream).is_open())
			throw ERROR_THROW(110);
		wcscpy_s(stream.logfile, logfile);
		return stream;
	}

	void writeLog(LOG &log) {//��������
		char buffer[80];
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		char* format = "%d.%m.%Y %H:%M:%S";
		strftime(buffer, 80, format, timeinfo);
		*log.stream << "\n----- �������� ------ ����: " << buffer << " -------- \n\n";
	}

	void writeParm(LOG &log, Parm::PARM &parm)//���������
	{
		char inTxt[PARM_MAX_SIZE],
			ITTxt[PARM_MAX_SIZE],
			LTTxt[PARM_MAX_SIZE],
			logTxt[PARM_MAX_SIZE];
		wcstombs(inTxt, parm.in, wcslen(parm.in) + 1);
		wcstombs(logTxt, parm.log, wcslen(parm.log) + 1);
		wcstombs(ITTxt, parm.lt, wcslen(parm.lt) + 1);
		wcstombs(LTTxt, parm.it, wcslen(parm.it) + 1);
		*log.stream << "\n----- ��������� --------";
		*log.stream << "\n-in: " << inTxt
			<< "\n-log: " << logTxt
			<< "\n-IT " << ITTxt
			<< "\n-LT " << LTTxt;
	}

	void writeIn(LOG &log, In::IN &in) {//�������� ������
		*log.stream << "\n---- �������� ������ ------";
		*log.stream << "\n���������� ��������: " << std::setw(3) << in.size
			<< "\n���������������: " << std::setw(3) << in.ignor
			<< "\n���������� �����: " << std::setw(3) << in.lines << "\n\n";
	}

	void writeError(std::ofstream *stream, Error::ERROR &e)//������
	{
		flaw = true;
		Error = false;

		if (stream == NULL)  // ������ ���������
		{
			if (e.position.cells == -1 || e.position.line == -1)
				std::cout << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message << std::endl;
			else if (e.position.cells == NULL)
				std::cout << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message
				<< " ������: " << e.position.line << std::endl;
			else
				std::cout << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message
				<< " ������: " << e.position.line
				<< " ������� � ������: " << e.position.cells << std::endl;
			system("pause");
		}
		else
		{
			if (e.position.cells == -1 || e.position.line == -1)
				std::cout << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message << std::endl;
			else if (e.position.cells == NULL)
				std::cout << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message
				<< " ������: " << e.position.line << std::endl;
			else
				std::cout << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message
				<< " ������: " << e.position.line
				<< " ������� � ������: " << e.position.cells << std::endl;

			if (e.position.cells == -1 || e.position.line == -1)
				*stream << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message;
			else if (e.position.cells == NULL)
				*stream << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message
				<< " ������: " << e.position.line;
			else
				*stream << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message
				<< " ������: " << e.position.line
				<< " ������� � ������: " << e.position.cells;
		}
	}

	void writeLexTable(LOG &log, LT::LexTable &Lextable)//������� ������
	{

		*log.stream << "\n---------------������� ������--------------------------------\n" <<
			std::setw(8) << std::left << "������� " <<
			std::setw(9) << std::left << "� ������ " <<
			std::setw(15) << std::left << "� ����. ������ " <<
			std::setw(15) << std::left << "� ����. �����. " << std::endl;

		for (int i = 0; i < Lextable.size; i++)
		{
			*log.stream << std::setw(8) << std::left << Lextable.table[i].lexema <<
				std::setw(9) << std::left << Lextable.table[i].sn;
			*log.stream << std::setw(15) << std::left << i;
			*log.stream << std::setw(15) << std::left;
			if (Lextable.table[i].idxTI != -1)
				*log.stream << Lextable.table[i].idxTI;
			else
				*log.stream << '-';
			*log.stream << std::setw(8) << std::left;
			*log.stream << std::endl;
		}
		*log.stream << "\n\n";
	}

	void writeIDtable(LOG &log, IT::IdTable &IDtable)//������� ���������������
	{
		*log.stream << "\n---------------������� ���������������-------------------------------\n" <<
			std::setw(19) << std::left << "��� �������������� " <<
			std::setw(10) << std::left << "��� ����� " <<
			std::setw(11) << std::left << "��� �������������� " <<
			std::setw(15) << std::left << "� ����. ����. " <<
			std::setw(8) << std::left << "��������" <<
			std::setw(20) << std::left << "	  �-�� ����������(��� �������) " <<
			std::setw(20) << std::left << "	  ���� ����������(��� �������) " <<
			std::endl;

		for (int i = 0; i < IDtable.size; i++)
		{
			*log.stream << std::setw(10) << std::left <<
				std::setw(19) << std::left << IDtable.table[i].id <<
				std::setw(10) << std::left;

			if (IDtable.table[i].iddatatype == IT::NUM)
				*log.stream << NUMBER;
			else
				*log.stream << STRING;

			*log.stream << std::setw(11) << std::left;
			switch (IDtable.table[i].idtype)
			{
			case IT::F:
				*log.stream << "�������             "; break;
			case IT::V:
				*log.stream << "����������          "; break;
			case IT::P:
				*log.stream << "��������            "; break;
			case IT::L:
				*log.stream << "�������             "; break;
			case IT::S:
				*log.stream << "����������� ������� "; break;
			}
			*log.stream << std::setw(15) << std::left << IDtable.table[i].idxfirstLE;
			if (IDtable.table[i].iddatatype == IT::NUM)
			{
				*log.stream << IDtable.table[i].value.vNUM;
			}
			else
			{
				if (IDtable.table[i].value.vSTR.len != 0)
					*log.stream << IDtable.table[i].value.vSTR.str;
				else
					*log.stream << "NULL";
			}
			if (IDtable.table[i].idtype == IT::F && IDtable.table[i].count_parm > 0)
			{
				*log.stream << "	  " << IDtable.table[i].count_parm << "				  ";
				for (int j = 0; j < INT_MAXSIZE_PARM; j++)
				{
					if (IDtable.table[i].parms[j] == 'n')
					{
						*log.stream << "Integer ";
					}
					if (IDtable.table[i].parms[j] == 'w')
					{
						*log.stream << "String ";
					}
				}
			}
			if (IDtable.table[i].idtype == IT::S && IDtable.table[i].count_parm > 0)
			{
				*log.stream << "	  " << IDtable.table[i].count_parm << "				  ";
				for (int j = 0; j < INT_MAXSIZE_PARM; j++)
				{
					if (IDtable.table[i].parms[j] == 'n')
					{
						*log.stream << "Integer ";
					}
					if (IDtable.table[i].parms[j] == 'w')
					{
						*log.stream << "String ";
					}
				}
			}
			else if (IDtable.table[i].idtype == IT::F && IDtable.table[i].count_parm < 0)
			{
				*log.stream << "	  0		  		  0";

			}
			else if (IDtable.table[i].idtype == IT::S && IDtable.table[i].count_parm < 0)
			{
				*log.stream << "	  0   			 	  0";
			}
			*log.stream << std::endl;
		}
		*log.stream << "\n\n";
	}

	void writeLexTableConsole(LOG &log, LT::LexTable &Lextable)//������� ������
	{

		std::cout << "\n---------------������� ������--------------------------------\n" <<
			std::setw(8) << std::left << "������� " <<
			std::setw(9) << std::left << "� ������ " <<
			std::setw(15) << std::left << "� ����. ������ " <<
			std::setw(15) << std::left << "� ����. �����. " << std::endl;

		for (int i = 0; i < Lextable.size; i++)
		{
			std::cout << std::setw(8) << std::left << Lextable.table[i].lexema <<
				std::setw(9) << std::left << Lextable.table[i].sn;
			std::cout << std::setw(15) << std::left << i;
			std::cout << std::setw(15) << std::left;
			if (Lextable.table[i].idxTI != -1)
				std::cout << Lextable.table[i].idxTI;
			else
				std::cout << '-';
			std::cout << std::setw(8) << std::left;
			std::cout << std::endl;
		}
		std::cout << "\n\n";
	}

	void writeIDTableConsole(LOG &log, IT::IdTable &IDtable)//������� ���������������
	{
		std::cout << "\n---------------������� ���������������-------------------------------\n" <<
			std::setw(19) << std::left << "��� �������������� " <<
			std::setw(10) << std::left << "��� ����� " <<
			std::setw(11) << std::left << "��� �������������� " <<
			std::setw(15) << std::left << "� ����. ����. " <<
			std::setw(8) << std::left << "��������" <<
			std::endl;

		for (int i = 0; i < IDtable.size; i++)
		{
			std::cout << std::setw(19) << std::left <<
				std::setw(19) << std::left << IDtable.table[i].id <<
				std::setw(10) << std::left;

			if (IDtable.table[i].iddatatype == IT::NUM)
				std::cout << NUMBER;
			else
				std::cout << STRING;

			std::cout << std::setw(19) << std::left << std::setw(19) << std::left;
			switch (IDtable.table[i].idtype)
			{
			case IT::F:
				std::cout << "�������"; break;
			case IT::V:
				std::cout << "����������"; break;
			case IT::P:
				std::cout << "��������"; break;
			case IT::L:
				std::cout << "�������"; break;
			case IT::S:
				std::cout << "����������� �������"; break;
			}
			std::cout << std::setw(15) << std::left << IDtable.table[i].idxfirstLE;
			if (IDtable.table[i].iddatatype == IT::NUM)
				std::cout << IDtable.table[i].value.vNUM;
			else
			{
				if (IDtable.table[i].value.vSTR.len != 0)
					std::cout << IDtable.table[i].value.vSTR.str;
				else
					std::cout << "NULL";
			}
			std::cout << std::endl;
		}
		std::cout << "\n\n";
	}

	void writeIntermediateCode(LOG &log, LT::LexTable &Lextable)//������ �������
	{
		int pb = NULL;
		char*buffer = new char[1024];
		*log.stream << "\n---------������������� ���------------------------------\n";
		for (int i = 0; i < Lextable.size; i++)
		{
			buffer[pb] = Lextable.table[i].lexema;
			pb++;
			if (Lextable.table[i + 1].sn != Lextable.table[i].sn)
			{
				buffer[pb] = '\0';
				if (Lextable.table[i].sn < 10)
				{
					*log.stream << '0';
				}

				*log.stream << Lextable.table[i].sn << ' ';
				*log.stream << buffer << std::endl;
				pb = NULL;
			}
		}
	}

	void Close(LOG &log)
	{
		(*log.stream).close();
	};
}