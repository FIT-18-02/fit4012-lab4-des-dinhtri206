#include <iostream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

string convert_decimal_to_binary(int decimal)
{
    return bitset<4>(decimal).to_string();
}

int convert_binary_to_decimal(const string &binary)
{
    return stoi(binary, nullptr, 2);
}

string Xor(const string &a, const string &b)
{
    string result = "";
    for (size_t i = 0; i < b.size(); i++)
    {
        result += (a[i] != b[i]) ? '1' : '0';
    }
    return result;
}

string hex_to_bin_string(const string &hex_str)
{
    string bin = "";
    for (char c : hex_str)
    {
        int val = (c >= '0' && c <= '9') ? (c - '0') : (c >= 'A' && c <= 'F') ? (c - 'A' + 10)
                                                     : (c >= 'a' && c <= 'f')   ? (c - 'a' + 10)
                                                                                : 0;
        bin += bitset<4>(val).to_string();
    }
    while (bin.length() < 64)
        bin = "0" + bin;
    return bin;
}

string bytes_to_bin_string(const char *buffer, int bytes_read)
{
    string bin = "";
    for (int i = 0; i < 8; ++i)
    {
        char c = (i < bytes_read) ? buffer[i] : 0x00;
        bin += bitset<8>((unsigned char)c).to_string();
    }
    return bin;
}

void print_bin_string_as_bytes(const string &bin)
{
    for (int i = 0; i < 8; ++i)
    {
        string byte_str = bin.substr(i * 8, 8);
        char c = static_cast<char>(stoi(byte_str, nullptr, 2));
        cout.put(c);
    }
}

string initial_permutation(const string &input)
{
    const int initial_permutation[64] = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7};

    string permuted = "";
    for (int i = 0; i < 64; i++)
    {
        permuted += input[initial_permutation[i] - 1];
    }
    return permuted;
}

string inverse_initial_permutation(const string &input)
{
    const int inverse_permutation[64] = {
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25};

    string permuted = "";
    for (int i = 0; i < 64; i++)
    {
        permuted += input[inverse_permutation[i] - 1];
    }
    return permuted;
}

class KeyGenerator
{
private:
    string key;
    vector<string> roundKeys;

    const int pc1[56] = {
        57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};

    const int pc2[48] = {
        14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

    string shift_left_once(const string &key_chunk)
    {
        return key_chunk.substr(1) + key_chunk[0];
    }

    string shift_left_twice(string key_chunk)
    {
        key_chunk = shift_left_once(key_chunk);
        return shift_left_once(key_chunk);
    }

public:
    KeyGenerator(const string &input_key) : key(input_key) {}

    void generateRoundKeys()
    {
        roundKeys.clear();
        string permutedKey = "";
        for (int i = 0; i < 56; ++i)
        {
            permutedKey += key[pc1[i] - 1];
        }

        string left = permutedKey.substr(0, 28);
        string right = permutedKey.substr(28, 28);

        for (int i = 0; i < 16; ++i)
        {
            if (i == 0 || i == 1 || i == 8 || i == 15)
            {
                left = shift_left_once(left);
                right = shift_left_once(right);
            }
            else
            {
                left = shift_left_twice(left);
                right = shift_left_twice(right);
            }

            string combinedKey = left + right;
            string roundKey = "";
            for (int j = 0; j < 48; ++j)
            {
                roundKey += combinedKey[pc2[j] - 1];
            }

            roundKeys.push_back(roundKey);
        }
    }

    const vector<string> &getRoundKeys() const
    {
        return roundKeys;
    }
};

class DES
{
private:
    const int expansion_table[48] = {
        32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11,
        12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21,
        22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};

    const int permutation_tab[32] = {
        16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
        2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};

    const int substition_boxes[8][4][16] = {{
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    }, {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    }, {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    }, {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    }, {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    }, {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    }, {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    }, {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }};

    vector<string> round_keys;

public:
    DES(const vector<string> &keys) : round_keys(keys) {}

    string encrypt(const string &input)
    {
        string perm = initial_permutation(input);
        string left = perm.substr(0, 32);
        string right = perm.substr(32, 32);

        for (int i = 0; i < 16; i++)
        {
            string right_expanded = "";
            for (int j = 0; j < 48; j++)
            {
                right_expanded += right[expansion_table[j] - 1];
            }
            string xored = Xor(round_keys[i], right_expanded);
            string res = "";
            for (int j = 0; j < 8; j++)
            {
                string row1 = xored.substr(j * 6, 1) + xored.substr(j * 6 + 5, 1);
                int row = convert_binary_to_decimal(row1);
                string col1 = xored.substr(j * 6 + 1, 4);
                int col = convert_binary_to_decimal(col1);
                int val = substition_boxes[j][row][col];
                res += convert_decimal_to_binary(val);
            }
            string perm2 = "";
            for (int j = 0; j < 32; j++)
            {
                perm2 += res[permutation_tab[j] - 1];
            }
            string new_right = Xor(perm2, left);
            left = right;
            right = new_right;
        }
        string combined_text = right + left;
        return inverse_initial_permutation(combined_text);
    }

    string decrypt(const string &input)
    {
        string perm = initial_permutation(input);
        string left = perm.substr(0, 32);
        string right = perm.substr(32, 32);

        for (int i = 15; i >= 0; i--)
        {
            string right_expanded = "";
            for (int j = 0; j < 48; j++)
            {
                right_expanded += right[expansion_table[j] - 1];
            }
            string xored = Xor(round_keys[i], right_expanded);
            string res = "";
            for (int j = 0; j < 8; j++)
            {
                string row1 = xored.substr(j * 6, 1) + xored.substr(j * 6 + 5, 1);
                int row = convert_binary_to_decimal(row1);
                string col1 = xored.substr(j * 6 + 1, 4);
                int col = convert_binary_to_decimal(col1);
                int val = substition_boxes[j][row][col];
                res += convert_decimal_to_binary(val);
            }
            string perm2 = "";
            for (int j = 0; j < 32; j++)
            {
                perm2 += res[permutation_tab[j] - 1];
            }
            string new_right = Xor(perm2, left);
            left = right;
            right = new_right;
        }
        string combined_text = right + left;
        return inverse_initial_permutation(combined_text);
    }
};

void process_q2(const string &key_hex, bool is_encrypt)
{
    KeyGenerator keygen(hex_to_bin_string(key_hex));
    keygen.generateRoundKeys();
    DES des(keygen.getRoundKeys());

    char buffer[8];
    while (cin.read(buffer, 8) || cin.gcount() > 0)
    {
        int bytes_read = cin.gcount();
        string block_bin = bytes_to_bin_string(buffer, bytes_read);

        string result_bin;
        if (is_encrypt)
        {
            result_bin = des.encrypt(block_bin);
        }
        else
        {
            result_bin = des.decrypt(block_bin);
        }

        print_bin_string_as_bytes(result_bin);
    }
}

void process_q4(const string &k1_hex, const string &k2_hex, const string &k3_hex, bool is_encrypt)
{
    KeyGenerator kg1(hex_to_bin_string(k1_hex));
    kg1.generateRoundKeys();
    DES des1(kg1.getRoundKeys());
    
    KeyGenerator kg2(hex_to_bin_string(k2_hex));
    kg2.generateRoundKeys();
    DES des2(kg2.getRoundKeys());
    
    KeyGenerator kg3(hex_to_bin_string(k3_hex));
    kg3.generateRoundKeys();
    DES des3(kg3.getRoundKeys());

    char buffer[8];
    while (cin.read(buffer, 8) || cin.gcount() > 0)
    {
        int bytes_read = cin.gcount();
        string block_bin = bytes_to_bin_string(buffer, bytes_read);

        string result_bin;
        if (is_encrypt)
        {
            string step1 = des1.encrypt(block_bin);
            string step2 = des2.decrypt(step1);
            result_bin = des3.encrypt(step2);
        }
        else
        {
            string step1 = des3.decrypt(block_bin);
            string step2 = des2.encrypt(step1);
            result_bin = des1.decrypt(step2);
        }
        print_bin_string_as_bytes(result_bin);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        cerr << "Usage: ./des -q2 <encrypt|decrypt> <key_hex>\n";
        cerr << "       ./des -q4 <encrypt|decrypt> <k1_hex> <k2_hex> <k3_hex>\n";
        return 1;
    }

    string mode = argv[1];
    string action = argv[2];
    bool is_encrypt = (action == "encrypt");

    if (mode == "-q2")
    {
        process_q2(argv[3], is_encrypt);
    }
    else if (mode == "-q4" && argc >= 6)
    {
        process_q4(argv[3], argv[4], argv[5], is_encrypt);
    }
    else
    {
        cerr << "Invalid arguments!" << endl;
        return 1;
    }

    return 0;
}