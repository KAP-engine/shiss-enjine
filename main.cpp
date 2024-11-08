#include <iostream>
#include <cstdint>
using namespace std;

enum ChessCoordinate {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};


void printBitboard(uint64_t board) {
    cout << "\n";
    for (int rank = 0; rank < 8; rank++) {
        cout << " " << (8 - rank) << " ";  // dispaly rank numbers on the left
        for (int file = 0; file < 8; file++) {
            int square =(rank * 8 + file);  // Convert (rank, file) to bit index
            cout << ((board >> square) & 1) << " ";  
        }
        cout << "\n";
    }
    cout << "\n  a b c d e f g h \n\n\n";  // display file labels
}

uint64_t set_bit(uint64_t board, ChessCoordinate coordinate) {
    return board |= (1ULL << static_cast<int>(coordinate));  // Set the bit at the specific coordinate
}

int main () {
    uint64_t board = 0; 
    long Whitepawns = 0b0001;  
    long Whiteknights = 0b0010;  
    long Whitebishops = 0b0011; 
    long Whitequeen=0b0101;  
    long Whiteking= 0b0110;  

    long Blackpawns = 0b1001;  
    long Blackknights= 0b1010; 
    long Blackbishops= 0b1011;
    long Blackrook= 0b1100; 
    long Blackqueen=0b1101;  
    long Blackking= 0b1110;

    bool whiteturn;
    int castlingright; 
    //setting up pawns on the second rank
    board = set_bit(board,ChessCoordinate::a2);
    board = set_bit(board,ChessCoordinate::b2);
    board = set_bit(board,ChessCoordinate::c2);
    board = set_bit(board,ChessCoordinate::d2);
    board = set_bit(board,ChessCoordinate::e2);
    board = set_bit(board,ChessCoordinate::f2);
    board = set_bit(board,ChessCoordinate::g2);
    board = set_bit(board,ChessCoordinate::h2);
    

    printBitboard(board);

    return 0;
    
}