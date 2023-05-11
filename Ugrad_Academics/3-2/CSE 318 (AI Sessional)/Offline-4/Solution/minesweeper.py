import itertools
import random


class Minesweeper():
    """
    Minesweeper game representation
    """

    def __init__(self, height=8, width=8, mines=8):

        # Set initial width, height, and number of mines
        self.height = height
        self.width = width
        self.mines = set()

        # Initialize an empty field with no mines
        self.board = []
        for i in range(self.height):
            row = []
            for j in range(self.width):
                row.append(False)
            self.board.append(row)

        # Add mines randomly
        while len(self.mines) != mines:
            i = random.randrange(height)
            j = random.randrange(width)
            if not self.board[i][j]:
                self.mines.add((i, j))
                self.board[i][j] = True

        # At first, player has found no mines
        self.mines_found = set()

    def print(self):
        """
        Prints a text-based representation
        of where mines are located.
        """
        for i in range(self.height):
            print("--" * self.width + "-")
            for j in range(self.width):
                if self.board[i][j]:
                    print("|X", end="")
                else:
                    print("| ", end="")
            print("|")
        print("--" * self.width + "-")

    def is_mine(self, cell):
        i, j = cell
        return self.board[i][j]

    def nearby_mines(self, cell):
        """
        Returns the number of mines that are
        within one row and column of a given cell,
        not including the cell itself.
        """

        # Keep count of nearby mines
        count = 0

        # Loop over all cells within one row and column

        """
        for i in range(cell[0] - 1, cell[0] + 2):
            for j in range(cell[1] - 1, cell[1] + 2):

                # Ignore the cell itself
                if (i, j) == cell:
                    continue

                # Update count if cell in bounds and is mine
                if 0 <= i < self.height and 0 <= j < self.width:
                    if self.board[i][j]:
                        count += 1

        return count
        """

        up_neighbour_cell = (cell[0]-1,cell[1])
        down_neighbour_cell = (cell[0]+1,cell[1])
        left_neighbour_cell = (cell[0],cell[1]-1)
        right_neighbour_cell = (cell[0],cell[1]+1)

        Neighbour_cells=[]

        Neighbour_cells.append(up_neighbour_cell)
        Neighbour_cells.append(down_neighbour_cell)
        Neighbour_cells.append(left_neighbour_cell)
        Neighbour_cells.append(right_neighbour_cell)

        for neighbour_cell in Neighbour_cells:
            if 0<= neighbour_cell[0] < self.height and 0 <= neighbour_cell[1] <self.width:
                if self.board[neighbour_cell[0]][neighbour_cell[1]]:
                    count = count + 1

        return count            
        





    def won(self):
        """
        Checks if all mines have been flagged.
        """
        return self.mines_found == self.mines


class Sentence():
    """
    Logical statement about a Minesweeper game
    A sentence consists of a set of board cells,
    and a count of the number of those cells which are mines.
    """

    def __init__(self, cells, count):
        self.cells = set(cells)
        self.count = count

    def __eq__(self, other):
        return self.cells == other.cells and self.count == other.count

    def __str__(self):
        return f"{self.cells} = {self.count}"

    def known_mines(self):

        """
        Returns the set of all cells in self.cells known to be mines.
        """
       # raise NotImplementedError
       #if {A,B,C} = 3 or if {A,B} = 2 or if {A} = 1
        if len(self.cells) == self.count and self.count != 0:
         return self.cells
        else:
         return set()
       

    def known_safes(self):

        """
        Returns the set of all cells in self.cells known to be safe.
        """
        # raise NotImplementedError
        if self.count == 0:
           return self.cells
        else:
           return set()
      
    
    

    def mark_mine(self, cell):


        """
        Updates internal knowledge representation given the fact that
        a cell is known to be a mine.
        """
        #raise NotImplementedError
        #if {A,B,C}=2 and if B has a mine then {A,C} = 1

        if cell in self.cells:
            self.cells.remove(cell)
            self.count = self.count - 1



    def mark_safe(self, cell):
        """
        Updates internal knowledge representation given the fact that
        a cell is known to be safe.
        """
        #raise NotImplementedError
         #if {A,B,C}=2 and if B is a safe cell then {A,C} = 2
        if cell in self.cells:
            self.cells.remove(cell)


class MinesweeperAI():
    """
    Minesweeper game player
    """

    def __init__(self, height=8, width=8):

        # Set initial height and width
        self.height = height
        self.width = width

        # Keep track of which cells have been clicked on
        self.moves_made = set()

        # Keep track of cells known to be safe or mines
        self.mines = set()
        self.safes = set()

        # List of sentences about the game known to be true
        self.knowledge = []

    def mark_mine(self, cell):
        """
        Marks a cell as a mine, and updates all knowledge
        to mark that cell as a mine as well.
        """
        self.mines.add(cell)
        for sentence in self.knowledge:
            sentence.mark_mine(cell)

    def mark_safe(self, cell):
        """
        Marks a cell as safe, and updates all knowledge
        to mark that cell as safe as well.
        """
        self.safes.add(cell)
        for sentence in self.knowledge:
            sentence.mark_safe(cell)


    # Here for managing knowledge base,the used data structures are ==>
    # 1)self.knowledge 
    # 2)self.mines
    # 3)self.safes
    # 4)self.move_mades


    #After each move (move by user or AI) if the move does not have mines then "add_knowledge()" will be called
    def add_knowledge(self, cell, count):
        """
        Called when the Minesweeper board tells us, for a given
        safe cell, how many neighboring cells have mines in them.

        This function should:
            1) mark the cell as a move that has been made
            2) mark the cell as safe
            3) add a new sentence to the AI's knowledge base
               based on the value of `cell` and `count`
            4) mark any additional cells as safe or as mines
               if it can be concluded based on the AI's knowledge base
            5) add any new sentences to the AI's knowledge base
               if they can be inferred from existing knowledge
        """
        #raise NotImplementedError
        #1
        self.moves_made.add(cell)
        #2
        self.mark_safe(cell)
        #3
        up_neighbour_cell = (cell[0]-1,cell[1])
        down_neighbour_cell = (cell[0]+1,cell[1])
        left_neighbour_cell = (cell[0],cell[1]-1)
        right_neighbour_cell = (cell[0],cell[1]+1)

        Neighbour_cells=[]

        Neighbour_cells.append(up_neighbour_cell)
        Neighbour_cells.append(down_neighbour_cell)
        Neighbour_cells.append(left_neighbour_cell)
        Neighbour_cells.append(right_neighbour_cell)

        New_sentence_cells=[]
        mine_count=0;

        #if {A,B,C,D} = 2 and "A" is already marked as a mine and "D" is already marked as safe then "{B,C} = 1" is a new knowledge

        for neighbour_cell in Neighbour_cells:
            if neighbour_cell in self.mines:
                mine_count = mine_count + 1
            #inference happening    
            if 0<= neighbour_cell[0] < self.height and 0 <= neighbour_cell[1] < self.width and neighbour_cell not in self.safes and neighbour_cell not in self.mines:
                New_sentence_cells.append(neighbour_cell)
        
        New_sentence = Sentence(New_sentence_cells,count-mine_count)
        self.knowledge.append(New_sentence)

        print("Move on cell ",cell," has added sentence to knowledge base ",New_sentence)
       


        #after adding a new knowledge(or sentence), each sentence in the knowledge base will be iterated and will try to update each sentence

        #inference happening 
        for sentence in self.knowledge:
            if sentence.known_mines():
                for cell in sentence.known_mines().copy():
                    self.mark_mine(cell)
            if sentence.known_safes():
                for cell in sentence.known_safes().copy():
                    self.mark_safe(cell)  


        #if the new sentence is the subset of an existing sentence
        # for example, if new sentence is {A,B,E}=2 and there is two existing sentence {A,B,D,E,F} = 3 and {A,B,D,E,G} = 3     
        # then two new knowledge will be {D,F} = 1 and  {D,G} = 1

        
        #iterating each sentence to check wether the "new_sentence" is the subset of that sentence

        #inference happening 
        for sentence in self.knowledge:
            if New_sentence.cells.issubset(sentence.cells) and sentence.count > 0 and New_sentence.count > 0 and sentence != New_sentence:
                New_cells = sentence.cells.difference(New_sentence_cells)
                New_count = sentence.count - New_sentence.count
                New_another_sentence = Sentence(list(New_cells),New_count)
                self.knowledge.append(New_another_sentence)
                print("Another sentence added due to subset process: ",New_another_sentence)

        #So overall,akta new sentence knowledge base a add korar por(i.e akta  move deyar por) existing sentence gula k 3 vabe change kora hocche
        # 1) move ti k jokhn "mark safe" kora hocche tokhn shobgulo sentence k update kora hocche
        # 2) protita sentence k iterate kore dekha hocche j sentence ti theke "known safes" ba "known_mines" ber kora jay ki na (i.e shohoj
        # kothay akta sentence dekhe bojha jacche kina kon cell "safe" ba kon cell a "mine" ase)
        # 3) new sentence ti existing kono sentence er subset hole new arekti knowledge add hocche          

        print("Size of knowledge base: ",len(self.knowledge))
        print("Known mines: ",self.mines)
        print("Remaining safe moves: ",self.safes.difference(self.moves_made))      
        print("===========================================================================") 



    def make_safe_move(self):
        """
        Returns a safe cell to choose on the Minesweeper board.
        The move must be known to be safe, and not already a move
        that has been made.

        This function may use the knowledge in self.mines, self.safes
        and self.moves_made, but should not modify any of those values.
        """
        #raise NotImplementedError
        for cell in self.safes:
            if cell not in self.moves_made:
                return cell
        return None        

    def make_random_move(self):
        """
        Returns a move to make on the Minesweeper board.
        Should choose randomly among cells that:
            1) have not already been chosen, and
            2) are not known to be mines
        """
        #raise NotImplementedError

        #listing all the possible valid move first..
        Available_Moves = []

        for i in range(self.height):
            for j in range(self.width):
                temp_cell = (i,j)
                if temp_cell not in self.moves_made and temp_cell not in self.mines:
                    Available_Moves.append(temp_cell)

        #then selecting a valid move randomly

        if len(Available_Moves) > 0:
            Random_cell = random.choice(Available_Moves)
            return Random_cell
        else:
            return None             

