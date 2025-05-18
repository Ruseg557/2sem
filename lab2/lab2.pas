program Lab2; 

{Kadri RF A-09-24 Variant 16
Существо (вампир, оборотень и т.д.)
Имя
Дата рождения

Найти: Первую запись о выбранном существе с именем на букву М

Переставить: С k-ой записью файла}

uses
  UnLab2;

var
  choice: char;
begin
  repeat
    writeln('--------------------------------------');
    writeln('D - создать новый тип.файл в диалоге; ');
    writeln('N - создать из текстового файла; ');
    writeln('F - поиск и изменение; ');
    writeln('V - просмотр;');
    writeln('E - конец.');
    write('Ваш выбор? '); readln(choice);
    writeln('--------------------------------------');

    choice:= UpCase(choice);  
    case choice of
    'D': CreateTypedFile1;  // диалог
    'N': CreateTypedFile2;  // из текстового
    'F': FindM;
    'V': ViewFile;
    'E': exit;

      else
        begin
          writeln('Нет такой команды');
          write('Press ENTER'); readln;
        end;
    end;

  until choice='E';
end.
