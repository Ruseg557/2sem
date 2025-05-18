Unit lab1UN;

//KADRI-RF A-09-24 Variant 16\\\\\\\

{Цифры в порядке возрастания (0..9)
Латинские строчные в порядке, обратном алфавитному (z..a)
Латинские ЗАГЛАВНЫЕ в исходно заданном порядке}

interface


const
  ALPH_SYMB = '0123456789zyxwvutsrqponmlkjihgfedcbaABCDEFGHIJKLMNOPQRSTUVWXYZ';
  Digits: set of '0'..'9' = ['0'..'9'];
  Symb_Uppercase: set of char = ['A'..'Z'];
  Symb_Lowercase: set of char = ['a'..'z'];
  
function Check1(const s: string): byte;
function Check2(const s: string): byte;
procedure Sort1(var s: string);
procedure Sort2(var s: string);

implementation


function Check1(const s: string): byte;
var
  error_number: byte;
  ind, len: word;

begin
  error_number := 0; len := Length(s);
  if (len = 0) then error_number := 1
  else
    begin
      ind := 1;
      while (ind <= len) and (error_number <> 1) do
      begin
        if not ((s[ind] in Digits) or (s[ind] in Symb_Uppercase) or (s[ind] in Symb_Lowercase)) then error_number:=2;
        Inc(ind);
      end;
    end;
  Check1 := error_number;
end;


function Check2(const s: string): byte;
var
 error_number: byte;
 ind, len: word;

begin
  error_number := 0; len:= Length(s);
  if (len = 0) then error_number := 1
  else
    begin
      ind := 1;
      while (ind <= len) and (error_number <> 1) do
      begin
        if not (Pos(s[ind], ALPH_SYMB)>0) then error_number:=2;
        Inc(ind);
      end;
    end;
  Check2 := error_number;
end;


procedure Sort1(var s: string);
var 
  ind, iter_step, len: word;
  flag: Boolean;
  ch: char;
begin
  iter_step:=1;  len:=length(s);
  repeat
    flag:=true;
    for ind:=1 to len-iter_step do
      if (s[ind] in Symb_Uppercase) and ((s[ind+1] in Digits) or (s[ind+1] in Symb_Lowercase)) or
         (s[ind] in Symb_Lowercase) and (s[ind+1] in Digits) or
         (s[ind] in Digits) and (s[ind+1] in Digits) and (s[ind]>s[ind+1]) or
         (s[ind] in Symb_Lowercase) and (s[ind+1] in Symb_Lowercase) and (s[ind]<s[ind+1])
      then
      begin
        ch:=s[ind]; s[ind]:=s[ind+1]; s[ind+1]:=ch; flag:= false;
      end;
    Inc(iter_step);
  until flag or (iter_step=len);
end; 


Procedure Sort2(var s: string);
var 
  ind, iter_step, len: word;
  flag: Boolean;
  ch: char;
  begin
    iter_step:=1;  len:=length(s);
    repeat
      flag:=true;
      for ind:=1 to len-iter_step do
        if (Pos(s[ind], ALPH_SYMB) > Pos(s[ind+1], ALPH_SYMB))
          and not ((s[ind] in Symb_Uppercase) and (s[ind+1] in Symb_Uppercase))
        then
        begin
          ch:=s[ind]; s[ind]:=s[ind+1]; s[ind+1]:=ch; flag:= false;
        end;
      Inc(iter_step);
    until flag or (iter_step=len);
  End; 
end.