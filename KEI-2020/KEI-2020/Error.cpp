#include "stdafx.h"
#include "Error.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "������������ ��� ������"),		//��� ������ ��� ��������� 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "��������� ����"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY_NODEF(5), ERROR_ENTRY_NODEF(6),
		ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "�������� -in ������ ���� �����"),//������ �������� ����
		ERROR_ENTRY_NODEF(101),
		ERROR_ENTRY_NODEF(102),
		ERROR_ENTRY(103, "��������� ������������ ���������� ���������� ��� ������ �������"),//lexanalize
		ERROR_ENTRY(104, "��������� ����� �������� ���������"),//parm
		ERROR_ENTRY(105, "�������� ������������ ������ ��������"),//in
		ERROR_ENTRY(106, "��� ���������� ������"),//lexanalize
		ERROR_ENTRY(107, "������� ���������������"),//lezanalize
		ERROR_ENTRY(108, "���������� ��������������� �����������"),//lexanalize
		ERROR_ENTRY(109, "��� ����������� �������"),//in
		ERROR_ENTRY(110, "������ ��� �������� ����� � �������� �����(-in)"),//in
		ERROR_ENTRY(111, "������������ ������ � �������� ����� (-in)"),//in
		ERROR_ENTRY(112, "������ ��� �������� ����� ���������(-log)"),
		ERROR_ENTRY(113),
		ERROR_ENTRY(114, "�������������� �����"),//
		ERROR_ENTRY(115, "��������� ����������� �������� �������"),//lexanalize
		ERROR_ENTRY(116),
		ERROR_ENTRY(117, "�������� ������ ������� ������"),//lt
		ERROR_ENTRY(118, "������������� �������� ��������"),//lexanalize
		ERROR_ENTRY(119, "���������� ���������� ��� ���������� �����������"),//lezanalize
		ERROR_ENTRY_NODEF10(120),ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300),
		ERROR_ENTRY(400, "����� ����� main() �� �������"),//lexanalize �� ����� ��������
		ERROR_ENTRY(401, "������� �������������� �����"),//lexanalize
		ERROR_ENTRY(402, "������������� ����������� ������� ��� ����������� ����������� ����������"),//lexanalize
		ERROR_ENTRY(403, "���������� ����� ����� ����������� ����������"),//lexanalize
		ERROR_ENTRY(404, "������� ���������� �������� �� ��������� ����� ������"),//lexanalize
		ERROR_ENTRY(405, "��� ������������� �������� � ��� ������� �� �������������"),//lexanalize
		ERROR_ENTRY(406, "������������ ���������� ���������� ��� ������ �������"),//lexanalize
		ERROR_ENTRY(407, "������������ ��� ���������� ��� ������ �������"),//lexanalize
		ERROR_ENTRY(408, "�������������� �����"),//-
		ERROR_ENTRY(409, "������������ ����� �������"),//lexanalize
		ERROR_ENTRY_NODEF10(410),ERROR_ENTRY_NODEF10(420),ERROR_ENTRY_NODEF10(430), ERROR_ENTRY_NODEF10(440),
		ERROR_ENTRY_NODEF10(450),ERROR_ENTRY_NODEF10(460), ERROR_ENTRY_NODEF10(470), ERROR_ENTRY_NODEF10(480),
		ERROR_ENTRY_NODEF10(490),
		ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "�������� ��������� ���������"),//grb? �� ����� ���������
		ERROR_ENTRY(601, "������ � ���������� ������� "),
		ERROR_ENTRY(602, "��������� ��������"),
		ERROR_ENTRY(603, "������ � ���������"),
		ERROR_ENTRY(604, "������ � ���������� ���������� �������"),
		ERROR_ENTRY(605, "������ � ���������� ���������"),//lexanalize
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800)
	};


	ERROR GetError(int id)
	{
		if (id < 0 || id > ERROR_MAX_ENTRY)
			return errors[0];
		else
			return errors[id];
	}

	ERROR GetError(int id, int line, int cells)
	{
		ERROR dopError = GetError(id);
		dopError.position.cells = cells;
		dopError.position.line = line;
		return dopError;
	}
}