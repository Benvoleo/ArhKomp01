#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define CONST 2
#define VAR 9
long a, b, left_res, right_res, a1, b1, left_resC, right_resC, tempo;
int C_err_L, err_OF_a;

long int check()
{
	char start[80], * end;
	gets_s(start);
	if (strpbrk(start, "0123456789"))
		return strtol(start, &end, 10);
	else
		printf("ERROR input \n");
		exit(3);

}
int main() {
	while (1) {

		printf("\nEnter a: ");
	//	scanf_s("%li", &a);
		a = check();
		printf("Enter b: ");
	//	scanf_s("%li", &b);
		b = check();
		C_err_L = 0;
		a1 = a / 9;
		b1 = b / 9;

	__asm {
		// a* a + b * b = (a - b) ^ 2 + 2ab
		mov		err_OF_a, 0

		//получаем а, согласно варианту (а/9)
		mov		ebx, VAR
		mov		eax, a
		cdq
		idiv	ebx
		mov		esi, eax;	esi = a / VAR
		//получаем б, согласно варианту (б/9)
		mov		ebx, VAR
		mov		eax, b
		cdq
		idiv	ebx
		mov		edi, eax;	edi =	 b / VAR

		//вычисляем левую сторону (a* a + b * b)
		imul	esi, esi
		imul	edi, edi
		add		esi, edi
		mov		left_res, esi
		jno		L1 //OF = 0
		mov		err_OF_a, 1//если переполнение, изменяем перемен. ошибки и заканчиваем
		jmp		End


		L1 :
		// право(ч1)
			//получаем а, согласно варианту (а/9)
			mov		ebx, VAR
			mov		eax, a
			cdq
			idiv	ebx
			mov		esi, eax;	esi = a / VAR
			//получаем б, согласно варианту (б/9)
			mov		ebx, VAR
			mov		eax, b
			cdq
			idiv	ebx
			mov		edi, eax;	edi = b / VAR
			//(a - b) ^ 2
			sub		esi, edi
			imul	esi, esi
			mov		tempo, esi//заносим результат во временній аккумулятор
			jno		L2
			mov		err_OF_a, 1
			jmp		End


		L2 :
			//право(ч2)
			//получаем а, согласно варианту (а/9)
			mov		ebx, VAR
			mov		eax, a
			cdq
			idiv	ebx
			mov		esi, eax;	esi = a / VAR
			//получаем б, согласно варианту (б/9)
			mov		ebx, VAR
			mov		eax, b
			cdq
			idiv	ebx
			mov		edi, eax;	edi = b / VAR
			//2ab
			imul	esi, CONST
			imul	esi, edi
			//Обьединение промежуточных результатов вычислений правой стороны
			add		esi, tempo

			//конец выполнения кода Ассемблера
			End :
			mov		right_res, esi

	}


		left_resC = (a1 * a1) + (b1 * b1);		//проверка
		right_resC = (a1 - b1) * (a1 - b1) + 2 * a1 * b1;		//проверка



		if (err_OF_a != 1) {

			printf("\n	(a*a)+(b*b) = (a-b)^2+2*a*b \n");//выв
			printf("	(%li*%li)+(%li*%li) = (%li-%li)^2+2*%li*%li \n", a1, a1, b1, b1, a1, b1, a1, b1);//выв

			printf("\nLEVO\n Ci: %li  \n Assem: %li  \n", left_resC, left_res);
			printf("\nPRAVO\n Ci: %li \n Assem: %li \n\n\n", right_resC, right_res);
			}
		else
			printf("\n\t######################Error overflow######################\n");



	}
	return 0;
}
