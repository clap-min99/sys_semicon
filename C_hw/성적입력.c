#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

int main() {
	int kor, eng, math, total;
	double avg;

	while (1) {
		printf("성적을 입력하시오\n");
		printf("국어(종료:0)): ");
		scanf("%d", &kor);
		if (kor == 0) {
			printf("프로그램이 종료되었습니다. !!!!!\n");
			break;
		}
		printf("영어(종료:0)): ");
		scanf("%d", &eng);
		if (eng == 0) {
			printf("프로그램이 종료되었습니다. !!!!!\n");
			break;
		}
		printf("수학(종료:0)): ");
		scanf("%d", &math);
		if (math == 0) {
			printf("프로그램이 종료되었습니다. !!!!!\n");
			break;
		}
		total = kor + eng + math;
		avg = total / 3.0;
		printf("**** 점수 ****\n");
		printf("국어 영어 수학 총점 평균\n");
		printf("%3d %3d %3d  %3d  %.2f\n", kor, eng, math, total, avg);
	}
}