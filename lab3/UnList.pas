unit UnList;

{Kadri RF A-09-24 Variant 16
Двусвязный
По возрастанию длины имени
Псевдослучайных, из массива названий стран
слов – названий стран
Первое название страны, с буквы «А»}

interface

uses UnCountries;

type
  TInfo = string;

  PElem = ^TElem;
  TElem = record
      info: TInfo;  //данные
      next: PElem;  //указатель на следующий элемент
      prev: PElem;  //указатель на предыдущий элемент
  end;

// создать список из одного элемента
procedure CreateList(var ListN, ListK: PElem; r: TInfo);

// добавить новый элемент перед первым
procedure AddFirst(var ListN: PElem; ListK: PElem; r: TInfo);

// добавить новый элемент в конец списка
procedure AddLast(ListN: PElem; var ListK: PElem; r: TInfo);

// добавить новый элемент в середину после ListC (не в конец)
procedure AddMedium(ListN,ListC,ListK: PElem; r: TInfo);

// очистить список
procedure FreeList(var ListN, ListK: PElem);

implementation

// создать список из одного элемента
procedure CreateList(var ListN, ListK: PElem; r: TInfo);
begin
  New(ListN); // выделение памяти
  ListK := ListN; // конец и начало совпадают
  ListN^.info := r; // присвоение данных
  ListN^.next := nil;
  ListN^.prev := nil;
end;

// добавить новый элемент перед первым
procedure AddFirst(var ListN: PElem; ListK: PElem; r: TInfo);
var Elem: PElem;
begin
  new(Elem);
  Elem^.info := r;
  Elem^.next := ListN; // новый элемент указывает на старый
  Elem^.prev := nil; // предыдущго элемента нет
  if ListN <> nil then
    ListN^.prev := Elem; // предыдущий первый (уже второй) указывает на новый 
  ListN := Elem; // теперь он 1-ый
end;


// добавить новый элемент в конец
procedure AddLast(ListN: PElem; var ListK: PElem; r: TInfo);
var Elem: PElem;
begin
  new(Elem);
  Elem^.info := r;
  Elem^.next := nil;
  Elem^.prev := ListK;
  if ListK <> nil then
    ListK^.next := Elem;  
  ListK := Elem; 
end;


// добавить новый элемент в середину после ListC (не в конец)
procedure AddMedium(ListN, ListC, ListK: PElem; r: TInfo);
var Elem: PElem;
begin
  new(Elem);
  Elem^.info := r;
  Elem^.next := ListC^.next; // новый элемент указывает на следующий после ListC
  Elem^.prev := ListC; // новый элемент идет после ListC
  if ListC^.next <> nil then
    ListC^.next^.prev := Elem;  // cледующий элемент теперь указывает на новый
  ListC^.next := Elem;  // ListC теперь указывает на новый элемент
end;

// очистить список
procedure FreeList(var ListN, ListK: PElem);
var Elem: PElem;
begin
  Elem := ListN;
  while Elem <> nil do
  begin
    ListN := ListN^.next; // указатель смещается на следующий элемент
    Dispose(Elem); // освобождаем память текущего элемента
    Elem := ListN; // переходим к следующему элементу
  end;
  ListK := nil; // очищаем указатель на последний элемент
end;

end.
