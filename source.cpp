#include <iostream>
#include <fstream>
#include <string>
#include <random>

struct block {
	std::string newhash;
	std::string merkleroot;
	int naunce = 0;

	std::string trade;
};
std::string merkletree(std::string trades);
std::string hash(std::string phash, std::string mkr, int nc);
int r();
int num;
int rnum;
char b[17];

int main() {
	std::string temp;
	int i = 0;
	std::string prehash = "@l1m)>k";
	block blocks[10];
	std::ofstream outFile("Blocks.txt");
	while (i < 10) {
		rnum = r();
		std::cout << "\n" << i << "블록\n";
		std::cin >> blocks[i].trade;
		blocks[i].merkleroot = merkletree(blocks[i].trade);
		blocks[i].merkleroot.resize(16);

		while (num == 0) {
			blocks[i].newhash = hash(prehash, blocks[i].merkleroot, blocks[i].naunce);
			blocks[i].naunce++;
		}
		num = 0;
		blocks[i].newhash.resize(16);
		std::cout << blocks[i].newhash << "\n채굴 완료\n";
		outFile << "{\nblock_number : " << i << "\nhash_value : " << blocks[i].newhash << "\nmerkleroot : " << blocks[i].merkleroot << "\nnaunce_value : " << blocks[i].naunce - 1 << "\n}\n";
		prehash = blocks[i].newhash;
		i++;
	}

}
std::string merkletree(std::string trades) {
	char temp;
	for (int i = 0; i < trades.length(); i++) {
		for (int j = 0; j < trades.length() - 1; j++) {
			if (int(trades[j]) > int(trades[j + 1])) {
				temp = trades[j + 1];
				trades[j + 1] = trades[j];
				trades[j] = temp;
			}
		}
	}
	return trades;
}
std::string hash(std::string phash, std::string mkr, int nc) {

	std::string combined = phash + mkr;

	for (int i = 0; i < combined.length(); i++)
	{
		if (int(combined[i]) + nc > 127) {
			combined[i] = char(int(combined[i]) % 5);
		}
		combined[i] = char(int(combined[i]) + nc);
	}
	if (nc == rnum) {
		num = 1;
	}
	return combined;
}
int r() {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> dis(1, 100);

	return dis(gen);
}
