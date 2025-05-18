program Lab3;

{Kadri RF A-09-24 Variant 16
C1 Двусвязный
C2 По возрастанию длины имени
C3 Псевдослучайных, из массива названий стран
C4 Слов – названий стран
C5 Первое название страны, с буквы «А»}

uses
  UnList in 'UnList.pas',   // подключаем модули с типами и процедурами, а затем и с переменными
  UnVar in 'UnVar.pas',
  UnCountries in 'UnCountries.pas'; // подключаем массив стран

// добавить элемент со значением R в соответствии с заданным порядком в список
procedure AddR(var ListN, ListK: PElem; r: TInfo); // адреса начала и конца списка и R
var ListC: PElem;  // текущий элемент списка
begin
  if ListN = nil then 
    CreateList(ListN, ListK, r)  // если список пуст
  else
  if length(r) <= length(ListN^.info) then AddFirst(ListN, ListK, r)  // добавить в начало
    else
       if length(r) >= length(ListK^.info) then AddLast(ListN, ListK, r)  // добавить в конец
       else
         begin // найти после какого
           ListC:=ListN; // с начала списка
           while length(ListC^.next^.info) <= length(r) do
             ListC := ListC^.next;
           AddMedium(ListN, ListC, ListK, r)  // добавить после текущего
         end;

end; 

//  "Добавить N псевдослучайных стран" в текущий список
procedure AddN;
var n,i: integer; s:string; r: TInfo;
begin
  write('Сколько N =? '); readln(s);
  if TryStrToInt(s,n) then
  begin
    for i:=1 to n do
    begin
      r:= CountryID[Random(191)];
      AddR(NachaloSpiska, KonecSpiska, r);
    end;
  end
  else begin
    writeln('Неккоректное значение. Введите целое число');
    write('Press ENTER'); readln; end;
end;

// Добавление всех данных из текстового файла в текущий список
procedure AddFromTextFile;
var
  f: TextFile;
  r: TInfo;
  f_name, id: string;
begin
    writeln('Введите название текстового файла (с расширением): ');
    read(f_name);
    AssignFile(f, f_name);
    try
      Reset(f);
      try
        try
            while not eof(f) do
            begin
              readln(f, id);
              if id in CountryID then r := id
              else r := CountryID[StrToInt(id)];
              AddR(NachaloSpiska, KonecSpiska,r);
            end;
            writeln('Список создан');
        except
         writeln('Некорректные данные в текстовом файле '+ f_name);
        end;
      finally
        CloseFile(f);
      end;
    except
      writeln('Не удалось открыть текстовый файл '+ f_name);
  end;
  readln();
end;

// Добавить один элемент  в текущий список
procedure Add1;
var
  r: TInfo;
  id: string;
  i: integer;
begin
 try
  write('Введите ID страны, либо её название. Или help для помощи: '); readln(id); 
  if LowerCase(id) = 'help' then
  begin
    for i := 0 to 190 do writeln(i,' = ', CountryID[i]);
    write('Введите ID страны = '); readln(id);
  end;
  if id in CountryID then r := id
  else r := CountryID[StrToInt(id)];
  AddR(NachaloSpiska, KonecSpiska, r);
 except
    writeln('Некорректное ID или ошибка добавления (ID принадлежат [0,190])');
 end;
end;

// "Найти в списке"
procedure SearchIt;
var
  ListC: PElem;
  IsFound: boolean;
begin
  IsFound := False;
  ListC := NachaloSpiska;
  while ((ListC <> nil) and (not IsFound)) do   
  begin
    if UpperCase(ListC^.info[1]) = 'A' then
    begin
      IsFound := True;
      writeln('Найдена страна ', ListC^.info); 
    end;
    ListC:=ListC^.next;
  end;
  if not IsFound then writeln('Страна, начинающаяся на букву "A" не найдена.');
end;

//  "Что сейчас в списке?" - вывод на экран консоли
procedure ViewList;
var
  ListC: PElem;
begin
  writeln('Список:');
  ListC := NachaloSpiska;
  if ListC = nil then writeln('Пустой')
  else
  begin
    writeln('От начала к концу:');
    while ListC <> nil do
    begin
      writeln(ListC^.info);
      ListC := ListC^.next;
    end;
    
    writeln();
    
    writeln('От конца к началу:');
    ListC := KonecSpiska;
    while ListC <> nil do
    begin
      writeln(ListC^.info);
      ListC := ListC^.prev;
    end;
  end;
  writeln(); writeln('PRESS ENTER'); readln();
end;

//--------------------главная программа-------------------------
var
  ch: char;
begin

{ Для того, чтобы каждый раз при запуске программы генерировалась
  НОВАЯ последовательность псевдослучайных чисел.
  Одна и та же последовательность удобна для отладки программы. }
  Randomize;

  repeat
    writeln('--------------------------------------');
    writeln('Q - добавить в список из текстового файла; ');
    writeln('W - сгенерировать и добавить в список; ');
    writeln('A - добавить в список; ');
    writeln('F - найти в списке;');
    writeln('T - удалить(очистить) список;');
    writeln('V - просмотр;');
    writeln('E - конец.');
    write('Ваш выбор?'); readln(ch);
    writeln('--------------------------------------');

    ch:= UpCase(ch);
    case ch of
//----------создать список из текстового файла------------------
    'Q': AddFromTextFile;
      
//----------сгенерировать список -------------------------------
    'W': AddN;
    
//----------добавить в список ----------------------------------
    'A': Add1;
    
//-----------поиск----------------------------------------------
    'F': SearchIt;
    
//-----------освобождение памяти--------------------------------
    'T': FreeList(NachaloSpiska, KonecSpiska);
    
//-----------просмотр----------------------------------------------
    'V': ViewList;
    
//-----------выход----------------------------------------------
    'E': exit;
//--------------------------------------------------------------
      
      else
        begin
          writeln('Нет такой команды');
          write('Press ENTER'); readln;
        end;
    end;

  until ch='E';
end.