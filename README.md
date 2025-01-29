# Task1328C
Тестовое задание для ООО "Агродинамика"

# Сборка
Если проект собирается под Windows, то необходимо сначала установить компялтор MinGW
и настроить проект. Для настройки проекта необходимо выполнить в командной строке в папке проекта

	cmake -G "MinGW Makefiles"
	
Для сборки проекта необходимо выполнить в командной строке в папке проекта

    cmake --build .

# Тестирование
Для тестирования проекта необходимо выполнить в командной строке в папке проекта

	ctest

