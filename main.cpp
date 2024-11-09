#include <iostream>
#include <cstdint>

using namespace std;

// @btats i fixed the bitboard representation (the way squares are mapped to the bits of the bitboard) to match this, its better to work with
// basicaly the square a1 is the least significant bit of the bitboard 
// and the square h8 is the most significant bit of the bitboard 
// https://pages.cs.wisc.edu/~psilord/blog/data/chess-pages/rep.html, check the chess board mapping section

enum ChessCoordinate {
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8,
};

void print_bin(uint64_t); // utility function to print bitboard in binary
void print_bitboard(uint64_t board);
uint64_t set_bit(uint64_t board, ChessCoordinate coordinate); 

int to_1D(int x,int y, int width) {
    //convert 2D coordinates to 1D coordinate
    return x + y * width;

}


void get_userinput(string& coordinate, uint64_t &main_bitboard){
    cout << "what coordinate?" << "\n";
    cin >> coordinate;

    main_bitboard = set_bit(main_bitboard,static_cast<ChessCoordinate>( to_1D(coordinate[0]-'a', coordinate[1]-'1',8) ));
}

int main () {
    uint64_t test_bitboard = 0; 

    // TOO ADVANCED FOR NOW
    // bool whiteturn;
    // int castlingright; 

    // testing
    // test_bitboard = set_bit(test_bitboard, a2);
    // test_bitboard = set_bit(test_bitboard, b2);
    // test_bitboard = set_bit(test_bitboard, c2);
    // test_bitboard = set_bit(test_bitboard, d2);
    // test_bitboard = set_bit(test_bitboard, e2);
    // test_bitboard = set_bit(test_bitboard, f2);
    // test_bitboard = set_bit(test_bitboard, g2);
    // test_bitboard = set_bit(test_bitboard, h2);
    string coordinate;
    get_userinput(coordinate,test_bitboard);

    print_bin(test_bitboard);
 
    print_bitboard(test_bitboard);

    return 0;
}

void print_bin(uint64_t n) {
    if (n > 1)
        print_bin(n >> 1);

    printf("%llu", n & 1);
}

uint64_t set_bit(uint64_t board, ChessCoordinate coordinate) {
    return board |= (1ULL << static_cast<int>(coordinate));
}

void print_bitboard(uint64_t board) {
    cout << "\n";

    for (int rank = 7; rank >= 0; rank--) {
        cout << " " << rank+1 << "  ";

        for (int file = 0; file < 8; file++) {
            int square = (rank * 8 + file);
            cout << ((board >> square) & 1) << " ";  
        }

        cout << "\n";
    }
    
    cout << "\n    a b c d e f g h \n\n\n";
}
