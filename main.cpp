#pragma once

#include <iostream>
#include <cstdint>
#include <algorithm>
#include <string>

#include "types_and_consts.h"
#include "display.h"
#include "utils.h"
#include "evaluation.h"

void get_userinput(std::string& coordinate, uint64_t &main_bitboard){
    std::cout << "what coordinate?" << "\n";
    getline(std::cin,coordinate);
    coordinate.erase(remove(coordinate.begin(), coordinate.end(), ' '), coordinate.end());
    int row_source, row_destination ,col_source,col_destination;

    row_source = coordinate[0]-'a';   
    col_source = coordinate[1]-'1';

    row_destination = coordinate[2] - 'a';
    col_destination = coordinate[3] - '1';

    
    main_bitboard = clear_bit(main_bitboard, to_index(row_source,col_source,8));
    main_bitboard = set_bit(main_bitboard,to_index(row_destination,col_destination,8));
}

int main () {
    uint64_t test_bitboard = 0; 

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

    std::string coordinate;

    print_bitboard(test_bitboard);
    std::cout << evaluate_bitboard(test_bitboard,pawn,1) << '\n';
    get_userinput(coordinate, test_bitboard);
    print_bitboard(test_bitboard);

    return 0;
}

