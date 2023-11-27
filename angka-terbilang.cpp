// GIVE NETIZEN TEKNOLOGI STAR ON GITHUB

#include <iostream>
#include <vector>

using namespace std;

const vector<string> units = {"", "ribu", "juta", "milyar", "triliun", "quadriliun", "quintiliun", "sextiliun", "septiliun", "oktiliun", "noniliun", "desiliun", "undesiliun", "duodesiliun", "tredesiliun", "quattuordesiliun", "quindesiliun", "sexdesiliun", "septendesiliun", "oktodesiliun", "novemdesiliun", "vigintiliun"};
const int maxIndex = units.size() - 1;

string digitToUnit(int digit) {
    int curIndex = digit / 3;
    return (curIndex <= maxIndex) ? units[curIndex] : units[maxIndex];
}

const vector<string> numbers = {"", "satu", "dua", "tiga", "empat", "lima", "enam", "tujuh", "delapan", "sembilan"};

string numberToText(int index) {
    return (index < numbers.size()) ? numbers[index] : "";
}

string terbilangSatuSatu(const string &angka) {
    string result;
    for (char digit : angka) {
        int curAngka = digit - '0';
        result += (curAngka == 0) ? "nol" : numberToText(curAngka);
        result += " ";
    }
    return result;
}

string terbilang(const string &angka) {
    int angkaLength = angka.length();
    int angkaMaxIndex = angkaLength - 1;

    if (angkaMaxIndex == 0 && angka[0] == '0') {
        return "nol";
    }

    string space = "";
    string result = "";

    int i = 0;
    while (i != angkaLength) {
        int digitCount = angkaMaxIndex - i;
        int modGroup = digitCount % 3;
        int curAngka = angka[i] - '0';

        if (digitCount == 3 && curAngka == 1 && (i == 0 || (angka[i - 2] == '0' && angka[i - 1] == '0'))) {
            result += space + "seribu";
        } else {
            if (curAngka != 0) {
                if (modGroup == 0) {
                    result += space + numberToText(curAngka) + ((i == angkaMaxIndex) ? "" : " ") + digitToUnit(digitCount);
                } else if (modGroup == 2) {
                    if (curAngka == 1) {
                        result += space + "seratus";
                    } else {
                        result += space + numberToText(curAngka) + " ratus";
                    }
                } else {
                    if (curAngka == 1) {
                        i++; 
                        int nextAngka = angka[i] - '0';
                        if (nextAngka == 0) {
                            result += space + "sepuluh";
                            if (digitCount != 1 && (angka[i - 2] != '0' || angka[i - 1] != '0')) {
                                result += " " + digitToUnit(digitCount - 1);
                            }
                        } else {
                            if (nextAngka == 1) {
                                result += space + "sebelas";
                            } else {
                                result += space + numberToText(nextAngka) + " belas";
                            }
                            if (digitCount != 1) {
                                result += " " + digitToUnit(digitCount - 1);
                            }
                        }
                    } else {
                        result += space + numberToText(curAngka) + " puluh";
                    }
                }
            } else {
                if (modGroup == 0 && (angka[i - 2] != '0' || angka[i - 1] != '0') && digitCount != 0) {
                    result += " " + digitToUnit(digitCount);
                }
            }
        }

        if (i <= 1) {
            space = " ";
        }
        i++;
    }

    return result;
}

string angkaTerbilang(string target, char decimal = '.') {
    size_t decimalPos = target.find(decimal);
    if (decimalPos != string::npos) {
        string beforeDecimal = target.substr(0, decimalPos);
        string afterDecimal = target.substr(decimalPos + 1);
        return terbilang(beforeDecimal) + " koma " + terbilangSatuSatu(afterDecimal);
    } else {
        return terbilang(target);
    }
}

int main() {
    string input;
    cout << "Masukkan angka: ";
    cin >> input;

    cout << "Hasil konversi: " << angkaTerbilang(input) << endl;

    return 0;
}
