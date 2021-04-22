'''
@author Sparsh Sah
@date 2017-10-25

Solves the N-Queens problem for general N.

e.g. for 4-Queens:

  C  0 1 2 3
R__|________
0  | - - Q -
1  | Q - - -
2  | - - - Q
3  | - Q - -

'''

from copy import deepcopy

######################################################################

n = 8

def blankBoard():
    return [[False for col in range(n)] for row in range(n)]

# precondition: dim(board) == NxN
def isValid(board):

    # check rows
    for row in range(n):
        if sum(board[row]) > 1:
            return False

    # check columns
    for col in range(n):
        columnValues = [board[row][col] for row in range(n)]
        if sum(columnValues) > 1:
            return False

    # check lower-left diagonals, skipping the last since it's a single cell
    for row in range(n-1):
        diagonalValues = []

        for j in range(n):
            if not row + j < n:
                break
            diagonalValues.append(board[row + j][j])

        if sum(diagonalValues) > 1:
            return False

    # check upper-right diagonals, skipping the last since it's a single cell and the first since it was checked above
    for col in range(1, n-1):
        diagonalValues = []

        for j in range(n):
            if not col + j < n:
                break
            diagonalValues.append(board[j][col + j])

        if sum(diagonalValues) > 1:
            return False

    # check lower-right diagonals, skipping the last since it's a single cell
    for row in range(n-1):
        diagonalValues = []

        for j in range(n):
            if not row + j < n:
                break
            diagonalValues.append(board[row + j][(n-1)-j])

        if sum(diagonalValues) > 1:
            return False

    # check upper-left diagonals, skipping the first since it's a single cell and the last since it was checked above
    for col in range(1, n-1):
        diagonalValues = []

        for j in range(n):
            if not col - j >= 0:
                break
            diagonalValues.append(board[j][col - j])

        if sum(diagonalValues) > 1:
            return False

    return True

# safe: does not modify original
# precondition: dim(board) = NxN
# precondition: row, col < N
def inject(board, row, col):
    board1 = deepcopy(board)
    board1[row][col] = True
    return board1

def buildSol(board, currentRow, unusedCols):
    if not currentRow < n:
        return board

    for col in list(unusedCols):
        board1 = inject(board, currentRow, col)
        if isValid(board1):
            attempt = buildSol(board1, currentRow + 1, unusedCols - set([col]))
            if not attempt == None:
                return attempt
    # if no cols allowed us to be valid, backtrack
    return None

def genSol():
    return buildSol(blankBoard(), 0, set(range(n)))

# precondition: dim(board) = NxN
def printBoard(board):
    if board == None:
        print('UNSOLVABLE\n')
        return

    representation = ''
    for row in range(n):
        for col in range(n):
            if board[row][col]:
                representation += 'Q '
            else:
                representation += '- '
        representation += '\n'
    print(representation)

######################################################################

printBoard(genSol())
