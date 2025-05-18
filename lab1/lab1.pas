Program Lab1;

//KADRI-RF A-09-24 Variant 16

{Цифры в порядке возрастания (0..9)
Латинские строчные в порядке, обратном алфавитному (z..a)
Латинские ЗАГЛАВНЫЕ в исходно заданном порядке}

Uses lab1UN;

var 
	S, S1, S2: string;
	error_num: Byte;

begin
  Writeln('Введите строку');
  readln(S); 

  S1:=Copy(S, 1, Length(S)); S2:=Copy(S, 1, Length(S)); 


  Writeln(#13#10, 'Строка до сортировки:'#13#10'"',S1,'"');
  error_num := Check1(s1);
  Case error_num of
    1: writeln('Пустая строка');
    2: writeln('Некорректные символы');
  else
    begin
      Sort1(s1);
      Writeln('Отсортированная строка 1 (со сложным условием обмена)'#13#10, S1);
    end;
  End;
  
  Writeln(#13#10, 'Строка до сортировки:'#13#10'"',S2,'"');
  Case error_num of
    1: writeln('Пустая строка');
    2: writeln('Некорректные символы');
  else
    begin
      Sort2(s2);
      Writeln('Отсортированная строка 2 (со своей таблицей символов)'#13#10, S2);
    end;
  end;
End.