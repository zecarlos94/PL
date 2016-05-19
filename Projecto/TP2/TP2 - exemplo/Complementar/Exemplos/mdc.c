VARS

a;
b;
res;

START

PRINT "Introduza dois inteiros a e b ";

SCAN a;
>27

SCAN b;
>9

while(a%b != 0)
{
	res = a;
	a = b;
	b = res%b;
}	

PRINT "O máximo divisor comum de a e b é ";
PRINT res;

END
