#include "chess/fen.h"
#include "chess/piece.h"

#include <sstream>
#include <stdexcept>

std::string
FEN::exportFEN(const Board &board, Turn turn, const GameState &state)
{
    std::string fen;
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        int emptyCount = 0;
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            int piece = board.pieceAt({ row, col });
            if (piece == Piece::None)
            {
                emptyCount++;
            }
            else
            {
                if (emptyCount > 0)
                {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += pieceToFenChar(piece);
            }
        }
        if (emptyCount > 0)
        {

            fen += std::to_string(emptyCount);
        }
        if (row < 7)
        {
            fen += '/';
        }
    }

    fen += ' ';
    fen += (turn == Turn::White) ? 'w' : 'b';

    fen += ' ';

    std::string castling;

    if (state.castling.whiteCanCastleKingside())
        castling += 'K';

    if (state.castling.whiteCanCastleQueenside())
        castling += 'Q';

    if (state.castling.blackCanCastleKingside())
        castling += 'k';

    if (state.castling.blackCanCastleQueenside())
        castling += 'q';

    fen += castling.empty() ? "-" : castling;

    fen += ' ';
    if (state.enPassantTarget.isValid())
    {
        fen += static_cast<char>('a' + state.enPassantTarget.col);
        fen += static_cast<char>('8' - state.enPassantTarget.row);
    }
    else
    {
        fen += '-';
    }

    fen += ' ';
    fen += std::to_string(state.halfMoveClock);
    fen += ' ';
    fen += std::to_string(state.fullMoveNumber);

    return fen;
}

char pieceToFenChar(int piece)
{
    switch (piece)
    {
    case Piece::WhitePawn:
        return 'P';
    case Piece::WhiteKnight:
        return 'N';
    case Piece::WhiteBishop:
        return 'B';
    case Piece::WhiteRook:
        return 'R';
    case Piece::WhiteQueen:
        return 'Q';
    case Piece::WhiteKing:
        return 'K';
    case Piece::BlackPawn:
        return 'p';
    case Piece::BlackKnight:
        return 'n';
    case Piece::BlackBishop:
        return 'b';
    case Piece::BlackRook:
        return 'r';
    case Piece::BlackQueen:
        return 'q';
    case Piece::BlackKing:
        return 'k';
    default:
        throw std::runtime_error("Invalid piece value");
    }
}

int fenCharToPiece(char c)
{
    switch (c)
    {
    case 'P':
        return Piece::WhitePawn;
    case 'N':
        return Piece::WhiteKnight;
    case 'B':
        return Piece::WhiteBishop;
    case 'R':
        return Piece::WhiteRook;
    case 'Q':
        return Piece::WhiteQueen;
    case 'K':
        return Piece::WhiteKing;
    case 'p':
        return Piece::BlackPawn;
    case 'n':
        return Piece::BlackKnight;
    case 'b':
        return Piece::BlackBishop;
    case 'r':
        return Piece::BlackRook;
    case 'q':
        return Piece::BlackQueen;
    case 'k':
        return Piece::BlackKing;
    default:
        throw std::runtime_error("Invalid FEN character");
    }
}

bool FEN::loadFEN(Board &board,
                  Turn &turn,
                  GameState &state,
                  const std::string &fen)
{

    board.clear();

    std::stringstream ss(fen);

    std::string boardField;
    std::string turnField;
    std::string castlingField;
    std::string enPassantField;
    int halfMoveClock;
    int fullMoveNumber;

    if (!(ss >> boardField >> turnField >> castlingField >> enPassantField >>
          halfMoveClock >> fullMoveNumber))
    {
        return false;
    }

    std::string extra;
    if (ss >> extra)
    {
        return false;
    }

    int row = 0;
    int col = 0;

    for (char c : boardField)
    {

        if (c == '/')
        {
            if (col != BOARD_SIZE)
            {
                return false; // Not enough columns in a row
            }
            row++;
            col = 0;
        }
        else if (c >= '1' && c <= '8')
        {
            col += c - '0';
        }
        else if (isdigit(c))
        {
            return false;
        }
        else
        {
            try
            {
                board.setPiece({ row, col }, fenCharToPiece(c));
            }
            catch (const std::runtime_error &e)
            {
                return false; // Invalid FEN character
            }

            col++;
        }

        if (row > BOARD_SIZE)
        {
            return false; // Too many rows
        }
        if (col > BOARD_SIZE)
        {
            return false; // Too many columns in a row
        }
    }

    if (row != BOARD_SIZE - 1 || col != BOARD_SIZE)
    {
        return false;
    }

    if (turnField == "w")
    {
        turn = Turn::White;
    }
    else if (turnField == "b")
    {
        turn = Turn::Black;
    }
    else
    {
        return false; // Invalid turn field
    }

    state.castling.reset();

    for (char c : castlingField)
    {
        switch (c)
        {
        case 'K':
            state.castling.whiteKingMoved = false;
            state.castling.whiteKingsideRookMoved = false;
            break;
        case 'Q':
            state.castling.whiteKingMoved = false;
            state.castling.whiteQueensideRookMoved = false;
            break;
        case 'k':
            state.castling.blackKingMoved = false;
            state.castling.blackKingsideRookMoved = false;
            break;
        case 'q':
            state.castling.blackKingMoved = false;
            state.castling.blackQueensideRookMoved = false;
            break;
        case '-':
            break; // No castling rights
        default:
            return false; // Invalid castling field
        }
    }

    if (enPassantField == "-")
    {
        state.enPassantTarget = { -1, -1 };
    }
    else if (enPassantField.length() == 2)
    {
        char file = enPassantField[0];
        char rank = enPassantField[1];

        if (file < 'a' || file > 'h' || rank < '1' || rank > '8')
        {
            return false; // Invalid en passant field
        }

        state.enPassantTarget.col = file - 'a';
        state.enPassantTarget.row = 8 - (rank - '0');
    }
    else
    {
        return false; // Invalid en passant field
    }

    state.halfMoveClock = halfMoveClock;
    state.fullMoveNumber = fullMoveNumber;

    return true;
}
