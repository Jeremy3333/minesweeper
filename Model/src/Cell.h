//
// Created by jerem on 14/12/2023.
//

#ifndef CELL_H
#define CELL_H



class Cell {
public:
    /**
     * \brief Create a Cell object
     */
    Cell();

    /**
     * \brief set the curent cell index which is if ther is a bomb or how many bomb is there around
     * \param p_index -1 if it's a bomb and -2 if the bomb is touched the number of bomb around otherwise
     */
    void setIndex(int p_index);
    bool revele();
    void reveleMine();
    void mark();
    void changeMark();
    void reset();
    [[nodiscard]] bool isReveled() const;
    [[nodiscard]] bool isMarked() const;
    [[nodiscard]] int getIndex() const;
    [[nodiscard]] bool isBomb() const;
private:
    bool reveled_;
    bool marked_;
    int index_;
};



#endif //CELL_H
