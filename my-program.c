#include<stdio.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
char cur; // ��ǰ����ȥ���ַ�
char token[100]; // ��ŵ��ʵ��ַ���
int num; // ��ǰ�����������ֵ
enum symbolList {
	BEGINSY=1, 	// BEIGIN
	ENDSY, 		// 2 END
	FORSY, 		// 3 FOR
	DOSY, 		// 4 DO
	IFSY, 		// 5 IF
	THENSY, 	// 6 THEN
	ELSESY, 	// 7 ELSE
	IDSY, 		// 8 ��ʶ�� 
	INTSY, 		// 9 ���������� 
	COLONSY, 	// 10 ð�� 
	PLUSSY, 	// 11 �Ӻ�
	STARSY, 	// 12 �Ǻ�
	COMSY, 		// 13 , 
	LPARSY, 	// 14 (
	RPARSY, 	// 15 )
	ASSIGNSY, 	// 16 := 
	MINUSSY,    // 17 ����
	SEMISY,		// 18 �ֺ�
	DIVSY,		// 19 ���� 
} symbol;

FILE * in; // �ļ�ָ��
int flag = 0; // ���˱�� 

/* ����һ���ַ�  */
void getChar() {
	if (!flag) {
		cur = fgetc(in);
	}
	flag = 0;
}

/* �����ַ�ָ�����һ�� */
void retract() {
	flag = 1;
}

/* ���token */
void clearToken() {
	memset(token, 0, strlen(token));
}

/* �����ж� */ 
int isSpace() {
	return cur == ' ' || cur == '\r';
}

int isNewline() {
	return cur == '\n';
}

int isTab() {
	return cur == '\t';
}

int isLetter() {
	return cur >= 'a' && cur <= 'z' || 
			cur >= 'A' && cur <= 'Z';
}

int isDigit() {
	return cur >= '0' && cur <= '9';
}

int isColon() {
	return cur == ':';
}

int isComma() {
	return cur == ',';
}

int isSemi() {
	return cur == ';';
}

int isEqu() {
	return cur == '=';
}

int isPlus() {
	return cur == '+';
}

int isMinus() {
	return cur == '-';
}

int isDivi() {
	return cur == '/';
}

/* �ж��Ǻ�* */
int isStar() {
	return cur == '*';
}

/* �ж��ǲ�����������() */
int isLpar() {
	return cur == '(';
}

int isRpar() {
	return cur == ')';
}

/* ��char�е�������token�ַ���ƴ�� */
void catToken() {
	int l = strlen(token);
	token[l] = cur;
}

/* ���ұ����֣����ر����ֵ�����룬0��ʾ��ʶ�� */
enum symbolList reserver() {
	if (strcmp(token,"BEGIN") == 0)
		return BEGINSY;
	else if (strcmp(token,"END") == 0)
		return ENDSY;
	else if (strcmp(token,"FOR") == 0)
		return FORSY;
	else if (strcmp(token,"IF") == 0)
		return IFSY;
	else if (strcmp(token,"THEN") == 0)
		return THENSY;
	else if (strcmp(token,"ELSE") == 0)
		return ELSESY;
	else
		return IDSY;
}

/* ��token�е��ַ���ת��Ϊ���� */
long long transNum() {
	long long ans = 0;
	int i;
	for (i=0; i<strlen(token); i++) {
		ans = ans * 10 + (token[i] - '0');
	}
	return ans;
}

/* ������ */
void error() {
	printf("ERROR!SOMETING WRONG HAPPEN\n");
}

/* �ʷ�������� */
int getsym()
{
	clearToken();
	while(isSpace() || isNewline() || isTab())	
		getChar();
	if (isLetter()) {
		while(isLetter() || isDigit()) {
			catToken();
			getChar();
		}
		retract();
		enum symbolList resultValue = reserver();
		symbol = resultValue;
	}
	else if (isDigit()) {
		while(isDigit()) {
			catToken();
			getChar();
		}
		retract();
		num = transNum();
		symbol = INTSY;
	}
	else if (isColon()) {
		getChar();
		if (isEqu()) 
			symbol = ASSIGNSY;
		else {
			retract();
			symbol = COLONSY;
		}
	}
	else if (isPlus()) symbol = PLUSSY;
	// else if (isMinus()) symbol = MINUSSY;
	else if (isStar()) symbol = STARSY;
	else if (isLpar()) symbol = LPARSY;
	else if (isRpar()) symbol = RPARSY;
	else if (isComma()) symbol = COMSY;
	// else if (isSemi()) symbol = SEMISY;
	else if (isDivi()) {
		getChar();
		if (isStar())
		{
			do {
				do {
					getChar();
				} while (!isStar());
				do {
					getChar();
					if (isDivi())
						return 0;
				} while(isStar());
			} while(!isStar());
		}
		symbol = DIVSY; // ������������� 
		retract();	
	}
	// else error();
	else return 1;
	return 0;
} 

int main(int argc,char *argv[]) {
	in = fopen(argv[1],"r");
	// in = fopen("test.txt","r");
	while(1) {
		getChar();
		if (cur == EOF)
			break;
		if (getsym() == 0) {
			switch(symbol) {
				case BEGINSY:
					printf("Begin\n");
					break;
				case ENDSY:
					printf("End\n");
					break;
				case FORSY:
					printf("For\n");
					break;
				case IFSY:
					printf("If\n");
					break;
				case THENSY:
					printf("Then\n");
					break;
				case ELSESY:
					printf("Else\n");
					break;
				case IDSY:
					printf("Ident(%s)\n",token);
					break;
				case INTSY:
					printf("Int(%d)\n",num);
					break;
				case COLONSY:
					printf("Colon\n");
					break;
				case PLUSSY:
					printf("Plus\n");
					break;
				case STARSY:
					printf("Star\n");
					break;
				case COMSY:
					printf("Comma\n");
					break;
				case LPARSY:
					printf("LParenthesis\n");
					break;
				case RPARSY:
					printf("RParenthesis\n");
					break;
				case ASSIGNSY:
					printf("Assign\n");
					break;
			}
		}
		else {
			printf("Unknown\n");
			break;
		}
		//	printf("%s,symbol=%d\n",token,symbol);
	}
}
