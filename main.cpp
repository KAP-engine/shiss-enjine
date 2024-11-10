#include <iostream>
#include <cstdint>
#include <algorithm>
#include <string>
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
enum Ranks {
    rank_1 = 0x00000000000000FF, 
    rank_2 = 0x000000000000FF00,
    rank_3 = 0x0000000000FF0000, 
    rank_4 = 0x00000000FF000000, 
    rank_5 = 0x000000FF00000000, 
    rank_6 = 0x0000FF0000000000, 
    rank_7 = 0x00FF000000000000, 
    rank_8 = 0xFF00000000000000  
};
enum Files {
    file_a = 0x0101010101010101,
    file_b = 0x0202020202020202,
    file_c = 0x0404040404040404,
    file_d = 0x0808080808080808,
    file_e = 0x1010101010101010,
    file_f = 0x2020202020202020,
    file_g = 0x4040404040404040,
    file_h = 0x8080808080808080
};
void print_bin(uint64_t); // utility function to print bitboard in binary
void print_bitboard(uint64_t board);
uint64_t set_bit(uint64_t board, ChessCoordinate coordinate); 
uint64_t clear_bit(uint64_t board, ChessCoordinate coordinate); 

int to_1D(int x,int y, int width) {
    //convert 2D coordinates to 1D coordinate
    return x + y * width;

}


void get_userinput(string& coordinate, uint64_t &main_bitboard){
    cout << "what coordinate?" << "\n";
    getline(cin,coordinate);
    coordinate.erase(remove(coordinate.begin(), coordinate.end(), ' '), coordinate.end());
    int row_source, row_destination ,col_source,col_destination;

    row_source = coordinate[0]-'a';   
    col_source = coordinate[1]-'1';

    row_destination = coordinate[2] - 'a';
    col_destination = coordinate[3] - '1';

    
    main_bitboard = clear_bit(main_bitboard,static_cast<ChessCoordinate>(to_1D(row_source,col_source,8)));
    main_bitboard = set_bit(main_bitboard,static_cast<ChessCoordinate>(to_1D(row_destination,col_destination,8)));
   

}
uint64_t maskrank(Ranks rank){ 
    // utility function that tells us which piece x is in rank y
    //for testing copy the following code:
    //test_bitboard = set_bit(test_bitboard, c2);
    //test_bitboard = set_bit(test_bitboard, f2);
    //test_bitboard = set_bit(test_bitboard, g3);
    //test_bitboard = set_bit(test_bitboard, h4);
    //test_bitboard = set_bit(test_bitboard, d4);
    //uint64_t WhitePawnsRank4 = test_bitboard & maskrank(rank_4);
    //print_bitboard(WhitePawnsRank4);
   
    return rank;
}
uint64_t maskfile(Files file){ // just like the mask rank function but for files instead of ranks
    return file;
}


int main () {
    uint64_t test_bitboard = 0; 

    // TOO ADVANCED FOR NOW
    // bool whiteturn;
    // int castlingright; 

    // testing
     test_bitboard = set_bit(test_bitboard, a2);
     test_bitboard = set_bit(test_bitboard, b2);
     test_bitboard = set_bit(test_bitboard, c2);
     test_bitboard = set_bit(test_bitboard, d2);
     test_bitboard = set_bit(test_bitboard, e2);
     test_bitboard = set_bit(test_bitboard, f2);
     test_bitboard = set_bit(test_bitboard, g2);
     test_bitboard = set_bit(test_bitboard, h2);

    //bitboards for pieces:
    // Black pieces 
    uint64_t Blackpawns = 0x00FF000000000000;  
    uint64_t Blackknights = 0x4200000000000000;
    uint64_t Blackbishops = 0x2400000000000000;  
    uint64_t Blackrooks = 0x8100000000000000;
    uint64_t Blackqueen = 0x800000000000000;   
    uint64_t Blackking = 0x1000000000000000;

    // White pieces 
    uint64_t Whitepawns =  0x000000000000FF00;    
    uint64_t Whiteknights = 0x0000000000000042;  
    uint64_t Whitebishops = 0x0000000000000024;   
    uint64_t Whiterooks = 0x0000000000000081;  
    uint64_t Whitequeen = 0x8;  
    uint64_t Whiteking = 0x0000000000000010;  
    //special bitboards:
    uint64_t AllWhitePieces = Whitepawns | Whiterooks | Whiteknights | Whitebishops | Whitequeen | Whiteking;
    uint64_t ALLBlackPieces =  Blackpawns | Blackrooks | Blackknights | Blackbishops | Blackqueen | Blackking;;
    uint64_t ALLPieces = AllWhitePieces | ALLBlackPieces;
    string coordinate;

    print_bitboard(test_bitboard);
    get_userinput(coordinate, test_bitboard);
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
uint64_t clear_bit(uint64_t board, ChessCoordinate coordinate) {
    return board & ~(1ULL << static_cast<int>(coordinate));
}

void print_bitboard(uint64_t board) {
    cout << "\n";

    for (int rank = 7; rank >= 0; rank--) {
        cout << " " << rank + 1 << "  ";

        for (int file = 0; file < 8; file++) {
            int square = (rank * 8 + file);
            cout << ((board >> square) & 1) << " ";  
        }

        cout << "\n";
    }
    
    cout << "\n    a b c d e f g h \n\n\n";
}
