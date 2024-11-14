#include <iostream>
#include <cstdint>
#include <algorithm>
#include <string>
using namespace std;

// @btats i fixed the bitboard representation (the way squares are mapped to the bits of the bitboard) to match this, its better to work with
// basicaly the square a1 is the least significant bit of the bitboard 
// and the square h8 is the most significant bit of the bitboard 
// https://pages.cs.wisc.edu/~psilord/blog/data/chess-pages/rep.html, check the chess board mapping section

// CHESSBOARD_T
typedef struct {
    // white pieces
    uint64_t white_pawns;
    uint64_t white_king;
    uint64_t white_ministers; // "queen"
    uint64_t white_rooks;
    uint64_t white_elephants; // "elephant"
    uint64_t white_knights;
    // black pieces
    uint64_t black_pawns;
    uint64_t black_king;
    uint64_t black_ministers; // "queen"
    uint64_t black_rooks;
    uint64_t black_elephants; // "elephant"
    uint64_t black_knights;
} chessboard_t;

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

enum Piece {
    pawn, knight, elephant, rook, queen, king
};

const int piece_value[12][64] {
    {//pawn value map
    0,  0,  0,  0,  0,  0,  0,  0,
    5, 10, 10,-20,-20, 10, 10,  5,
    5, -5,-10,  0,  0,-10, -5,  5,
    0,  0,  0, 20, 20,  0,  0,  0,
    5,  5, 10, 25, 25, 10,  5,  5,
    10, 10, 20, 30, 30, 20, 10, 10,
    50, 50, 50, 50, 50, 50, 50, 50,
    0,  0,  0,  0,  0,  0,  0,  0
    },

    {//knight value map
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50
    },

    {//elephant value map
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10,-10,-10,-10,-10,-20
    },

    {//rook value map
    0,  0,  0,  5,  5,  0,  0,  0,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    5, 10, 10, 10, 10, 10, 10,  5,
    0,  0,  0,  0,  0,  0,  0,  0
    },

    {//queen value map
    -20,-10,-10, -5, -5,-10,-10,-20,
    -10,  0,  5,  0,  0,  0,  0,-10,
    -10,  5,  5,  5,  5,  5,  0,-10,
    0,  0,  5,  5,  5,  5,  0, -5,
    -5,  0,  5,  5,  5,  5,  0, -5,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20
    },

    {//king value map
    20, 30, 10,  0,  0, 10, 30, 20,
    20, 20,  0,  0,  0,  0, 20, 20,
    -10,-20,-20,-20,-20,-20,-20,-10,
    -20,-30,-30,-40,-40,-30,-30,-20,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30
    },

    // ABOVE IS WHITE, BELOW IS BLACK

    {//pawn value map
    0,  0,  0,  0,  0,  0,  0,  0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
    5,  5, 10, 25, 25, 10,  5,  5,
    0,  0,  0, 20, 20,  0,  0,  0,
    5, -5,-10,  0,  0,-10, -5,  5,
    5, 10, 10,-20,-20, 10, 10,  5,
    0,  0,  0,  0,  0,  0,  0,  0
    },

    {//knight value map
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50
    },

    {//elephant
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -20,-10,-10,-10,-10,-10,-10,-20,
    },

    {//rook
    0,  0,  0,  0,  0,  0,  0,  0,
    5, 10, 10, 10, 10, 10, 10,  5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    0,  0,  0,  5,  5,  0,  0,  0
    },

    {//queen
    -20,-10,-10, -5, -5,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -5,  0,  5,  5,  5,  5,  0, -5,
    0,  0,  5,  5,  5,  5,  0, -5,
    -10,  5,  5,  5,  5,  5,  0,-10,
    -10,  0,  5,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20
    },

    { //king 
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -20,-30,-30,-40,-40,-30,-30,-20,
    -10,-20,-20,-20,-20,-20,-20,-10,
    20, 20,  0,  0,  0,  0, 20, 20,
    20, 30, 10,  0,  0, 10, 30, 20
    }
    
};


chessboard_t new_chessboard(); 
void print_bin(uint64_t); // utility function to print bitboard in binary
void print_bitboard(uint64_t board);
uint64_t set_bit(uint64_t board, ChessCoordinate coordinate); 
uint64_t clear_bit(uint64_t board, ChessCoordinate coordinate); 

int to_1D(int x,int y, int width) {
    //convert 2D coordinates to 1D coordinate
    return x + y * width;

}


int evaluate_piece(uint64_t board, Piece piece,int color) {
    int result = 0;
    for (int i = 0;i<64;i++) {
        if ((1ULL << i ) & board) {
            result += piece_value[static_cast<int>(piece)+color*6][i];
        }
    }

    return result;
}

int evaluate_board(chessboard_t chessboard) {
    int whiteAdvantage = 0;
    int blackAdvantage = 0;

    whiteAdvantage =
    evaluate_piece(chessboard.white_pawns,pawn,0) +
    evaluate_piece(chessboard.white_knights,knight,0) +
    evaluate_piece(chessboard.white_elephants,elephant,0) +
    evaluate_piece(chessboard.white_rooks,rook,0);
    evaluate_piece(chessboard.white_ministers,queen,0) +
    evaluate_piece(chessboard.white_king,king,0); 

    blackAdvantage =
    evaluate_piece(chessboard.black_pawns, pawn, 0) +
    evaluate_piece(chessboard.black_knights, knight, 0) +
    evaluate_piece(chessboard.black_elephants, elephant, 0) +
    evaluate_piece(chessboard.black_rooks, rook, 0) +
    evaluate_piece(chessboard.black_ministers, queen, 0) +
    evaluate_piece(chessboard.black_king, king, 0);

    return whiteAdvantage-blackAdvantage;
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

    // NOTE TO THE BOYS, WE'LL WORK ON THIS LATER, SINCE WE HAVE TO UPDATE IT WITH EACH MOVE, IM GONNA FIND A WAY TO MAKE IT EASIER
    //special bitboards:
    // uint64_t AllWhitePieces = Whitepawns | Whiterooks | Whiteknights | Whiteelephants | Whitequeen | Whiteking;
    // uint64_t ALLBlackPieces =  Blackpawns | Blackrooks | Blackknights | Blackelephants | Blackqueen | Blackking;
    // uint64_t ALLPieces = AllWhitePieces | ALLBlackPieces;

    string coordinate;

    print_bitboard(test_bitboard);
    cout << evaluate_piece(test_bitboard,pawn,1) << '\n';
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

chessboard_t new_chessboard() {
    return (chessboard_t) {
        .white_pawns = 0x000000000000FF00,
        .white_king = 0x0000000000000010,
        .white_ministers = 0x8, 
        .white_rooks = 0x0000000000000081,
        .white_elephants = 0x0000000000000024, 
        .white_knights = 0x0000000000000042,
        .black_pawns = 0x00FF000000000000,
        .black_king = 0x1000000000000000,
        .black_ministers = 0x800000000000000, 
        .black_rooks = 0x8100000000000000,
        .black_elephants = 0x2400000000000000, 
        .black_knights = 0x4200000000000000,
    };
} 
