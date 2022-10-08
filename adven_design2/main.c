#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA_SIZE 26

typedef struct Trie_node		/*트라이 노드에 대한 구조체 정의*/
{
	struct Trie_node* children[ALPHA_SIZE];
	int word_end;
}Trie;

Trie* Get_node() {				/*트라이노드를 생성하는 함수 초기값을 셋팅해서 노드 포인터로 돌려준다.*/
	Trie* trie_node = malloc(sizeof(Trie));
	trie_node->word_end = 0;
	for (int i = 0; i < ALPHA_SIZE; i++) {
		trie_node->children[i] = NULL;
	}
	return trie_node;
}

Trie* Word_insert(Trie* root, char* word) {		/*트라이에 단어를 추가하는 함수*/
	Trie* cur = root;
	int i = 0;

	while (word[i]) {					/*word의 값이 NULL(끝)이 나올때까지 반복한다.*/
		int idx = word[i] - 'a';		/*문자의 값에 a를 빼서 단어 a부터 0으로 시작하여 배열의 인덱스의 값에 맞게 단어의 값을 바꾸어준다.*/
		if (cur->children[idx] == NULL) {	/*만약 문자의 인덱스값의 배열공간이 비어있다면 노드를 생성해서 만들어주고 존재하면 노드를 따라 움직인다.*/
			cur->children[idx] = Get_node();
		}
		cur = cur->children[idx];
		i += 1;
	}
	cur->word_end = 1;		/*단어의 끝에 도달했을 경우 단어의 끝을 알려주는 word_end의 값을 1로 바꿔주고 루트노드를 반환해준다.*/
	return root;
}

int Word_search(Trie* root, char* word) {	/*트라이에서 입력받은 단어의 존재여부를 확인하는 함수*/
	if (root == 0) {						/*루트노드가 NULL인 경우의 예외처리*/
		return 0;
	}
	Trie* cur = root;
	int i = 0;
	while (word[i]) {						/*단어의 값에 따라 노드를 타고 들어가는 while문*/
		int idx = word[i] - 'a';
		cur = cur->children[idx];
		if (cur == NULL) {					/*하위 단어노드가 존재하지않으면 존재하지 않는 0을 return해준다.*/
			return 0;
		}
		i += 1;
	}
	return cur->word_end;					/*만약 단어가 존재한다면 cur에 word_end 숫자 1을 반환할 것이고 없으면 0을 반환할 것이다.*/
}

int nodechildren(Trie* cur) {				/*해당 트라이 노드에 자식노드가 존재하는지 확인하는 함수이다.*/
	for (int i = 0; i < ALPHA_SIZE; i++) {	/*for문을 통하여 children배열에 저장된 값이 모두 NULL값을 갖는지 확인하는 단계이다.*/
		if (cur->children[i] != NULL)
			return 0;						/*하나의 인덱스에서도 NULL값을 가지지 않는다면 자식노드를 가지고 있는 것으로 자식이 존재한다는 0을 return한다.*/
	}
	return 1;				/*모두 NULL값을 갖는 결과로써 자식노드를 가지지 않는다는 의미로 1의 값을 return해준다.*/
}

Trie* Word_delete(Trie* cur, char* word, int depth) {	/*트라이에서 단어를 삭제하는 함수*/
	if (cur == NULL)		/*입력노드가 NULL이면 처리할 예외처리*/
		return NULL;
	if (depth == strlen(word)) {	/*단어의 끝에 도달했는지 확인*/
		if (cur->word_end == 1)		/*단어의 끝을 표시하는 word_end를 다시 0으로 set*/
			cur->word_end = 0;
		if (nodechildren(cur) == 1) {		/*삭제할 단어의 자식노드가 없으면 바로 삭제*/
			free(cur);
			cur = NULL;
			return cur;
		}
	}
	int idx = word[depth] - 'a';
	cur->children[idx] = Word_delete(cur->children[idx], word, depth + 1);		/*재귀적으로 자식노드들의 삭제를 수행한다.*/
	if (nodechildren(cur) == 1 && cur->word_end == 0) {			/*단어의 끝에 도달하여 자식노드가 없고 word_end의 값이 0인 경우 노드를 삭제한다.*/
		free(cur);
		cur = NULL;
	}
	return cur;
}


void main() {			/*전체 함수의 기능을 테스트하기 위한 메인함수*/
	int menu = 0;		/*사용자가 선택하는 메뉴의 담는 변수*/
	char word[50] = {0};		/*사용자가 입력하는 단어를 임시로 저장하는 변수*/
	Trie* root = Get_node();	/*루트노드를 초기화해줌*/
	while (1)
	{
		printf("트라이에 단어를 추가하시려면 1을\n트라이에 단어를 삭제하시려면 2를\n트라이에 단어를 검색하시려면 3을\n프로그램을 종료하시려면 4를 입력해주세요: ");
		scanf("%d", &menu);
		if (menu == 1) {
			printf("트라이에 추가하실 단어를 입력해주세요: ");
			scanf("%s", &word);
			Word_insert(root, word);
		}
		else if (menu == 2) {
			printf("트라이에서 삭제하실 단어를 입력해주세요: ");
			scanf("%s", &word);
			Word_delete(root, word, 0);
		}
		else if (menu == 3) {
			printf("트라이에서 검색하실 단어를 입력해주세요: ");
			scanf("%s", &word);
			int find = Word_search(root, word);
			if (find == 1) {
				printf("단어가 트라이에 존재합니다.\n");
			}
			else if (find == 0) {
				printf("단어가 트라이에 존재하지 않습니다.\n");
			}
		}
		else if (menu == 4) {
			printf("프로그램을 종료합니다.");
			break;
		}
		else {
			printf("잘못된 값입니다. 다시 입력해주세요.\n");
		}
		printf("\n");
	}
}