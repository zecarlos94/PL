VARS

n;
q;

START

PRINT "Introduza inteiro ";

SCAN n;

q = 1;

while(n > 0)
{
	q *= n;
	n--;
}

PRINT "Factorial de ";
PRINT n;
PRINT " é ";
PRINT q;

END
