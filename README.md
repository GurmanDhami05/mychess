# ♟️ Chess

A chess game written in **modern C++** using **SDL2**.

This project was built from scratch as a learning exercise in C++, software architecture, and game development. Every chess rule has been implemented manually without using external chess libraries.

---

## Features

### Core Gameplay

- ✅ Complete chess board rendering
- ✅ Piece movement for all six pieces
- ✅ Piece captures
- ✅ Turn-based gameplay

### Chess Rules

- ✅ Check detection
- ✅ Checkmate detection
- ✅ Stalemate detection
- ✅ Castling
- ✅ En passant
- ✅ Automatic pawn promotion (currently promotes to Queen)

The engine now supports a complete legal game of chess.

---

## Project Structure

```
include/
src/
assets/
CMakeLists.txt
```

The project is split into small modules, including:

- Board rendering
- Input handling
- Move validation
- Check detection
- Checkmate/Stalemate
- Castling
- En Passant
- Promotion

---

## Technologies

- C++17
- SDL2
- SDL2_image
- CMake

---

## Building

```bash
git clone https://github.com/<your-username>/Chess.git
cd Chess

cmake -B build
cmake --build build

./build/chess
```

---

## Roadmap

### Gameplay

- [ ] Promotion piece selection
- [ ] Move highlighting
- [ ] Legal move indicators
- [ ] Move history
- [ ] Undo / Redo

### User Interface

- [ ] Main menu
- [ ] Game over screen
- [ ] Restart game
- [ ] Board themes
- [ ] Piece themes

### Chess Features

- [ ] Algebraic notation
- [ ] PGN export/import
- [ ] FEN import/export
- [ ] Draw by repetition
- [ ] Fifty-move rule
- [ ] Insufficient material detection

### AI

- [ ] Minimax
- [ ] Alpha-Beta Pruning
- [ ] Evaluation function
- [ ] Opening book

---

## Learning Goals

This project is part of my journey to improve my understanding of:

- Modern C++
- Object-Oriented Design
- Game Programming
- Software Architecture
- Git & GitHub workflow
- Chess engine development

---

## License

This project is licensed under the MIT License.
