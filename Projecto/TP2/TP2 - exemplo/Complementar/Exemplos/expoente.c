VARS

a;
b;
exp;

START

PRINT "Introduza base e expoente: ";

SCAN a;
>2

SCAN b;
>3

exp = 1;

while(b > 0)
{
	exp = exp * a;
	b = b - 1;
}

PRINT "Resultado é ";
PRINT exp;

END
