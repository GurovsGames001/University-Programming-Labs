int getNumberStringInFile(); // Функция получения номера строки

// Проверка корректности фамилии
template <typename Lines>
bool isCorrectSurname(const Lines& surname, size_t sizeStr)
{
	bool isTrue = false;
	if (('A' <= surname[0]) && ('Z' >= surname[0]))
	{
		if ((sizeStr >= 3) && (sizeStr <= 20))
		{
			isTrue = true;
			for (int i = 1; (i < sizeStr) && (isTrue == true); i++)
			{
				if (!((('a' <= surname[i]) && ('z' >= surname[i])) || ((surname[i] == '-') && (i != sizeStr - 1))))
				{
					isTrue = false;
				}
			}
		}
	}

	return isTrue;
}

// Проверка корректности имени
template <typename Lines>
bool isCorrectName(const Lines& name, size_t sizeStr)
{
	bool isTrue = false;
	if (('A' <= name[0]) && ('Z' >= name[0]))
	{
		if ((sizeStr >= 2) && (sizeStr <= 10))
		{
			isTrue = true;
			for (int i = 1; (i < sizeStr) && (isTrue == true); i++)
			{
				if (!(('a' <= name[i]) && ('z' >= name[i])))
				{
					isTrue = false;
				}
			}
		}
	}

	return isTrue;
}

// Проверка корректности года рождения
template <typename Lines>
bool isCorrectYearBirth(const Lines& yearBirth, size_t sizeStr)
{
	bool isTrue = false;
	if (sizeStr == 4)
	{
		isTrue = true;
		for (int i = 0; (i < sizeStr) && (isTrue == true); i++)
		{
			if (!(('0' <= yearBirth[i]) && ('9' >= yearBirth[i])))
			{
				isTrue = false;
			}
		}
	}

	return isTrue;
}