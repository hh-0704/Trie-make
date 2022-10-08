#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA_SIZE 26

typedef struct Trie_node		/*Ʈ���� ��忡 ���� ����ü ����*/
{
	struct Trie_node* children[ALPHA_SIZE];
	int word_end;
}Trie;

Trie* Get_node() {				/*Ʈ���̳�带 �����ϴ� �Լ� �ʱⰪ�� �����ؼ� ��� �����ͷ� �����ش�.*/
	Trie* trie_node = malloc(sizeof(Trie));
	trie_node->word_end = 0;
	for (int i = 0; i < ALPHA_SIZE; i++) {
		trie_node->children[i] = NULL;
	}
	return trie_node;
}

Trie* Word_insert(Trie* root, char* word) {		/*Ʈ���̿� �ܾ �߰��ϴ� �Լ�*/
	Trie* cur = root;
	int i = 0;

	while (word[i]) {					/*word�� ���� NULL(��)�� ���ö����� �ݺ��Ѵ�.*/
		int idx = word[i] - 'a';		/*������ ���� a�� ���� �ܾ� a���� 0���� �����Ͽ� �迭�� �ε����� ���� �°� �ܾ��� ���� �ٲپ��ش�.*/
		if (cur->children[idx] == NULL) {	/*���� ������ �ε������� �迭������ ����ִٸ� ��带 �����ؼ� ������ְ� �����ϸ� ��带 ���� �����δ�.*/
			cur->children[idx] = Get_node();
		}
		cur = cur->children[idx];
		i += 1;
	}
	cur->word_end = 1;		/*�ܾ��� ���� �������� ��� �ܾ��� ���� �˷��ִ� word_end�� ���� 1�� �ٲ��ְ� ��Ʈ��带 ��ȯ���ش�.*/
	return root;
}

int Word_search(Trie* root, char* word) {	/*Ʈ���̿��� �Է¹��� �ܾ��� ���翩�θ� Ȯ���ϴ� �Լ�*/
	if (root == 0) {						/*��Ʈ��尡 NULL�� ����� ����ó��*/
		return 0;
	}
	Trie* cur = root;
	int i = 0;
	while (word[i]) {						/*�ܾ��� ���� ���� ��带 Ÿ�� ���� while��*/
		int idx = word[i] - 'a';
		cur = cur->children[idx];
		if (cur == NULL) {					/*���� �ܾ��尡 �������������� �������� �ʴ� 0�� return���ش�.*/
			return 0;
		}
		i += 1;
	}
	return cur->word_end;					/*���� �ܾ �����Ѵٸ� cur�� word_end ���� 1�� ��ȯ�� ���̰� ������ 0�� ��ȯ�� ���̴�.*/
}

int nodechildren(Trie* cur) {				/*�ش� Ʈ���� ��忡 �ڽĳ�尡 �����ϴ��� Ȯ���ϴ� �Լ��̴�.*/
	for (int i = 0; i < ALPHA_SIZE; i++) {	/*for���� ���Ͽ� children�迭�� ����� ���� ��� NULL���� ������ Ȯ���ϴ� �ܰ��̴�.*/
		if (cur->children[i] != NULL)
			return 0;						/*�ϳ��� �ε��������� NULL���� ������ �ʴ´ٸ� �ڽĳ�带 ������ �ִ� ������ �ڽ��� �����Ѵٴ� 0�� return�Ѵ�.*/
	}
	return 1;				/*��� NULL���� ���� ����ν� �ڽĳ�带 ������ �ʴ´ٴ� �ǹ̷� 1�� ���� return���ش�.*/
}

Trie* Word_delete(Trie* cur, char* word, int depth) {	/*Ʈ���̿��� �ܾ �����ϴ� �Լ�*/
	if (cur == NULL)		/*�Է³�尡 NULL�̸� ó���� ����ó��*/
		return NULL;
	if (depth == strlen(word)) {	/*�ܾ��� ���� �����ߴ��� Ȯ��*/
		if (cur->word_end == 1)		/*�ܾ��� ���� ǥ���ϴ� word_end�� �ٽ� 0���� set*/
			cur->word_end = 0;
		if (nodechildren(cur) == 1) {		/*������ �ܾ��� �ڽĳ�尡 ������ �ٷ� ����*/
			free(cur);
			cur = NULL;
			return cur;
		}
	}
	int idx = word[depth] - 'a';
	cur->children[idx] = Word_delete(cur->children[idx], word, depth + 1);		/*��������� �ڽĳ����� ������ �����Ѵ�.*/
	if (nodechildren(cur) == 1 && cur->word_end == 0) {			/*�ܾ��� ���� �����Ͽ� �ڽĳ�尡 ���� word_end�� ���� 0�� ��� ��带 �����Ѵ�.*/
		free(cur);
		cur = NULL;
	}
	return cur;
}


void main() {			/*��ü �Լ��� ����� �׽�Ʈ�ϱ� ���� �����Լ�*/
	int menu = 0;		/*����ڰ� �����ϴ� �޴��� ��� ����*/
	char word[50] = {0};		/*����ڰ� �Է��ϴ� �ܾ �ӽ÷� �����ϴ� ����*/
	Trie* root = Get_node();	/*��Ʈ��带 �ʱ�ȭ����*/
	while (1)
	{
		printf("Ʈ���̿� �ܾ �߰��Ͻ÷��� 1��\nƮ���̿� �ܾ �����Ͻ÷��� 2��\nƮ���̿� �ܾ �˻��Ͻ÷��� 3��\n���α׷��� �����Ͻ÷��� 4�� �Է����ּ���: ");
		scanf("%d", &menu);
		if (menu == 1) {
			printf("Ʈ���̿� �߰��Ͻ� �ܾ �Է����ּ���: ");
			scanf("%s", &word);
			Word_insert(root, word);
		}
		else if (menu == 2) {
			printf("Ʈ���̿��� �����Ͻ� �ܾ �Է����ּ���: ");
			scanf("%s", &word);
			Word_delete(root, word, 0);
		}
		else if (menu == 3) {
			printf("Ʈ���̿��� �˻��Ͻ� �ܾ �Է����ּ���: ");
			scanf("%s", &word);
			int find = Word_search(root, word);
			if (find == 1) {
				printf("�ܾ Ʈ���̿� �����մϴ�.\n");
			}
			else if (find == 0) {
				printf("�ܾ Ʈ���̿� �������� �ʽ��ϴ�.\n");
			}
		}
		else if (menu == 4) {
			printf("���α׷��� �����մϴ�.");
			break;
		}
		else {
			printf("�߸��� ���Դϴ�. �ٽ� �Է����ּ���.\n");
		}
		printf("\n");
	}
}