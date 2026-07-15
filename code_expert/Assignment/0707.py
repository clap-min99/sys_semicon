'''
첫 줄에 문자열(s) 하나가 입력된다.
두 번째 줄에 s에서 변경할 대상 단어(o)와 바꿀 단어(n)가 공백으로 분리되어 입력된다.
s에서 단어 o를 새로운 단어 n으로 변경한 문자열을 인쇄하는 코드를 설계하라.
단, o와 n은 문자 수가 다를 수 있으며 문자열 s에는 바꿀 대상 단어 o는 딱 하나만 존재한다.

단, 아직 str 메서드인 replace는 배우지 않았으므로 str.replace 메서드는 사용하지 않고 작성하여 본다.

입력
I don't dislike python.
dislike like

출력
I don't like python.
'''

# s = input()
# o, n = input().split()
# p = s.index(o)
# result = s[:p] + n + s[p + len(o):]
# print(result)

'''
10 이하의 양의 정수 n을 입력 받는다.
0부터 시작하는 3의 배수 값들에서 차례대로 n개의 합을 인쇄하라.
만약 n이 1이면 0, n이 2이면 0+3 = 3, n이 3이면 0+3+6 = 9가 인쇄되어야 한다.

입력 10
출력 135

'''

# n = int(input())
# ans = sum(range(0, 3*n, 3))
# print(ans)