unit UnVar;

{Kadri RF A-09-24 Variant 16
Двусвязный
По возрастанию длины имени
Псевдослучайных, из массива названий стран
слов – названий стран
Первое название страны, с буквы «А»}

interface

uses UnList;  // описание типа и все процедуры

var 
  NachaloSpiska, KonecSpiska: PElem; // начало и конец списка

implementation
  // пусто

initialization
  NachaloSpiska:=nil;  // инициализация переменных
  KonecSpiska:=nil;
finalization
  FreeList(NachaloSpiska, KonecSpiska);  // освобождение памяти
end.
