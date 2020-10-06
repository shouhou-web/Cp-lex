#include<stdio.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
char cur; // 当前读进去的字符
char token[100]; // 存放单词的字符串
int num; // 当前读入的整型数值
enum symbolList {
	BEGINSY=1, 	// BEIGIN
	ENDSY, 		// 2 END
	FORSY, 		// 3 FOR
	DOSY, 		// 4 DO
	IFSY, 		// 5 IF
	THENSY, 	// 6 THEN
	ELSESY, 	// 7 ELSE
	IDSY, 		// 8 标识符 
	INTSY, 		// 9 常数（整） 
	COLONSY, 	// 10 冒号 
	PLUSSY, 	// 11 加号
	STARSY, 	// 12 星号
	COMSY, 		// 13 , 
	LPARSY, 	// 14 (
	RPARSY, 	// 15 )
	ASSIGNSY, 	// 16 := 
	MINUSSY,    // 17 减号
	SEMISY,		// 18 分号
	DIVSY,		// 19 除号 
} symbol;

FILE * in; // 文件指针
int flag = 0; // 回退标记 

/* 读入一个字符  */
void getChar() {
	if (!flag) {
		cur = fgetc(in);
	}
	flag = 0;
}

/* 将读字符指针后退一个 */
void retract() {
	flag = 1;
}

/* 清空token */
void clearToken() {
	memset(token, 0, strlen(token));
}

/* 几种判断 */ 
int isSpace() {
	return cur == ' ';
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

/* 判断星号* */
int isStar() {
	return cur == '*';
}

/* 判断是不是左右括号() */
int isLpar() {
	return cur == '(';
}

int isRpar() {
	return cur == ')';
}

/* 将char中的数据与token字符串拼接 */
void catToken() {
	int l = strlen(token);
	token[l] = cur;
}

/* 查找保留字：返回保留字的类编码，0表示标识符 */
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

/* 将token中的字符串转换为整型 */
long long transNum() {
	long long ans = 0;
	for (int i=0; i<strlen(token); i++) {
		ans = ans * 10 + (token[i] - '0');
	}
	return ans;
}

/* 错误处理 */
void error() {
	printf("ERROR!SOMETING WRONG HAPPEN\n");
}

/* 词法处理程序 */
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
	else if (isMinus()) symbol = MINUSSY;
	else if (isStar()) symbol = STARSY;
	else if (isLpar()) symbol = LPARSY;
	else if (isRpar()) symbol = RPARSY;
	else if (isComma()) symbol = COMSY;
	else if (isSemi()) symbol = SEMISY;
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
		symbol = DIVSY;
		retract();	
	}
	else error();
	return 0;
} 

int main() {
	in = fopen("test.txt","r");
	int n = 10;
	while(cur != EOF) {
		getChar();
		getsym();
		printf("%s,symbol=%d\n",token,symbol);
	}
}
