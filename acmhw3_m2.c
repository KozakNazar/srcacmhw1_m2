/*************************************************************************
* N.Kozak // Lviv'2020 // ACM // DFA for input string example (method 2) *
*    file: acmhw3.c                                                      *
**************************************************************************/
#include "stdio.h"

#define DECLSTATE(NAME, ...) typedef enum {__VA_ARGS__, size##NAME} NAME;
#define GET_ENUM_SIZE(NAME) size##NAME

DECLSTATE(A,
	vA/*A*/,
	vB/*B*/,
	vC/*C*/,
	vD/*D*/,
	vE/*E*/,
	vF/*F*/,
	vG/*G*/,
	vH/*H*/,
	vI/*I*/,
	vJ/*J*/,
	vK/*K*/,
	vL/*L*/,
	vM/*M*/,
	vN/*N*/,
	vO/*O*/,
	vP/*P*/,
	vQ/*Q*/,
	vR/*R*/,
	vS/*S*/,
	vT/*T*/,
	vU/*U*/,
	vV/*V*/,
	vW/*W*/,
	vX/*X*/,
	vY/*Y*/,
	vZ/*Z*/,
	sZ/*[*/,
	sY/*\*/,
	sC/*]*/,
	sH/*^*/,
	sB/*_*/,
	sT/*`*/,
	va/*a*/,
	vb/*b*/,
	vc/*c*/,
	vd/*d*/,
	ve/*e*/,
	vf/*f*/,
	vg/*g*/,
	vh/*h*/,
	vi/*i*/,
	vj/*j*/,
	vk/*k*/,
	vl/*l*/,
	vm/*m*/,
	vn/*n*/,
	vo/*o*/,
	vp/*p*/,
	vq/*q*/,
	vr/*r*/,
	vs/*s*/,
	vt/*t*/,
	vu/*u*/,
	vv/*v*/,
	vw/*w*/,
	vx/*x*/,
	vy/*y*/,
	vz/*z*/,
	sF/*end mark*/
	)

	DECLSTATE(Q,
	q0,
	q1,
	q2,
	q3,
	q4,
	qf
	)

typedef unsigned char INSTRUCTION;
#define MAX_RULE_COUNT 16
typedef struct {
	unsigned char input;
	INSTRUCTION toState;
} SimpleRule;
typedef SimpleRule PROGRAM[GET_ENUM_SIZE(Q)][MAX_RULE_COUNT];

#define DEFAULT GET_ENUM_SIZE(A)

PROGRAM program = {
	//          q0                               q1                               q2                               q3                               q4                            qf
	{ { vK, q1 }, { DEFAULT, q0 } }, { { vo, q2 }, { DEFAULT, q0 } }, { { vz, q3 }, { DEFAULT, q0 } }, { { va, q4 }, { DEFAULT, q0 } }, { { vk, qf }, { DEFAULT, q0 } }, { { DEFAULT, qf } },
};

typedef struct structDFA{
	unsigned char * data;
	PROGRAM * program;
	void(*run)(struct structDFA * dfa);
	Q state;
} DFA;

void runner(DFA * dfa){
	for (; *dfa->data != sF; ++dfa->data){
		SimpleRule *prevRule, *rule;
		for (prevRule = rule = (*dfa->program)[dfa->state]; prevRule->input != DEFAULT; prevRule = rule, ++rule){
			if (DEFAULT == rule->input){
				dfa->state = rule->toState;
				break;
			}
			else if (*dfa->data == rule->input){
				dfa->state = rule->toState;
				break;
			}
		}
	}
}

#define MAX_TEXT_SIZE 256
int main(){
	unsigned char data[MAX_TEXT_SIZE] = "Kozak Nazar Bohdanovych", *data_ = data;
	DFA dfa = { data, (PROGRAM*)program, runner, q0 };

	for (; *data_; *data_ -= 'A', *data_ %= GET_ENUM_SIZE(A), ++data_);
	*data_ = sF;
	dfa.run(&dfa);

	if (dfa.state == qf){
		printf("DFA: finit state\r\n");
	}
	else{
		printf("DFA: no finit state\r\n");
	}

	getchar();
	return 0;
}