Команда make в корне проекта создаст 2 файла в папке bin:

Оба нужно запускать с полномочиями суперпользователя, первым запускается sniffer, он начинает собирать статистику по входящим пакетам, sniffer может принимать опции при запуске со значениями для фильтрации пакетов:

--ipsrc: аргумент - значения ip адреса отправителя

--ipdest: аргумент - значение ip адреса получателя

--portsrc: аргумент - значение порта отправителя

--portdest: аргумент - значение порта получателя

После того, как первый отработает необходимое время нужно запустить representer, он напечатает в стандартный вывод статистику по пакетам. 