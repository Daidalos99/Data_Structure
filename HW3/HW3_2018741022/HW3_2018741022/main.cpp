#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <iomanip>

using namespace std;

int a = 0;

// 좌표 이동: 2차원 배열의 경우이므로, 
// 아래쪽(x): row증가, 오른쪽(y): col증가, 함수 좌표와 다름! 신경쓸 것
const int V[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
const int U = 0, D = 1, L = 3, R = 2;
const int N = U, S = D, E = R, W = L;

vector<string> split(string input, char delimiter);
void print_90(vector<string> k, int index, int depth, string**& arr);
bool insert_list_check(string input, string* list, int size);
void make_htree(string str, int index, int i, int j, int depth, int U, int D, int R, int L, string**& H_tree_arr);
int h_center(int number) { return number <= 1 ? 0 : 2 * h_center(number / 4) + 1; }
int h_depth(int number) { return number <= 7 ? 1 : 2 * h_depth(number / 4); }

int main(void) {
	string token;								// 공백을 기준으로 구분될 문자열 토큰
	string input = "";							// 입력받은 문자열을 저장할 변수
	int number = 0;								// 트리 원소개수
	int depth = 0;								// 트리의 깊이
	int row_90 = 0, col_90 = 0;					// 90도 돌아간 트리를 저장할 배열의 행, 열
	int row = 0, col = 0;						// 트리를 저장할 배열의 행, 열
	const int operation_num = 200;				// 최대 연산 횟수
	int operation_cnt = 0;						// 연산 횟수 카운트

	// 삽입가능한 문자 리스트
	string insert_list[63] = {
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "?", 
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", 
		"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"
	};
	
	// 키보드 입력을 받는 부분(token으로 받은 줄별 입력을 input에 한줄짜리 문자열로 누적)
	while (true) {
		getline(cin, token);
		// 한 줄의 마지막 입력이 EOI일때
		if (token[token.size() - 3] == 'E' && token[token.size() - 2] == 'O' && token[token.size() - 1] == 'I') {
			if (input == "") {	// input의 첫 입력이라면 공백을 띄우지 않고 input에 바로 추가
				for (unsigned int i = 0; i < token.size() - 3; i++) {
					input += token[i];
				}
			}
			else {
				input += " ";	// 앞에 이미 다른 값이 존재하면 아니라면 공백을 띄우고 input에 추가
				for (unsigned int i = 0; i < token.size() - 3; i++) {
					input += token[i];
				}
			}
			break;
		}
		// 한 줄의 마지막 입력이 EOI가 아닐 때
		else {	// 첫 입력이라면 공백을 띄우지 않고 input에 바로 추가
			if (input == "") {
				input += token;
			}
			else { // 앞에 이미 다른 값이 존재하면 아니라면 공백을 띄우고 input에 추가
				input += ' ';
				input += token;
			}
		}
	}	

	vector<string> command;			// 입력받은 heap operation과 값을 저장할 벡터
	command = split(input, ' ');	// 공백을 기준으로 저장
	vector<string> v;				// heap 벡터 v
	make_heap(v.begin(), v.end());	// v로 heap을 생성

	for (unsigned int i = 0; i < command.size(); i++) {
		if (operation_cnt > 200) {
			cout << "Error! Number of operations exceeded 200" << endl;
			return 0;
		}
		else {
			// INS가 들어오면 바로 다음 값을 push_heap 수행
			if (command[i] == "INS") {
				if (insert_list_check(command[i + 1], insert_list, sizeof(insert_list)/sizeof(string))) {
					v.push_back(command[i + 1]);
					push_heap(v.begin(), v.end());
					i++;
					number++;
					operation_cnt++;
				}
				else {
					return 0;
				}
			}
			// DEL이 들어오면 pop_heap 수행
			else if (command[i] == "DEL") {
				pop_heap(v.begin(), v.end());
				v.pop_back();
				number--;
				operation_cnt++;
			}
			// 다른 이상한 입력이 들어올 경우 
			else {
				cout << "Error! Heap Operation Command is not correct. Try again!" << endl;
				return 0;
			}
		}
	}

	depth = log2(number + 1);	// 따른 트리의 깊이
	row_90 = number;
	col_90 = depth+1;
	// 트리의 행, 열을 바꿈(회전 없는 트리)
	row = col_90;				
	col = row_90;				

	// rotated form 2차원 배열 동적할당 및 t로 초기화
	string** rotated_tree_arr = new string* [row_90];
	for (int i = 0; i < row_90; i++) {
		rotated_tree_arr[i] = new string[col_90];
	}

	for (int i = 0; i < row_90; i++) {
		for (int j = 0; j < col_90; j++) {
			rotated_tree_arr[i][j] = 't';
		}
	}

	// not-rotated form 2차원 배열 동적할당 및 t로 초기화
	string** original_tree = new string * [row];
	for (int i = 0; i < row; i++) {
		original_tree[i] = new string[col];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			original_tree[i][j] = 't';
		}
	}
	
	// 1. rotated form 출력
	cout << "1. rotated form" << endl;
	print_90(v, 0, 0, rotated_tree_arr);	// 회전 트리를 그림


	// rotated form 반시계 방향으로 90도 회전
	for (int i = 0; i < row_90; i++) {
		for (int j = 0; j < col_90; j++) {
			original_tree[j][row_90 - i - 1] = rotated_tree_arr[i][j];
		}
	}

	// 2. not-rotated form 출력
	cout << "2. not-rotated form" << endl;
	// complete binary tree 출력, t의 경우 공백으로 출력처리
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (original_tree[i][j] == "t") {
				cout << " ";
			}
			else {
				cout << original_tree[i][j];
			}
		}
		cout << endl;
	}

	// H-Tree
	string h_tree_str;

	for (int i = 0; i < v.size(); i++) {
		h_tree_str += v[i];
	}

	int h_tree_center = 0;
	int h_tree_depth = 0;
	
	h_tree_center = h_center(h_tree_str.length());
	h_tree_depth = h_depth(h_tree_str.length());

	int h_tree_row = h_tree_center * 2 + 1;
	int h_tree_col = h_tree_row; // h-tree를 담을 배열은 정방배열

	// H-Tree를 담을 2차원 동적배열 생성
	string** H_tree = new string * [h_tree_row];
	for (int i = 0; i < h_tree_row; i++) {
		H_tree[i] = new string[h_tree_col * 2 + 1];
	}

	for (int i = 0; i < h_tree_row; i++) {
		for (int j = 0; j < h_tree_col; j++) {
			H_tree[i][j] = 't';
		}
	}
	
	make_htree(h_tree_str, 1, h_tree_center, h_tree_center, h_tree_depth, N, S, E, W, H_tree);
	
	// 3. H-tree form 출력
	cout << "3. H-tree form" << endl;
	for (int i = 0; i < h_tree_row; i++) {
		for (int j = 0; j < h_tree_col; j++) {
			if (H_tree[i][j] == "t") {
				cout << " ";
			}
			else {
				cout << H_tree[i][j];
			}
		}
		cout << endl;
	}

	return 0;
}

// delimiter를 기반으로 문자열을 쪼개는 함수
vector<string> split(string input, char delimiter)
{
	vector<string> result;
	stringstream ss(input);
	string temp;

	while (getline(ss, temp, delimiter)) {
		result.push_back(temp);
	}
	return result;
}


// 회전 트리를 그리는 함수
void print_90(vector<string> k, int index, int depth, string**& arr) {
	if (index < k.size()) {
		// 왼쪽 자식 노드 출력
		print_90(k, 2 * index + 2, depth + 1, arr);
		// 자기 자신 출력
		cout << setw(depth * 2 + 1) << k[index] << endl;
		if (depth == 0) {
			arr[a][0] = k[index];
		}
		else {
			arr[a][depth] = k[index];
		}
		a++;
		// 오른쪽 자식 출력
		print_90(k, 2 * index + 1, depth + 1, arr);
	}
}

// 입력받은 값이 정해진 입력값에 속하는지 확인
bool insert_list_check(string input, string* list, int size) {
	for (int i = 0; i < size; i++) {
		if (input == list[i]) {
			return true;
		}
	}
	cout << "Error! Value is not on the insert list!" << endl;
	return false;
}

// H-Tree 만드는 함수
void make_htree(string str, int index, int i, int j, int depth, int U, int D, int R, int L, string**& H_tree_arr) {
	if (index > str.length()) return;	// 예외처리
	H_tree_arr[i][j] = str[index - 1];	// 0 인덱스 값을 센터점 출력
	// 좌
	if (2 * index <= str.length()) {
		H_tree_arr[i + depth * V[L][0]][j + depth * V[L][1]] = str[2 * index - 1];	// 좌 출력
		make_htree(str, 4 * index, i + depth * (V[L][0] + V[U][0]), j + depth * (V[L][1] + V[U][1]), depth / 2, D, U, L, R, H_tree_arr);		// 좌상 출력
		make_htree(str, 4 * index + 1, i + depth * (V[L][0] + V[D][0]), j + depth * (V[L][1] + V[D][1]), depth / 2, U, D, R, L, H_tree_arr);	// 좌하 출력
	}
	// 우
	if (2 * index + 1 <= str.length()) {
		H_tree_arr[i + depth * V[R][0]][j + depth * V[R][1]] = str[2 * index];	// 우 출력
		make_htree(str, 4 * index + 2, i + depth * (V[R][0] + V[D][0]), j + depth * (V[R][1] + V[D][1]), depth / 2, U, D, R, L, H_tree_arr);	// 우하 출력
		make_htree(str, 4 * index + 3, i + depth * (V[R][0] + V[U][0]), j + depth * (V[R][1] + V[U][1]), depth / 2, D, U, L, R, H_tree_arr);	// 우상 츌력
	}
}