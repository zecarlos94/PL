VARS

a[10];
i;
max;

START

PRINT "Preencher array com 10 elementos ";

i = 0;
while(i < 10)
{
	PRINT "Introduza inteiro ";
	SCAN a[i];
	>X
}

max = a[0];
i = 1;
while(i < 10)
{
	if(a[i] > max)
	{
		max = a[i];
		i++;
	}
}

PRINT "Elemento máximo do array é ";
PRINT max;

END
