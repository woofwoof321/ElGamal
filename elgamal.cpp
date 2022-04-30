#include <bits/stdc++.h>
using namespace std;

#define int long long

int binary_exp(int a, int b, int c) {
	if (b == 0) {
		return 1;
	}
	int t = binary_exp(a, b / 2, c);
	if (b % 2) {
		return t * t % c * a % c; 
	} else return t * t % c;
}

int mod = 1e9 + 7;
int g = 5;

int getrand(int l, int r) {
	// generates a uniformly distributed random number in the range [l, r]
	std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(l, r);
    return distr(gen);
}

pair<int, int> generate_key() {
	int private_key = getrand(1, mod - 1);
	int public_key = binary_exp(g, private_key, mod);
	return {private_key, public_key};
}

pair<int, int> encrypt(int message, int public_key) {
	int secret = getrand(1, mod - 1);
	int shared_secret = binary_exp(public_key, secret, mod);
	int c1 = binary_exp(g, secret, mod);
	int c2 = message * shared_secret % mod; 
	return {c1, c2};
}

int decrypt(pair<int, int> encrypted_message, int private_key) {
	int c1 = encrypted_message.first;
	int c2 = encrypted_message.second;
	// Generate shared secret
	int shared_secret = binary_exp(c1, private_key, mod);
	// Now invert the multiplaction
	int inverse = binary_exp(shared_secret, mod - 2, mod);
	int message = c2 * inverse % mod;
	return message;
}

void show_menu() {
	cout << "\n\n\nChoose an operation:\n";
	cout << "1. Generate key pair\n";
	cout << "2. Encrypt\n";
	cout << "3. Decrypt\n";
	cout << "4. Exit\n";
}

signed main() {
	while (1) {
		show_menu();
		int response;
		cin >> response;
		if (response == 1) {
			pair<int, int> key = generate_key();
			cout << "Private key: " << key.first << "\n";
			cout << "Public key: " << key.second << "\n";
		} else if (response == 2) {
			cout << "Enter your message (a number between 1 and " << mod << "): ";
			int message;
			cin >> message;
			cout << "Enter public key of receiver: ";
			int public_key;
			cin >> public_key;
			pair<int, int> encrypted_message = encrypt(message, public_key);
			cout << "First part:" << encrypted_message.first << "\n";
			cout << "Second part:" << encrypted_message.second << "\n";
		} else if (response == 3) {
			pair<int, int> encrypted_message;
			cout << "Enter first part of encrypted message: ";
			cin >> encrypted_message.first;
			cout << "Enter second part of encrypted message: ";
			cin >> encrypted_message.second;
			cout << "Enter your private key: ";
			int private_key;
			cin >> private_key;
			int message = decrypt(encrypted_message, private_key);
			cout << "Decrypted message: " << message << "\n";
		} else {
			break;
		}
		getchar();
	}
	return 0;
}