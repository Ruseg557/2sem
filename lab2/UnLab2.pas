Unit  UnLab2; 

{Kadri RF A-09-24 Variant 16
Существо (вампир, оборотень и т.д.)
Имя
Дата рождения

Найти: Первую запись о выбранном существе с именем на букву М

Переставить: С k-ой записью файла}

Interface

Type
  entityTypeID = (Vampire, Werewolf, Zombie, Elf, Gnome, Human); 
  Entity = record
    entity_type: entityTypeID;
    name: string[30];
    Bday: record
      D, M, Y: string[4];
    end;
  end;


Procedure CreateTypedFile1();

Procedure CreateTypedFile2();

Procedure ViewFile();

procedure FindM();

Implementation 

Procedure CreateTypedFile1(); //диалог
var
  Ent: Entity;
  fr: file of Entity;
  n, count: integer;
  choice: char;
  FileName:string[80];
begin
  
  writeln('Введите имя типизированного файла');
  readln(FileName);

  AssignFile(fr, FileName);
  Try  ReWrite(fr); 
  Except
    writeln('Error: не удалось создать типизированный файл ',FileName);
    write('Press ENTER'); readln;  exit
  end;

  count:=0;
  repeat
    write('Номер типа сущности? (ID) (0-5) = '); readln(n); Ent.entity_type := entityTypeID(n);
    write('Имя сущности = '); readln(Ent.name);
    writeln('Дата рождения существа:');
    write('День = ');   readln(Ent.Bday.D);
    write('Месяц = ');  readln(Ent.Bday.M);
    write('Год = ');    readln(Ent.Bday.Y);

    write(fr, Ent);
    inc(count);

    write('Ещё сущность? (y/n)');
    readln(choice)
  until UpCase(choice)='N';

  CloseFile(fr);

  writeln('Создан типизированный файл из ',count,' записей');
  write('Press ENTER');
  readln;
end;


Procedure CreateTypedFile2(); //из текстового
var
  
  Ent: Entity;
  fr: file of Entity;
  ft: TextFile;
  n, count: integer;
  choice: char;
  FileName:string[80];
begin
  if ParamCount<1 then
  begin
    writeln('Мало параметров '#13#10'Press enter');
    readln;  exit
  end;

  writeln('Введите имя выходного текстового файла');
  readln(FileName); 

  AssignFile(fr, FileName);
    Try  Rewrite(fr); 
  Except
    writeln('Error: не удалось создать типизированный файл ',FileName);
    write('Press ENTER'); readln;  exit
  end;
  
  AssignFile(ft, ParamStr(1));
    Try  Reset(ft);
  Except
    writeln('Error: не удалось открыть текстовый файл ',Paramstr(1));
    write('Press ENTER'); readln;  exit
  end;

  count:=0;
  while not eof(ft) do
  begin
    readln(ft, n); Ent.entity_type := entityTypeID(n);
    readln(ft, Ent.name);
    readln(ft, Ent.Bday.D);
    readln(ft, Ent.Bday.M);
    readln(ft, Ent.Bday.Y);

    write(fr, Ent);
    inc(count);
  end;
  
  CloseFile(ft);
  CloseFile(fr);

  writeln('Создан типизированный файл из ',count,' записей');
  write('Press ENTER');
  readln;
end;


Procedure ViewFile();
var
  Ent: Entity;
  fr: file of Entity;
  n, count: integer;
  buffer: Entity;
  FileName:string[80];
begin
  writeln('Введите имя типизированного файла');
  readln(FileName); 

  AssignFile(fr, FileName);
  Try  reset(fr);
  Except
    writeln('Error: не удалось открыть типизированный файл ',FileName);
    write('Press ENTER'); readln;  exit
  end;

  count:=0;
  while not eof(fr) do
  begin
    read(fr, Ent); // считывание

    writeln('Найден ', Ent.entity_type, ' ', Ent.name,
      ' Дата рождения: ', Ent.Bday.D, '\', Ent.Bday.M, '\', Ent.Bday.Y);
      inc(count);
  end;

  if count=0 then
    writeln('Данные не найдены')
  else
    writeln('Найдено ',count, ' записей');

  CloseFile(fr);

  write('Press ENTER');  readln;
end;

Procedure FindM();
var
  Ent: Entity;
  fr: file of Entity;
  n, k: integer;
  IDentityType: integer;
  isFound: boolean;
  buffer: Entity;
  FileName:string[80];
begin
  writeln('Введите имя типизированного файла');
  readln(FileName); 
  
  AssignFile(fr, FileName);
  Try  ReSet(fr);
  Except
    writeln('Error: не удалось открыть типизированный файл ',FileName);
    write('Press ENTER'); readln;  exit
  end;
  
  
  isFound := False;
  
  if not eof(fr) then 
  begin
    writeln('Введите тип существа'); writeln('-----------------------');
    writeln('0 - Вампир'); writeln('1 - Оборотень'); writeln('2 - Зомби');
    writeln('3 - Эльф'); writeln('4 - Гном'); writeln('5 - Человек'); 
    writeln('-----------------------'); writeln('Ваш выбор? '); readln(IDentityType);
    while not eof(fr) and (not isFound) do
    begin
      read(fr, Ent); 
        
      if (((UpperCase(Ent.name[1]) = 'M') or (UpperCase(Ent.name[1]) = 'М')) and (Ent.entity_type = entityTypeID(IDentityType))) then  
      begin
        writeln('Найден ', Ent.entity_type, ' ', Ent.name,
        ' Дата рождения: ', Ent.Bday.D, '\', Ent.Bday.M, '\', Ent.Bday.Y);
        isFound := True;
  
        n := FilePos(fr); 
        
        writeln('Введите k (Найденная по условию запись будет переставлена с k-ой записью)');
        readln(k);
        if (k < 1) or (k > FileSize(fr)) then begin 
          writeln('Error: такого номера k не существует');
          write('Press ENTER'); readln; closefile(fr); exit; end;
        
        if (n <> k) then
        begin
          seek(fr, k - 1);
          read(fr, buffer);
    
          seek(fr, n - 1);
          write(fr, buffer);
    
          seek(fr, k - 1);
          write(fr, Ent);
          
          writeln('В файле запись номер ', n, ' поменена местами с записью номер ', k);
        end
        else writeln('Перестановок нет, так как найденная запись и так имеет k-ый номер');
      end;
    end;
   end;  
  if isFound = False then
    writeln('Данные, соответствующие запросу, не найдены');

  CloseFile(fr);

  write('Press ENTER');  readln;
  end;
End.